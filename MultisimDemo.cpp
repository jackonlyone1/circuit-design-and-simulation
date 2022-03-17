// MultisimDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MultisimDemo.h"
#include "registry.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MultisimDemoDoc.h"
#include "MultisimDemoView.h"
#include "FOHyperLink.h"
#include "NewVisualProxy.h"
#include "FOPGDIPlusProxy.h"
#include "NewVisualProxy.h"
#include "CodeEditDoc.h"
#include "CodeEditView.h"
#include "MyExtFileDialog.h"
#include "process.h"
#include "ETAPDemoView.h"

#include "NewProjectPage0.h"
#include "NewProjectMain.h"
#include "NewProjectPage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultisimDemoApp

BEGIN_MESSAGE_MAP(CMultisimDemoApp, CFOProjectApp)
	//{{AFX_MSG_MAP(CMultisimDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_NEW_PROJECT, OnNewProject)
	ON_UPDATE_COMMAND_UI(ID_NEW_PROJECT, OnUpdateNewProject)
	ON_COMMAND(ID_OPEN_PROJECT, OnOpenProject)
	ON_UPDATE_COMMAND_UI(ID_OPEN_PROJECT, OnUpdateOpenProject)
	ON_COMMAND(ID_SAVE_PROJECT, OnSaveProject)
	ON_UPDATE_COMMAND_UI(ID_SAVE_PROJECT, OnUpdateSaveProject)
	ON_COMMAND(ID_CLOSE_PROJECT, OnCloseProject)
	ON_UPDATE_COMMAND_UI(ID_CLOSE_PROJECT, OnUpdateCloseProject)
	ON_COMMAND(ID_SAVE_ALL, OnSaveAll)
	ON_UPDATE_COMMAND_UI(ID_SAVE_ALL, OnUpdateSaveAll)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_NEW_SCRIPT, OnNewScript)
	ON_COMMAND(ID_OPEN_SAMPLES, OnOpenSamples)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CFOProjectApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CFOProjectApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CFOProjectApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultisimDemoApp construction

static BOOL NEAR PASCAL FO_SetRegKey(LPCTSTR lpszKey, LPCTSTR lpszValue) { 
	if (::RegSetValue(HKEY_CLASSES_ROOT, lpszKey, REG_SZ, lpszValue,
		lstrlen(lpszValue)) != ERROR_SUCCESS)
	{
		TRACE1("Warning: registration database update failed for key'%Fs'\n", lpszKey);
		return FALSE;
	}
	
	return TRUE;
	
} 

BOOL FO_WriteRegStringCreateValue(HKEY MainKey, LPCTSTR SubPath, LPTSTR SectionName,TCHAR *KeyName)
{
	DWORD dwErrorCode;
	HKEY hKey;
	DWORD dwDisposition;
	
	dwErrorCode = RegCreateKeyEx(MainKey,
		SubPath,
		0,
		_T(""),
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL, //Security
		&hKey,
		&dwDisposition );
	if (dwErrorCode != ERROR_SUCCESS) goto end;
	
	if(!KeyName) goto end;
	dwErrorCode = RegSetValueEx(hKey, SectionName, NULL, REG_SZ, 
		(LPBYTE)KeyName, _tcslen(KeyName)*sizeof(TCHAR));
	
end:
	if (hKey) RegCloseKey(hKey);
	if (dwErrorCode == ERROR_SUCCESS) 
	       return TRUE;
	else
		return FALSE;
}

CMultisimDemoApp::CMultisimDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_bGrid = TRUE;
	m_bFreeFormDrawing = FALSE;
	m_bGuide = TRUE;
	m_bGridSnap = TRUE;
	m_bNewSnap = TRUE;
	m_bMargin = TRUE;
	m_bShowPorts = TRUE;
	m_bDrawingFromCenter = FALSE;
	m_bGlueToShape = TRUE;
	m_bGlueToSpot = TRUE;
	
	m_bSnapToHelpLine = TRUE;
	m_bSnapToIntersect = TRUE;
	m_bListBar = TRUE;
	m_bRuler = TRUE;
	bWithDotShow = TRUE;
	strCurSelectFile = _T("");
	strCurSelectShape = _T("");
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMultisimDemoApp object

CMultisimDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMultisimDemoApp initialization

BOOL CMultisimDemoApp::InitInstance()
{
	// E-XD++ Library Add line.
	AfxOleInit();
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
	FOEnableXPStyle(TRUE);
	
	FOPEnableLinkRoute(FALSE);

	//E-XD++ Library add lines.
	FOInit(RUNTIME_CLASS(CNewVisualProxy));
	DoLoadSetting();
	gfxData.m_bWithPinNumberShow = TRUE;
	gfxData.m_bWithPinNameShow = TRUE;
	gfxData.m_bWithPortIndexShow = TRUE;
	gfxData.InitGUIType(GUI_STANDARD);
	gfxData.fo_DefaultArrowType = 0;
	gfxData.fo_DefaultArrowStartWidth = 4;
	gfxData.fo_DefaultArrowEndWidth = 4;
	gfxData.fo_DefaultArrowStartLength = 5;
	gfxData.fo_DefaultArrowEndLength = 5;
	gfxData.fo_DefaultLineColor = RGB(0,0,0);
	FOEnableContinueDraw(TRUE);
	gfxData.m_bAroundCenterLink = FALSE;
	gfxData.m_strDefToolboxFile = _T("newcircuit.dat");
	gfxData.m_bWithContinuePan = FALSE;
	gfxData.m_bWithPanningRunTime = FALSE;
	gfxData.m_nDefNearestPortDist = 10;
	gfxData.m_nDefCompLabelSpace = 2;
	gfxData.m_bfoLinkOnLink = TRUE;
	gfxData.m_bWithStyle = FALSE;
	gfxData.fo_WithSpecifySelectColorMode = TRUE;
	gfxData.m_bNotHitLinkFirst = TRUE;
	gfxData.m_bWithFixRotateLabel = TRUE;
	gfxData.m_nDefFontSize = 10;
//	gfxData.SetSpecifySelectColor(RGB(0,255, 0));
	AfxInitRichEdit();

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif // MFC 6.0 or earlier

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("ucancode\\multisimdemo"));
	LoadSettings ();
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplate = new CMultiDocTemplateEx(
		IDR_MULTISTYPE,
		RUNTIME_CLASS(CMultisimDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CETAPDemoView));
	AddDocTemplate(m_pDocTemplate);

	pCodeTemplate = new CFOZeroDocTemplate(
		IDR_SAMPLETYPE,
		RUNTIME_CLASS(CCodeDocument),
		RUNTIME_CLASS(CCodeChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCodeEditView));
	AddDocTemplate(pCodeTemplate);

	// Enable DDE Execute open
	EnableShellOpen();

	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	
	m_pMainWnd = pMainFrame;
	//	DragAcceptFiles(pMainFrame->m_hWnd,TRUE);
	SetClassLong(m_pMainWnd->m_hWnd, GCL_HICON, (LONG)LoadIcon(IDR_MAINFRAME));
	/////////////////////////////////////////////////////////////
	CString      strFileTypeId;
	m_pDocTemplate->GetDocString(strFileTypeId,CDocTemplate::regFileTypeId);
	FO_SetRegKey(_T(".Ms0"), strFileTypeId);
	FO_SetRegKey(_T(".MSP"), strFileTypeId);
	FO_SetRegKey(_T(".scp"), strFileTypeId);
	
	TCHAR pathname[512];
	TCHAR _pathname[512];
	TCHAR sname[512];
	TCHAR tmppath[512];
	::GetModuleFileName(m_hInstance, pathname, 512);
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	
	_tsplitpath( pathname, drive, dir, fname, ext );
	_tcscpy(sname,fname);
	_tcscat(sname,ext);
	
	_tcscpy(_pathname,_T("\""));
	_tcscat(_pathname,pathname);
	_tcscat(_pathname,_T("\" \"%1\""));
	OutputDebugString(_pathname);
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,strFileTypeId + _T("\\shell\\open\\command"),NULL,_pathname);
	
	_tcscpy( tmppath , _T(".Ms0\\OpenWithList\\"));_tcscat( tmppath ,sname);
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,tmppath,NULL,NULL);
	
	_tcscpy( tmppath , _T(".MSP\\OpenWithList\\"));_tcscat( tmppath ,sname);
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,tmppath,NULL,NULL);
	
	_tcscpy( tmppath , _T(".scp\\OpenWithList\\"));_tcscat( tmppath ,sname);
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,tmppath,NULL,NULL);
	
	_tcscpy(pathname,_T("Applications\\"));
	_tcscat(pathname,sname);
	_tcscat(pathname,_T("\\shell\\open\\command"));
	FO_WriteRegStringCreateValue(HKEY_CLASSES_ROOT,pathname ,NULL,_pathname);
	
	//////////////////////////////////////////////////////////////
	m_pMainWnd->ShowWindow(SW_HIDE);
	
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	WINDOWPLACEMENT wp;
	if(m_pMainWnd == NULL)
	{
		return FALSE;
	}
	
	if(::IsWindow(m_pMainWnd->m_hWnd))
	{
		m_pMainWnd->GetWindowPlacement(&wp);	
		// If it was closed minimized, then show it normally.	
		if(wp.showCmd == SW_SHOWMINIMIZED)		
		{
			wp.showCmd = SW_NORMAL;	
		}
		m_pMainWnd->SetWindowPlacement(&wp);
	}
	
	m_pMainWnd -> UpdateWindow();

	if (m_lpCmdLine[0] == '\0')
	{
//		m_pDocTemplate->OpenDocumentFile(NULL);
		//		OnFileNew();
	}
	else
	{
		CString FileType;
		FileType = _T(m_lpCmdLine);
		
		if(FileType.Left(1) == _T("\""))
			FileType = FileType.Right(FileType.GetLength() -1);
		
		if(FileType.Right(1) == _T("\""))
			FileType = FileType.Left(FileType.GetLength() -1);
		
		FileType.MakeUpper();
		CString strFile = FileType;
		FileType = FileType.Right(4);
		if(FileType == _T(".MSP"))
		{
			CString string;
			string = strFile;
			IsNeedOpen(string);
			
			CString strExt;
			strExt = XGetExtension(string);
			strExt.MakeUpper();
			strExt.TrimLeft();
			strExt.TrimRight();
			if(strExt == "MSP")
			{
				OpenWorkspace(string);
			}
			
		}
		else if(FileType == _T(".MS0"))
		{
			m_pDocTemplate->OpenDocumentFile(strFile);
			
		}
		else  if(FileType == _T(".SCP"))
		{
			
			pCodeTemplate->OpenDocumentFile(strFile);
		}
		else
		{
			OpenDocumentFile(strFile);
		}
	}

	OnOpenSamples();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	CFOHyperLink m_Home;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_HOMEPAGE, m_Home);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON_SYS1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustomMSampleApp message handlers


void CAboutDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	HKEY hKey1;
	LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Shared Tools\\MSInfo",0L,KEY_ALL_ACCESS,&hKey1);
	if (res == ERROR_SUCCESS)
	{
		DWORD bufsize = _MAX_PATH;
		char msinfo[_MAX_PATH];

		res = RegQueryValueEx(hKey1,"Path",0L,0,(LPBYTE)msinfo,(LPDWORD)&bufsize);
		RegCloseKey(hKey1);
		if (res == ERROR_SUCCESS) WinExec(msinfo, SW_SHOW);
	}
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Home.SetColors(RGB(0,0,255), RGB(0,0,255), RGB(51,102,153) );
	m_Home.SetURL("http://www.ucancode.net");
	GetDlgItem(IDC_EDIT_SYS1)->SetWindowText(_T("If you want to learn more about E-XD++ Visualization Enterprise Edition,Visit:http://www.ucancode.net"));
	return TRUE;
}

// App command to run the dialog
void CMultisimDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMultisimDemoApp message handlers


void CMultisimDemoApp::MakeProjectPath(UINT nType)
{	
	XFOPMakeDirectory(m_strPath);
	CString string;
	
	string = m_strPath +_T("Ms0Files");
	XFOPMakeDirectory(string);	
	
	string = m_strPath +_T("ScriptFiles");
	XFOPMakeDirectory(string);	
	
}

