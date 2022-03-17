// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__6EB9193F_17F6_43F7_A44A_C1058DB67CD4__INCLUDED_)
#define AFX_CHILDFRM_H__6EB9193F_17F6_43F7_A44A_C1058DB67CD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExtListBar.h"
 
class CExtTabModel; 
//===========================================================================
// Summary:
//     The CChildFrame class derived from CFOPMDIChildWnd
//      Child Frame
//===========================================================================

class CChildFrame : public CFOPMDIChildWnd
{
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N C R E A T E, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CChildFrame---Child Frame, Specifies a CChildFrame object.
	DECLARE_DYNCREATE(CChildFrame)
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Child Frame, Constructs a CChildFrame object.
	//		Returns A  value.
	CChildFrame();

// Attributes
public:
	
	BOOL IsPageExist(const CString &str);
	CFOTabPageModel *AddNewPage2(const CString &strTitle);

	// Add new page.
	CString AddNew(CExtTabModel *pModel);
	
	// Delete page.
	void DeleteTab(const CString &strPage);
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Activate Page, Activates the specified object.
	// Parameters:
	//		&strPage---&strPage, Specifies A CString type value.
	void ActivatePage(const CString &strPage);

	//-----------------------------------------------------------------------
	// Summary:
	// Do Add New Page, Do a event. 
	//		Returns a CString type value.
	CString DoAddNewPage();

	// List Bar, This member specify CExtListBar object.  
	CExtListBar		   m_ListBar;

	CFOPFlatComboBox* GetPageBox();
public:
	// Status Bar, This member specify E-XD++ CFOPStatusBar object.  
	CFOPTabBar     m_wndStatusBar;
	virtual void OnHome();
	virtual void OnPrev();
	virtual void OnNext();
	virtual void OnDel();
	virtual void OnAdd();
	virtual void PageChange(const int &nIndex);
	void UpdateBox();
// Operations
public:

	// Goto a specify page.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Go To Page, None Description.
	// Parameters:
	//		&nPage---&nPage, Specifies A integer value.
	void GoToPage(const int &nPage);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Create Window, Called before the creation of the Windows window attached to this CWnd object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		cs---Specifies a CREATESTRUCT& cs object.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//E-XD++ Library add lines.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Create Client, Called as a part of window creation.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpcs---Specifies a LPCREATESTRUCT lpcs object.  
	//		pContext---pContext, A pointer to the CCreateContext or NULL if the call failed.
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Activate Frame, Activates the specified object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nCmdShow---Cmd Show, Specifies A integer value.
	virtual void ActivateFrame(int nCmdShow);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Child Frame, Destructor of class CChildFrame
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CChildFrame();
#ifdef _DEBUG
	
	//-----------------------------------------------------------------------
	// Summary:
	// Assert Valid, Assert performs a validity check on this object by checking its internal state.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void AssertValid() const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Dump, Dumps the contents of your object to a CDumpContext object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		dc---Specifies a CDumpContext& dc object.
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Create, Called as a part of window creation.
	//		Returns a int type value.  
	// Parameters:
	//		LPCREATESTRUCT---P C R E A T E S T R U C T, Specifies a LPCREATESTRUCT LPCREATESTRUCT object.
	afx_msg int OnCreate(LPCREATESTRUCT LPCREATESTRUCT);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Fo Add Newpage, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFoAddNewpage();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Fo Remove Page, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFoRemovePage();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On View Toolbox, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnViewToolbox();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update View Toolbox, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateViewToolbox(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Move Previous, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMovePrevious();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Move Previous, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateMovePrevious(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Move Next, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMoveNext();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Move Next, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateMoveNext(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Mb Createpage Copy, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnMbCreatepageCopy();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Mb Createpage Copy, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateMbCreatepageCopy(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Destroy, Called when CWnd is being destroyed.

	afx_msg void OnDestroy();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

 
//===========================================================================
// Summary:
//     The CCodeChildFrame class derived from CFOPMDIChildWnd
//      Code Child Frame
//===========================================================================

class CCodeChildFrame : public CFOPMDIChildWnd
{
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N C R E A T E, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CCodeChildFrame---Code Child Frame, Specifies a CCodeChildFrame object.
	DECLARE_DYNCREATE(CCodeChildFrame)
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Code Child Frame, Constructs a CCodeChildFrame object.
	//		Returns A  value.
	CCodeChildFrame();
	
	// Attributes
public:
 
	// m_wndSplitter, This member specify CSplitterWnd object.  
	CSplitterWnd m_wndSplitter;
	
	// Operations
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeChildFrame)
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Create Window, Called before the creation of the Windows window attached to this CWnd object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		cs---Specifies a CREATESTRUCT& cs object.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Activate Frame, Activates the specified object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nCmdShow---Cmd Show, Specifies A integer value.
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Code Child Frame, Destructor of class CCodeChildFrame
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CCodeChildFrame();
#ifdef _DEBUG
	
	//-----------------------------------------------------------------------
	// Summary:
	// Assert Valid, Assert performs a validity check on this object by checking its internal state.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void AssertValid() const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Dump, Dumps the contents of your object to a CDumpContext object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		dc---Specifies a CDumpContext& dc object.
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CCodeChildFrame)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Create, Called as a part of window creation.
	//		Returns a int type value.  
	// Parameters:
	//		LPCREATESTRUCT---P C R E A T E S T R U C T, Specifies a LPCREATESTRUCT LPCREATESTRUCT object.
	afx_msg int OnCreate(LPCREATESTRUCT LPCREATESTRUCT);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__6EB9193F_17F6_43F7_A44A_C1058DB67CD4__INCLUDED_)
