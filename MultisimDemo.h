// MultisimDemo.h : main header file for the MULTISIMDEMO application
//

#if !defined(AFX_MULTISIMDEMO_H__D1EBE189_96C4_467A_9B73_E1901F68098C__INCLUDED_)
#define AFX_MULTISIMDEMO_H__D1EBE189_96C4_467A_9B73_E1901F68098C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultisimDemoApp:
// See MultisimDemo.cpp for the implementation of this class
//
#include "FOProjectApp.h"
#define REG_EDITPAD_IDE     _T ("Software\\UCanCode Software\\MultisimDemo\\IDE")

 
typedef void (*ThreadTimerProc)(void* obj, UINT idEvent);

 
//===========================================================================
// Summary:
//      To use a CThreadTimer object, just call the constructor.
//      Thread Timer
//===========================================================================
#define FO_TIMER 1002
class CThreadTimer  
{
	enum CTEvent{CTECheck, CTEExit};
	enum {CT_HANDLE_TEVENT=0, CT_HANDLE_TTIMER=1,CT_HANDLE_COUNT = 2};
	
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Thread Timer, Constructs a CThreadTimer object.
	//		Returns A  value.
	CThreadTimer();
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Thread Timer, Destructor of class CThreadTimer
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CThreadTimer();
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open, None Description.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL Open();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Close, None Description.

	void Close();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Open, Determines if the given value is correct or exist.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL IsOpen()const;
	
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Timer, Sets a specify value to current class CThreadTimer
	//		Returns a UINT type value.  
	// Parameters:
	//		nIDEvent---I D Event, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		lElapseMS---Elapse M S, Specifies A 32-bit signed integer.  
	//		lpFunc---lpFunc, Specifies a ThreadTimerProc lpFunc=NULL object.  
	//		lpUser---lpUser, Specifies a LPVOID lpUser=NULL object.
	UINT SetTimer(UINT nIDEvent, LONG lElapseMS, ThreadTimerProc lpFunc=NULL, LPVOID lpUser=NULL);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Timer Set, Determines if the given value is correct or exist.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL IsTimerSet()const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Cancel Timer, None Description.

	void CancelTimer();
	
	
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// T Thread_ Func, None Description.
	// This member function is a static function.
	// Parameters:
	//		lpParam---lpParam, Specifies a LPVOID lpParam object.
	static void CTThread_Func(LPVOID lpParam);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Thread Event, Sets a specify value to current class CThreadTimer
	// Parameters:
	//		Event---Event, Specifies a CTEvent Event object.
	void	SetThreadEvent(CTEvent Event);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Exit Thread, None Description.

	void	ExitThread();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Thread Timer, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnThreadTimer();
	
protected:
 
	// m_lpcfFunc, This member specify ThreadTimerProc object.  
	ThreadTimerProc m_lpcfFunc;
 
	// User Data, This member specify LPVOID object.  
	LPVOID	m_lpUserData;
 
	// idEvent, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT idEvent;   // timer ID
	
 
	// C T Thread, This member specify HANDLE object.  
	HANDLE	m_hCTThread;
 
	// C T Handles[ C T_ H A N D L E_ C O U N T], This member specify HANDLE object.  
	HANDLE	m_hCTHandles[CT_HANDLE_COUNT];
 
	// Threa Event, This member specify CTEvent object.  
	CTEvent m_emThreaEvent;
	
 
	// Set Timer, This member sets TRUE if it is right.  
	BOOL	m_bSetTimer;
};

inline BOOL CThreadTimer::IsTimerSet()const
{return m_bSetTimer;}

//===========================================================================
// Summary:
//     The CMultisimDemoApp class derived from CFOProjectApp
//      Multisim Demo Application
//===========================================================================

