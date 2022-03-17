// CodeEditView.cpp : implementation of the CCodeEditView class
//

#include "stdafx.h"
#include "MultisimDemo.h"
#include "CodeEditDoc.h"
#include "CodeEditView.h"

#include "messages.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeEditView
IMPLEMENT_DYNCREATE(CCodeEditView, CEditView)

BEGIN_MESSAGE_MAP(CCodeEditView, CEditView)
	//{{AFX_MSG_MAP(CCodeEditView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_REPEAT, OnEditRepeat)
	ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateNeedFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPLACE, OnUpdateNotReadOnly)
	ON_COMMAND(ID_FORMAT_FONT, OnFormatFont)
	ON_MESSAGE (WM_NOTIFY_FILE_CHANGE, OnNotifyFileChange)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPEAT, OnUpdateNeedFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateNeedFind)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeEditView construction/destruction

CCodeEditView::CCodeEditView() :
	m_bCanDrop (false),
 	m_iPointSize (0),
	m_uiTimer (0),
	m_bFileChange (false),
	m_strHeader (_T("&f")),
	m_strFooter (_T("Page &p")),
	m_pUndo (0),
	m_bModifiedBeforeFirstUndo (false)
{
	TCHAR szMeasurement[2] = _T("");
	int iHorizontal = 0;
	int iVertical = 0;

	::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_IMEASURE, szMeasurement,
		sizeof (szMeasurement));
	m_bMetric = *szMeasurement == '0';
	iHorizontal = m_bMetric ? 2000 : 750;
	iVertical = m_bMetric ? 2500 : 1000;
	m_rectMargin.SetRect (iHorizontal, iVertical, iHorizontal, iVertical);

	m_pUndo = new FOCodeUndo (FOCodeUndo::eHead, 0, 0, 0);
	m_pMenuData			= NULL;
}

CCodeEditView::~CCodeEditView()
{
	ClearUndoHistory (FALSE);
	delete m_pUndo;
	m_pUndo = 0;
	if(m_pMenuData)
	{
		delete m_pMenuData;
		m_pMenuData = NULL;
	}

}

void CCodeEditView::ToggleWordWrap ()
{
	bool bWordWrap = !IsWordWrapEnabled ();

	m_DropTarget.Revoke();
	ReCreateWindow (bWordWrap, IsReadOnlyEnabled ());
	m_DropTarget.Register (this);
}

void CCodeEditView::ToggleReadOnly ()
{
	bool bReadOnly = !IsReadOnlyEnabled ();

	GetDocument ()->SetReadOnly (bReadOnly);
	m_DropTarget.Revoke();
	ReCreateWindow (IsWordWrapEnabled (), bReadOnly);
	m_DropTarget.Register (this);
}
// windowsx.h defines SubclassWindow as a macro.  This
// definition conflicts with CWnd::SubclassWindow().
#ifdef SubclassWindow
#undef SubclassWindow
#endif

void CCodeEditView::ReCreateWindow (const bool bWordWrap,
	const bool bReadOnly)
{
	CWaitCursor wc;
	int iLineIndex = GetEditCtrl ().
		LineIndex (GetEditCtrl ().GetFirstVisibleLine ());
	int iStart, iEnd;

	GetEditCtrl().GetSel (iStart, iEnd);

	// preserve original control's state.
	CFont* pFont = GetFont ();
	int iLen = GetBufferLength ();
	TCHAR* pszSaveText = new TCHAR[iLen + 1];

	GetWindowText(pszSaveText, iLen + 1);

	// create new edit control with appropriate style and size.
	DWORD dwStyle = dwStyleDefault & ~(ES_AUTOHSCROLL|WS_HSCROLL|WS_VISIBLE);

	if (!bWordWrap)
		dwStyle |= ES_AUTOHSCROLL | WS_HSCROLL;

	if (bReadOnly)
		dwStyle |= ES_READONLY;

	CWnd* pParent = GetParent ();
	CRect rect;
	GetWindowRect (rect);
	pParent->ScreenToClient (rect);
	CWnd *pFocus = GetFocus ();
	UINT uiID = GetDlgCtrlID ();
	CString strEdit = _T("edit");
	HWND hWnd = ::CreateWindowEx(WS_EX_CLIENTEDGE, strEdit, NULL, dwStyle,
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		pParent->m_hWnd, (HMENU) uiID, AfxGetInstanceHandle(), NULL);

	if (hWnd == NULL)
	{
		delete[] pszSaveText;
		return;
	}

	// set the window text to nothing to make sure following set doesn't fail
	SetWindowText(NULL);

	// restore visual state
	::SetWindowText (hWnd, pszSaveText);
	delete[] pszSaveText;

	if (pFont != NULL)
	{
		CFont newFont;
		HFONT hFont = NULL;
#ifdef WIN32
		hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
#endif
		if (hFont == NULL)
			hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);
		newFont.Attach(hFont);
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		newFont.GetLogFont(&lf);
		lf.lfWeight = 550;
		CFont font;
		font.CreateFontIndirect(&lf);
		
		
		CFont NoActiveFont;
		lf.lfWeight = 450;
		NoActiveFont.CreateFontIndirect(&lf);
		newFont.DeleteObject();
	

		ASSERT(pFont->m_hObject != NULL);
		::SendMessage(hWnd, WM_SETFONT, (WPARAM)NoActiveFont.m_hObject, 0);
	}

	// detach old window, attach new
	SetDlgCtrlID (uiID + 1);

	HWND hWndOld = Detach();

	::SetWindowLong (hWndOld, GWL_WNDPROC, (LONG)*GetSuperWndProcAddr());
	ASSERT(m_hWnd == NULL);
	SubclassWindow(hWnd);
	ASSERT(m_hWnd == hWnd);

	UINT nTabStops = m_nTabStops;
	GetEditCtrl().SetTabStops(nTabStops);
	GetEditCtrl ().FmtLines (bWordWrap);

	GetClientRect(&rect);
	SetWindowPos(NULL, 0, 0, 0, 0,
		SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER|SWP_SHOWWINDOW);
	SetWindowPos(NULL, 0, 0, 0, 0,
		SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER|SWP_DRAWFRAME);
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	UpdateWindow();

	// destroy old
	::SetWindowPos(hWndOld, NULL, 0, 0, 0, 0,
		SWP_HIDEWINDOW|SWP_NOREDRAW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|
		SWP_NOZORDER);
	::DestroyWindow(hWndOld);

	// restore rest of state...
	if (pFocus == this)
		SetFocus();

	ASSERT_VALID(this);
	GetEditCtrl ().LineScroll (GetEditCtrl ().LineFromChar (iLineIndex));
	SetSel (iStart, iEnd);
	GetEditCtrl ().SetLimitText (0x7fffffff);
}

