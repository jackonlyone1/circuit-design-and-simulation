/////////////////////////////////////////////////////////////////////////////
// EditTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EditTreeCtrl.h"
#include "MultisimDemo.h"
#include "ExtTabModel.h"
#include "TableBar.h"
#include "ExtTabModelManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(4:4503)		// decorated name length exceeded

/////////////////////////////////////////////////////////////////////////////
// CMyRenameDlg dialog

CMyRenameDlg::CMyRenameDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMyRenameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyRenameDlg)
	m_strCaption = _T("");
	//}}AFX_DATA_INIT
}


void CMyRenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyRenameDlg)
	DDX_Text(pDX, IDC_FO_RENAME_EDIT, m_strCaption);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyRenameDlg, CDialog)
//{{AFX_MSG_MAP(CMyRenameDlg)
ON_EN_CHANGE(IDC_FO_RENAME_EDIT, OnChangeEdit1)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRenameDlg message handlers

BOOL CMyRenameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(_T("Please enter a new state text."));
	GetDlgItem(IDC_FO_RENAME_EDIT)->SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMyRenameDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO: Add your control notification handler code here
	
}


enum ECmdHandler 
{
	ID_RENAME = 1,
	ID_DELETE,
	ID_ADD_SCREEN,
	ID_ADD_SCRIPT,
	ID_SORT_LEVEL,
	ID_SORT_LEVELANDBELOW,
	ID_EXP_FOLDER,
	ID_EXP_REFRESH,
	ID_APP_PUBLISHER,
	ID_MAX_CMD
};

enum ERightDragHandler
{
	ID_DRAG_COPY = 15,
	ID_DRAG_MOVE,
	ID_DRAG_CANCEL,

	ID_MAX_DRH
};

// --------------------------------------------------------------------------
// CEditTreeCtrl

CEditTreeCtrl::CEditTreeCtrl()
	: m_pDragData(0)
{
	// m_Keymap[key][ctrl-modifier][shift-modifier] = method;
}


CEditTreeCtrl::~CEditTreeCtrl()
{
}


bool CEditTreeCtrl::CanEditLabel(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::CanEditLabel('%s')\n"), LPCTSTR(GetItemText(hItem)));
	return true;
}


bool CEditTreeCtrl::CanSetLabelText(TVITEM & item) 
{
	TRACE1(_T("CEditTreeCtrl::CanSetLabelText('%s')\n"), item.pszText);
	return true;
}


bool CEditTreeCtrl::CanDeleteItem(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::CanDeleteItem('%s')\n"), LPCTSTR(GetItemText(hItem)));
	return true;
}


bool CEditTreeCtrl::CanInsertItem(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::CanInsertItem('%s')\n"), (hItem && hItem != TVI_ROOT) ? LPCTSTR(GetItemText(hItem)) : _T("<Root>"));
	return true;
}


bool CEditTreeCtrl::CanSortLevel(HTREEITEM hItem)
{
	TRACE1(_T("CEditTreeCtrl::CanSortLevel('%s')\n"), (hItem && hItem != TVI_ROOT) ? LPCTSTR(GetItemText(hItem)) : _T("<Root>"));
	return true;
}


// --------------------------------------------------------------------------
// Keyboard handling

bool CEditTreeCtrl::HandleKeyDown(WPARAM wParam, LPARAM lParam)
{
	bool bCtrl = (::GetKeyState(VK_CONTROL) & 0x8000) != 0;
	bool bShift = (::GetKeyState(VK_SHIFT) & 0x8000) != 0;
	HTREEITEM hCur = GetSelectedItem();

	
	// under some circumstances we need to check some more keys
	switch(int(wParam)) 
	{
		case VK_ESCAPE:
			if(m_pDragData)
			{
				DragStop();
				return true;
			}
			/*FALLTHRU*/

		case VK_RETURN:
			if(GetEditControl() != 0) 
			{
				GetEditControl()->SendMessage(WM_KEYDOWN, wParam, lParam);
				return true;
			}
			break;

		default:
			break;
	}

	return false;
}


bool CEditTreeCtrl::DoEditLabel(HTREEITEM hItem) 
{
	return hItem ? (EditLabel(hItem) != 0) : false;
}

