
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "MultisimDemo.h"

//E-XD++ Library add lines.
#include "MultisimDemoDoc.h"
#include "MultisimDemoView.h"
#include "ChildFrm.h"
#include "fores.h"
#include "MBEventEditDlg6.h"
#include "ETAPDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CFOPMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CFOPMDIChildWnd)
//{{AFX_MSG_MAP(CChildFrame)
ON_WM_CREATE()
ON_COMMAND(ID_FO_ADD_NEWPAGE, OnFoAddNewpage)
ON_COMMAND(ID_FO_REMOVE_PAGE, OnFoRemovePage)
ON_COMMAND(ID_VIEW_TOOLBOX, OnViewToolbox)
ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBOX, OnUpdateViewToolbox)
ON_COMMAND(ID_MOVE_PREVIOUS, OnMovePrevious)
ON_UPDATE_COMMAND_UI(ID_MOVE_PREVIOUS, OnUpdateMovePrevious)
ON_COMMAND(ID_MOVE_NEXT, OnMoveNext)
ON_UPDATE_COMMAND_UI(ID_MOVE_NEXT, OnUpdateMoveNext)
ON_COMMAND(ID_MB_CREATEPAGE_COPY, OnMbCreatepageCopy)
ON_UPDATE_COMMAND_UI(ID_MB_CREATEPAGE_COPY, OnUpdateMbCreatepageCopy)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREAFOAPPWIZARDRUCT cs

	if( !CFOPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
//E-XD++ Library add lines.
	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CFOPMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CFOPMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

void CChildFrame::OnHome()
{
	int nCurrentTab = GetPageBox()->GetCurSel();
	if(nCurrentTab >= 0)
	{
		CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
		if(pDoc != NULL)
		{
			CString str;
			GetPageBox()->GetLBText(nCurrentTab, str);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nCurrentTab);
			CFORenameDlg dlg;
			dlg.m_strCaption = str;
			if(dlg.DoModal() == IDOK)
			{
				if(str != dlg.m_strCaption)
				{
					if(!IsPageExist(dlg.m_strCaption))
					{
						pModelx->m_strCaption = dlg.m_strCaption;
						
						
						GetPageBox()->ResetContent();
						for(int x = 0;x < pDoc->m_pModelManager->GetTabCount(); x++)
						{
							CFOTabPageModel *pModelx = (CFOTabPageModel *)pDoc->m_pModelManager->m_arTabs[x];
							if(pModelx != NULL)
							{
								CString strPage = pModelx->m_strCaption;
								int nIndex = m_wndStatusBar.pComboBox->AddString(strPage);
								m_wndStatusBar.pComboBox->SetItemData(nIndex, (DWORD)pModelx);
								//	m_wndTab.InsertPage(pModelx,NULL);
							}
						}
						GetPageBox()->SetCurSel(nCurrentTab);
				 
					}
					else
					{
						AfxMessageBox(_T("This page name is already exist, please try again!"), MB_OK|MB_ICONINFORMATION);

					}
				}
				
			}
		}
	}
	

}


void CChildFrame::UpdateBox()
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		GetPageBox()->ResetContent();
		for(int x = 0;x < pDoc->m_pModelManager->GetTabCount(); x++)
		{
			CFOTabPageModel *pModelx = (CFOTabPageModel *)pDoc->m_pModelManager->m_arTabs[x];
			if(pModelx != NULL)
			{
				CString strPage = pModelx->m_strCaption;
				int nIndex = m_wndStatusBar.pComboBox->AddString(strPage);
				m_wndStatusBar.pComboBox->SetItemData(nIndex, (DWORD)pModelx);
				
			}
		}
		
	}
}

void CChildFrame::OnPrev()
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		int nTotal = GetPageBox()->GetCount();
		if(nTotal <= 1)
		{
			return;
		}
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		int nCurrentTab = GetPageBox()->GetCurSel();
		if(nCurrentTab > 0)
		{
			
			int nIndex = nCurrentTab -1;
			GetPageBox()->SetCurSel(nIndex);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
			
			if(pView != NULL)
			{
				pView->SetTabModel(pModelx);
				pModelx->NotifyObserver(0,pModelx);
				pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
			}
		}
		
	}
}


