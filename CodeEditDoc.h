// CodeEditDoc.h : interface of the CCodeEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEEDITDOC_H__8FB27E16_50B6_4882_AEB5_29B1B7A95387__INCLUDED_)
#define AFX_CODEEDITDOC_H__8FB27E16_50B6_4882_AEB5_29B1B7A95387__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NotepadreFile.h"
#pragma warning (disable:4786)

 
//===========================================================================
// Summary:
//     The CCodeDocument class derived from CDocument
//      Code Document
//===========================================================================

class CCodeDocument : public CDocument
{
protected: // create from serialization only
	
	//-----------------------------------------------------------------------
	// Summary:
	// Code Document, Constructs a CCodeDocument object.
	//		Returns A  value.
	CCodeDocument();
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ D Y N C R E A T E, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CCodeDocument---Code Document, Specifies a CCodeDocument object.
	DECLARE_DYNCREATE(CCodeDocument)

// Attributes
public:
	void CCodeDocument::SetReadOnly (const bool bReadOnly);
	bool CCodeDocument::GetReadOnly () const;
	void SetFileType (const CCodeHelperFile::e_FileType eFileType,
		const CCodeHelperFile::e_FileFormat eFileFormat);
	void GetFileType (CCodeHelperFile::e_FileType &eFileType,
		CCodeHelperFile::e_FileFormat &eFileFormat) const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Start File Change Notification, None Description.
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	void StartFileChangeNotification (LPCTSTR lpszPathName);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Stop File Change Notification, Call this function to stop

	void StopFileChangeNotification ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Find Text, None Description.
	//		Returns a CString type value.
	const CString &GetFindText () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Replace Text, None Description.
	//		Returns a CString type value.
	const CString &GetReplaceText () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Whole Word Only, Returns the specified value.
	//		Returns A Boolean value.
	const bool GetWholeWordOnly () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Match Case, Returns the specified value.
	//		Returns A Boolean value.
	const bool GetMatchCase () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Registry Ex, Returns the specified value.
	//		Returns A Boolean value.
	const bool GetRegEx () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Compiled, Returns the specified value.
	//		Returns A Boolean value.
	const bool GetCompiled () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Search Forward, Returns the specified value.
	//		Returns A Boolean value.
	const bool GetSearchForward () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Search Forward, Sets a specify value to current class CCodeDocument
	// Parameters:
	//		bSearchForward---Search Forward, Specifies A Boolean value.
	void SetSearchForward (const bool bSearchForward);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Close On Match, Returns the specified value.
	//		Returns A Boolean value.
	const bool GetCloseOnMatch () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Replace All Like Notepad, Returns the specified value.
	//		Returns A Boolean value.
	const bool GetReplaceAllLikeNotepad () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Need Find, None Description.
	//		Returns A Boolean value.
	const bool NeedFind () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Text, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns A Boolean value.
	bool FindText ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Text R E, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns A Boolean value.
	bool FindTextRE ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Notify Find Replace, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		wParam---wParam, Provides additional information used in processing the message. The parameter value depends on the message.  
	//		lParam---lParam, Specifies A lparam value.
	void OnNotifyFindReplace (WPARAM wParam, LPARAM lParam);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Scroll To End, Returns the specified value.
	//		Returns A Boolean value.
	bool GetScrollToEnd () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Toggle Scroll To End, None Description.

	void ToggleScrollToEnd ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get File Change Notify, Returns the specified value.
	//		Returns A Boolean value.
	bool GetFileChangeNotify () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Toggle File Change Notify, None Description.

	void ToggleFileChangeNotify ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Auto Reload, Returns the specified value.
	//		Returns A Boolean value.
	bool GetAutoReload () const;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Toggle Auto Reload, None Description.