bool CEditTreeCtrl::DoInsertSibling(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::OnInsertChild('%s')\n"), LPCTSTR(GetItemText(hItem)));
	TVINSERTSTRUCT ins;
	CString strPath1 = theApp.m_strPath +_T("ScriptFiles");
	if(theApp.DirectoryExists(strPath1))
	{
fopDoStart0311:
	CMyRenameDlg dlg;
	dlg.m_strCaption = _T("New Script");
	//		dlg.GetDlgItem(IDC_FO_RENAME_EDIT)->SetFocus();
	if(dlg.DoModal() == IDOK)
	{
		CString strFile = dlg.m_strCaption;
		CString strExt = strFile.Right(3);
		CString strCaption = strFile;
		CString strSave = strCaption;
		strExt.MakeLower();
		if(strExt != _T("scp"))
		{
			strFile += _T(".scp");
			strSave += _T(".scp");
		}
		else
		{
			strCaption = strCaption.Left(strCaption.GetLength() -4);
		}
		
		strFile = strPath1 + _T("\\")+ strFile;
		if(theApp.XFileExists(strFile))
		{
			goto fopDoStart0311;
		}
		
		memset(&ins, 0, sizeof(ins));
		ins.item.mask = TVIF_TEXT|TVIF_STATE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
		ins.item.lParam=(LPARAM)NULL;
		ins.item.cChildren=0;
		ins.item.pszText = (LPTSTR) (LPCTSTR)strCaption;
		ins.hParent = hItem;
		ins.hInsertAfter = TVI_LAST;
		ins.item.state=TVIS_EXPANDED|TVIS_EXPANDEDONCE;
		ins.item.stateMask=ins.item.state;
		ins.item.iImage=3;
		ins.item.iSelectedImage=3;
		CString strFileName;
		strFileName = strFile;// File name
		
		CStdioFile fileWriteUnicode;
		
		if (fileWriteUnicode.Open(strFileName, 
			CFile::modeCreate | CFile::modeWrite))
		{
			fileWriteUnicode.WriteString(_T("Please enter your description text here!"));
			fileWriteUnicode.Close();
			}
		theApp.m_pObj->SetModified(TRUE);
		return NewItem2(ins);
	}
	}
	
	return false;

}


bool CEditTreeCtrl::DoInsertChild(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::OnInsertChild('%s')\n"), LPCTSTR(GetItemText(hItem)));
	TVINSERTSTRUCT ins;
	CString strPath1 = theApp.m_strPath +_T("Ms0Files");
	if(theApp.DirectoryExists(strPath1))
	{
fopDoStart0311:
	CMyRenameDlg dlg;
	dlg.m_strCaption = _T("New Screen");
	//		dlg.GetDlgItem(IDC_FO_RENAME_EDIT)->SetFocus();
	if(dlg.DoModal() == IDOK)
	{
		CString strFile = dlg.m_strCaption;
		CString strExt = strFile.Right(3);
		CString strCaption = strFile;
		CString strSave = strCaption;
		strExt.MakeLower();
		if(strExt != _T("ms0"))
		{
			strFile += _T(".Ms0");
			strSave += _T(".Ms0");
		}
		else
		{
			strCaption = strCaption.Left(strCaption.GetLength() -4);
		}
		
		strFile = strPath1 + _T("\\")+ strFile;
		if(theApp.XFileExists(strFile))
		{
			goto fopDoStart0311;
		}
		
		memset(&ins, 0, sizeof(ins));
		ins.item.mask = TVIF_TEXT|TVIF_STATE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
		ins.item.lParam=(LPARAM)NULL;
		ins.item.cChildren=0;
		ins.item.pszText = (LPTSTR) (LPCTSTR)strCaption;
		ins.hParent = hItem;
		ins.hInsertAfter = TVI_LAST;
		ins.item.state=TVIS_EXPANDED|TVIS_EXPANDEDONCE;
		ins.item.stateMask=ins.item.state;
		ins.item.iImage=2;
		ins.item.iSelectedImage=2;

		CExtTabModelManager m_model;
		m_model.InsertTab();
		m_model.SaveDocument(strFile);
				
		theApp.m_pObj->SetModified(TRUE);
		return NewItem(ins);
	}
	}

	return false;
}