CFOTabPageModel *CChildFrame::AddNewPage2(const CString &strTitle)
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		
		CFOTabPageModel *pModelx = (CFOTabPageModel *)pDoc->m_pModelManager->InsertTab(strTitle);
		CString strPage = pModelx->m_strCaption;
		int nIndex = m_wndStatusBar.pComboBox->AddString(strPage);
		m_wndStatusBar.pComboBox->SetItemData(nIndex, (DWORD)pModelx);
		
		GetPageBox()->SetCurSel(nIndex);
		
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		if(pView != NULL)
		{
			pView->SetTabModel(pModelx);
			pModelx->NotifyObserver(0,pModelx);
			pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
			m_wndStatusBar.UpdatePanel();
			
			return pModelx;
		}
	}
	return NULL;
}

BOOL CChildFrame::IsPageExist(const CString &str)
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc == NULL)
	{
		return FALSE;
	}
	for(int x = 0;x < pDoc->m_pModelManager->GetTabCount(); x++)
	{
		CExtTabModel *pModelx = (CExtTabModel *)pDoc->m_pModelManager->m_arTabs[x];
		if(pModelx != NULL)
		{
			if(pModelx->m_strCaption == str)
			{
				
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

void CChildFrame::OnNext()
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		int nTotal = GetPageBox()->GetCount();
		if(nTotal <= 1)
		{
			return;
		}
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		int nCurrentTab = GetPageBox()->GetCurSel();
		if(nCurrentTab < nTotal-1)
		{
			int nIndex = nCurrentTab + 1;
			GetPageBox()->SetCurSel(nIndex);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
			
			if(pView != NULL)
			{
				pView->SetTabModel(pModelx);
				pModelx->NotifyObserver(0,pModelx);
				pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
			}
		}
		
	}
}
void CChildFrame::OnDel()
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		int nTotal = GetPageBox()->GetCount();
		if(nTotal <= 1)
		{
			return;
		}
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		int nCurrentTab = GetPageBox()->GetCurSel();
		if(nCurrentTab == 0)
		{
			pDoc->m_pModelManager->DeleteTab(nCurrentTab);
			UpdateBox();
			pView->SetOnlyModel(NULL);
			int nIndex = 0;
			GetPageBox()->SetCurSel(nIndex);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
			
			if(pView != NULL)
			{
				pView->SetTabModel(pModelx);
				pModelx->NotifyObserver(0,pModelx);
				pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
			}
		}
		else
		{
			pDoc->m_pModelManager->DeleteTab(nCurrentTab);
			UpdateBox();
			pView->SetOnlyModel(NULL);
			int nIndex = nCurrentTab -1;
			GetPageBox()->SetCurSel(nIndex);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
		 
			if(pView != NULL)
			{
				pView->SetTabModel(pModelx);
				pModelx->NotifyObserver(0,pModelx);
				pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
			}
		}
		 
	}
}

void CChildFrame::OnAdd()
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		
		CFOTabPageModel *pModelx = (CFOTabPageModel *)pDoc->m_pModelManager->InsertTab(_T(""));
		CString strPage = pModelx->m_strCaption;
		int nIndex = m_wndStatusBar.pComboBox->AddString(strPage);
		m_wndStatusBar.pComboBox->SetItemData(nIndex, (DWORD)pModelx);
		
		GetPageBox()->SetCurSel(nIndex);

		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		if(pView != NULL)
		{
			pView->SetTabModel(pModelx);
			pModelx->NotifyObserver(0,pModelx);
			pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);

		}
	}
}

