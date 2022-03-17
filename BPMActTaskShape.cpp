// BPMActTaskShape.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BPMActTaskShape.h"
#include "MultisimDemo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CBPMActTaskShape Class
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CBPMActTaskShape, CFORectShape, 0)
CBPMActTaskShape::CBPMActTaskShape()
{
	SetType(BPM_ACT_TASK_SHAPE);

	SetBrushType(1);
	SetBkColor(RGB(224,248,248));
	SetMultiLine(FALSE);
	m_bShowLabelAtFirst = TRUE;
	SetWithLabelShow(TRUE);
	SetWithLabelRotating(TRUE);
	m_bWithTextWrap		= TRUE;
	SetWeight(700);
	SetFaceName(_T("Arial"));
	SetPointSize(12);
	AddStringUserProperty(P_ID_EXT_CONNECT_FORM, _T(""),  _T("Connect Form"));
	AddIntUserProperty(P_ID_EXT_PERFORMER, 0,  _T("Connect Form"));
	SetStateString(_T("User@Adapters@Subprocesses"));
	SetStateType(_T("User"));
m_bWithTextClip		= FALSE;
}

CBPMActTaskShape::CBPMActTaskShape(const CBPMActTaskShape& src)
{
	*this = src;
}

CBPMActTaskShape::~CBPMActTaskShape()
{

}

/////////////////////////////////////////////////////////////////////////////
// CBPMActTaskShape diagnostics

#ifdef _DEBUG
void CBPMActTaskShape::AssertValid() const
{
	CFORectShape::AssertValid();
}

void CBPMActTaskShape::Dump(CDumpContext& dc) const
{
	CFORectShape::Dump(dc);
}
#endif //_DEBUG

void CBPMActTaskShape::ExtGeometryUpdated(CFOArea* pArea)
{
	pArea->Clear();
	if (m_lpShapePoints && pArea)
	{
		
		CPoint ptPoints[3];
		ptPoints[0] = m_lpShapePoints[0];
		ptPoints[1] = m_ptExtAnchor;
		ptPoints[2] = m_lpShapePoints[1];
		
		pArea->BuildArea(ptPoints, 3,CFOArea::AreaLine);
		
		m_rectPosition = pArea->GetBoundingRect();
		
		CalcExtendBoundRect(m_rectPosition);
	}
}