bool CEditTreeCtrl::DoDeleteItem(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::OnDeleteItem('%s')\n"), LPCTSTR(GetItemText(hItem)));
	{
		CString strPath1 = theApp.m_strPath +_T("Ms0Files");
		if(theApp.DirectoryExists(strPath1))
		{
			CString strFile = LPCTSTR(GetItemText(hItem));
			if(!strFile.IsEmpty())
			{
				strFile = strPath1 + _T("\\")+ strFile + _T(".Ms0");
				if(theApp.XFileExists(strFile))
				{
					CString strMsg = strFile;
					strMsg += _T("\nDo you really need to delete this file from disk? \n Warning: The deleted file cann't be recovered. It is deleted from disk. ");
					if(AfxMessageBox(strMsg, MB_YESNO|MB_ICONINFORMATION ) == IDYES)
					{
						CFile::Remove((const TCHAR *) strFile);
						theApp.m_pObj->SetModified(TRUE);
						return hItem ? (CanDeleteItem(hItem) && DeleteItem(hItem)) : false;
					}
				}
			}
		}
	}
	
	return false;
}


bool CEditTreeCtrl::DoDeleteScpItem(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::OnDeleteItem('%s')\n"), LPCTSTR(GetItemText(hItem)));
	{
		CString strPath1 = theApp.m_strPath +_T("ScriptFiles");
		if(theApp.DirectoryExists(strPath1))
		{
			CString strFile = LPCTSTR(GetItemText(hItem));
			if(!strFile.IsEmpty())
			{
				strFile = strPath1 + _T("\\")+ strFile + _T(".scp");
				if(theApp.XFileExists(strFile))
				{
					CString strMsg = strFile;
					strMsg += _T("\nDo you really need to delete this file from disk? \n Warning: The deleted file cann't be recovered. It is deleted from disk. ");
					if(AfxMessageBox(strMsg, MB_YESNO|MB_ICONINFORMATION ) == IDYES)
					{
						CFile::Remove((const TCHAR *) strFile);
						theApp.m_pObj->SetModified(TRUE);
						return hItem ? (CanDeleteItem(hItem) && DeleteItem(hItem)) : false;
					}
				}
			}
		}
	}
	
	return false;
}

bool CEditTreeCtrl::DoSortCurrentLevel(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::OnSortCurrentLevel('%s')\n"), LPCTSTR(GetItemText(hItem)));
	SortCurrentLevel(hItem);
	return true;
}


bool CEditTreeCtrl::DoSortCurrentLevelAndBelow(HTREEITEM hItem) 
{
	TRACE1(_T("CEditTreeCtrl::OnSortCurrentLevelAndBelow('%s')\n"), LPCTSTR(GetItemText(hItem)));
	SortCurrentLevelAndBelow(hItem);
	return true;
}


bool CEditTreeCtrl::NewItem(TVINSERTSTRUCT & ins) 
{
	TRACE1(_T("CEditTreeCtrl::NewItem('%s')\n"), ins.item.pszText ? ins.item.pszText : _T("NULL"));

	if(!CanInsertItem(ins.hParent))
		return false;

	HTREEITEM hItem = InsertItem(&ins);
	SetItemData(hItem, 2001);
	if(hItem) 
	{
		SelectItem(hItem);
		OnNewItem(hItem);
		EditLabel(hItem);
	}
	return hItem != 0;
}

bool CEditTreeCtrl::NewItem2(TVINSERTSTRUCT & ins) 
{
	TRACE1(_T("CEditTreeCtrl::NewItem('%s')\n"), ins.item.pszText ? ins.item.pszText : _T("NULL"));
	
	if(!CanInsertItem(ins.hParent))
		return false;
	
	HTREEITEM hItem = InsertItem(&ins);
	SetItemData(hItem, 2002);
	if(hItem) 
	{
		SelectItem(hItem);
		OnNewItem(hItem);
		EditLabel(hItem);
	}
	return hItem != 0;
}


void CEditTreeCtrl::OnNewItem(HTREEITEM) 
{
}


// --------------------------------------------------------------------------
// Dragging

CDragData * CEditTreeCtrl::CreateDragData(HTREEITEM hDragItem, bool bRightDrag) 
{
	return new CDragData(*this, hDragItem, bRightDrag);
}


