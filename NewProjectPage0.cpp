// NewProjectPage0.cpp : implementation file
//

#include "stdafx.h"
#include "MultisimDemo.h"
#include "NewProjectPage0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage0 dialog


CNewProjectPage0::CNewProjectPage0(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CNewProjectPage0::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProjectPage0)
		// NOTE: the ClassWizard will add member initialization here
	m_strPath = _T("c:\\temp\\");
	//}}AFX_DATA_INIT
	nDocType = 100;
}


void CNewProjectPage0::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProjectPage0)
	DDX_Control(pDX, IDC_LIST_SYS1, m_listCtrl);
	DDX_Control(pDX, IDC_EDIT_SYS3, m_edtPath);
	DDX_Text(pDX, IDC_EDIT_SYS3, m_strPath);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProjectPage0, CNewWizPage)
	//{{AFX_MSG_MAP(CNewProjectPage0)
	ON_EN_CHANGE(IDC_EDIT_SYS1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT_SYS3, OnChangeEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS1, OnKillfocusEdit1)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SYS1, OnClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYS1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_SYS1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage0 message handlers

BOOL CNewProjectPage0::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	
	GetDlgItem(IDC_EDIT_SYS1)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_EDIT_SYS3)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_MSG1)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_TIPS)->SetFont(&gfxData.fontBold);
	// TODO: Add extra initialization here
	m_pImagesNew.Create (32, 32, ILC_MASK, 0, 1);
	m_pImagesNew.Add (AfxGetApp()->LoadIcon (IDR_MULTISTYPE));
	
	CString strVer;
	strVer = _T("New Project");
	m_listCtrl.SetImageList (&m_pImagesNew, LVSIL_NORMAL);
	int nItem = m_listCtrl.InsertItem (0, strVer, 0);
	m_listCtrl.SetItemData(nItem,100);
	
	m_listCtrl.SetItemState(0,LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	
	if(!theApp.DirectoryExists(m_strPath))
	{
		theApp.MakeDirectory(m_strPath);
	}

	// TODO: Add extra initialization here
	char sFile[255];
	::GetCurrentDirectory(sizeof(sFile),sFile);
	CString strTemp;
	strTemp.Format("%s",sFile);
	if(strTemp.GetLength()>3)
		strTemp = strTemp +"\\";
	GetDlgItem(IDC_EDIT_SYS3)->SetWindowText(strTemp);
	strPath.Format("%s",strTemp);
	GetDlgItem(IDC_EDIT_SYS1)->SetFocus();

	m_strPath = strTemp;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CNewProjectPage0::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString string1;
	GetDlgItem(IDC_EDIT_SYS1)->GetWindowText(string1);
	if(string1.Left(1) == "C")
	{
		string1 = string1.Right(string1.GetLength() -1);
	}
	CString strTemp;
	GetDlgItem(IDC_EDIT_SYS3)->GetWindowText(strTemp);
	strTemp = "Path:"+strTemp+string1;
	GetDlgItem(IDC_MSG1)->SetWindowText(strTemp);
	
	// TODO: Add your control notification handler code here
	
}
void CNewProjectPage0::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString string1;
	GetDlgItem(IDC_EDIT_SYS1)->GetWindowText(string1);
	if(string1.Left(1) == "C")
	{
		string1 = string1.Right(string1.GetLength() -1);
	}
	CString strTemp;
	GetDlgItem(IDC_EDIT_SYS3)->GetWindowText(strTemp);
	strTemp = "Path:"+strTemp+string1;
	GetDlgItem(IDC_MSG1)->SetWindowText(strTemp);
	
}
void CNewProjectPage0::OnKillfocusEdit1() 
{
	// TODO: Add your control notification handler code here
	
}

void CNewProjectPage0::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;
	// TODO: Add your control notification handler code here
	int iSelIndex = m_listCtrl.GetNextItem (-1, LVNI_ALL | LVNI_SELECTED);
	
	if (iSelIndex == -1)
	{
		return;
	}
	nDocType = (UINT)m_listCtrl.GetItemData(iSelIndex);
	switch(nDocType)
	{
	case 100:
		{
			CString strTemp;
			strTemp.LoadString(IDS_PROJECT_TIP);
			GetDlgItem(IDC_TIPS)->SetWindowText(strTemp);
		}
		break;
	default:
		{
			CString strTemp;
			strTemp.LoadString(IDS_PROJECT_TIP);
			GetDlgItem(IDC_TIPS)->SetWindowText(strTemp);
		}
		break;
	}
	*pResult = 0;
}

static int CALLBACK FOPBrowseForFolderProc( HWND hwnd, UINT w, LPARAM l, LPARAM lpData )
{
	UNUSED_ALWAYS(l);
	if( w == BFFM_INITIALIZED )
	{
		::SendMessage( hwnd, BFFM_SETSELECTION, (WPARAM)FALSE, lpData );
	}
	return 0;
}