class CMultisimDemoApp : public CFOProjectApp
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Multisim Demo Application, Constructs a CMultisimDemoApp object.
	//		Returns A  value.
	CMultisimDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultisimDemoApp)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Initial Instance, Override to perform Windows instance initialization, such as creating your window objects.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL InitInstance();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Document File, Open document from specify file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CDocument,or NULL if the call failed  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Exit Instance, Override to clean up when your application terminates.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a int type value.
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
 
	// Document Template, This member maintains a pointer to the object CMultiDocTemplateEx.  
	CMultiDocTemplateEx* m_pDocTemplate;
 
	// Code Template, This member maintains a pointer to the object CFOZeroDocTemplate.  
	CFOZeroDocTemplate* pCodeTemplate;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Make Project Path, None Description.
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void MakeProjectPath(UINT nType);
	//Image List
	// Saving keys.
 
	// m_bGrid, This member sets TRUE if it is right.  
	BOOL	m_bGrid;
 
	// Free Form Drawing, This member sets TRUE if it is right.  
	BOOL	m_bFreeFormDrawing;
 
	// m_bGuide, This member sets TRUE if it is right.  
	BOOL	m_bGuide;
 
	// Grid Snap, This member sets TRUE if it is right.  
	BOOL	m_bGridSnap;
 
	// New Snap, This member sets TRUE if it is right.  
	BOOL	m_bNewSnap;
 
	// m_bMargin, This member sets TRUE if it is right.  
	BOOL	m_bMargin;
 
	// Show Ports, This member sets TRUE if it is right.  
	BOOL	m_bShowPorts;
 
	// Drawing From Center, This member sets TRUE if it is right.  
	BOOL	m_bDrawingFromCenter;
 
	// Glue To Shape, This member sets TRUE if it is right.  
	BOOL	m_bGlueToShape;
 
	// Glue To Spot, This member sets TRUE if it is right.  
	BOOL	m_bGlueToSpot;
	
 
	// Snap To Help Line, This member sets TRUE if it is right.  
	BOOL	m_bSnapToHelpLine;
 
	// Snap To Intersect, This member sets TRUE if it is right.  
	BOOL	m_bSnapToIntersect;
 
	// List Bar, This member sets TRUE if it is right.  
	BOOL	m_bListBar;
 
	// m_bRuler, This member sets TRUE if it is right.  
	BOOL	m_bRuler;
	
	BOOL	bWithDotShow;

	// Select File, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString strCurSelectFile;
	
	//
	CString strCurSelectShape;

	//-----------------------------------------------------------------------
	// Summary:
	// Do Save Setting, Saves the specify data to a file..

	void DoSaveSetting();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Load Setting, Loads the specify data from a file.

	void DoLoadSetting();

// Implementation
	//{{AFX_MSG(CMultisimDemoApp)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Application About, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnAppAbout();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On New Project, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnNewProject();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update New Project, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateNewProject(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Open Project, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnOpenProject();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Open Project, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateOpenProject(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Save Project, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnSaveProject();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Save Project, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateSaveProject(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Close Project, Called as a signal that CWnd should be closed.

	afx_msg void OnCloseProject();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Close Project, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateCloseProject(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Save All, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnSaveAll();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Update Save All, Called to notify a view that its document has been modified.
	// Parameters:
	//		pCmdUI---Cmd U I, A pointer to the CCmdUI or NULL if the call failed.
	afx_msg void OnUpdateSaveAll(CCmdUI* pCmdUI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On File New, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFileNew();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On File Open, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnFileOpen();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On New Script, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnNewScript();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Open Samples, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnOpenSamples();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};


#define P_ID_MATHER_TEXT1			3008
#define P_ID_MATHER_LINEWIDTH		3016
const int nfoDefSep = 10;
const int nfoLabelSep = 36;
const int nfoBoxW = 24;
const int nfoBoxH = 18;
/////////////////////////////////////////////////////////////////////////////
extern CMultisimDemoApp theApp;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTISIMDEMO_H__D1EBE189_96C4_467A_9B73_E1901F68098C__INCLUDED_)