BOOL CCodeEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	HKEY hKey = 0;
	CString strNotepadRegKey;
	LONG lRet = 0;
	ULONG ulSize = 4;
	DWORD dwType = 0;

	strNotepadRegKey = "Software\\Microsoft\\Notepad";
	lRet = ::RegOpenKey (HKEY_CURRENT_USER, strNotepadRegKey, &hKey);

	if (lRet == ERROR_SUCCESS)
	{
		CString strEntry;
		DWORD dwWrap = 0;

		strEntry = "fWrap";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &dwWrap, &ulSize);

		if (lRet == ERROR_SUCCESS && dwWrap)
		{
			cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL); // Enable word-wrapping
		}

		::RegCloseKey (hKey);
	}

	return bPreCreated;
}

DROPEFFECT CCodeEditView::OnDragEnter (COleDataObject* pDataObject,
	DWORD dwKeyState, CPoint point)
{
#ifdef UNICODE
	if (pDataObject->IsDataAvailable (CF_UNICODETEXT))
#else
	if (pDataObject->IsDataAvailable (CF_TEXT))
#endif
	{
		m_bCanDrop = true;
	}
	else
	{
		m_bCanDrop = false;
	}

	return OnDragOver (pDataObject, dwKeyState, point);
}

DROPEFFECT CCodeEditView::OnDragOver(COleDataObject* pDataObject,
	DWORD dwKeyState, CPoint point)
{
	DROPEFFECT de = DROPEFFECT_NONE;

	if (m_bCanDrop)
	{
		if (dwKeyState & MK_ALT)
		{
			de = DROPEFFECT_MOVE;
		}
		else
		{
			de = DROPEFFECT_COPY;
		}
	}

	return de;
}

BOOL CCodeEditView::OnDrop (COleDataObject* pDataObject,
	DROPEFFECT dropEffect, CPoint point)
{
	BOOL bSuccess = TRUE;
	STGMEDIUM stg;
	FORMATETC fe;

#ifdef UNICODE
	fe.cfFormat = CF_UNICODETEXT;
#else
	fe.cfFormat = CF_TEXT;
#endif
	fe.tymed = TYMED_HGLOBAL;
	fe.lindex = -1;
	fe.dwAspect = DVASPECT_CONTENT;
	fe.ptd = 0;

#ifdef UNICODE
	if (pDataObject->GetData (CF_UNICODETEXT, &stg, &fe))
#else
	if (pDataObject->GetData (CF_TEXT, &stg, &fe))
#endif
	{
		CString str = (TCHAR *) GlobalLock (stg.hGlobal);

		GlobalUnlock (stg.hGlobal);
		ReplaceSelWithUndo (str);
	}
	else
	{
		bSuccess = FALSE;
	}

	return bSuccess;
}

/////////////////////////////////////////////////////////////////////////////
// CCodeEditView drawing

void CCodeEditView::OnDraw(CDC* pDC)
{
	CCodeDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CCodeEditView printing

void CCodeEditView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CEditView::OnBeginPrinting(pDC, pInfo);

	// BUG FIX: calculate how many page there are
	// to avoid printing an unnecessary (blank) page
	pInfo->m_nCurPage = 0xffff;
	OnPrepareDC (pDC, pInfo);
	pInfo->m_nCurPage = 1;
	pInfo->SetMaxPage (m_aPageStart.GetSize ());
	pInfo->m_bContinuePrinting = TRUE;
}

inline int Round (double n)
{
	int iFloor = (int)floor (n);
	int iMod = (int)fmod (n, 10);

	if (iMod >= 5) iFloor++;

	return iFloor;
}

void CCodeEditView::OnPrint (CDC* pDC, CPrintInfo* pInfo)
{
	double dDivisor = m_bMetric ? 2540 : 1000;
	int iMarginX = pDC->GetDeviceCaps (PHYSICALOFFSETX);
	int iMarginY = pDC->GetDeviceCaps (PHYSICALOFFSETY);
	CString strHeader = m_strHeader;
	CString strFooter = m_strFooter;
	int iWidth = pInfo->m_rectDraw.right;
	RECT rectMargin;

	rectMargin.left = Round ((double) m_rectMargin.left / dDivisor *
		(double) pDC->GetDeviceCaps (LOGPIXELSX));
	rectMargin.top = Round ((double) m_rectMargin.top / dDivisor *
		(double) pDC->GetDeviceCaps (LOGPIXELSY));
	rectMargin.right = Round ((double) m_rectMargin.right / dDivisor *
		(double) pDC->GetDeviceCaps (LOGPIXELSX));
	rectMargin.bottom = Round ((double) m_rectMargin.bottom / dDivisor *
		(double) pDC->GetDeviceCaps (LOGPIXELSY));
	rectMargin.left = rectMargin.left < iMarginX ? 0 :
		rectMargin.left - iMarginX;
	rectMargin.top = rectMargin.top < iMarginY ? 0 :
		rectMargin.top - iMarginY;
	rectMargin.right = rectMargin.right < iMarginX ? 0 :
		rectMargin.right - iMarginX;
	rectMargin.bottom = rectMargin.bottom < iMarginY ? 0 :
		rectMargin.bottom - iMarginY;
	pInfo->m_rectDraw.DeflateRect (&rectMargin);

	if (m_aPageStart[pInfo->m_nCurPage - 1] < GetBufferLength())
	{
		PrintHeaderFooter (strHeader, true, iWidth, pDC, pInfo);
		PrintHeaderFooter (strFooter, false, iWidth, pDC, pInfo);
	}

	CEditView::OnPrint (pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CCodeEditView diagnostics

#ifdef _DEBUG
void CCodeEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CCodeEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CCodeDocument* CCodeEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCodeDocument)));
	return (CCodeDocument*)m_pDocument;
}
#endif //_DEBUG