CDocument* CMultisimDemoApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	CString strExt;
	strExt = XGetExtension(lpszFileName);
	strExt.MakeLower();
	if(strExt == _T("msp"))
	{
		if(!IsNeedOpen(lpszFileName))
		{
			return NULL;
		}

		if(OpenWorkspace(lpszFileName))
		{
			return NULL;
		}
	}
	else if(strExt == _T("ms0"))
	{
		ASSERT(m_pDocManager != NULL);
		return m_pDocManager->OpenDocumentFile(lpszFileName);
	}
	else if(strExt == _T("scp"))
	{
		ASSERT(pCodeTemplate != NULL);
		return pCodeTemplate->OpenDocumentFile(lpszFileName);
	}

	return NULL;
}

void CMultisimDemoApp::OnNewProject() 
{
	// TODO: Add your command handler code here
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	CNewProjectMain Dlg;
	
	CNewProjectPage0 m_Page0;
	CNewProjectPage3 m_Page3;
	
	Dlg.AddPage(&m_Page0, CNewProjectPage0::IDD);
//	Dlg.AddPage(&m_Page2, CNewProjectPage2::IDD);
	Dlg.AddPage(&m_Page3, CNewProjectPage3::IDD);
	
	if (Dlg.DoModal() == ID_WIZFINISH)
	{
		ClearOldProject();
		m_strPath = m_Page0.strPath+ _T("\\");
		strProjectName = m_Page0.strProjectName;

		m_pObj->m_strAuthor = m_Page3.m_strAuthor;
		m_pObj->m_strDepartment = m_Page3.m_strDepartment;
		m_pObj->m_strCompany = m_Page3.m_strCompany;
		m_pObj->m_strEMail = m_Page3.m_strEMail;
		m_pObj->m_strURL = m_Page3.m_strURL;
		m_pObj->m_strCopyright = m_Page3.m_strCopyright;
		
		MakeProjectPath(0);

		if(!strProjectName.IsEmpty())
		{
			CString string;
			string = m_strPath +strProjectName + _T(".msp");
			m_pObj->SaveDocument(string);
			CString strText;
			strText = strProjectName + _T(" - MultisimDemo Editor");
			pParent->SetWindowText(strText);

			string.TrimLeft();
			string.TrimRight();
			string.MakeLower();
			POSITION pos1 = m_lstProjects.Find (string);
			if (pos1)
				m_lstProjects.RemoveAt (pos1);
			m_lstProjects.AddHead (string);

			{
				CString strPath1 = theApp.m_strPath +_T("Ms0Files");
				CString strFile = strPath1 + _T("\\Main.Ms0");
				CExtTabModelManager m_model;
				m_model.InsertTab();
				m_model.SaveDocument(strFile);
				theApp.m_pObj->strMainApp = _T("Main.Ms0");
			}

			{
				CString strPath1 = theApp.m_strPath +_T("ScriptFiles");
				CString strFile = strPath1 + _T("\\system.scp");
				CString strFileName;
				strFileName = strFile;// File name
				
				CStdioFile fileWriteUnicode;
				
				if (fileWriteUnicode.Open(strFileName, 
					CFile::modeCreate | CFile::modeWrite))
				{
					fileWriteUnicode.WriteString(_T("Please enter your description text here!"));
					fileWriteUnicode.Close();
				}
			}
			
			theApp.m_pObj->SetModified(TRUE);
		}
		pParent->UpdateTree();
	}
}

void CMultisimDemoApp::OnUpdateNewProject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMultisimDemoApp::OnOpenProject() 
{
	// TODO: Add your command handler code here
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	static char szFilter[]="MultisimDemo Project(.msp)|*.msp||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,szFilter,AfxGetMainWnd());
	if(dlg.DoModal()== IDOK)
	{
		CString string;
		string = dlg.GetPathName();
		if(!IsNeedOpen(string))
		{
			return;
		}
	
		CString strExt;
		strExt = XGetExtension(string);
		strExt.MakeUpper();
		strExt.TrimLeft();
		strExt.TrimRight();
		if(strExt == "MSP")
		{
			OpenWorkspace(string);
		}
	}
}