CEditTreeCtrl::EDropHint CEditTreeCtrl::GetDropHint(UINT flags) 
{
	EDropHint hint = DROP_NODROP;

	if((flags & TVHT_ONITEMRIGHT))
		hint = DROP_CHILD;

	else if(flags & TVHT_ONITEM) {
		// check whether we should drop below or above
		// the item
		CRect rc;
		if(GetItemRect(GetDropHilightItem(), rc, false)) {
			CPoint pt;
			::GetCursorPos(&pt);
			ScreenToClient(&pt);
			if((pt.y - rc.top) > (rc.bottom - pt.y))
				hint = DROP_BELOW;
			else
				hint = DROP_ABOVE;
		} else
			hint = DROP_ABOVE;

	} else if((flags & TVHT_NOWHERE))
		// below the last item
		hint = DROP_BELOW;

	ASSERT(m_pDragData != 0);
	m_pDragData->SetDropHint(hint);

	return hint;
}


HTREEITEM CEditTreeCtrl::GetDropTarget(EDropHint & hint) 
{
	ASSERT(m_pDragData != 0);

	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	UINT flags;
	HTREEITEM hDrop = HitTest(pt, &flags);
	hint = GetDropHint(flags);
	m_pDragData->SetDropTarget(hDrop);
	if(hDrop) {
		m_pDragData->DragLeave();	// allow updates

		SelectDropTarget(hDrop);

		if(m_pDragData->CheckExpand(hDrop))
			Expand(hDrop, TVE_EXPAND);

		// Make sure the surrounding items are visible, too
		// This will scroll the tree if necessary.
		HTREEITEM hPrev = GetPrevVisibleItem(hDrop);
		if(hPrev)
			EnsureVisible(hPrev);
		HTREEITEM hNext = GetNextVisibleItem(hDrop);
		if(hNext)
			EnsureVisible(hNext);

		// if the drop target is a descendent of the dragged item, then
		// disallow dropping the item here...
		if(IsAncestor(m_pDragData->GetDragItem(), hDrop) || !CanDropItem(m_pDragData->GetDragItem(), hDrop, hint))
			hint = DROP_NODROP;

		m_pDragData->DragEnter(pt);
	} else if(hint != DROP_NODROP && !CanDropItem(m_pDragData->GetDragItem(), hDrop, hint))
		hint = DROP_NODROP;

	return hDrop;
}


bool CEditTreeCtrl::CanDragItem(TVITEM & item) 
{
	TRACE1(_T("CEditTreeCtrl::CanDragItem('%s')\n"), item.pszText);
	return true;
}


bool CEditTreeCtrl::CanDropItem(HTREEITEM hDrag, HTREEITEM hDrop, EDropHint) 
{
	TRACE2(_T("CEditTreeCtrl::CanDropItem('%s', '%s')\n"), LPCTSTR(GetItemText(hDrag)), LPCTSTR(GetItemText(hDrop)));
	return true;
}


void CEditTreeCtrl::DragStart() 
{
	ASSERT(m_pDragData != 0);
	TRACE1(_T("CEditTreeCtrl::DragStart('%s')\n"), LPCTSTR(GetItemText(m_pDragData->GetDragItem())));

	m_pDragData->StartDrag();
	SelectItem(m_pDragData->GetDragItem());
}


void CEditTreeCtrl::DragMove() 
{
	ASSERT(m_pDragData != 0);
	TRACE1(_T("CEditTreeCtrl::DragMove('%s')\n"), LPCTSTR(GetItemText(m_pDragData->GetDragItem())));

	EDropHint eHint;
	HTREEITEM hDrop = GetDropTarget(eHint);
	SetDragCursor(hDrop, eHint);
}


void CEditTreeCtrl::DragEnd() 
{
	ASSERT(m_pDragData != 0);
	TRACE1(_T("CEditTreeCtrl::DragEnd('%s')\n"), LPCTSTR(GetItemText(m_pDragData->GetDragItem())));

	EDropHint eHint;
	HTREEITEM hDrop = GetDropTarget(eHint);

	if(m_pDragData->IsRightDragging())
	{
		if(eHint == DROP_NODROP)
			DragStop();
		else 
		{
			CPoint point;
			GetCursorPos(&point);
			DragDisplayContextMenu(point);
		}
	} else {
		bool bCtrl = (::GetKeyState(VK_CONTROL) & 0x8000) != 0;
		DragMoveItem(m_pDragData->GetDragItem(), hDrop, eHint, bCtrl);
		DragStop();
	}
}