void CCodeEditView::StartTimer (LPCTSTR lpszPathName)
{
	if (m_uiTimer == 0 && _tcslen (lpszPathName))
	{
		m_uiTimer = SetTimer (1, 2000, 0);
		::GetFileAttributesEx (lpszPathName,
			GetFileExInfoStandard, &m_FileAttributeData);
	}
}

void CCodeEditView::StopTimer ()
{
	KillTimer (m_uiTimer);
	m_uiTimer = 0;
}

bool CCodeEditView::IsWordWrapEnabled () const
{
	return (GetStyle() & ES_AUTOHSCROLL) == 0;
}

bool CCodeEditView::IsReadOnlyEnabled () const
{
	return (static_cast<const CCodeDocument *> (m_pDocument))->
		GetReadOnly ();
}

void CCodeEditView::InsertTimeDate (const bool bCRLF)
{
	SYSTEMTIME SysTime;
	int iLen = 0;
	TCHAR *psz = 0;
	CString strTimeDate;
	CString strCRLF;

	::GetLocalTime (&SysTime);
	iLen = ::GetTimeFormat (LOCALE_USER_DEFAULT, TIME_NOSECONDS,
		&SysTime, 0, 0, 0);
	psz = new TCHAR[iLen];
	::GetTimeFormat (LOCALE_USER_DEFAULT, TIME_NOSECONDS,
		&SysTime, 0, psz, iLen);
	strTimeDate = psz;
	strTimeDate += ' ';
	delete psz;
	iLen = ::GetDateFormat (LOCALE_USER_DEFAULT, DATE_SHORTDATE, &SysTime, 0,
		0, 0);
	psz = new TCHAR[iLen];
	::GetDateFormat (LOCALE_USER_DEFAULT, DATE_SHORTDATE, &SysTime, 0,
		psz, iLen);
	strTimeDate += psz;
	delete psz;

	if (bCRLF)
	{
		strCRLF = "\r\n";
		strTimeDate = strCRLF + strTimeDate + strCRLF;
	}

	ReplaceSelWithUndo (strTimeDate);
}

void CCodeEditView::DisplayErrorMsg (const CString &str)
{
	CWnd *pWnd = GetFocus ();
	CString strNotepadRE;

	MessageBeep (-1);
	strNotepadRE = "Notepad RE";
	MessageBox (str, strNotepadRE, MB_ICONEXCLAMATION | MB_OK);

	if (pWnd)
	{
		pWnd->SetFocus ();
	}
}

void CCodeEditView::SetSel (const int iStart, const int iEnd,
	const BOOL bNoScroll/* = FALSE*/)
{
	GetEditCtrl ().SetSel (iStart, iEnd, bNoScroll);
}

void CCodeEditView::GetSel (int &iStart, int &iEnd)
{
	GetEditCtrl ().GetSel (iStart, iEnd);
}

void CCodeEditView::ReplaceSelWithUndo (const TCHAR *pszText,
	int iStart/* = -1*/, int iEnd/* = -1*/, const bool bDoInsert/* = true*/)
{
	int iLen = ::_tcslen (pszText);
	CEdit &EditCtrl = GetEditCtrl ();
	const TCHAR *pszBuffer = LockBuffer ();

	if (iStart == -1)
	{
		EditCtrl.GetSel (iStart, iEnd);
	}

	if (iStart != iEnd)
	{
		DelSelWithUndo (iStart, iEnd, pszBuffer);
		m_pUndo->m_bTransaction = true;
	}
	else
	{
		ClearUndos (m_pUndo->m_pNext);
	}

	if (iLen)
	{
		if (m_pUndo->m_eWhat == FOCodeUndo::eInsert &&
			iStart == m_pUndo->m_iEnd &&
			!::_tcschr (_T(" \t\r\n"), *pszText) &&
			!::_tcschr (_T(" \t\r\n"), m_pUndo->
				m_strText[m_pUndo->m_strText.length () - 1]))
		{
			m_pUndo->m_iEnd += iLen;
			m_pUndo->m_strText += pszText;
		}
		else
		{
			m_pUndo->m_pNext = new FOCodeUndo (FOCodeUndo::eInsert,
				iStart, iStart + iLen, m_pUndo);
			m_pUndo->m_pNext->m_pPrev = m_pUndo;
			m_pUndo = m_pUndo->m_pNext;
			m_pUndo->m_strText = pszText;
		}
	}

	UnlockBuffer ();

	if (bDoInsert) EditCtrl.ReplaceSel (pszText);
}

void CCodeEditView::DelSelWithUndo (int iStart, int iEnd,
	const TCHAR *pszBuffer/* = 0*/)
{
	const TCHAR *pszBuff = pszBuffer;

	if (pszBuff == 0)
	{
		pszBuff = LockBuffer ();
	}

	if (pszBuff[iStart] != 0)
	{
		if (pszBuff[iStart] == '\n')
		{
			--iStart;
		}
		else if (pszBuff[iEnd] == '\n')
		{
			++iEnd;
		}

		ClearUndos (m_pUndo->m_pNext);

		if (m_pUndo->m_eWhat == FOCodeUndo::eDelete &&
			iEnd == m_pUndo->m_iStart && iEnd - iStart == 1 &&
			!::_tcschr (_T(" \t\r\n"), pszBuff[iStart]) &&
			!::_tcschr (_T(" \t\r\n"), m_pUndo->
				m_strText[m_pUndo->m_strText.length () - 1]))
		{
			m_pUndo->m_iStart -= iEnd - iStart;
			m_pUndo->m_strText.insert (m_pUndo->m_strText.begin (),
				pszBuff + iStart, pszBuff + iEnd);
		}
		else if (m_pUndo->m_eWhat == FOCodeUndo::eDelete &&
			iStart == m_pUndo->m_iStart && iEnd - iStart == 1 &&
			!::_tcschr (_T(" \t\r\n"), pszBuff[iStart]) &&
			!::_tcschr (_T(" \t\r\n"), m_pUndo->
				m_strText[m_pUndo->m_strText.length () - 1]))
		{
			m_pUndo->m_iEnd += iEnd - iStart;
			m_pUndo->m_strText.append (pszBuff + iStart, pszBuff + iEnd);
		}
		else
		{
			m_pUndo->m_pNext = new FOCodeUndo (FOCodeUndo::eDelete,
				iStart, iEnd, m_pUndo);
			m_pUndo->m_pNext->m_pPrev = m_pUndo;
			m_pUndo = m_pUndo->m_pNext;
			m_pUndo->m_strText.assign (pszBuff + iStart, pszBuff + iEnd);
		}
	}

	if (pszBuffer == 0)
	{
		UnlockBuffer ();
	}
}

