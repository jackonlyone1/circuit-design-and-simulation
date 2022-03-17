// CodeEditDoc.cpp : implementation of the CCodeEditDoc class
//

#include "stdafx.h"
#include "messages.h"
#include "MultisimDemo.h"

#include "MainFrm.h"
#include "CodeEditDoc.h"
#include "CodeEditView.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeDocument

#ifdef _UNICODE
#define _tcstoi _wtoi
#else
#define _tcstoi atoi
#endif

bool CCodeDocument::m_bReplaceAllLikeNotepad = false;
LPCTSTR CCodeDocument::m_pszText = 0;
ULONG CCodeDocument::m_ulTextIndex = 0;
ULONG CCodeDocument::m_ulBufferIncrement = 1024;
LPCTSTR CCodeDocument::m_lpszReplace = 0;

IMPLEMENT_DYNCREATE(CCodeDocument, CDocument)

BEGIN_MESSAGE_MAP(CCodeDocument, CDocument)
	//{{AFX_MSG_MAP(CCodeDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeDocument construction/destruction

CCodeDocument::CCodeDocument () :
	m_bReadOnly (false),
	m_eFileType (CCodeHelperFile::eANSI),
	m_eFileFormat (CCodeHelperFile::eWindows),
	m_eRequestedFileType (CCodeHelperFile::eANSI),
	m_eRequestedFileFormat (CCodeHelperFile::eWindows),
	m_bWholeWordOnly (false),
	m_bMatchCase (false),
	m_bRegEx (true),
	m_bCompiled (false),
	m_bSearchForward (true),
	m_bCloseOnMatch (false),
	m_bScrollToEnd (false),
	m_bFileChangeNotify (true),
	m_bAutoReload (false)
{
	
}

CCodeDocument::~CCodeDocument ()
{
}

void CCodeDocument::SetReadOnly (const bool bReadOnly)
{
	m_bReadOnly = bReadOnly;
}

bool CCodeDocument::GetReadOnly () const
{
	return m_bReadOnly;
}

void CCodeDocument::SetFileType (const CCodeHelperFile::e_FileType eFileType,
	const CCodeHelperFile::e_FileFormat eFileFormat)
{
	m_eRequestedFileType = eFileType;
	m_eRequestedFileFormat = eFileFormat;
}

void CCodeDocument::GetFileType (CCodeHelperFile::e_FileType &eFileType,
	CCodeHelperFile::e_FileFormat &eFileFormat) const
{
	eFileType = m_eFileType;
	eFileFormat = m_eFileFormat;
}

void CCodeDocument::StartFileChangeNotification (LPCTSTR lpszPathName)
{
	CCodeEditView *pView = static_cast <CCodeEditView *>
		(m_viewList.GetHead());

	pView->StartTimer (lpszPathName);
}

void CCodeDocument::StopFileChangeNotification ()
{
	// Cater for the case when an invalid file is passed on the command line
	if (!m_viewList.IsEmpty ())
	{
		CCodeEditView *pView = static_cast <CCodeEditView *>
			(m_viewList.GetHead());

		if (pView)
		{
			pView->StopTimer ();
		}
	}
}

const CString &CCodeDocument::GetFindText () const
{
	return m_strFind;
}

const CString &CCodeDocument::GetReplaceText () const
{
	return m_strReplace;
}

const bool CCodeDocument::GetWholeWordOnly () const
{
	return m_bWholeWordOnly;
}

const bool CCodeDocument::GetMatchCase () const
{
	return m_bMatchCase;
}

const bool CCodeDocument::GetRegEx () const
{
	return m_bRegEx;
}

const bool CCodeDocument::GetCompiled () const
{
	return m_bCompiled;
}

const bool CCodeDocument::GetSearchForward () const
{
	return m_bSearchForward;
}

void CCodeDocument::SetSearchForward (const bool bSearchForward)
{
	m_bSearchForward = bSearchForward;
}

const bool CCodeDocument::GetCloseOnMatch () const
{
	return m_bCloseOnMatch;
}

const bool CCodeDocument::GetReplaceAllLikeNotepad () const
{
	return m_bReplaceAllLikeNotepad;
}