static UINT indicators2[] =
{
	ID_SEPARATOR,           // status line indicator
		ID_FO_INDEX_WIDTH,
		ID_FO_INDEX_HEIGHT,
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
//E-XD++ add lines.
int CChildFrame::OnCreate(LPCREATESTRUCT LPCREATESTRUCT) 
{
	if (CFOPMDIChildWnd::OnCreate(LPCREATESTRUCT) == -1)
		return -1;
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators2,
		sizeof(indicators2)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetFont(&gfxData.fontLarge);

	if(theApp.m_bListBar)
	{
		if (!m_ListBar.Create(this, _T("Toolbox Window"), WS_CHILD|WS_VISIBLE|CBRS_LEFT|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC, 
			CBRS_FOP_DEFAULT|CBRS_FOP_BDSP, 1212))
		{
			TRACE(_T("Failed to create List Bar\n"));
			return -1;
		}
		
	}
	else
	{
		if (!m_ListBar.Create(this, _T("Toolbox Window"), WS_CHILD|CBRS_LEFT|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC, 
			CBRS_FOP_DEFAULT|CBRS_FOP_BDSP, 1212))
		{
			TRACE(_T("Failed to create List Bar\n"));
			return -1;
		}
		
	}

	m_ListBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarEx(&m_ListBar, AFX_IDW_DOCKBAR_BOTTOM, 0.50, 200);

	return 0;
}

CString CChildFrame::AddNew(CExtTabModel *pModel)
{
	CString strPage = pModel->m_strCaption;
	if(strPage.IsEmpty())
	{
		return strPage;
	}

	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		
		CFOTabPageModel *pModelx = pModel;
		CString strPage = pModelx->m_strCaption;
		int nIndex = m_wndStatusBar.pComboBox->AddString(strPage);
		m_wndStatusBar.pComboBox->SetItemData(nIndex, (DWORD)pModelx);
		
		GetPageBox()->SetCurSel(nIndex);
		
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		if(pView != NULL)
		{
			pView->SetTabModel(pModelx);
			pModelx->NotifyObserver(0,pModelx);
			pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
			m_wndStatusBar.UpdatePanel();
		}
	}
	 
	return pModel->m_strCaption;
	
}

void CChildFrame::ActivatePage(const CString &strPage)
{
	if(strPage.IsEmpty())
	{
		return;
	}

	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		int nTotal = GetPageBox()->GetCount();
		if(nTotal <= 1)
		{
			return;
		}
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		int nCurrentTab = GetPageBox()->FindString(-1, strPage);
		if(nCurrentTab < nTotal)
		{
			int nIndex = nCurrentTab;
			GetPageBox()->SetCurSel(nIndex);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
			
			if(pView != NULL)
			{
				pView->SetTabModel(pModelx);
				pModelx->NotifyObserver(0,pModelx);
				pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
				m_wndStatusBar.UpdatePanel();
				return;
			}
		}
		
	}

	
	AfxMessageBox(_T("This page is not exist!"), MB_OK|MB_ICONINFORMATION);
}

CString CChildFrame::DoAddNewPage()
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		
		CFOTabPageModel *pModelx = (CFOTabPageModel *)pDoc->m_pModelManager->InsertTab(_T(""));
		CString strPage = pModelx->m_strCaption;
		int nIndex = m_wndStatusBar.pComboBox->AddString(strPage);
		m_wndStatusBar.pComboBox->SetItemData(nIndex, (DWORD)pModelx);
		
		GetPageBox()->SetCurSel(nIndex);
		
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		if(pView != NULL)
		{
			pView->SetTabModel(pModelx);
			pModelx->NotifyObserver(0,pModelx);
			pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
			m_wndStatusBar.UpdatePanel();
			return strPage;
		}
	}

	return _T("");
}

void CChildFrame::DeleteTab(const CString &strPage)
{
	if(strPage.IsEmpty())
	{
		return;
	}

	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		int nTotal = GetPageBox()->GetCount();
		if(nTotal <= 1)
		{
			return;
		}
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		int nCurrentTab = GetPageBox()->FindString(-1, strPage);
		if(nCurrentTab == 0)
		{
			pDoc->m_pModelManager->DeleteTab(nCurrentTab);
			UpdateBox();
			pView->SetOnlyModel(NULL);
			int nIndex = 0;
			GetPageBox()->SetCurSel(nIndex);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
			
			if(pView != NULL)
			{
				pView->SetTabModel(pModelx);
				pModelx->NotifyObserver(0,pModelx);
				pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
				m_wndStatusBar.UpdatePanel();
			}
		}
		else
		{
			pDoc->m_pModelManager->DeleteTab(nCurrentTab);
			UpdateBox();
			pView->SetOnlyModel(NULL);
			int nIndex = nCurrentTab -1;
			GetPageBox()->SetCurSel(nIndex);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
			
			if(pView != NULL)
			{
				pView->SetTabModel(pModelx);
				pModelx->NotifyObserver(0,pModelx);
				pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
				m_wndStatusBar.UpdatePanel();
			}
		}
		
	}
	
}

