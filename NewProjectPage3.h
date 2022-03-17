#if !defined(AFX_NEWPROJECTPAGE3_H__1F9EB987_2419_11DB_97E2_A12D0D642CF1__INCLUDED_)
#define AFX_NEWPROJECTPAGE3_H__1F9EB987_2419_11DB_97E2_A12D0D642CF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProjectPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage3 dialog
#include "NewWizPage.h"

 
//===========================================================================
// Summary:
//     The CNewProjectPage3 class derived from CNewWizPage
//      New Project Page3
//===========================================================================

class CNewProjectPage3 : public CNewWizPage
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Project Page3, Constructs a CNewProjectPage3 object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CNewProjectPage3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewProjectPage3)
	enum { IDD = IDD_DIALOG_NEWPAGE3 };
 
	// m_strRemark, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strRemark;
 
	// m_strAuthor, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strAuthor;
 
	// m_strDepartment, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strDepartment;
 
	// E Mail, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strEMail;
 
	// U R L, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strURL;
 
	// m_strCompany, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strCompany;
 
	// m_strCopyright, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strCopyright;
	//}}AFX_DATA
 
	// Old Lang Type, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT nOldLangType;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectPage3)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Translate Message, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pMsg---pMsg, A pointer to the MSG or NULL if the call failed.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Data Exchange, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDX---D X, A pointer to the CDataExchange or NULL if the call failed.
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Wizard Finish, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnWizardFinish();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Set Active, This member function is called by the framework to allow your application to handle a Windows message.

	void OnSetActive();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewProjectPage3)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECTPAGE3_H__1F9EB987_2419_11DB_97E2_A12D0D642CF1__INCLUDED_)
