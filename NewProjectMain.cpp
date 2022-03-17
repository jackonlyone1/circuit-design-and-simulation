// NewProjectMain.cpp : implementation file
//

#include "stdafx.h"
#include "MultisimDemo.h"
#include "NewProjectMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProjectMain dialog


CNewProjectMain::CNewProjectMain(CWnd* pParent /*=NULL*/)
	: CNewWizDialog(CNewProjectMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProjectMain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	nOldLangType = 1000;
}


void CNewProjectMain::DoDataExchange(CDataExchange* pDX)
{
	CNewWizDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProjectMain)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProjectMain, CNewWizDialog)
	//{{AFX_MSG_MAP(CNewProjectMain)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectMain message handlers

BOOL CNewProjectMain::OnInitDialog() 
{
	SetPlaceholderID(IDC_SHEETRECT);
	CNewWizDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