void CEditTreeCtrl::DragStop() 
{
	TRACE0(_T("CEditTreeCtrl::DragStop()\n"));

	// reset dragging variables...
	ASSERT(m_pDragData != 0);
	m_pDragData->EndDrag();
	delete m_pDragData;
	m_pDragData = 0;
}


void CEditTreeCtrl::SetDragCursor(HTREEITEM hDropTarget, EDropHint eHint) 
{

	bool bCtrl = (::GetKeyState(VK_CONTROL) & 0x8000) != 0;

}


void CEditTreeCtrl::DragDisplayContextMenu(CPoint & point) 
{
	CMenu menu;
	VERIFY(menu.CreatePopupMenu());
	VERIFY(menu.AppendMenu(MF_STRING, ID_DRAG_COPY, _T("&Add New Screen")));
	VERIFY(menu.AppendMenu(MF_STRING, ID_DRAG_MOVE, _T("Add New &Script")));
	VERIFY(menu.AppendMenu(MF_SEPARATOR));
	VERIFY(menu.AppendMenu(MF_STRING, ID_DRAG_CANCEL, _T("Open")));

	bool bCtrl = (::GetKeyState(VK_CONTROL) & 0x8000) != 0;
	menu.SetDefaultItem(bCtrl ? ID_DRAG_COPY : ID_DRAG_MOVE);

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}


void CEditTreeCtrl::DragMoveItem(HTREEITEM hDrag, HTREEITEM hDrop, EDropHint eHint, bool bCopy)
{
	if(eHint == DROP_NODROP)
		return;

	if(IsAncestor(hDrag, hDrop) || !CanDropItem(hDrag, hDrop, eHint))
		return;

	ASSERT(hDrag != 0);
	ASSERT(hDrop != 0 || eHint == DROP_BELOW);

	if(!hDrop && eHint == DROP_BELOW)
		for(hDrop = GetRootItem(); GetNextSiblingItem(hDrop) != 0; hDrop = GetNextSiblingItem(hDrop));

	// Setup insertion parameters
	HTREEITEM hInsertAfter = 0;
	HTREEITEM hParent = 0;
	switch(eHint) {
		case DROP_BELOW:
			hInsertAfter = hDrop;
			hParent = GetParentItem(hDrop);
			break;

		case DROP_ABOVE:
			hInsertAfter = GetPrevSiblingItem(hDrop);
			if(!hInsertAfter)
				hInsertAfter = TVI_FIRST;
			hParent = GetParentItem(hDrop);
			break;

		case DROP_CHILD:
			hInsertAfter = TVI_LAST;
			hParent = hDrop;
			break;

		default:
			ASSERT(false);
			break;
	}

	HTREEITEM hNew = CopyItem(hDrag, hParent, hInsertAfter);
	SelectItem(hNew);

	// If the control-key ist down, we copy the data, otherwise we move
	// it, thus we have to delete the dragged item.
	if(!bCopy)
		DeleteItem(hDrag);
}


HTREEITEM CEditTreeCtrl::CopyItem(HTREEITEM hOrig, HTREEITEM hParent, HTREEITEM hInsertAfter) 
{
	// Get item information
	TVITEMEX item;
	memset(&item, 0, sizeof(item));
	item.mask = TVIF_HANDLE|TVIF_IMAGE|TVIF_PARAM|TVIF_SELECTEDIMAGE|TVIF_STATE|TVIF_INTEGRAL ;
	item.stateMask = TVIS_OVERLAYMASK|TVIS_STATEIMAGEMASK;
	item.hItem = hOrig;
	VERIFY(GetItem((TVITEM*)&item));
	CString strText = GetItemText(hOrig);

	// Insert new item and copy data
	HTREEITEM hNew = InsertItem(strText, hParent, hInsertAfter);
	ASSERT(hNew != 0);
	item.hItem = hNew;
	VERIFY(SetItem((TVITEM*)&item));

	// copy entire subtree, too
	if(ItemHasChildren(hOrig))
		for(HTREEITEM hChild = GetChildItem(hOrig); hChild != 0; hChild = GetNextSiblingItem(hChild))
			CopyItem(hChild, hNew, TVI_LAST);

	return hNew;
}