void CMultisimDemoApp::OnUpdateOpenProject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMultisimDemoApp::OnSaveProject() 
{
	// TODO: Add your command handler code here
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	if(!strProjectName.IsEmpty())
	{
		CString string;
		string = m_strPath +strProjectName +".msp";
		m_pObj->SaveDocument(string);

		string.TrimLeft();
		string.TrimRight();
		string.MakeLower();
		POSITION pos1 = m_lstProjects.Find (string);
		if (pos1)
			m_lstProjects.RemoveAt (pos1);
		m_lstProjects.AddHead (string);

		m_pObj->SetModified(FALSE);
	}
}

void CMultisimDemoApp::OnUpdateSaveProject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!strProjectName.IsEmpty());
}

void CMultisimDemoApp::OnCloseProject() 
{
	// TODO: Add your command handler code here
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	
	CString string;
	string = m_strPath +strProjectName +".msp";
	m_pObj->SaveDocument(string);
	
	string.TrimLeft();
	string.TrimRight();
		string.MakeLower();
	POSITION pos = m_lstProjects.Find (string);
	if (pos)
		m_lstProjects.RemoveAt (pos);
	m_lstProjects.AddHead (string);
	m_pObj->ClearAllParam();
	m_pObj->ClearAllDbp();
	
	CloseAllDocuments(TRUE);
	strProjectName = "";
	m_strPath = "";
	pParent->UpdateTree();
}

void CMultisimDemoApp::OnUpdateCloseProject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!strProjectName.IsEmpty());
}

void CMultisimDemoApp::OnSaveAll() 
{
	// TODO: Add your command handler code here
	CMainFrame *pParent = STATIC_DOWNCAST(CMainFrame,AfxGetMainWnd());
	ASSERT_VALID(pParent);
	SaveAll();
	if(!strProjectName.IsEmpty())
	{
		CString string;
		string = m_strPath +strProjectName + _T(".msp");
		m_pObj->SaveDocument(string);
		
		string.TrimLeft();
		string.TrimRight();
		string.MakeLower();
		POSITION pos1 = m_lstProjects.Find (string);
		if (pos1)
			m_lstProjects.RemoveAt (pos1);
		m_lstProjects.AddHead (string);
	}
}

void CMultisimDemoApp::OnUpdateSaveAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	if(GetOpenDocumentCount() != 0 || !strProjectName.IsEmpty())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMultisimDemoApp::OnFileNew() 
{
	// TODO: Add your command handler code here
	m_pDocTemplate->OpenDocumentFile(NULL);
}

void CMultisimDemoApp::DoSaveSetting()
{
	CReg reg;
	if (reg.Create (HKEY_CURRENT_USER, REG_EDITPAD_IDE, KEY_WRITE))
    {
		DWORD dTest = 1;
		reg.SaveNumber( _T ("nTest0"), (DWORD)dTest);
		reg.SaveNumber( _T ("nSetVal0"), (DWORD)m_bGrid);
		reg.SaveNumber( _T ("nSetVal1"), (DWORD)m_bFreeFormDrawing);
		reg.SaveNumber( _T ("nSetVal2"), (DWORD)m_bGuide);
		reg.SaveNumber( _T ("nSetVal3"), (DWORD)m_bGridSnap);
		reg.SaveNumber( _T ("nSetVal4"), (DWORD)m_bNewSnap);
		reg.SaveNumber( _T ("nSetVal5"), (DWORD)m_bMargin);
		reg.SaveNumber( _T ("nSetVal6"), (DWORD)m_bShowPorts);
		reg.SaveNumber( _T ("nSetVal7"), (DWORD)m_bDrawingFromCenter);
		reg.SaveNumber( _T ("nSetVal8"), (DWORD)m_bGlueToShape);
		reg.SaveNumber( _T ("nSetVal9"), (DWORD)m_bGlueToSpot);



		reg.SaveNumber( _T ("nSetVal10"), (DWORD)gfxData.m_bExpandEditBoxCenter);
		reg.SaveNumber( _T ("nSetVal11"), (DWORD)gfxData.m_bFullFeaturePort);
		reg.SaveNumber( _T ("nSetVal12"), (DWORD)gfxData.m_bWithSnap);
		
		reg.SaveNumber( _T ("nSetVal13"), (DWORD)gfxData.m_bWithStyle);
		reg.SaveNumber( _T ("nSetVal14"), (DWORD)gfxData.m_bWithPortIndexShow);
		reg.SaveNumber( _T ("nSetVal15"), (DWORD)gfxData.m_bWithPinNumberShow);
//		reg.SaveNumber( _T ("nSetVal16"), (DWORD)gfxData.m_bfoWithPort);

		reg.SaveNumber( _T ("nSetVal17"), (DWORD)gfxData.m_nDefPortHeight);
		reg.SaveNumber( _T ("nSetVal18"), (DWORD)gfxData.m_nDefPortWidth);
		reg.SaveNumber( _T ("nSetVal19"), (DWORD)gfxData.m_nDefPortType);
		reg.SaveNumber( _T ("nSetVal20"), (DWORD)gfxData.m_nDefPortSide);
		reg.SaveNumber( _T ("nSetVal21"), (DWORD)gfxData.m_bUseDefaultPort);
		reg.SaveNumber( _T ("nSetVal22"), (DWORD)gfxData.m_nDefShapeHeight);

		reg.SaveNumber( _T ("nSetVal23"), (DWORD)m_bSnapToHelpLine);
		reg.SaveNumber( _T ("nSetVal24"), (DWORD)m_bSnapToIntersect);
		reg.SaveNumber( _T ("nSetVal25"), (DWORD)gfxData.m_bWithSnap);
		reg.SaveNumber( _T ("nSetVal26"), (DWORD)m_bListBar);
		reg.SaveNumber( _T ("nSetVal27"), (DWORD)m_bRuler);

		
    }
	reg.Close ();

}

