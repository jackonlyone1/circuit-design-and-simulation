// CodeEditView.h : interface of the CCodeEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEEDITVIEW_H__DCA986CB_57A6_4F7A_BF2B_E2F7199744AE__INCLUDED_)
#define AFX_CODEEDITVIEW_H__DCA986CB_57A6_4F7A_BF2B_E2F7199744AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////
// FOCodeUndo
#include<iostream>
struct FOCodeUndo
{
	enum eWhat {eHead, eDelete, eInsert};

	eWhat m_eWhat;
	int m_iStart;
	int m_iEnd;
	std::basic_string<TCHAR> m_strText;
	bool m_bTransaction;
	FOCodeUndo *m_pPrev;
	FOCodeUndo *m_pNext;

	FOCodeUndo (const eWhat what, const int iStart,
		const int iEnd, FOCodeUndo *pPrev) :
		m_eWhat (what),
		m_iStart (iStart),
		m_iEnd (iEnd),
		m_bTransaction (false),
		m_pPrev (pPrev),
		m_pNext (0)
	{
	}
};

/////////////////////////////////////////
// CCodeEditView
 
 
//===========================================================================
// Summary:
//     The CCodeEditView class derived from CEditView
//      Code Edit View
//===========================================================================

class CCodeEditView : public CEditView
{
	enum e_Alignment {eLeft, eCentre, eRight};

protected: // create from serialization only
	
	//-----------------------------------------------------------------------
	// Summary:
	// Code Edit View, Constructs a CCodeEditView object.
	//		Returns A  value.
	CCodeEditView ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N C R E A T E, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CCodeEditView---Code Edit View, Specifies a CCodeEditView object.
	DECLARE_DYNCREATE (CCodeEditView)

// Attributes
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Document, Returns the specified value.
	//		Returns a pointer to the object CCodeDocument ,or NULL if the call failed
	CCodeDocument *GetDocument ();
	
	// Image data.
	CFOPMenuTheme *		m_pMenuData;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Start Timer, None Description.
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	void StartTimer (LPCTSTR lpszPathName);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Stop Timer, Call this function to stop