const bool CCodeDocument::NeedFind () const
{
	return false;
}

bool CCodeDocument::FindText ()
{
	
	return false;
}

bool CCodeDocument::FindTextRE ()
{
	
	return false;
}

void CCodeDocument::OnNotifyFindReplace (WPARAM wParam, LPARAM lParam)
{
}

bool CCodeDocument::GetScrollToEnd () const
{
	return m_bScrollToEnd;
}

void CCodeDocument::ToggleScrollToEnd ()
{
	m_bScrollToEnd ^= 1;
}

bool CCodeDocument::GetFileChangeNotify () const
{
	return m_bFileChangeNotify;
}

void CCodeDocument::ToggleFileChangeNotify ()
{
	m_bFileChangeNotify = !m_bFileChangeNotify;

	if (m_bFileChangeNotify)
	{
		StartFileChangeNotification (GetPathName ());
	}
	else
	{
		StopFileChangeNotification ();
		m_bAutoReload = false;
	}
}

bool CCodeDocument::GetAutoReload () const
{
	return m_bAutoReload;
}

void CCodeDocument::ToggleAutoReload ()
{
	m_bAutoReload = !m_bAutoReload;
}

void CCodeDocument::OnCloseDocument()
{
	if (m_bFileChangeNotify)
	{
		StopFileChangeNotification ();
	}

	CDocument::OnCloseDocument();
}

BOOL CCodeDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CCodeEditView *pView = ((CCodeEditView *)m_viewList.GetHead ());

	pView->SetWindowText (NULL);

	if (m_bFileChangeNotify)
	{
		StopFileChangeNotification ();
	}

	if (m_bReadOnly)
	{
		pView->ToggleReadOnly ();
	}

	m_eFileType = CCodeHelperFile::eANSI;
	m_eFileFormat = CCodeHelperFile::eWindows;
	pView->ClearUndoHistory (FALSE);
	// (SDI documents will reuse this document)
	return TRUE;
}