void CMultisimDemoApp::DoLoadSetting()
{
	DWORD dTest = 0;
	CReg reg;
	if (reg.Create (HKEY_CURRENT_USER, REG_EDITPAD_IDE, KEY_READ))
	{
		reg.LoadNumber( _T ("nTest0"), &dTest);
		if(dTest == 1)
		{
			DWORD nTemp =1;
			reg.LoadNumber( _T ("nSetVal0"), &nTemp);
			if(nTemp == 1)
			{
				m_bGrid = TRUE;
			}
			else
			{
				m_bGrid = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal1"), &nTemp);
			if(nTemp == 1)
			{
				m_bFreeFormDrawing = TRUE;
			}
			else
			{
				m_bFreeFormDrawing = FALSE;
			}
			
			reg.LoadNumber( _T ("nSetVal2"), &nTemp);
			if(nTemp == 1)
			{
				m_bGuide = TRUE;
			}
			else
			{
				m_bGuide = FALSE;
			}
			
			reg.LoadNumber( _T ("nSetVal3"), &nTemp);
			if(nTemp == 1)
			{
				m_bGridSnap = TRUE;
			}
			else
			{
				m_bGridSnap = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal4"), &nTemp);
			if(nTemp == 1)
			{
				m_bNewSnap = TRUE;
			}
			else
			{
				m_bNewSnap = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal5"), &nTemp);
			if(nTemp == 1)
			{
				m_bMargin = TRUE;
			}
			else
			{
				m_bMargin = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal6"), &nTemp);
			if(nTemp == 1)
			{
				m_bShowPorts = TRUE;
			}
			else
			{
				m_bShowPorts = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal7"), &nTemp);
			if(nTemp == 1)
			{
				m_bDrawingFromCenter = TRUE;
			}
			else
			{
				m_bDrawingFromCenter = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal8"), &nTemp);
			if(nTemp == 1)
			{
				m_bGlueToShape = TRUE;
			}
			else
			{
				m_bGlueToShape = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal9"), &nTemp);
			if(nTemp == 1)
			{
				m_bGlueToSpot = TRUE;
			}
			else
			{
				m_bGlueToSpot = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal10"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bExpandEditBoxCenter = TRUE;
			}
			else
			{
				gfxData.m_bExpandEditBoxCenter = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal11"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bFullFeaturePort = TRUE;
			}
			else
			{
				gfxData.m_bFullFeaturePort = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal12"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithSnap = TRUE;
			}
			else
			{
				gfxData.m_bWithSnap = FALSE;
			}
			
			reg.LoadNumber( _T ("nSetVal13"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithStyle = TRUE;
			}
			else
			{
				gfxData.m_bWithStyle = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal14"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithPortIndexShow = TRUE;
			}
			else
			{
				gfxData.m_bWithPortIndexShow = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal15"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithPinNumberShow = TRUE;
			}
			else
			{
				gfxData.m_bWithPinNumberShow = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal16"), &nTemp);
// 			if(nTemp == 1)
// 			{
// 				gfxData.m_bfoWithPort = TRUE;
// 			}
// 			else
// 			{
// 				gfxData.m_bfoWithPort = FALSE;
// 			}
			reg.LoadNumber( _T ("nSetVal17"), &nTemp);
			gfxData.m_nDefPortHeight = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal18"), &nTemp);
			gfxData.m_nDefPortWidth = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal19"), &nTemp);
			gfxData.m_nDefPortType = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal20"), &nTemp);
			gfxData.m_nDefPortSide = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal21"), &nTemp);
			gfxData.m_bUseDefaultPort = (int)nTemp;
			reg.LoadNumber( _T ("nSetVal22"), &nTemp);
			gfxData.m_nDefShapeHeight = (int)nTemp;


			reg.LoadNumber( _T ("nSetVal23"), &nTemp);
			if(nTemp == 1)
			{
				m_bSnapToHelpLine = TRUE;
			}
			else
			{
				m_bSnapToHelpLine = FALSE;
			}

			reg.LoadNumber( _T ("nSetVal24"), &nTemp);
			if(nTemp == 1)
			{
				m_bSnapToIntersect = TRUE;
			}
			else
			{
				m_bSnapToIntersect = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal25"), &nTemp);
			if(nTemp == 1)
			{
				gfxData.m_bWithSnap = TRUE;
			}
			else
			{
				gfxData.m_bWithSnap = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal26"), &nTemp);
			if(nTemp == 1)
			{
				m_bListBar = TRUE;
			}
			else
			{
				m_bListBar = FALSE;
			}
			reg.LoadNumber( _T ("nSetVal27"), &nTemp);
			if(nTemp == 1)
			{
				m_bRuler = TRUE;
			}
			else
			{
				m_bRuler = FALSE;
			}

		}
		
    }
	reg.Close ();

	if(dTest == 0)
	{
		DoSaveSetting();
	}
}

void CMultisimDemoApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CString title;
	
	static char szFilter[] = _T("All Format (.Ms0;.msp;.scp)|*.Ms0;*.msp;*.scp|Screen Files(.Ms0)|*.Ms0|Script Files (.scp)|*.scp|Project Files(.msp)|*.msp|All Files(*.*)|*.*||");
	title = _T("MultisimDemo Editor");
	
	CMyFileDialog dlgFile (TRUE,NULL,NULL,OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,szFilter,AfxGetMainWnd());
	dlgFile.m_ofn.Flags |= OFN_ALLOWMULTISELECT;
	CString strFileNames;
	dlgFile.m_ofn.lpstrFile = strFileNames.GetBuffer(2048);
	dlgFile.m_ofn.nMaxFile = 2048;
	BOOL bRet = (dlgFile.DoModal() == IDOK) ? TRUE : FALSE;
	strFileNames.ReleaseBuffer();
	if (bRet)
	{
		POSITION pos = dlgFile.GetStartPosition();
		do{
			CString csfncbl =  dlgFile.GetNextPathName( pos);
			OpenDocumentFile(csfncbl);
			
		}while(pos!=NULL);
		
	}
}

void CMultisimDemoApp::OnNewScript() 
{
	// TODO: Add your command handler code here
	pCodeTemplate->OpenDocumentFile(NULL);
}

void CMultisimDemoApp::OnOpenSamples() 
{
	// TODO: Add your command handler code here
	CString strPathX = AfxGetApp()->m_pszHelpFilePath;
	strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
	CString strOtherFile;
	BeginWaitCursor();
	strOtherFile = strPathX+_T("\\TestProject\\testproject.msp");

	if(!IsNeedOpen(strOtherFile))
	{
		return;
	}
	
	CString strExt;
	strExt = XGetExtension(strOtherFile);
	strExt.MakeUpper();
	strExt.TrimLeft();
	strExt.TrimRight();
	if(strExt == "MSP")
	{
		OpenWorkspace(strOtherFile);
	}
	EndWaitCursor();
}

int CMultisimDemoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	DoSaveSetting();
	return CFOProjectApp::ExitInstance();
}

void CThreadTimer::CTThread_Func(LPVOID lpParam)
{
	CoInitialize(0);
	CThreadTimer *pCTime = (CThreadTimer *)lpParam;
	for(;;)
	{
		DWORD dwWait = WaitForMultipleObjects(2, pCTime->m_hCTHandles, FALSE, INFINITE);
		if(pCTime->m_emThreaEvent == CTEExit)
			break;
		if(dwWait == WAIT_OBJECT_0+1 && pCTime->m_bSetTimer)
		{
			pCTime->OnThreadTimer();
		}
	}
	
	TRACE(_T("CThreadTimer::ThreadTimer Exit Normaly>>>>>>>>>>\n"));
	CoUninitialize();
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreadTimer::CThreadTimer():
m_hCTThread(NULL),m_lpcfFunc(NULL),m_lpUserData(NULL),
m_bSetTimer(FALSE)
{
	idEvent = 0;
	memset(m_hCTHandles, 0, sizeof(HANDLE)*CT_HANDLE_COUNT);
}

CThreadTimer::~CThreadTimer()
{
	Close();
}

BOOL CThreadTimer::Open()
{
	if(IsOpen())return TRUE;


	m_hCTHandles[CT_HANDLE_TEVENT] = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hCTHandles[CT_HANDLE_TTIMER] = CreateWaitableTimer(NULL, FALSE, NULL);

	m_emThreaEvent = CTECheck;
	m_hCTThread = (HANDLE)_beginthread(CTThread_Func, 0, this);
	if(!IsOpen())
	{
		Close();
		return FALSE;
	}

	return TRUE;
}

void CThreadTimer::Close()
{
	CancelTimer();
	ExitThread();
	
	if(m_hCTHandles[CT_HANDLE_TEVENT])
	{
		CloseHandle(m_hCTHandles[CT_HANDLE_TEVENT]);
		m_hCTHandles[CT_HANDLE_TEVENT] = NULL;
	}

	if(m_hCTHandles[CT_HANDLE_TTIMER])
	{
		CancelWaitableTimer(m_hCTHandles[CT_HANDLE_TTIMER]);
		CloseHandle(m_hCTHandles[CT_HANDLE_TTIMER]);
		m_hCTHandles[CT_HANDLE_TTIMER] = NULL;
	}
}

BOOL CThreadTimer::IsOpen()const
{
	if(m_hCTThread==NULL)
		return FALSE;

	return (WaitForSingleObject(m_hCTThread, 0)==WAIT_TIMEOUT);
}

UINT CThreadTimer::SetTimer(UINT nIDEvent, LONG lElapseMS, ThreadTimerProc lpFunc, LPVOID lpUser)
{
	m_lpcfFunc = lpFunc;
	m_lpUserData = lpUser;
	idEvent = nIDEvent;
	LARGE_INTEGER liUTC = {0};
	if(!SetWaitableTimer(m_hCTHandles[CT_HANDLE_TTIMER], &liUTC, lElapseMS, NULL, NULL, TRUE))
		return FALSE;

	m_bSetTimer = TRUE;
	return nIDEvent;
}

void CThreadTimer::CancelTimer()
{
	if(m_hCTHandles[CT_HANDLE_TTIMER]==NULL)return;
	if(IsTimerSet())
	{
		m_bSetTimer = FALSE;
		CancelWaitableTimer(m_hCTHandles[CT_HANDLE_TTIMER]);
	}
}

void CThreadTimer::ExitThread()
{
	if(m_hCTThread == NULL)
		return;

	SetThreadEvent(CTEExit);
	if(WaitForSingleObject(m_hCTThread, 5000) == WAIT_TIMEOUT)
	{
		TerminateThread(m_hCTThread, 1);
	}
	m_hCTThread = NULL;
}

void CThreadTimer::SetThreadEvent(CTEvent Event)
{
	m_emThreaEvent = Event;
	SetEvent(m_hCTHandles[CT_HANDLE_TEVENT]);
}

void CThreadTimer::OnThreadTimer()
{
	if(m_bSetTimer && (m_lpcfFunc != NULL))
		m_lpcfFunc(m_lpUserData, idEvent);
}