	void StopTimer ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Word Wrap Enabled, Determines if the given value is correct or exist.
	//		Returns A Boolean value.
	bool IsWordWrapEnabled () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Read Only Enabled, Determines if the given value is correct or exist.
	//		Returns A Boolean value.
	bool IsReadOnlyEnabled () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Insert Time Date, Inserts a child object at the given index..
	// Parameters:
	//		bCRLF---C R L F, Specifies A Boolean value.
	void InsertTimeDate (const bool bCRLF);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Display Error Message, None Description.
	// Parameters:
	//		&str---Specifies A CString type value.
	void DisplayErrorMsg (const CString &str);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Sel, Sets a specify value to current class CCodeEditView
	// Parameters:
	//		iStart---iStart, Specifies A integer value.  
	//		iEnd---iEnd, Specifies A integer value.  
	//		bNoScroll---No Scroll, Specifies A Boolean value.
	void SetSel (const int iStart, const int iEnd,
		const BOOL bNoScroll = FALSE);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Sel, Returns the specified value.
	// Parameters:
	//		&iStart---&iStart, Specifies A integer value.  
	//		&iEnd---&iEnd, Specifies A integer value.
	void GetSel (int &iStart, int &iEnd);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Replace Sel With Undo, None Description.
	// Parameters:
	//		*pszText---*pszText, A pointer to the const TCHAR  or NULL if the call failed.  
	//		iStart---iStart, Specifies A integer value.  
	//		iEnd---iEnd, Specifies A integer value.  
	//		bDoInsert---Do Insert, Specifies A Boolean value.
	void ReplaceSelWithUndo (const TCHAR *pszText,
		int iStart = -1, int iEnd = -1, const bool bDoInsert = true);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Del Sel With Undo, None Description.
	// Parameters:
	//		iStart---iStart, Specifies A integer value.  
	//		iEnd---iEnd, Specifies A integer value.  
	//		*pszBuffer---*pszBuffer, A pointer to the const TCHAR  or NULL if the call failed.
	void DelSelWithUndo (int iStart, int iEnd,
		const TCHAR *pszBuffer = 0);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear Undo History, Remove the specify data from the list.
	// Parameters:
	//		bModifiedBeforeFirstUndo---Modified Before First Undo, Specifies A Boolean value.
	void ClearUndoHistory (const bool bModifiedBeforeFirstUndo);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeEditView)
	public:
	virtual void OnDraw (CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragEnter (COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver (COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop (COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnBeginPrinting (CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint (CDC* pDC, CPrintInfo* pInfo);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Code Edit View, Destructor of class CCodeEditView
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CCodeEditView ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Toggle Word Wrap, None Description.

	void ToggleWordWrap ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Toggle Read Only, None Description.

	void ToggleReadOnly ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Re Create Window, None Description.
	// Parameters:
	//		bWordWrap---Word Wrap, Specifies A Boolean value.  
	//		bReadOnly---Read Only, Specifies A Boolean value.
	void ReCreateWindow (const bool bWordWrap, const bool bReadOnly);
#ifdef _DEBUG
	
	//-----------------------------------------------------------------------
	// Summary:
	// Assert Valid, Assert performs a validity check on this object by checking its internal state.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void AssertValid () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Dump, Dumps the contents of your object to a CDumpContext object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		dc---Specifies a CDumpContext& dc object.
	virtual void Dump (CDumpContext& dc) const;
#endif

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear Undos, Remove the specify data from the list.
	// Parameters:
	//		*pUndo---*pUndo, A pointer to the FOCodeUndo  or NULL if the call failed.
	void ClearUndos (FOCodeUndo *pUndo);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Prepare Printing, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		*pInfo---*pInfo, A pointer to the CPrintInfo  or NULL if the call failed.
	virtual BOOL OnPreparePrinting (CPrintInfo *pInfo);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Print Header Footer, None Description.
	// Parameters:
	//		&str---Specifies A CString type value.  
	//		bHeader---bHeader, Specifies A Boolean value.  
	//		iWidth---iWidth, Specifies A integer value.  
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		*pInfo---*pInfo, A pointer to the CPrintInfo  or NULL if the call failed.
	void PrintHeaderFooter (const CString &str, const bool bHeader,
		const int iWidth, CDC *pDC, CPrintInfo *pInfo);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Format Header Footer, None Description.
	// Parameters:
	//		&strHeaderFooter---Header Footer, Specifies A CString type value.  
	//		iPage---iPage, Specifies A integer value.  
	//		&eAlignment---&eAlignment, Specifies a e_Alignment &eAlignment object.
	void FormatHeaderFooter (CString &strHeaderFooter, const int iPage,
		e_Alignment &eAlignment);

// Generated message map functions
protected:
	//{{AFX_MSG(CCodeEditView)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Create, Called as a part of window creation.
	//		Returns a int type value.  
	// Parameters:
	//		lpCreateStruct---Create Struct, Specifies a LPCREATESTRUCT lpCreateStruct object.
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Destroy, Called when CWnd is being destroyed.

	afx_msg void OnDestroy ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update File Save, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update File Save As, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On File Page Setup, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFilePageSetup();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Edit Undo, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Edit Undo, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnEditUndo ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Edit Redo, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Edit Redo, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnEditRedo ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Edit Clear Undo History, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateEditClearUndoHistory (CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Edit Clear Undo History, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnEditClearUndoHistory ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Edit Find, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnEditFind ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Edit Repeat, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnEditRepeat ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Edit Replace, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnEditReplace ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Edit Goto, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnEditGoto ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Edit Timedate, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnEditTimedate ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Edit Paste, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateEditPaste (CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Need Find, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateNeedFind (CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Not Read Only, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateNotReadOnly (CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Options Scroll To End, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateOptionsScrollToEnd(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Options Scroll To End, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnOptionsScrollToEnd();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Options File Change Notify, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateOptionsFileChangeNotify(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Options File Change Notify, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnOptionsFileChangeNotify();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Format Word Wrap, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateFormatWordWrap (CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Format Read Only, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateFormatReadOnly(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Format Word Wrap, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFormatWordWrap ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Format Read Only, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFormatReadOnly();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Format Font, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFormatFont ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Notify File Change, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns A 32-bit value returned from a window procedure or callback function.  
	// Parameters:
	//		wParam---wParam, Provides additional information used in processing the message. The parameter value depends on the message.  
	//		lParam---lParam, Specifies A lparam value.
	afx_msg LRESULT OnNotifyFileChange (WPARAM wParam, LPARAM lParam);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Down, Called when the user presses the left mouse button.
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Options Auto Reload, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateOptionsAutoReload(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Options Auto Reload, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnOptionsAutoReload();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Timer, Called after each interval specified in SetTimer.
	// Parameters:
	//		nIDEvent---I D Event, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	afx_msg void OnTimer(UINT nIDEvent);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Char, Handle WM_CHAR message.
	// Parameters:
	//		nChar---nChar, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nRepCnt---Rep Cnt, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Key Down, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		nChar---nChar, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nRepCnt---Rep Cnt, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()

private:
 
	// Drop Target, This member specify COleDropTarget object.  
	COleDropTarget m_DropTarget;
 
	// Can Drop, Specify A Boolean value.  
	bool m_bCanDrop;

 
	// Point Size, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int m_iPointSize;
 
	// Default Font, This member specify LOGFONT object.  
	LOGFONT m_lfDefFont;
 
	// The CFont class encapsulates a Windows graphics device interface (GDI) font and provides member functions for manipulating the font.  
	CFont m_font;

 
	// m_uiTimer, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	unsigned int m_uiTimer;
 
	// File Attribute Data, This member specify WIN32_FILE_ATTRIBUTE_DATA object.  
	WIN32_FILE_ATTRIBUTE_DATA m_FileAttributeData;
 
	// File Change, Specify A Boolean value.  
	bool m_bFileChange;

 
	// m_bMetric, Specify A Boolean value.  
	bool m_bMetric;
 
	// m_rectMargin, This member sets a CRect value.  
	CRect m_rectMargin;
 
	// m_strHeader, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strHeader;
 
	// m_strFooter, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strFooter;
 
	// m_pUndo, This member maintains a pointer to the object FOCodeUndo.  
	FOCodeUndo *m_pUndo;
 
	// Modified Before First Undo, Specify A Boolean value.  
	bool m_bModifiedBeforeFirstUndo;
};

#ifndef _DEBUG  // debug version in notepadreView.cpp
inline CCodeDocument* CCodeEditView::GetDocument ()
   { return (CCodeDocument*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODEEDITVIEW_H__DCA986CB_57A6_4F7A_BF2B_E2F7199744AE__INCLUDED_)