void CCodeEditView::ClearUndoHistory (const bool bModifiedBeforeFirstUndo)
{
	while (m_pUndo->m_eWhat != FOCodeUndo::eHead)
	{
		m_pUndo = m_pUndo->m_pPrev;
	}

	ClearUndos (m_pUndo->m_pNext);
	m_pUndo->m_pNext = 0;
	m_bModifiedBeforeFirstUndo = bModifiedBeforeFirstUndo;
}

void CCodeEditView::ClearUndos (FOCodeUndo *pUndo)
{
	while (pUndo)
	{
		FOCodeUndo *pNext = pUndo->m_pNext;

		delete pUndo;
		pUndo = pNext;
	}
}

BOOL CCodeEditView::OnPreparePrinting (CPrintInfo *pInfo)
{
	ASSERT(pInfo != NULL);
	ASSERT(pInfo->m_pPD != NULL);

	if (pInfo->m_pPD->m_pd.nMinPage > pInfo->m_pPD->m_pd.nMaxPage)
		pInfo->m_pPD->m_pd.nMaxPage = pInfo->m_pPD->m_pd.nMinPage;

	// don't prompt the user if we're doing print preview, printing directly,
	// or printing via IPrint and have been instructed not to ask
	CMultisimDemoApp *pApp = static_cast<CMultisimDemoApp *> (AfxGetApp());

	if (pInfo->m_bPreview || pInfo->m_bDirect ||
		(pInfo->m_bDocObject && !(pInfo->m_dwFlags & PRINTFLAG_PROMPTUSER)))
	{
		if (pInfo->m_pPD->m_pd.hDC == NULL)
		{
			// if no printer set then, get default printer DC and create DC without calling
			//   print dialog.
			if (!pApp->GetPrinterDeviceDefaults(&pInfo->m_pPD->m_pd))
			{
				// bring up dialog to alert the user they need to install a printer.
				if (!pInfo->m_bDocObject || (pInfo->m_dwFlags & PRINTFLAG_MAYBOTHERUSER))
					if (pApp->DoPrintDialog(pInfo->m_pPD) != IDOK)
						return FALSE;
			}

			if (pInfo->m_pPD->m_pd.hDC == NULL)
			{
				// call CreatePrinterDC if DC was not created by above
				if (pInfo->m_pPD->CreatePrinterDC() == NULL)
					return FALSE;
			}
		}

		// set up From and To page range from Min and Max
		pInfo->m_pPD->m_pd.nFromPage = (WORD)pInfo->GetMinPage();
		pInfo->m_pPD->m_pd.nToPage = (WORD)pInfo->GetMaxPage();
	}
	else
	{
		// otherwise, bring up the print dialog and allow user to change things
		// preset From-To range same as Min-Max range
		pInfo->m_pPD->m_pd.nFromPage = (WORD)pInfo->GetMinPage();
		pInfo->m_pPD->m_pd.nToPage = (WORD)pInfo->GetMaxPage();

		if (pApp->DoPrintDialog (pInfo->m_pPD) != IDOK)
			return FALSE;       // do not print
	}

	ASSERT(pInfo->m_pPD != NULL);
	ASSERT(pInfo->m_pPD->m_pd.hDC != NULL);
	if (pInfo->m_pPD->m_pd.hDC == NULL)
		return FALSE;

	pInfo->m_nNumPreviewPages = pApp->m_nNumPreviewPages;
	VERIFY(pInfo->m_strPageDesc.LoadString(AFX_IDS_PREVIEWPAGEDESC));
	return TRUE;
}

void CCodeEditView::PrintHeaderFooter (const CString &str,
	const bool bHeader, const int iWidth, CDC *pDC, CPrintInfo *pInfo)
{
	CString strHeaderFooter = str;
	e_Alignment eAlignment = eCentre;
	CFont* pOldFont = NULL;
	int iX = 0;
	int iY = 0;
	CSize Extent;

	if (m_hPrinterFont != NULL)
		pOldFont = pDC->SelectObject (CFont::FromHandle(m_hPrinterFont));

	pDC->SetBkMode(TRANSPARENT);
	FormatHeaderFooter (strHeaderFooter, pInfo->m_nCurPage,  eAlignment);
	Extent = pDC->GetTextExtent (strHeaderFooter);
	iY = bHeader ? pInfo->m_rectDraw.top : pInfo->m_rectDraw.bottom - Extent.cy;

	if (eAlignment == eLeft)
	{
		iX = pInfo->m_rectDraw.left;
	}
	else if (eAlignment == eCentre)
	{
		iX = iWidth / 2 - Extent.cx / 2;
	}
	else
	{
		iX = pInfo->m_rectDraw.right - Extent.cx;
	}

	pDC->TextOut (iX, iY, strHeaderFooter);

	if (strHeaderFooter.GetLength ())
	{
		if (bHeader)
		{
#ifdef _DEBUG
			pDC->MoveTo (pInfo->m_rectDraw.left, pInfo->m_rectDraw.top);
			pDC->LineTo (pInfo->m_rectDraw.right, pInfo->m_rectDraw.top);
			pDC->LineTo (pInfo->m_rectDraw.right, pInfo->m_rectDraw.bottom);
			pDC->LineTo (pInfo->m_rectDraw.left, pInfo->m_rectDraw.bottom);
			pDC->LineTo (pInfo->m_rectDraw.left, pInfo->m_rectDraw.top);
#endif
			pInfo->m_rectDraw.top += Extent.cy;
		}
		else
		{
			pInfo->m_rectDraw.bottom -= Extent.cy;
		}
	}

	if (pOldFont != NULL)
		pDC->SelectObject(pOldFont);
}

