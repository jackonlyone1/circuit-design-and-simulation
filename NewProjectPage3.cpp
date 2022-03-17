// NewProjectPage3.cpp : implementation file
//

#include "stdafx.h"
#include "MultisimDemo.h"
#include "NewProjectMain.h"
#include "NewProjectPage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage3 dialog

#define CLASS_TIPS2 "This Library is the essential reference for developers, with more than a gigabyte of technical programming information, including sample code, documentation, technical articles"
CNewProjectPage3::CNewProjectPage3(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CNewProjectPage3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProjectPage3)
	m_strRemark = _T(" ");
	m_strAuthor = _T("");
	m_strDepartment = _T("");
	m_strEMail = _T("mailto:");
	m_strURL = _T("http://");
	m_strCompany = _T("");
	m_strCopyright = _T("");
	//}}AFX_DATA_INIT
	nOldLangType = 0;
}


void CNewProjectPage3::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProjectPage3)
	DDX_Text(pDX, IDC_EDIT_SYS1, m_strRemark);
	DDX_Text(pDX, IDC_EDIT_SYS2, m_strAuthor);
	DDX_Text(pDX, IDC_EDIT_SYS3, m_strDepartment);
	DDX_Text(pDX, IDC_EDIT_SYS4, m_strEMail);
	DDX_Text(pDX, IDC_EDIT_SYS5, m_strURL);
	DDX_Text(pDX, IDC_EDIT_SYS6, m_strCompany);
	DDX_Text(pDX, IDC_EDIT_SYS7, m_strCopyright);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProjectPage3, CNewWizPage)
	//{{AFX_MSG_MAP(CNewProjectPage3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage3 message handlers

BOOL CNewProjectPage3::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	GetDlgItem(IDC_EDIT_SYS1)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_EDIT_SYS2)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_EDIT_SYS3)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_EDIT_SYS4)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_EDIT_SYS5)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_EDIT_SYS6)->SetFont(&gfxData.fontBold);
	GetDlgItem(IDC_EDIT_SYS7)->SetFont(&gfxData.fontBold);

	GetDlgItem(IDC_EDIT_SYS2)->SetWindowText("Author Name");
	GetDlgItem(IDC_EDIT_SYS6)->SetWindowText("Author Company Name");
	GetDlgItem(IDC_EDIT_SYS7)->SetWindowText("(C)Copyright ? 2000,All Rights Reversed");
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
// refer to CPropertyPage class members for a description of this function
BOOL CNewProjectPage3::OnWizardFinish()
{
	GetDlgItem(IDC_EDIT_SYS1)->GetWindowText(m_strRemark);
	GetDlgItem(IDC_EDIT_SYS2)->GetWindowText(m_strAuthor);
	GetDlgItem(IDC_EDIT_SYS3)->GetWindowText(m_strDepartment);
	GetDlgItem(IDC_EDIT_SYS4)->GetWindowText(m_strEMail);
	GetDlgItem(IDC_EDIT_SYS5)->GetWindowText(m_strURL);
	GetDlgItem(IDC_EDIT_SYS6)->GetWindowText(m_strCompany);
	GetDlgItem(IDC_EDIT_SYS7)->GetWindowText(m_strCopyright);
	return CNewWizPage::OnWizardFinish();
}

void CNewProjectPage3::OnSetActive()
{
	CNewProjectMain *pDlg = (CNewProjectMain *)m_pParent;
	if(pDlg->nOldLangType != nOldLangType)
	{
		nOldLangType = pDlg->nOldLangType;
		switch(nOldLangType)
		{
		case 1000:
			{
//				m_strRemark = CLASS_TIPS;
//				GetDlgItem(IDC_EDIT_SYS1)->SetWindowText(m_strRemark);
			}

			break;
		}
	}
}

BOOL CNewProjectPage3::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		return TRUE;
	}

	return CNewWizPage::PreTranslateMessage(pMsg);
}