CRect CBPMActTaskShape::CalcLabelPosition(CDC *pDC,BOOL &bFullSize) const
{
	CBPMActTaskShape *pShape = (CBPMActTaskShape *) ((const CBPMActTaskShape *)this);
	
	CPoint ptLabel = m_ptExtAnchor;
	
	CRect rcNew = GetSnapRect();
	if(!m_bWithTextWrap)
		rcNew.InflateRect(gfxData.fo_DefaultSnapLineSizPix * 20000,gfxData.fo_DefaultSnapLineSizPix * 20000,
		gfxData.fo_DefaultSnapLineSizPix * 20000,gfxData.fo_DefaultSnapLineSizPix * 20000);
	
	
	CString strCaption = GetObjectCaption();
	
	int nH;
	CSize sizeText = pShape->GetTextSize(pDC,rcNew,strCaption,nH);
	sizeText += CSize(4,4);
	
	CPoint ptCenter;
	
	ptCenter = ptLabel;
	
	CRect rcTextBox;
	rcTextBox.left = (ptCenter.x - sizeText.cx / 2);
	rcTextBox.right = rcTextBox.left + sizeText.cx;
	
	rcTextBox.top = (ptCenter.y - sizeText.cy / 2);
	rcTextBox.bottom = rcTextBox.top + sizeText.cy;
	
	rcTextBox.NormalizeRect();
	bFullSize = FALSE;
	
	return rcTextBox;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void CBPMActTaskShape::Create(CRect &rcPos,CString strCaption)
{
	CFORectShape::Create(rcPos,strCaption);

	// FODO: Add your own code here.
	RemoveAllPorts();

	CreateDefaultPort(0.0, 0.5);
	CreateDefaultPort(0.5, 0.0);
	CreateDefaultPort(1.0, 0.5);
	CreateDefaultPort(0.5, 1.0);

	FOPRect rce = rcPos;
	CPoint ptx = rce.BottomCenter();
	ptx.y += 17;
	m_ptSaveExtAnchor = m_ptExtAnchor = ptx;

}

void CBPMActTaskShape::DoSubMenuChange(const int &nMenuItem, const CString &strState)
{
	SetStateType(strState);
	PutPropIntValue(P_ID_EXT_PERFORMER, nMenuItem);
}

void CBPMActTaskShape::Serialize(CArchive& ar)
{
	CFORectShape::Serialize(ar);
	if(ar.IsStoring())
	{
		//FODO:Add your own code here.
	ar << m_ptSaveExtAnchor.x;
	ar << m_ptSaveExtAnchor.y;
	}
	else
	{
		//FODO:Add your own code here.
	if(m_nVersion >= 48)
	{
		ar >> m_ptSaveExtAnchor.x;
		ar >> m_ptSaveExtAnchor.y;
	}
	else
	{
		FOPPoint ptAt;
		ar >>ptAt;
		m_ptSaveExtAnchor = ptAt;
	}
		CFOMatrix* pMat = GetValidateMatrix();
		
		FOPPoint ptx;
		ptx = m_ptSaveExtAnchor;
		pMat->ChangeValue(ptx);
		m_ptExtAnchor = ptx;
	}
}

BOOL CBPMActTaskShape::IsSelected()
{
	if(GetParentWnd() != NULL)
	{		
		CFOPCanvasCore *pView = static_cast<CFOPCanvasCore *>(GetParentWnd());
		POSITION pos = pView->GetSelectShapes()->GetHeadPosition();
		while(pos != NULL)
		{
			CFODrawShape *pShape = (CFODrawShape *)pView->GetSelectShapes()->GetNext(pos);
			if(pShape == this)
			{
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

void CBPMActTaskShape::OnDrawTextAndEdit(CDC *pDC,const CRect &rcText,const BOOL &bFullSize)
{
	//FODO:Add your own code below.
	if(!GetWithLabelShow())
	{
		return;
	}
	
	if(!GetShowLabelAtFirst())
	{
		return;
	}
	
	if(!gfxData.m_bfoDrawText)
	{
		return;
	}
	
	if(gfxData.m_bWithPanningDraw)
	{
		int nL = GetLineWidth();
		BOOL bNull = IsNullPen();
		if(!bNull && nL > 0)
		{
			return;
		}
	}
	
	BOOL bSelected = IsSelected();
	
	BOOL bDisable = FALSE;
	FO_VALUE value;
	if (TRUE == GetPropValue(value, P_ID_DISABLED))
		bDisable = value.m_bValue;
	
	CString strLabel = GenEditingLabel();
	
	UINT nAlign = GetDrawFormatType();
	if (m_pEdit != NULL)
	{
		if(GetWithLabelEditing())
		{
			DrawEditBox(pDC,rcText,strLabel,bFullSize);
		}
	}
	else
	{
		if(!IsFlat())
		{
			int nBrushType = GetShadowBrushType();
			if(GetShadow())
			{
				UINT nAlign = GetDrawFormatType();
				if (m_pEdit == NULL)
				{
					COLORREF crText;
					if(nBrushType != 2)
					{
						crText = (COLORREF)GetShadowColor();
					}
					else 
					{
						crText = (COLORREF)GetShadowPatternColor();
					}
					
					CRect rcPos = rcText;
					rcPos.NormalizeRect();
					
					CPoint ptOffset = CPoint(GetShadowOffsetX(),GetShadowOffsetY());
					rcPos.OffsetRect(ptOffset);
					DoDrawText(pDC,strLabel,rcPos,nAlign,crText,FALSE);
				}
			}
		}
		
		COLORREF crColor = GetFontColor();
		if(bDisable)
		{
			crColor = gfxData.m_crBtnShadow;
		}
		if(bSelected)
		{
			crColor = RGB(255,0,0);
		}
		DoDrawText(pDC,strLabel,rcText,nAlign,crColor,bFullSize);
	}
}
void CBPMActTaskShape::OnDraw(CDC *pDC)
{
	if(!IsVisible())
	{
		return;
	}
	
	if(m_bCurUpdateDraw)
	{ 
		DoCurrentValueChange(m_dCurValue);
		m_bCurUpdateDraw = FALSE; 
	}
 
	if(m_bNeedValid)
	{
		UpdateComp();
		m_bNeedValid = FALSE;
	}
	
	if(GetShadow() && gfxData.m_bShadowTemp)
	{
		PrepareShadowDC(pDC);
		OnDrawShadow(pDC);
		ClearShadowDC(pDC);
	}
	
	PrepareDC(pDC);
	
	
	if(IsFlat())
	{
		OnDrawFlat(pDC);
	}
	else
	{
		OnDraw3d(pDC);
	}
	
	ClearDC(pDC);
	
	OnDrawPorts(pDC,TRUE);
}

void CBPMActTaskShape::GetPlusSpotLocation(CFOPHandleList& lstHandle)
{
	CFOPHandle* pHandle = NULL;
	pHandle = new CFOPHandle(FOPPoint(m_ptExtAnchor),SPOT_2_ANCHOR);
	lstHandle.AddHandle(pHandle);
	
}

void CBPMActTaskShape::DoAddCustProp()
{
	CFORectShape::DoAddCustProp();

}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CBPMActTaskShape::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
								 CFileException* pError)
{
	CMirrorFile* pFile = new CMirrorFile;
	ASSERT(pFile != NULL);
	if (!pFile->Open(lpszFileName, nOpenFlags, pError))
	{
		delete pFile;
		pFile = NULL;
	}
	return pFile;
}

void CBPMActTaskShape::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CBPMActTaskShape::OpenDocument(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		return FALSE;
	}
	
	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		if (pFile->GetLength() != 0)
			Serialize(loadArchive);     // load me
		loadArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
		return TRUE;
}

BOOL CBPMActTaskShape::SaveDocument(LPCTSTR lpszPathName)
{
	
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	
	if (pFile == NULL)
	{
		
		return FALSE;
	}
	
	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
		return TRUE;        // success
}

CBPMActTaskShape& CBPMActTaskShape::operator=(const CBPMActTaskShape& src)
{
	(*(CFORectShape*)this) = src;
	return (*this);
}

CFODrawShape* CBPMActTaskShape::Copy() const
{
	return (new CBPMActTaskShape(*this));
}

void CBPMActTaskShape::PrepareDC(CDC* pDC)
{
	CFORectShape::PrepareDC(pDC);

	//FODO:Add your own code below.
	
}

void CBPMActTaskShape::OnDrawTrackCustom(CDC *pDC)
{
	CFORectShape::OnDrawTrackCustom(pDC);

	// Add your own code here.

}

void CBPMActTaskShape::OnDrawShadow(CDC *pDC)
{
	CFORectShape::OnDrawShadow(pDC);
	
	//FODO:Add your own code below.
	
}

void CBPMActTaskShape::OnDrawFlat(CDC *pDC)
{
	OnDraw3d(pDC);
}

void CBPMActTaskShape::OnDraw3d(CDC *pDC)
{
	CFODrawShape::OnDraw3d(pDC);

	//FODO:Add your own code below.
	CRect rcTemp = GetDrawRect();
	rcTemp.NormalizeRect();

	CPen pen(PS_SOLID, 2, RGB(0,0,0));
	CPen *pOldPen = (CPen *)pDC->SelectObject(&pen);

	pDC->RoundRect(&rcTemp, CPoint(15,15));
	CPoint ptX = rcTemp.CenterPoint();
	
// 	if(theApp.m_drawlist.GetSafeHandle() != NULL)
// 	{
// 		int nType = 1;
// 		GetPropIntValue(nType, P_ID_EXT_PERFORMER);
// 		theApp.m_drawlist.Draw( pDC, nType, CPoint(ptX.x - 16, ptX.y - 16), ILD_TRANSPARENT );
// 	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	CPoint m_ptLabel = m_ptExtAnchor;
	
	CRect rcNew = GetSnapRect();
	if(!m_bWithTextWrap)
		rcNew.InflateRect(gfxData.fo_DefaultSnapLineSizPix * 20000,gfxData.fo_DefaultSnapLineSizPix * 20000,
		gfxData.fo_DefaultSnapLineSizPix * 20000,gfxData.fo_DefaultSnapLineSizPix * 20000);
	
	
	CString strCaption = GetObjectCaption();
	
	int nH;
	CSize sizeText = GetTextSize(pDC,rcNew,strCaption,nH);
	sizeText += CSize(4,4);
	
	CPoint ptCenter = m_ptLabel;
	
	CRect rcTextBox;
	rcTextBox.left = (ptCenter.x - sizeText.cx / 2);
	rcTextBox.right = rcTextBox.left + sizeText.cx;
	
	rcTextBox.top = (ptCenter.y - sizeText.cy / 2);
	rcTextBox.bottom = rcTextBox.top + sizeText.cy;
	
	
	rcTextBox.NormalizeRect();
	OnDrawTextAndEdit(pDC,rcTextBox,FALSE);
}

void CBPMActTaskShape::ClearDC(CDC* pDC)
{
	CFORectShape::ClearDC(pDC);

	//FODO:Add your own code below.

}

void CBPMActTaskShape::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFORectShape::OnLButtonDown(nFlags,point);
	
	//FODO:Add your own code below.

}

void CBPMActTaskShape::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CFORectShape::OnLButtonUp(nFlags,point);

	//FODO:Add your own code below.

}

void CBPMActTaskShape::GeometryUpdated(CFOArea* pRgn)
{
	CFORectShape::GeometryUpdated(pRgn);

	//FODO:Add your own code below.

}