//E-XD++ Library add lines.
void CChildFrame::ActivateFrame(int nCmdShow)
{
//	nCmdShow = SW_SHOWMAXIMIZED;
	CFOPMDIChildWnd::ActivateFrame(nCmdShow);
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
 	if(pDoc != NULL)
	{
		GetPageBox()->ResetContent();
		for(int x = 0;x < pDoc->m_pModelManager->GetTabCount(); x++)
		{
			CFOTabPageModel *pModelx = (CFOTabPageModel *)pDoc->m_pModelManager->m_arTabs[x];
			if(pModelx != NULL)
			{
				CString strPage = pModelx->m_strCaption;
				int nIndex = m_wndStatusBar.pComboBox->AddString(strPage);
				m_wndStatusBar.pComboBox->SetItemData(nIndex, (DWORD)pModelx);
				//	m_wndTab.InsertPage(pModelx,NULL);
			}
		}
		GetPageBox()->SetCurSel(0);
	}
	
	if(pDoc->bNewDocument)
	{
		pDoc->bNewDocument = FALSE;
	}
	else if(pDoc->bOpenDocument)
	{
		pDoc->bOpenDocument = FALSE;
		if(pDoc->m_pModelManager->GetTabCount() < 2)
		{
			return;
		}
		
		CFOTabPageModel *pModel = (CFOTabPageModel *)pDoc->m_pModelManager->m_arTabs[1];
	 
	}
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	BOOL bReturn = CFOPMDIChildWnd::OnCreateClient(lpcs, pContext);
	// specify the runtime class for the first sheet
	// don't forget to register the document template in InitInstance!
	pContext->m_pNewViewClass = RUNTIME_CLASS(CMultisimDemoView);

	return TRUE;
}

void CChildFrame::OnFoAddNewpage() 
{
	// TODO: Add your command handler code here
	OnAdd();
}

void CChildFrame::OnFoRemovePage() 
{
	// TODO: Add your command handler code here
	OnDel();
}

//E-XD++ Library add lines.
void CChildFrame::OnViewToolbox() 
{
	// TODO: Add your command handler code here
	BOOL bVisible = m_ListBar.IsWindowVisible();
	if(bVisible)
	{
		ShowControlBar(&m_ListBar,FALSE,FALSE);
	}
	else
	{
		ShowControlBar(&m_ListBar,TRUE,FALSE);
	}
}

void CChildFrame::OnUpdateViewToolbox(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_ListBar.IsWindowVisible());
}

void CChildFrame::GoToPage(const int &nGoPage) 
{
	// TODO: Add your command handler code here
	int nPage = nGoPage;

	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		int nTotal = GetPageBox()->GetCount();
		if(nTotal <= 1)
		{
			return;
		}
		CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
		int nCurrentTab = nPage;
		if(nCurrentTab < nTotal)
		{
			int nIndex = nCurrentTab;
			GetPageBox()->SetCurSel(nIndex);
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
			
			if(pView != NULL)
			{
				pView->SetTabModel(pModelx);
				pModelx->NotifyObserver(0,pModelx);
				pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
				m_wndStatusBar.UpdatePanel();
				return;
			}
		}
		
	}
 

}

void CChildFrame::OnMovePrevious() 
{
	// TODO: Add your command handler code here
	OnPrev();
}

void CChildFrame::OnUpdateMovePrevious(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int nCount = GetPageBox()->GetCount();
	int nCurrentTab = GetPageBox()->GetCurSel();
 
	if(nCount == 1)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(nCurrentTab != 0);
	}
}

void CChildFrame::OnMoveNext() 
{
	// TODO: Add your command handler code here
	OnNext();
}

void CChildFrame::OnUpdateMoveNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int nCount = GetPageBox()->GetCount();
	int nCurrentTab = GetPageBox()->GetCurSel();
 
	if(nCount == 1)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(nCurrentTab < (nCount-1));
	}
}