BOOL CCodeDocument::OnOpenDocument (LPCTSTR lpszPathName)
{
	BOOL bRet = TRUE;
	CCodeEditView *pView = static_cast <CCodeEditView *>
		(m_viewList.GetHead());
	DWORD dwChars = 0;

	if (m_bFileChangeNotify)
	{
		StopFileChangeNotification ();
	}

	// Throws an exception if there is a problem
	TRY
	{
		CFile File (lpszPathName, CFile::modeRead | CFile::shareDenyNone);

		LoadText (&File, dwChars, pView);
		SetModifiedFlag (FALSE);

		// Check if start of file starts with ".LOG"
		if (dwChars > 3)
		{
			TCHAR szHeader[4 + 1] = _T("");
			CString strDotLog;

			m_pszText = pView->LockBuffer ();
			_tcsncpy (szHeader, m_pszText, 4);
			szHeader[4] = 0;
			pView->UnlockBuffer ();
			m_pszText = 0;
			strDotLog = ".LOG";

			if (_tcscmp (strDotLog, szHeader) == 0)
			{
				pView->SetSel (dwChars, dwChars, FALSE);
				pView->InsertTimeDate (true);
			}
		}

		pView->Invalidate ();
		// File loaded, so flags can be safely set
		m_eFileType = m_eRequestedFileType;
		m_eFileFormat = m_eRequestedFileFormat;

		if (m_bScrollToEnd)
		{
			// Re-calculate in case ".LOG" was at start of file
			int iLen = pView->GetWindowTextLength ();

			pView->SetSel (iLen, iLen);
		}
	}
	CATCH_ALL(e)
	{
		TRY
		{
			ReportSaveLoadException (lpszPathName, e,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		}
		END_TRY

		bRet = FALSE;
	}
	END_CATCH_ALL

	if (m_bFileChangeNotify)
	{
		if (bRet)
		{
			StartFileChangeNotification (lpszPathName);
		}
		else
		{
			StartFileChangeNotification (GetPathName ());
		}
	}

	if (bRet)
	{
		pView->ClearUndoHistory (FALSE);
	}

	return bRet;
}

BOOL CCodeDocument::OnSaveDocument (LPCTSTR lpszPathName)
{
	CCodeEditView *pView = static_cast <CCodeEditView *>
		(m_viewList.GetHead());

	if (m_bFileChangeNotify)
	{
		StopFileChangeNotification ();
	}

	if (pView->IsWordWrapEnabled ())
		pView->GetEditCtrl ().FmtLines (FALSE);

	TRY
	{
		LPCTSTR lpszText = pView->LockBuffer ();
		const UINT nLen = pView->GetBufferLength ();
		CFile File (lpszPathName, CFile::modeCreate | CFile::modeWrite);

		CCodeHelperFile::Save (lpszText, nLen, m_eRequestedFileType,
			m_eRequestedFileFormat, &File);

		SetModifiedFlag (FALSE);
	}
	CATCH_ALL(e)
	{
		pView->UnlockBuffer ();

		if (pView->IsWordWrapEnabled ())
			pView->GetEditCtrl ().FmtLines (TRUE);

		if (m_bFileChangeNotify)
		{
			StartFileChangeNotification (GetPathName ());
		}

		THROW_LAST ();
	}
	END_CATCH_ALL

	pView->UnlockBuffer ();

	if (pView->IsWordWrapEnabled ())
		pView->GetEditCtrl ().FmtLines (TRUE);

	m_eFileType = m_eRequestedFileType;
	m_eFileFormat = m_eRequestedFileFormat;

	if (m_bFileChangeNotify)
	{
		StartFileChangeNotification (lpszPathName);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCodeDocument diagnostics

#ifdef _DEBUG
void CCodeDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CCodeDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CCodeDocument::LoadText (CFile *pFile, DWORD &dwChars, CEditView *pView)
{
	LPVOID hText = 0;
	LPTSTR pszText = 0;

	m_eRequestedFileType = CCodeHelperFile::eAutoFileType;
	m_eRequestedFileFormat = CCodeHelperFile::eAutoFileFormat;
	dwChars = 0;

	hText = CCodeHelperFile::Load (pFile, m_eRequestedFileType,
		m_eRequestedFileFormat, dwChars);

	dwChars /= sizeof(TCHAR);
	HLOCAL hOldText = pView->GetEditCtrl ().GetHandle ();

	ASSERT (hOldText != NULL);
	::LocalFree (hOldText);
	pView->GetEditCtrl ().SetHandle ((HLOCAL)(UINT)(DWORD)hText);
}

bool CCodeDocument::OnFindNext ()
{
	bool bSuccess = false;

	if (m_bRegEx)
	{
		if (CompileRegEx ())
		{
			CWaitCursor wait;

			try
			{
				bSuccess = FindTextRE ();
			}
			catch (std::runtime_error &e)
			{
				CCodeEditView *pView = static_cast <CCodeEditView *>
					(m_viewList.GetHead());
				CString strErrorMsg = e.what ();

				bSuccess = false;
				// Clean up
				pView->UnlockBuffer ();
				// Display error
				pView->DisplayErrorMsg (strErrorMsg);
			}
		}
	}
	else
	{
		CWaitCursor wait;

		bSuccess = FindText ();
	}

	return bSuccess;
}

bool CCodeDocument::CompileRegEx ()
{
	
	return false;
}

bool CCodeDocument::FindTextHelper (int &iStart, const TCHAR *pszTextStart,
	const TCHAR *pszTextEnd, const int iTotalTextLen, const TCHAR *pszTextToFind,
	const int iTextToFindLen)
{
	bool bFound = false;
	
	return bFound;
}


void CCodeDocument::OnReplaceSel()
{
	
}

void CCodeDocument::AppendToBuffer (const TCHAR *pszText, const ULONG ulTextLen)
{
	
}

void CCodeDocument::ReplaceAllHelper (const int iTextLen)
{
	
}

void CCodeDocument::ReplaceAll ()
{
	
}

void CCodeDocument::OnReplaceAll()
{
	CWaitCursor wait;

	if (m_bRegEx)
	{
		if (CompileRegEx ())
		{
			ReplaceAll ();
		}
	}
	else
	{
		ReplaceAll ();
	}
}