void CCodeEditView::FormatHeaderFooter (CString &strHeaderFooter,
	const int iPage, e_Alignment &eAlignment)
{
	CString strExpanded;
	const TCHAR *psz = strHeaderFooter;

	while (*psz)
	{
		while (*psz && *psz != '&')
		{
			strExpanded += *psz++;
		}

		if (*psz == '&')
		{
			psz++;

			if (*psz == 'f' || *psz == 'F')
			{
				CCodeDocument *pDoc = GetDocument ();

				// Insert filename (without path)
				strExpanded += pDoc->GetTitle ();
			}
			else if (*psz == 'd' || *psz == 'D')
			{
				SYSTEMTIME PrintTime;
				LCID lcid = GetUserDefaultLCID ();
				int iLen = 0;
				TCHAR *pszFormattedDate = 0;

				::GetLocalTime (&PrintTime);
				iLen = ::GetDateFormat (lcid, DATE_LONGDATE, &PrintTime, NULL,
					pszFormattedDate, 0);
				pszFormattedDate = new TCHAR[iLen];
				::GetDateFormat (lcid, DATE_LONGDATE, &PrintTime, NULL,
					pszFormattedDate, iLen);
				strExpanded += pszFormattedDate;
				delete pszFormattedDate;
			}
			else if (*psz == 't' || *psz == 'T')
			{
				SYSTEMTIME PrintTime;
				LCID lcid = GetUserDefaultLCID ();
				int iLen = 0;
				TCHAR *pszFormattedTime = 0;

				::GetLocalTime (&PrintTime);
				iLen = ::GetTimeFormat (lcid, 0, &PrintTime, NULL,
					pszFormattedTime, 0);
				pszFormattedTime = new TCHAR[iLen];
				::GetTimeFormat (lcid, 0, &PrintTime, NULL,
					pszFormattedTime, iLen);
				strExpanded += pszFormattedTime;
				delete pszFormattedTime;
			}
			else if (*psz == 'p' || *psz == 'P')
			{
				int iOffset = 0;
				CString strPage;

				psz++;

				if (*psz == '+')
				{
					psz++;

					while (_istdigit (*psz))
					{
						iOffset = iOffset * 10 + *psz - '0';
						*psz++;
					}
				}

				strPage.Format (_T("%d"), iPage + iOffset);
				strExpanded += strPage;
				psz--;
			}
			else if (*psz == '&')
			{
				strExpanded += '&';
			}
			else if (*psz == 'l' || *psz == 'L')
			{
				eAlignment = eLeft;
			}
			else if (*psz == 'c' || *psz == 'C')
			{
				eAlignment = eCentre;
			}
			else if (*psz == 'r' || *psz == 'R')
			{
				eAlignment = eRight;
			}

			psz++;
		}
	}

	strHeaderFooter = strExpanded;
}

/////////////////////////////////////////////////////////////////////////////
// CCodeEditView message handlers

int CCodeEditView::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate (lpCreateStruct) == -1)
		return -1;

	m_DropTarget.Register (this);

	// Read Font info and set CEditView to use this font.
	// The registry settings for NOTEPAD are used
	// so that the applications are interchangable.
	HKEY hKey = 0;
	CString strNotepadRegKey;
	LONG lRet = 0;

	strNotepadRegKey = "Software\\Microsoft\\Notepad";
	lRet = ::RegOpenKey (HKEY_CURRENT_USER, strNotepadRegKey, &hKey);

	if (lRet == ERROR_SUCCESS)
	{
		CString strEntry;
		ULONG ulSize = 4;
		DWORD dwType = 0;
		CDC *pDC = GetDC ();
		TCHAR szHeaderFooter[40 + 1] = _T("");

		strEntry = "iPointSize";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_iPointSize, &ulSize);
		m_lfDefFont.lfHeight = -MulDiv(m_iPointSize / 10,
			GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);
		m_lfDefFont.lfWidth = 0;
		ReleaseDC (pDC);
		strEntry = "lfEscapement";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfEscapement, &ulSize);
		strEntry = "lfOrientation";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfOrientation, &ulSize);
		strEntry = "lfWeight";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfWeight, &ulSize);
		strEntry = "lfItalic";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfItalic, &ulSize);
		strEntry = "lfUnderline";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfUnderline, &ulSize);
		strEntry = "lfStrikeOut";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfStrikeOut, &ulSize);
		strEntry = "lfCharSet";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfCharSet, &ulSize);
		strEntry = "lfOutPrecision";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfOutPrecision, &ulSize);
		strEntry = "lfClipPrecision";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfClipPrecision, &ulSize);
		strEntry = "lfQuality";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfQuality, &ulSize);
		strEntry = "lfPitchAndFamily";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_lfDefFont.lfPitchAndFamily, &ulSize);
		strEntry = "iMarginBottom";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_rectMargin.bottom, &ulSize);
		strEntry = "iMarginLeft";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_rectMargin.left, &ulSize);
		strEntry = "iMarginRight";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_rectMargin.right, &ulSize);
		strEntry = "iMarginTop";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) &m_rectMargin.top, &ulSize);
		ulSize = sizeof (m_lfDefFont.lfFaceName);
		strEntry = "lfFaceName";
		lRet = ::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) m_lfDefFont.lfFaceName, &ulSize);
		strEntry = "szHeader";

		if (!::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) szHeaderFooter, &ulSize))
		{
			m_strHeader = szHeaderFooter;
		}

		strEntry = "szTrailer";

		if (!::RegQueryValueEx (hKey, strEntry, 0, &dwType,
			(unsigned char *) szHeaderFooter, &ulSize))
		{
			m_strFooter = szHeaderFooter;
		}

		::RegCloseKey (hKey);
		m_font.CreateFontIndirect(&m_lfDefFont);
		SetFont (&m_font);
	}

	GetEditCtrl ().SetLimitText (0x7fffffff);
	return 0;
}