	void ToggleAutoReload ();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeDocument)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Close Document, Called as a signal that CWnd should be closed.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnCloseDocument ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On New Document, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnNewDocument ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Open Document, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OnOpenDocument (LPCTSTR lpszPathName);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Save Document, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OnSaveDocument (LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Code Document, Destructor of class CCodeDocument
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CCodeDocument();
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

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load Text, Call this function to read a specified number of bytes from the archive.
	// Parameters:
	//		*pFile---*pFile, A pointer to the CFile  or NULL if the call failed.  
	//		&dwChars---&dwChars, Specifies A 32-bit unsigned integer or the address of a segment and its associated offset.  
	//		*pView---*pView, A pointer to the CEditView  or NULL if the call failed.
	void LoadText (CFile *pFile, DWORD &dwChars, CEditView *pView);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Find Next, This member function is called by the framework to allow your application to handle a Windows message.
	//		Returns A Boolean value.
	bool OnFindNext ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Compile Registry Ex, None Description.
	//		Returns A Boolean value.
	bool CompileRegEx ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Text Helper, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns A Boolean value.  
	// Parameters:
	//		&iStart---&iStart, Specifies A integer value.  
	//		*pszTargetText---Target Text, A pointer to the const TCHAR  or NULL if the call failed.  
	//		*pszTextEnd---Text End, A pointer to the const TCHAR  or NULL if the call failed.  
	//		iTotalTextLen---Total Text Len, Specifies A integer value.  
	//		*pszTextToFind---Text To Find, A pointer to the const TCHAR  or NULL if the call failed.  
	//		iTextToFindLen---Text To Find Len, Specifies A integer value.
	bool FindTextHelper (int &iStart, const TCHAR *pszTargetText,
		const TCHAR *pszTextEnd, const int iTotalTextLen, const TCHAR *pszTextToFind,
		const int iTextToFindLen);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Replace Sel, This member function is called by the framework to allow your application to handle a Windows message.

	void OnReplaceSel ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Append To Buffer, None Description.
	// This member function is a static function.
	// Parameters:
	//		*pszText---*pszText, A pointer to the const TCHAR  or NULL if the call failed.  
	//		ulTextLen---Text Len, Specifies A 32-bit signed integer.
	static void AppendToBuffer (const TCHAR *pszText, const ULONG ulTextLen);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Replace All Helper, None Description.
	// Parameters:
	//		iTextLen---Text Len, Specifies A integer value.
	void ReplaceAllHelper (const int iTextLen);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Replace All, None Description.

	void ReplaceAll ();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Replace All, This member function is called by the framework to allow your application to handle a Windows message.

	void OnReplaceAll ();

// Generated message map functions
protected:
	//{{AFX_MSG(CCodeDocument)
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()

private:
 
	// Read Only, Specify A Boolean value.  
	bool m_bReadOnly;
	// Current file type
	CCodeHelperFile::e_FileType m_eFileType;
	CCodeHelperFile::e_FileFormat m_eFileFormat;

	// These values are filled from the Save As dialog
	CCodeHelperFile::e_FileType m_eRequestedFileType;
	CCodeHelperFile::e_FileFormat m_eRequestedFileFormat;

 
	// Valid Chars, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strValidChars;
 
	// m_strFind, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strFind;
 
	// m_strReplace, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strReplace;
 
	// Whole Word Only, Specify A Boolean value.  
	bool m_bWholeWordOnly;
 
	// Match Case, Specify A Boolean value.  
	bool m_bMatchCase;
 
	// Registry Ex, Specify A Boolean value.  
	bool m_bRegEx;
 
	// m_bCompiled, Specify A Boolean value.  
	bool m_bCompiled;
 
	// Replace All Like Notepad, Specify A Boolean value.  
	static bool m_bReplaceAllLikeNotepad;
 
	// Search Forward, Specify A Boolean value.  
	bool m_bSearchForward;
 
	// Close On Match, Specify A Boolean value.  
	bool m_bCloseOnMatch;
	// The last match...

 
	// m_pszText, This member maintains a pointer to the object TCHAR const.  
	static TCHAR const *m_pszText;
 
	// Text Index, Specify a A 32-bit signed integer.  
	static ULONG m_ulTextIndex;
 
	// Buffer Increment, Specify a A 32-bit signed integer.  
	static ULONG m_ulBufferIncrement;
 
	// m_lpszReplace, This member sets A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	static LPCTSTR m_lpszReplace;

 
	// Scroll To End, Specify A Boolean value.  
	bool m_bScrollToEnd;
 
	// File Change Notify, Specify A Boolean value.  
	bool m_bFileChangeNotify;
 
	// Auto Reload, Specify A Boolean value.  
	bool m_bAutoReload;
	// Path and file name used for File Change Notification code
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODEEDITDOC_H__8FB27E16_50B6_4882_AEB5_29B1B7A95387__INCLUDED_)