BOOL CNewProjectPage0::BrowseForFolder( CString& strPath )
{
	strPath = m_strPath;
	BOOL bRet = FALSE;

	LPMALLOC pMalloc = NULL;
	HRESULT hr = ::SHGetMalloc(&pMalloc);
	ASSERT(SUCCEEDED(hr));

	if(SUCCEEDED(hr))
	{
		LPSHELLFOLDER pShellFolder = NULL;

		hr = ::SHGetDesktopFolder(&pShellFolder);
	
		if(SUCCEEDED(hr))
		{
			if( strPath.IsEmpty() )
			{
				TCHAR temp[_MAX_PATH];
				::GetCurrentDirectory( sizeof(temp), temp );
				strPath = temp;
			}

			OLECHAR olePath[_MAX_PATH];
			::ZeroMemory( olePath, sizeof(olePath) );

			LPITEMIDLIST pidl = NULL;
			DWORD dwEaten   = 0;
			DWORD dwAttribs = 0;

#ifndef UNICODE
			char* pszPath = strPath.GetBuffer(strPath.GetLength()+1);
			::MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, pszPath, -1, olePath, _MAX_PATH );
			strPath.ReleaseBuffer(-1);
#else
			_tcsncpy( olePath, (LPCTSTR)strPath, _MAX_PATH );
#endif

			hr = pShellFolder->ParseDisplayName( NULL, NULL, olePath, &dwEaten, &pidl, &dwAttribs );
	
			if(SUCCEEDED(hr))
			{
				TCHAR szPath[_MAX_PATH];
				::ZeroMemory( szPath, sizeof(szPath) );

				BROWSEINFO bi;
				::ZeroMemory(&bi, sizeof(bi));

				bi.hwndOwner = (m_pParentWnd != NULL) ? m_pParentWnd->GetSafeHwnd() : NULL;
				bi.pidlRoot = NULL;
#if (_MFC_VER < 0x0420) & defined(UNICODE)
				bi.pszDisplayName = (char *)&szPath[0];
				bi.lpszTitle = (const char *)_T("Path setting...");
#else
				bi.pszDisplayName = szPath;
				bi.lpszTitle = _T("Path setting...");
#endif
				bi.ulFlags = 0;
				bi.lpfn = FOPBrowseForFolderProc;
				bi.lParam = (LPARAM)pidl;

				LPITEMIDLIST pidlPath = ::SHBrowseForFolder(&bi);

				if( pidlPath != NULL )
				{
#if (_MFC_VER < 0x0420) & defined(UNICODE)
					if( ::SHGetPathFromIDList(pidlPath,(char *)&szPath[0]) )
#else
					if( ::SHGetPathFromIDList(pidlPath,szPath) )
#endif
					{
						bRet = TRUE;
						strPath = szPath;
						if(strPath.Right(1) != _T("\\"))
							strPath += _T("\\");

						pMalloc->Free(pidlPath);
					}
				}

				pMalloc->Free(pidl);
			}

			pShellFolder->Release();
			pShellFolder = NULL;
		}

		pMalloc->Release();
		pMalloc = NULL;
	}

	return bRet;
}

void CNewProjectPage0::OnButton1() 
{
	// TODO: Add your control notification handler code here

	BrowseForFolder(m_strPath);
	m_edtPath.SetWindowText(m_strPath);
}

BOOL CNewProjectPage0::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		return TRUE;
	}

	return CNewWizPage::PreTranslateMessage(pMsg);
}


void CNewProjectPage0::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pNMHDR;
	// TODO: Add your control notification handler code here
	//OnOK();
	*pResult = 0;
}

LRESULT CNewProjectPage0::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	int iSelIndex = m_listCtrl.GetNextItem (-1, LVNI_ALL | LVNI_SELECTED);
	
	if (iSelIndex == -1)
	{
		CString strMsg;
		strMsg.LoadString(IDS_PROJECT_MSG1);
		AfxMessageBox(strMsg,MB_OK|MB_ICONINFORMATION);
		return -1;
	}
	nDocType = (UINT)m_listCtrl.GetItemData(iSelIndex);
	GetDlgItem(IDC_EDIT_SYS1)->GetWindowText(strProjectName);
	strProjectName.TrimLeft();
	strProjectName.TrimRight();
	int nLength = strProjectName.GetLength();
	if(strProjectName.IsEmpty())
	{
		GetDlgItem(IDC_EDIT_SYS1)->SetFocus();
		AfxMessageBox(IDS_PROJECT_MSG2,MB_OK|MB_ICONINFORMATION);
		return -1;
	}
	
	for(int j = 0; j < nLength; j++)
	{
		TCHAR ch = strProjectName.GetAt(j);
		
		if(ch != '_')
		{
			if(!isalnum(ch))
			{
				
				GetDlgItem(IDC_EDIT_SYS1)->SetFocus();
				AfxMessageBox(IDS_PROJECT_MSG3,MB_OK|MB_ICONINFORMATION);
				return -1;
			}
		}				
	}
	CString strTemp;
	GetDlgItem(IDC_EDIT_SYS3)->GetWindowText(strTemp);
	if(strTemp.IsEmpty())
	{
		GetDlgItem(IDC_EDIT_SYS3)->SetFocus();
		return -1;
	}
	strPath = strTemp + strProjectName;
	CString strWillFile;

	strWillFile = strPath + _T("\\")+strProjectName+ _T(".msp");
	if(theApp.XFileExists(strWillFile))
	{
		
		GetDlgItem(IDC_EDIT_SYS1)->SetFocus();
		AfxMessageBox(IDS_PROJECT_MSG4,MB_OK|MB_ICONINFORMATION);
		return -1;
	}
	return CNewWizPage::OnWizardNext();
}