void CCodeEditView::OnDestroy ()
{
	HKEY hKey = 0;
	CString strNotepadRegKey;
	LONG lRet = 0;

	strNotepadRegKey = "Software\\Microsoft\\Notepad";
	lRet = ::RegOpenKey (HKEY_CURRENT_USER, strNotepadRegKey, &hKey);

	if (lRet == ERROR_SUCCESS)
	{
		CString strEntry;
		DWORD dwType = REG_DWORD;
		ULONG ulSize = sizeof (REG_DWORD);
		DWORD dwWrap = IsWordWrapEnabled ();
		const TCHAR *pszHeader = m_strHeader;
		const TCHAR *pszFooter = m_strFooter;
#if 0
		strEntry.LoadString (IDS_WRAP);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &dwWrap, ulSize);
		strEntry.LoadString (IDS_POINT_SIZE);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_iPointSize, ulSize);
		strEntry.LoadString (IDS_ESCAPEMENT);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfEscapement, ulSize);
		strEntry.LoadString (IDS_ORIENTATION);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfOrientation, ulSize);
		strEntry.LoadString (IDS_WEIGHT);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfWeight, ulSize);
		strEntry.LoadString (IDS_ITALIC);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfItalic, ulSize);
		strEntry.LoadString (IDS_UNDERLINE);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfUnderline, ulSize);
		strEntry.LoadString (IDS_STRIKE_OUT);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfStrikeOut, ulSize);
		strEntry.LoadString (IDS_CHAR_SET);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfCharSet, ulSize);
		strEntry.LoadString (IDS_OUT_PRECISION);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfOutPrecision, ulSize);
		strEntry.LoadString (IDS_CLIP_PRECISION);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfClipPrecision, ulSize);
		strEntry.LoadString (IDS_QUALITY);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfQuality, ulSize);
		strEntry.LoadString (IDS_PITCH_AND_FAMILY);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_lfDefFont.lfPitchAndFamily, ulSize);
		strEntry.LoadString (IDS_MARGIN_BOTTOM);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_rectMargin.bottom, ulSize);
		strEntry.LoadString (IDS_MARGIN_LEFT);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_rectMargin.left, ulSize);
		strEntry.LoadString (IDS_MARGIN_RIGHT);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_rectMargin.right, ulSize);
		strEntry.LoadString (IDS_MARGIN_TOP);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) &m_rectMargin.top, ulSize);
		ulSize = sizeof (m_lfDefFont.lfFaceName);
		dwType = REG_SZ;
		strEntry.LoadString (IDS_FACE_NAME);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) m_lfDefFont.lfFaceName, ulSize);
		strEntry.LoadString (IDS_HEADER);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) pszHeader, ulSize);
		strEntry.LoadString (IDS_TRAILER);
		lRet = ::RegSetValueEx (hKey, strEntry, 0, dwType,
			(unsigned char *) pszFooter, ulSize);
#endif
		::RegCloseKey (hKey);
	}

	CEditView::OnDestroy();
}

void CCodeEditView::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (!GetDocument()->GetReadOnly ());
}

void CCodeEditView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (!GetDocument()->GetReadOnly ());
}

void CCodeEditView::OnFilePageSetup ()
{
#if 0
	CMyPageSetupDlg dlg (m_strHeader, m_strFooter);
	PRINTDLG pd;

	pd.hDevNames = NULL;
	pd.hDevMode = NULL;
	AfxGetApp ()->GetPrinterDeviceDefaults (&pd);
	dlg.m_psd.hDevNames = pd.hDevNames;
	dlg.m_psd.hDevMode = pd.hDevMode;
	dlg.m_psd.rtMargin = m_rectMargin;

	if (dlg.DoModal () == IDOK)
	{
		dlg.GetMargins (&m_rectMargin, 0);
		dlg.GetHeader (m_strHeader);
		dlg.GetFooter (m_strFooter);
		AfxGetApp ()->SelectPrinter (dlg.m_psd.hDevNames,
			dlg.m_psd.hDevMode);
	}
#endif
}

void CCodeEditView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable (m_pUndo && m_pUndo->m_eWhat != FOCodeUndo::eHead);
}

void CCodeEditView::OnEditUndo ()
{
	if (m_pUndo->m_eWhat != FOCodeUndo::eHead)
	{
		bool bTransaction = false;

		do
		{
			bTransaction = m_pUndo->m_bTransaction;

			if (m_pUndo->m_eWhat == FOCodeUndo::eDelete)
			{
				SetSel (m_pUndo->m_iStart, m_pUndo->m_iStart);
				// Don't record undo history..!
				GetEditCtrl ().ReplaceSel (m_pUndo->m_strText.c_str ());
			}
			else
			{
				SetSel (m_pUndo->m_iStart, m_pUndo->m_iEnd);
				// Don't record undo history..!
				GetEditCtrl ().ReplaceSel (_T(""));
			}

			if (m_pUndo->m_pPrev) m_pUndo = m_pUndo->m_pPrev;
		} while (m_pUndo->m_bTransaction && !bTransaction);

		if (m_pUndo->m_eWhat == FOCodeUndo::eHead && !m_bModifiedBeforeFirstUndo)
			GetDocument ()->SetModifiedFlag (FALSE);
	}
}

void CCodeEditView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (m_pUndo && m_pUndo->m_pNext);
}

void CCodeEditView::OnEditRedo ()
{
	if (m_pUndo->m_pNext)
	{
		bool bTransaction = false;

		do
		{
			bTransaction = m_pUndo->m_bTransaction;
			m_pUndo = m_pUndo->m_pNext;

			if (m_pUndo->m_eWhat == FOCodeUndo::eDelete)
			{
				SetSel (m_pUndo->m_iStart, m_pUndo->m_iEnd);
				// Don't record undo history..!
				GetEditCtrl ().ReplaceSel (_T(""));
			}
			else
			{
				SetSel (m_pUndo->m_iStart, m_pUndo->m_iStart);
				// Don't record undo history..!
				GetEditCtrl ().ReplaceSel (m_pUndo->m_strText.c_str ());
			}
		} while (m_pUndo->m_bTransaction && m_pUndo->m_pNext && !bTransaction);
	}
}

void CCodeEditView::OnUpdateEditClearUndoHistory (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (m_pUndo && (m_pUndo->m_pPrev || m_pUndo->m_pNext));
}

void CCodeEditView::OnEditClearUndoHistory ()
{
	ClearUndoHistory (GetDocument ()->IsModified () != 0);
}

void CCodeEditView::OnEditFind ()
{
//	static_cast<CMainFrame *> (AfxGetMainWnd ())->OnEditFind ();
}

void CCodeEditView::OnEditRepeat ()
{
	CWaitCursor wait;

	CCodeDocument *pDoc = GetDocument ();

	if (pDoc->GetFindText ().GetLength ())
	{
		if (pDoc->GetRegEx ())
		{
			if (pDoc->GetCompiled ())
			{
				pDoc->FindTextRE ();
			}
			else
			{
				OnEditFind ();
			}
		}
		else
		{
			pDoc->FindText ();
		}
	}
	else
	{
		OnEditFind ();
	}
}