// --------------------------------------------------------------------------
// misc

void CEditTreeCtrl::DisplayContextMenu(CPoint & point) 
{
	if(theApp.strProjectName.IsEmpty())
	{
		return;
	}

	CPoint pt(point);
	ScreenToClient(&pt);
	UINT flags;
	HTREEITEM hItem = HitTest(pt, &flags);
	bool bOnItem = (flags & TVHT_ONITEM) != 0;

	CMenu add;
	VERIFY(add.CreatePopupMenu());
	if(bOnItem) {
		if(CanInsertItem(GetParentItem(hItem)))
		{
			CString strMenu;
			strMenu.LoadString(IDS_PROJECT_MENU1);
			VERIFY(add.AppendMenu(MF_STRING, ID_ADD_SCREEN, strMenu));
		}

		if(CanInsertItem(hItem))
		{
			CString strMenu;
			strMenu.LoadString(IDS_PROJECT_MENU2);
			VERIFY(add.AppendMenu(MF_STRING, ID_ADD_SCRIPT, strMenu));
		}
	}

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());
	if(bOnItem) 
	{
		if(CanEditLabel(hItem))
		{
			CString strMenu;
			strMenu.LoadString(IDS_PROJECT_MENU3);
			VERIFY(menu.AppendMenu(MF_STRING, ID_RENAME, strMenu));
		}

		if(CanDeleteItem(hItem))
		{
			CString strMenu;
			strMenu.LoadString(IDS_PROJECT_MENU4);
			VERIFY(menu.AppendMenu(MF_STRING, ID_DELETE, strMenu));
		}
	}

	if(add.GetMenuItemCount() > 0)
	{
		CString strMenu;
		strMenu.LoadString(IDS_PROJECT_MENU5);
		VERIFY(menu.AppendMenu(MF_POPUP, UINT(add.GetSafeHmenu()), strMenu));
	}

	CString strMenu;
	strMenu.LoadString(IDS_PROJECT_MENU6);
	VERIFY(menu.AppendMenu(MF_STRING, ID_SORT_LEVEL, strMenu));

	strMenu.LoadString(IDS_PROJECT_MENU7);
	VERIFY(menu.AppendMenu(MF_STRING, ID_EXP_FOLDER, strMenu));

	strMenu.LoadString(IDS_PROJECT_MENU8);
	VERIFY(menu.AppendMenu(MF_STRING, ID_EXP_REFRESH, strMenu));

	strMenu.LoadString(IDS_PROJECT_MENU9);
	VERIFY(menu.AppendMenu(MF_STRING, ID_APP_PUBLISHER, strMenu));
	
	ExtendContextMenu(menu);

	// maybe the menu is empty...
	if(menu.GetMenuItemCount() > 0)
		menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}


void CEditTreeCtrl::ExtendContextMenu(CMenu & menu) 
{
}


bool CEditTreeCtrl::IsAncestor(HTREEITEM hItem, HTREEITEM hCheck) const 
{
	for(HTREEITEM hParent = hCheck; hParent != 0; hParent = GetParentItem(hParent))
		if(hParent == hItem)
			return true;
	return false;
}


void CEditTreeCtrl::SortCurrentLevel(HTREEITEM hItem) 
{
	if(!hItem)
		hItem = GetSelectedItem();
	if(CanSortLevel(hItem))
		SortChildren(hItem ? GetParentItem(hItem) : hItem);
}


void CEditTreeCtrl::SortCurrentLevelAndBelow(HTREEITEM hItem) 
{
	SortCurrentLevel(hItem);
	for(hItem = hItem ? GetChildItem(GetParentItem(hItem)) : GetRootItem(); hItem != 0; hItem = GetNextSiblingItem(hItem))
		if(ItemHasChildren(hItem))
			SortCurrentLevelAndBelow(GetChildItem(hItem));
}


BOOL CEditTreeCtrl::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message) 
	{
		case WM_KEYDOWN:
			if(HandleKeyDown(pMsg->wParam, pMsg->lParam))
				return true;
			break;

		default:
			break;
	}
	return CFOPExtTreeCtrl::PreTranslateMessage(pMsg);
}


