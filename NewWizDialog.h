#if !defined(AFX_NEWWIZDIALOG_H__915D4C89_2E27_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_NEWWIZDIALOG_H__915D4C89_2E27_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewWizDialog.h : header file
//

class CNewWizPage;

/////////////////////////////////////////////////////////////////////////////
// CNewWizDialog dialog

 
//===========================================================================
// Summary:
//     The CNewWizDialog class derived from CDialog
//      New Wiz Dialog
//===========================================================================

class CNewWizDialog : public CDialog
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Wiz Dialog, Constructs a CNewWizDialog object.
	//		Returns A  value.  
	// Parameters:
	//		lpszTemplate---lpszTemplate, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CNewWizDialog (LPCTSTR lpszTemplate, CWnd* pParent = NULL);
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Wiz Dialog, Constructs a CNewWizDialog object.
	//		Returns A  value.  
	// Parameters:
	//		nIDTemplate---I D Template, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
  CNewWizDialog (UINT nIDTemplate, CWnd* pParent = NULL);
	
	//-----------------------------------------------------------------------
	// Summary:
	// C New Wiz Dialog, Destructor of class CNewWizDialog
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
  virtual ~CNewWizDialog ();


// Attributes
public:
 
	// m_Classes, The member supports arrays of CString objects.  
	CStringArray m_Classes;
 
	// nPages, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int nPages;
 
	// Insert Class, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strInsertClass;
 
	// Sheet Class, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strSheetClass;
protected:
 
	// Page List, This member specify CObList object.  
	CObList m_PageList; // this list of CNewWizPage objects
 
	// Placeholder I D, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
  UINT m_nPlaceholderID; // control ID for the palceholder


// Operations
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Page, Adds an object to the specify list.
	// Parameters:
	//		pPage---pPage, A pointer to the CNewWizPage or NULL if the call failed.  
	//		nID---I D, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void AddPage(CNewWizPage* pPage, UINT nID);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Active Page By Resource, Sets a specify value to current class CNewWizDialog
	// Parameters:
	//		nResourceID---Resource I D, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
  void SetActivePageByResource(UINT nResourceID);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set First Page, Sets a specify value to current class CNewWizDialog
	//		Returns TRUE on success; FALSE otherwise.
  BOOL SetFirstPage();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Next Page, Sets a specify value to current class CNewWizDialog

  void SetNextPage();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Focus And Default, Sets a specify value to current class CNewWizDialog
	// Parameters:
	//		*pPage---*pPage, A pointer to the CNewWizPage  or NULL if the call failed.
	void SetFocusAndDef(CNewWizPage *pPage);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Enable Finish, Call this member function to enable or disable the specify object for this command.
	// Parameters:
	//		bEnable---bEnable, Specifies A Boolean value.
	void EnableFinish(BOOL bEnable);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Enable Back, Call this member function to enable or disable the specify object for this command.
	// Parameters:
	//		bEnable---bEnable, Specifies A Boolean value.
	void EnableBack(BOOL bEnable);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Enable Next, Call this member function to enable or disable the specify object for this command.
	// Parameters:
	//		bEnable---bEnable, Specifies A Boolean value.
	void EnableNext(BOOL bEnable);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Active Index, Returns the specified value.
	//		Returns a int type value.
	int GetActiveIndex() const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Page Index, Returns the specified value.
	//		Returns a int type value.  
	// Parameters:
	//		pPage---pPage, A pointer to the CNewWizPage or NULL if the call failed.
	int GetPageIndex(CNewWizPage* pPage) const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Page Count, Returns the specified value.
	//		Returns a int type value.
	int GetPageCount();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Page, Returns the specified value.
	//		Returns a pointer to the object CNewWizPage,or NULL if the call failed  
	// Parameters:
	//		nPage---nPage, Specifies A integer value.
	CNewWizPage* GetPage(int nPage) const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Active Page, Sets a specify value to current class CNewWizDialog
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		nPage---nPage, Specifies A integer value.
	BOOL SetActivePage(int nPage);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Active Page, Sets a specify value to current class CNewWizDialog
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pPage---pPage, A pointer to the CNewWizPage or NULL if the call failed.
	BOOL SetActivePage(CNewWizPage* pPage);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Title, Sets a specify value to current class CNewWizDialog
	// Parameters:
	//		lpszText---lpszText, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	void SetTitle(LPCTSTR lpszText);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Title, Sets a specify value to current class CNewWizDialog
	// Parameters:
	//		nIDText---I D Text, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void SetTitle(UINT nIDText);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Finish Text, Sets a specify value to current class CNewWizDialog
	// Parameters:
	//		lpszText---lpszText, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	void SetFinishText(LPCTSTR lpszText);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Finish Text, Sets a specify value to current class CNewWizDialog
	// Parameters:
	//		nIDText---I D Text, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void SetFinishText(UINT nIDText);

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Activate Page, Activates the specified object.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pPage---pPage, A pointer to the CNewWizPage or NULL if the call failed.
  BOOL ActivatePage(CNewWizPage* pPage);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Deactivate Page, None Description.
	//		Returns TRUE on success; FALSE otherwise.
  BOOL DeactivatePage();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Placeholder I D, Sets a specify value to current class CNewWizDialog
	// Parameters:
	//		nPlaceholderID---Placeholder I D, Specifies A integer value.
	void SetPlaceholderID(int nPlaceholderID);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Page By Resource I D, Returns the specified value.
	//		Returns a pointer to the object CNewWizPage,or NULL if the call failed  
	// Parameters:
	//		nResourceID---Resource I D, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	CNewWizPage* GetPageByResourceID(UINT nResourceID);


private:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial, Call Init after creating a new object.

  void Init();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Destroy Page, Call this function to destroy an existing object.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pPage---pPage, A pointer to the CNewWizPage or NULL if the call failed.
  BOOL DestroyPage(CNewWizPage* pPage);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get First Page, Returns the specified value.
	//		Returns a pointer to the object CNewWizPage,or NULL if the call failed
  CNewWizPage* GetFirstPage();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Last Page, Returns the specified value.
	//		Returns a pointer to the object CNewWizPage,or NULL if the call failed
  CNewWizPage* GetLastPage();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Active Page, Returns the specified value.
	//		Returns a pointer to the object CNewWizPage,or NULL if the call failed
  CNewWizPage* GetActivePage() const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Next Page, Returns the specified value.
	//		Returns a pointer to the object CNewWizPage,or NULL if the call failed
  CNewWizPage* GetNextPage();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewWizDialog)
	protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Data Exchange, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDX---D X, A pointer to the CDataExchange or NULL if the call failed.
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewWizDialog)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Destroy, Called when CWnd is being destroyed.

	afx_msg void OnDestroy();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Wizard Finish, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnWizardFinish();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Wizard Back, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnWizardBack(); 
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Wizard Next, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnWizardNext(); 
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Cancel, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnCancel(); 
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWWIZDIALOG_H__915D4C89_2E27_11D4_9FA9_0030DB0011C6__INCLUDED_)