void CCodeEditView::OnEditReplace ()
{
//	static_cast<CMainFrame *> (AfxGetMainWnd ())->OnEditReplace ();
}

void CCodeEditView::OnEditGoto()
{
#if 0
	CGotoDlg Dlg;

	if (Dlg.DoModal () == IDOK)
	{
		int iLine = Dlg.m_uiLine - 1;
		int iColumn = Dlg.m_uiColumn - 1;
		int iLineIndex = GetEditCtrl ().LineIndex (iLine) + iColumn;

		SetSel (iLineIndex, iLineIndex);
	}
#endif
}

void CCodeEditView::OnUpdateEditPaste (CCmdUI* pCmdUI)
{
	if (GetDocument ()->GetReadOnly ())
	{
		pCmdUI->Enable (false);
	}
	else
	{
		CEditView::OnUpdateNeedClip (pCmdUI);
	}
}

void CCodeEditView::OnUpdateNeedFind(CCmdUI* pCmdUI)
{
//	bool bEnable = GetWindowTextLength() != 0 &&
//		GetDocument()->NeedFind ();

	pCmdUI->Enable (TRUE);
}

void CCodeEditView::OnUpdateNotReadOnly (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (!GetDocument ()->GetReadOnly ());
}

void CCodeEditView::OnEditTimedate()
{
	InsertTimeDate (false);
}

void CCodeEditView::OnOptionsScrollToEnd ()
{
	GetDocument ()->ToggleScrollToEnd ();
}

void CCodeEditView::OnUpdateOptionsScrollToEnd(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (GetDocument ()->GetScrollToEnd ());
}

void CCodeEditView::OnUpdateOptionsFileChangeNotify(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (GetDocument ()->GetFileChangeNotify ());
}

void CCodeEditView::OnOptionsFileChangeNotify()
{
	GetDocument ()->ToggleFileChangeNotify ();
}

void CCodeEditView::OnUpdateOptionsAutoReload (CCmdUI* pCmdUI)
{
	if (GetDocument ()->GetFileChangeNotify ())
	{
		pCmdUI->SetCheck (GetDocument ()->GetAutoReload ());
	}
	else
	{
		pCmdUI->SetCheck (FALSE);
		pCmdUI->Enable (FALSE);
	}
}

void CCodeEditView::OnOptionsAutoReload ()
{
	GetDocument ()->ToggleAutoReload ();
}

void CCodeEditView::OnUpdateFormatWordWrap (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (IsWordWrapEnabled ());
}

void CCodeEditView::OnFormatWordWrap ()
{
	ToggleWordWrap ();
	ClearUndoHistory (GetDocument ()->IsModified () != 0);
}

void CCodeEditView::OnUpdateFormatReadOnly (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (IsReadOnlyEnabled ());
}

void CCodeEditView::OnFormatReadOnly ()
{
	ToggleReadOnly ();
}

void CCodeEditView::OnFormatFont ()
{
   // get current font description
   CFont* pFont = GetFont();
   LOGFONT lf;

   if (pFont != NULL)
	   pFont->GetObject(sizeof(LOGFONT), &lf);
   else
	   ::GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);

	CFontDialog dlg(&lf, CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT);

	if (dlg.DoModal() == IDOK)
	{
		// switch to new font.
		m_font.DeleteObject ();

		if (m_font.CreateFontIndirect(&lf))
		{
			CWaitCursor wait;

			SetFont(&m_font);
			m_lfDefFont = lf;
			m_iPointSize = dlg.m_cf.iPointSize;
		}
	}
}

LRESULT CCodeEditView::OnNotifyFileChange (WPARAM wParam, LPARAM lParam)
{
	// This function is called via PostMessage, therefore
	// m_bFileChange can only be set by the main thread,
	// meaning no critical section is required...
	if (!m_bFileChange)
	{
		CCodeDocument *pDoc = GetDocument ();
		CString strFmt;
		CString strMsg;
		CString strPathName = pDoc->GetPathName ();
		CString strNotepadRE;

		strFmt = "%s\r\n\r\nThis file has been modified outside of the editor.  Do you want to reload it?";
		strMsg.Format (strFmt, strPathName);
		m_bFileChange = true;
		strNotepadRE = "Software\\Microsoft\\Notepad";

		if ((pDoc->GetAutoReload () && !pDoc->IsModified ()) ||
			MessageBox (strMsg, strNotepadRE, MB_ICONQUESTION | MB_YESNO) ==
			IDYES)
		{
			AfxGetApp ()->OpenDocumentFile (strPathName);
		}

		m_bFileChange = false;
	}

	return 0;
}

void CCodeEditView::OnLButtonDown(UINT nFlags, CPoint point)
{
	int iStart, iEnd;
	bool bDrag = false;

	GetEditCtrl ().GetSel (iStart, iEnd);

	if (iStart != iEnd)
	{
		CRect rect;
		CPoint startPoint;
		CPoint endPoint;
		CDC *pDC = GetDC ();
		LPCTSTR pszText = LockBuffer ();
		TCHAR szEndChar[1 + 1];
		CSize EndCharSize;

		// Determine whether a drag is being attempted
		_tcsncpy (szEndChar, pszText + iEnd - 1, 1);
		szEndChar[1] = 0;
		UnlockBuffer ();
		startPoint = GetEditCtrl ().PosFromChar (iStart);
		endPoint = GetEditCtrl ().PosFromChar (iEnd - 1);
		EndCharSize = pDC->GetTextExtent (szEndChar, 1);
		rect.left = startPoint.x;
		rect.top = startPoint.y;
		rect.right = endPoint.x + EndCharSize.cx;
		rect.bottom = endPoint.y + EndCharSize.cy;
		bDrag = PtInRect (&rect, point) != 0;
	}

	if (bDrag)
	{
		LPCTSTR pszText = LockBuffer ();
		const int iSize = iEnd - iStart;
		TCHAR *pszSelection = new TCHAR[iSize + 1];
		COleDropSource DropSource;
		COleDataSource DropData;

		_tcsncpy (pszSelection, pszText + iStart, iSize);
		pszSelection[iSize] = 0;
		UnlockBuffer ();
		HGLOBAL hMem =
			::GlobalAlloc (GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE,
			(iSize + 1) * sizeof (TCHAR));
		memcpy ((TCHAR *) ::GlobalLock (hMem), pszSelection,
			(iSize + 1) * sizeof (TCHAR));
		::GlobalUnlock (hMem);
#ifdef UNICODE
		DropData.CacheGlobalData (CF_UNICODETEXT, hMem);
#else
		DropData.CacheGlobalData (CF_TEXT, hMem);
#endif

		DROPEFFECT de = DropData.DoDragDrop (DROPEFFECT_COPY|DROPEFFECT_MOVE,
			NULL);

		::GlobalFree (hMem);
		delete[] pszSelection;

		if (de == DROPEFFECT_MOVE)
		{
			ReplaceSelWithUndo (_T(""));
		}
	}
	else
	{
		CEditView::OnLButtonDown(nFlags, point);
	}
}