void CEditTreeCtrl::CreateCursorMap() 
{
	// make sure this method is only called once.

}


BEGIN_MESSAGE_MAP(CEditTreeCtrl, CFOPExtTreeCtrl)
	//{{AFX_MSG_MAP(CEditTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(TVN_BEGINRDRAG, OnBeginrdrag)
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_RENAME, ID_MAX_CMD-1, OnContextCmd)
	ON_COMMAND_RANGE(ID_DRAG_COPY, ID_MAX_DRH-1, OnDragContextCmd)
END_MESSAGE_MAP()

// --------------------------------------------------------------------------
// CEditTreeCtrl message handlers

void CEditTreeCtrl::OnContextCmd(UINT id)
{
	CTableBar *pParent = (CTableBar *)GetParent()->GetParent();
	HTREEITEM hCur = GetSelectedItem();
	
	switch(id)
	{
	case 1:
		{
			AfxMessageBox(IDS_PROJECT_MSG9, MB_OK|MB_ICONINFORMATION);
	//		DoEditLabel(hCur);
		}
		break;

	case 2:
		{
			HTREEITEM hRoot = GetParentItem(hCur);
			if(hRoot != NULL)
			{
				int nData = GetItemData(hCur);

				if(nData == 2001)
				{
					DoDeleteItem(hCur);
				}

				if(nData == 2002)
				{
					DoDeleteScpItem(hCur);
				}
			}

		}
		break;
		
	case 3:
		{
			if(pParent != NULL)
			{

				DoInsertChild(pParent->hMs0Root);
			}
		}
		break;

	case 4:
		{
			if(pParent != NULL)
			{
				
				DoInsertSibling(pParent->hSptRoot);
			}

		}
		break;

	case 5:
		{
//			theApp.OnProjectSetting();
		}
		break;

	case 7:
		{
			if(!theApp.strProjectName.IsEmpty())
				theApp.ExpFolder(theApp.m_strPath);
		}
		break;

	case 8:
		{
			if(pParent != NULL)
			{
				
				pParent->InitShapes();
			}
		}
		break;

	case 9:
		{
//			if(!theApp.strProjectName.IsEmpty())
//				theApp.OnMbRelease();
		}
		break;
	}
	// unknown command in context menu
//	ASSERT(false);
}


void CEditTreeCtrl::OnDragContextCmd(UINT id) 
{
	// Should only reach this during a right-drag...
	ASSERT(m_pDragData != 0);

	if(id != ID_DRAG_CANCEL) 
	{
		bool bCopy = (id == ID_DRAG_COPY);
		DragMoveItem(m_pDragData->GetDragItem(), m_pDragData->GetDropTarget(), EDropHint(m_pDragData->GetDropHint()), bCopy);
	}

	DragStop();
}


void CEditTreeCtrl::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	*pResult = 1;

	if(CanEditLabel(pTVDispInfo->item.hItem))
		*pResult = 0;
}

void CEditTreeCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	TVITEM & item = pTVDispInfo->item;
	*pResult = 1;

	if(item.pszText && CanSetLabelText(item)) 
	{
		SetItem(&item);
		*pResult = 0;
	}
}

void CEditTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

//	if(CanDragItem(pNMTreeView->itemNew)) 
	{
//		m_pDragData = CreateDragData(pNMTreeView->itemNew.hItem, false);
	//	DragStart();
	}
}

void CEditTreeCtrl::OnBeginrdrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	if(CanDragItem(pNMTreeView->itemNew)) {
		m_pDragData = CreateDragData(pNMTreeView->itemNew.hItem, true);
		DragStart();
	}
}

void CEditTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_pDragData)
		DragMove();
	CFOPExtTreeCtrl::OnMouseMove(nFlags, point);
}

void CEditTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_pDragData)
		DragEnd();
	CFOPExtTreeCtrl::OnLButtonUp(nFlags, point);
}


void CEditTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_pDragData)
		CFOPExtTreeCtrl::OnRButtonDown(nFlags, point);
}

void CEditTreeCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if(m_pDragData) {
		if(m_pDragData->IsRightDragging())
			DragEnd();
		else
			// Right-click during a left-click-drag breaks the drag operation
			DragStop();
	} else
		CFOPExtTreeCtrl::OnRButtonUp(nFlags, point);
}

void CEditTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	DisplayContextMenu(point);
}

void CEditTreeCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 1;
	UINT flags;
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	HTREEITEM hItem = HitTest(point, &flags);
//	if(hItem && (flags & TVHT_ONITEM) && !(flags & TVHT_ONITEMRIGHT))
//		SelectItem(hItem);
	ClientToScreen(&point);
	DisplayContextMenu(point);
}

void CEditTreeCtrl::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	UINT & action = pNMTreeView->action;
	if(action == TVC_UNKNOWN) {
		// Software generated change of selection.
		// The CFOPExtTreeCtrl implements a strange behavior when beginning
		// a drag operation by clicking an a different item than the
		// default and not releasing the mouse button before starting to drag:
		// First the 'begin drag' operation occurs. The selected item is
		// the old item, so the "CreateDragImage() method returns the image of the
		// old item. Then occur the 'selection changed' events :-\ 
		// We try to correct this behavior here...
		if(m_pDragData) {
			// Yep - that's it. The 'begin drag' event was already fired while the
			// old item was still selected...
			// If the 'new' item still has no selected state, then we have to
			// deselect all the other selected items.
			if(!(pNMTreeView->itemNew.state & TVIS_SELECTED)) {
				HTREEITEM hNew = pNMTreeView->itemNew.hItem;
				// The new item still has not the selected state set.
				// Creating a new drag image might fail if we don't
				// set it now.
				SetItemState(hNew, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
				// The drag image must be changed, too
				m_pDragData->ReleaseDragImage();
				m_pDragData->CreateDragImage();
			}
		}
	}
}

void CEditTreeCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UINT flags;
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	BOOL bNeedOpen = FALSE;
	BOOL bOpenScript = FALSE;
	BOOL bOpenSetting = FALSE;
	BOOL bPushApp = FALSE;
	BOOL bExpFolder = FALSE;
	BOOL bParam = FALSE;
	HTREEITEM hItem = HitTest(point, &flags);
	if(hItem && (flags & TVHT_ONITEM) && !(flags & TVHT_ONITEMRIGHT))
	{
		int nData = GetItemData(hItem);
		{
			if(nData == 2001)
			{
				bNeedOpen = TRUE;
			}
			else if(nData == 2002)
			{
				bOpenScript = TRUE;
			}
			else if(nData == 3000)
			{
				bOpenSetting = TRUE;
			}
			else if(nData == 4000)
			{
				bPushApp = TRUE;
			}
			else if(nData == 5000)
			{
				bExpFolder = TRUE;
			}
			else if(nData == 6000)
			{
				bParam = TRUE;
			}
		}
//		SelectItem(hItem);
	}

	if(bNeedOpen)
	{
		CString strFile = LPCTSTR(GetItemText(hItem));
		strFile += _T(".Ms0");
		CString strPath1 = theApp.m_strPath +_T("Ms0Files");
		strFile = strPath1 + _T("\\")+ strFile;
		if(theApp.XFileExists(strFile))
		{
			theApp.OpenDocumentFile(strFile);
		}

	}

	if(bOpenScript)
	{
		CString strFile = LPCTSTR(GetItemText(hItem));
		strFile += _T(".scp");
		CString strPath1 = theApp.m_strPath +_T("ScriptFiles");
		strFile = strPath1 + _T("\\")+ strFile;
		if(theApp.XFileExists(strFile))
		{
			theApp.OpenDocumentFile(strFile);
		}
		
	}

	if(bOpenSetting)
	{
//		theApp.OnProjectSetting();
		AfxMessageBox(_T("This is a not supported feature by now, you need create it by yourself, thanks!"));
	}

	if(bPushApp)
	{
		AfxMessageBox(_T("This is a not supported feature by now, you need create it by yourself, thanks!"));
//		if(!theApp.strProjectName.IsEmpty())
//				theApp.OnMbRelease();
	}

	if(bExpFolder)
	{
		if(!theApp.strProjectName.IsEmpty())
			theApp.ExpFolder(theApp.m_strPath);
	}
	
	if(bParam)
	{
		AfxMessageBox(_T("This is a not supported feature by now, you need create it by yourself, thanks!"));
//		if(!theApp.strProjectName.IsEmpty())
//				theApp.OnParamManager();
	}
	*pResult = 0;
}
