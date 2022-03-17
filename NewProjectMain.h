#if !defined(AFX_NEWPROJECTMAIN_H__FED35388_E868_11DA_8D99_AAE03EA530FF__INCLUDED_)
#define AFX_NEWPROJECTMAIN_H__FED35388_E868_11DA_8D99_AAE03EA530FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProjectMain.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewProjectMain dialog
#include "NewWizDialog.h"

 
//===========================================================================
// Summary:
//     The CNewProjectMain class derived from CNewWizDialog
//      New Project Main
//===========================================================================

class CNewProjectMain : public CNewWizDialog
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Project Main, Constructs a CNewProjectMain object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CNewProjectMain(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewProjectMain)
	enum { IDD = IDD_DIALOG_NEWMAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

 
	// Old Lang Type, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT nOldLangType;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectMain)
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
	//{{AFX_MSG(CNewProjectMain)
	
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

#endif // !defined(AFX_NEWPROJECTMAIN_H__FED35388_E868_11DA_8D99_AAE03EA530FF__INCLUDED_)