void CCodeEditView::OnTimer (UINT nIDEvent)
{
	if (nIDEvent == m_uiTimer)
	{
		CString strPathName = GetDocument ()->GetPathName ();
		WIN32_FILE_ATTRIBUTE_DATA FileAttributeData;

		// Check if someone else has deleted the file
		if (GetFileAttributes (strPathName) != 0xffffffff)
		{
			::GetFileAttributesEx (strPathName, GetFileExInfoStandard,
				&FileAttributeData);

			if (FileAttributeData.ftLastWriteTime.dwLowDateTime !=
				m_FileAttributeData.ftLastWriteTime.dwLowDateTime ||
				FileAttributeData.ftLastWriteTime.dwHighDateTime !=
				m_FileAttributeData.ftLastWriteTime.dwHighDateTime)
			{
				PostMessage (WM_NOTIFY_FILE_CHANGE);
				m_FileAttributeData = FileAttributeData;
			}
		}
		else
		{
			// If the file no longer exists, mark it in need of a save
			GetDocument ()->SetModifiedFlag ();
		}
	}
	else
	{
		CEditView::OnTimer(nIDEvent);
	}
}

void CCodeEditView::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 3 /*Ctrl-C*/ && nChar != 22 /*Ctrl-V*/ &&
		nChar != 24 /*Ctrl-X*/ && nChar != 26 /*Ctrl-Z*/)
	{
		int iStart = 0;
		int iEnd = 0;

		ASSERT (nRepCnt == 1);
		GetSel (iStart, iEnd);

		if (nChar == VK_BACK)
		{
			if (!(iStart == iEnd && iStart == 0))
			{
				DelSelWithUndo (iStart == iEnd ? iStart - 1 : iStart, iEnd);
			}
		}
		else
		{
			TCHAR sz[2] = {nChar, 0};

			ReplaceSelWithUndo (sz, iStart, iEnd, false);

			if (nChar == '\r')
			{
				++m_pUndo->m_iEnd;
				m_pUndo->m_strText += '\n';
			}
		}

		CEditView::OnChar (nChar, nRepCnt, nFlags);
	}
}

void CCodeEditView::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	bool bExecute = true;

	// VK_DELETE never reaches OnChar, so we process it here.
	// Shift-Del is ignored as it will be processed by the WM_CUT
	// handler.
	if (nChar == VK_DELETE && !(GetKeyState (VK_SHIFT) & 0x80))
	{
		int iStart = 0;
		int iEnd = 0;

		GetEditCtrl ().GetSel (iStart, iEnd);
		DelSelWithUndo (iStart, iStart == iEnd ? iStart + 1 : iEnd);
	}
	else if (!(GetKeyState (VK_SHIFT) &0x80) &&
		(GetKeyState (VK_CONTROL) & 0x80))
	{
		// ^X and ^V do not have virtual key codes so we cannot
		// cleanly process them in OnChar. CFilterEdit::WindowProc deals with
		// responding to WM_CUT, WM_COPY and WM_PASTE
		if (nChar == 'x' || nChar == 'X')
		{
			SendMessage (WM_CUT, 0, 0);
			// Will handle cut ourselves, so don't pass char on...
			bExecute = false;
		}
		// Event though WM_COPY doesn't have any special processing for Undo/Redo
		// trap it here as it is ignored by OnChar().
		else if (nChar == 'c' || nChar == 'C')
		{
			SendMessage (WM_COPY, 0, 0);
			// Will handle copy ourselves, so don't pass char on...
			bExecute = false;
		}
		else if (nChar == 'v' || nChar == 'V')
		{
			SendMessage (WM_PASTE, 0, 0);
			// Will handle paste ourselves, so don't pass char on...
			bExecute = false;
		}
	}

	if (bExecute)
	{
		CEditView::OnKeyDown (nChar, nRepCnt, nFlags);
	}
}

LRESULT CCodeEditView::WindowProc (UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLEAR:
	case WM_CUT:
	{
		int iStart = 0;
		int iEnd = 0;

		GetEditCtrl ().GetSel (iStart, iEnd);

		if (iStart != iEnd)
		{
			DelSelWithUndo (iStart, iEnd);
		}

		break;
	}
	case WM_PASTE:
	{
		int iStart = 0;
		int iEnd = 0;
		const TCHAR *psz = LockBuffer ();

		GetEditCtrl ().GetSel (iStart, iEnd);

		if (message == WM_PASTE)
		{
			if (OpenClipboard ())
			{
#ifdef _UNICODE
				HANDLE hClipMem = ::GetClipboardData (CF_UNICODETEXT);
#else
				HANDLE hClipMem = ::GetClipboardData (CF_TEXT);
#endif

				if (hClipMem)
				{
					const TCHAR *lpClipMem = (const TCHAR *) ::GlobalLock (hClipMem);

					if (lpClipMem)
					{
						ReplaceSelWithUndo (lpClipMem, iStart, iEnd, false);
					}

					::GlobalUnlock (hClipMem);
				}

				::CloseClipboard ();
			}
		}

		UnlockBuffer ();
		break;
	}
	default:
		break;
	}

	return CEditView::WindowProc (message, wParam, lParam);
}

void CCodeEditView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	{
		m_pMenuData = new CFOPMenuTheme;
		m_pMenuData->InstallWnd(this);
	
	}
}
