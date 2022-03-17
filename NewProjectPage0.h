#if !defined(AFX_NEWPROJECTPAGE0_H__FED35386_E868_11DA_8D99_AAE03EA530FF__INCLUDED_)
#define AFX_NEWPROJECTPAGE0_H__FED35386_E868_11DA_8D99_AAE03EA530FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProjectPage0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage0 dialog
#include "NewWizPage.h"
 
//===========================================================================
// Summary:
//     The CNewProjectPage0 class derived from CNewWizPage
//      New Project Page0
//===========================================================================

class CNewProjectPage0 : public CNewWizPage
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Project Page0, Constructs a CNewProjectPage0 object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CNewProjectPage0(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewProjectPage0)
	enum { IDD = IDD_DIALOG_NEWPAGE0 };
 
	// m_listCtrl, This member specify CListCtrl object.  
	CListCtrl	m_listCtrl;
 
	// m_edtPath, This member specify CEdit object.  
	CEdit	m_edtPath;
 
	// m_strPath, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strPath;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
 
	// strPath, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strPath;
 
	// Project Name, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strProjectName;
 
	// Images New, This member is a collection of same-sized images.  
	CImageList			m_pImagesNew;
 
	// Document Type, This variable specifies a 32-bit signed integer on 32-bit platforms.  
 	int nDocType; 
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Wizard Next, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns A 32-bit value returned from a window procedure or callback function.
	LRESULT OnWizardNext();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Browse For Folder, None Description.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		strPath---strPath, Specifies A CString type value.
	BOOL BrowseForFolder( CString& strPath );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectPage0)
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

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewProjectPage0)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Change Edit1, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnChangeEdit1();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Change Edit3, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnChangeEdit3();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Killfocus Edit1, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnKillfocusEdit1();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Click List1, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Double click List1, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Button1, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnButton1();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECTPAGE0_H__FED35386_E868_11DA_8D99_AAE03EA530FF__INCLUDED_)
