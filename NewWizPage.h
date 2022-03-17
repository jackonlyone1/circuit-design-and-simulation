#if !defined(AFX_NEWWIZPAGE_H__915D4C8B_2E27_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_NEWWIZPAGE_H__915D4C8B_2E27_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewWizPage.h : header file
//

class CNewWizDialog;

/////////////////////////////////////////////////////////////////////////////
// CNewWizPage dialog

 
//===========================================================================
// Summary:
//     The CNewWizPage class derived from CDialog
//      New Wiz Page
//===========================================================================

class CNewWizPage : public CDialog
{
 
	// New Wiz Dialog, This member specify friend class object.  
  friend class CNewWizDialog;

// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Wiz Page, Constructs a CNewWizPage object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CNewWizPage(CWnd* pParent = NULL);   // standard constructor

	
	//-----------------------------------------------------------------------
	// Summary:
	// New Wiz Page, Constructs a CNewWizPage object.
	//		Returns A  value.  
	// Parameters:
	//		lpszTemplateName---Template Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CNewWizPage(LPCTSTR lpszTemplateName, CWnd* pParent = NULL);
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Wiz Page, Constructs a CNewWizPage object.
	//		Returns A  value.  
	// Parameters:
	//		nIDTemplate---I D Template, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
  CNewWizPage(UINT nIDTemplate, CWnd* pParent = NULL);
	
	//-----------------------------------------------------------------------
	// Summary:
	// C New Wiz Page, Destructor of class CNewWizPage
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
  virtual ~CNewWizPage();

// Attributes
public:
 
	// Large Font, The CFont class encapsulates a Windows graphics device interface (GDI) font and provides member functions for manipulating the font.  
	CFont m_LargeFont; // a large font for any titles we may want

protected:
 
	// m_Brush, The CBrush class encapsulates a Windows graphics device interface (GDI) brush.  
	CBrush m_Brush; // brush for white background
 
	// m_pParent, This member maintains a pointer to the object CNewWizDialog.  
  CNewWizDialog *m_pParent; // Parent dialog

private:
 
	// m_bCreated, This member sets TRUE if it is right.  
  BOOL m_bCreated; // flag to tell us if the dialog has been created
 
	// m_bActive, This member sets TRUE if it is right.  
  BOOL m_bActive;		// flag to tell is if the dialog is the active page
 
	// Dialog I D, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
  UINT m_nDialogID; // resource ID for thie page


// Operations
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Create Page, Called as a part of window creation.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
  virtual BOOL OnCreatePage();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Destroy Page, Called when CWnd is being destroyed.
	// This member function is also a virtual function, you can Override it if you need,
  virtual void OnDestroyPage();

	// these functions are the same as CPropertyPage
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Cancel, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnCancel();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Kill Active, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
  virtual BOOL OnKillActive();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Set Active, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
  virtual void OnSetActive();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Query Cancel, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		---Specifies a  object.
	virtual BOOL OnQueryCancel( );
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Wizard Back, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A 32-bit value returned from a window procedure or callback function.
	virtual LRESULT OnWizardBack();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Wizard Next, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A 32-bit value returned from a window procedure or callback function.
	virtual LRESULT OnWizardNext();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Wizard Finish, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnWizardFinish();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Update List, Call this member function to update the object.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void UpdateList();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewWizPage)
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
	//{{AFX_MSG(CNewWizPage)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Ctl Color, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns A afx_msg HBRUSH value.  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.  
	//		pWnd---pWnd, A pointer to the CWnd or NULL if the call failed.  
	//		nCtlColor---Ctl Color, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWWIZPAGE_H__915D4C8B_2E27_11D4_9FA9_0030DB0011C6__INCLUDED_)