void CChildFrame::OnMbCreatepageCopy() 
{
	// TODO: Add your command handler code here
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*)GetActiveDocument();
	CETAPDemoView* pView = (CETAPDemoView*)GetActiveView();
	// TODO: Add your command handler code here
	CString strCurPage;
	strCurPage = "";
	if(pView != NULL)
	{
		CExtTabModel *pModel = (CExtTabModel *)pView->GetCurrentModel();
		strCurPage = pModel->m_strCaption;
	}
	CMBEventEditDlg6 dlg;
	dlg.strPageName = strCurPage;
	if(dlg.DoModal() == IDOK)
	{
		CString strName = dlg.strPageName;
		if(!strName.IsEmpty())
		{
			CExtTabModel *pModel = (CExtTabModel *)pDoc->m_pModelManager->FindModel(strName);
			if(pModel != NULL)
			{
				CFODrawShapeSet *pList = pModel->GetFormObjects();
				pModel->ResetLinkNames(*pList);

				pModel->EndEditingBack();

				CExtTabModel *pNewModel = (CExtTabModel *)pModel->Copy();
				pNewModel->RestoreAllConnections();
				CString strCaption = pDoc->m_pModelManager->GetUniquePageCaption();
				CExtTabModel *pModelX = (CExtTabModel *)pDoc->m_pModelManager->InsertTab(pNewModel);
				pModelX->m_strCaption = strCaption;
				AddNew(pModelX);
			//	m_wndTab.InsertPage(pModelX,NULL);
			}
		}
	}
}

CFOPFlatComboBox* CChildFrame::GetPageBox()
{
	return m_wndStatusBar.pComboBox;
}

void CChildFrame::PageChange(const int &nIndex)
{
	CMultisimDemoDoc* pDoc = (CMultisimDemoDoc*) GetActiveDocument();
	if(pDoc != NULL)
	{
		int nOld = pDoc->m_pModelManager->m_nCurrent;
		if(nOld != nIndex)
		{
			CFOTabPageModel *pModelx = (CFOTabPageModel *)GetPageBox()->GetItemData(nIndex);
			if(pModelx != NULL)
			{
				CFOTabPageView *pView = (CFOTabPageView *)FOGetActiveView();
				if(pView != NULL)
				{
					pView->SetTabModel(pModelx);
					pModelx->NotifyObserver(0,pModelx);
					pModelx->NotifyObserver(FO_HINT_MODEL_CHANGED);
					m_wndStatusBar.UpdatePanel();
				}
			}
		}
	}
}

void CChildFrame::OnUpdateMbCreatepageCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI;
}

/////////////////////////////////////////////////////////////////////////////
// CCodeChildFrame

IMPLEMENT_DYNCREATE(CCodeChildFrame, CFOPMDIChildWnd)

BEGIN_MESSAGE_MAP(CCodeChildFrame, CFOPMDIChildWnd)
//{{AFX_MSG_MAP(CCodeChildFrame)
ON_WM_CREATE()
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code !
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeChildFrame construction/destruction

CCodeChildFrame::CCodeChildFrame()
{
	// TODO: add member initialization code here
	
}

CCodeChildFrame::~CCodeChildFrame()
{
}

BOOL CCodeChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	if( !CFOPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	
	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	
	return TRUE;
}

void CCodeChildFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	nCmdShow = SW_SHOWMAXIMIZED;
	CFOPMDIChildWnd::ActivateFrame(nCmdShow);
}

int CCodeChildFrame::OnCreate(LPCREATESTRUCT LPCREATESTRUCT) 
{
	if (CFOPMDIChildWnd::OnCreate(LPCREATESTRUCT) == -1)
		return -1;
	

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CCodeChildFrame diagnostics

#ifdef _DEBUG
void CCodeChildFrame::AssertValid() const
{
	CFOPMDIChildWnd::AssertValid();
}

void CCodeChildFrame::Dump(CDumpContext& dc) const
{
	CFOPMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

void CChildFrame::OnDestroy() 
{
	theApp.m_bListBar = m_ListBar.IsWindowVisible();
	CFOPMDIChildWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
 
