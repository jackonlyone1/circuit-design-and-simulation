// ExtTabModel.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MultisimDemo.h"
#include "ExtTabModel.h"
#include "MyCorsssLineShape.h"
#include "MyBackShape.h"
#include "FOMatherLineShape.h"
#include "FOVertMatherLineShape.h"
#include "FOMatherDotShape.h"
#include "MultisimDemoDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtTabModel construction/destruction

IMPLEMENT_SERIAL(CExtTabModel, CFOTabPageModel, 0)

CExtTabModel::CExtTabModel()
{
	//FOTO:Add you code here.
	DoInitData();
	SetCanvasSize(30,26);
	m_nCurRotateAngle = 0;
	m_strSymFile = _T("");
	//	m_bWithDiagramMode = FALSE;
	m_pCurSelect = NULL;
}

CExtTabModel::CExtTabModel(const CExtTabModel& source)
{
	m_pCurSelect = NULL;
	*this			= source;
}

CExtTabModel::~CExtTabModel()
{
	//FOTO:Add you code here.
	if(m_pCurSelect != NULL)
	{
		delete m_pCurSelect;
		m_pCurSelect = NULL;
	}
}

CFODataModel* CExtTabModel::Copy() const
{
	return (new CExtTabModel(*this));
}

void CExtTabModel::ClearAll()
{
	if(GetShapes()->GetCount() <= 0)
	{
		return;
	}
	
	BOOL bNeedDo = FALSE;
	CFODirectActionMacro *pAction = new CFODirectActionMacro(this);
	
	CFODrawShapeList m_ListTemp;
	CFODrawShape *pShape = NULL;
	int xy = 0;
	for(xy = 0; xy < GetShapes()->GetCount(); xy ++)
	{
		pShape = (CFODrawShape* )GetShapes()->GetObject(xy);
		if(!pShape->IsDeleteProtect() && (pShape->GetMainShape() == NULL))
		{
			if(HAS_BASE(pShape,CFOLinkShape))
			{
				CFOLinkShape *pLink = static_cast<CFOLinkShape *>(pShape);
				CFORemoveLinkAction *pActionTemp = new CFORemoveLinkAction(this, pLink);
				pActionTemp->SetFromPort(pLink->GetFromPort());
				pActionTemp->SetToPort(pLink->GetToPort());
				pActionTemp->SetThirdPort(pLink->GetThirdPort());
				pActionTemp->SetLayLink(pLink->GetLayOnLink());
				pAction->AddAction(pActionTemp);
				bNeedDo = TRUE;
			}
			else
			{
				m_ListTemp.AddTail((CFODrawShape *)pShape);
			}
		}
	}
	
	if(m_ListTemp.GetCount() > 0)
	{
		bNeedDo = TRUE;
		pAction->AddAction(new CExtRemoveCompsAction(this, m_ListTemp));
	}
	
	if(bNeedDo)
	{
		if(!Do(pAction,TRUE))
		{
			delete pAction;
		}
	}
	else
	{
		delete pAction;
	}
	
}

CFODrawShape* CExtTabModel::HitTestOnBus(CPoint point)
{
	if(m_ShapeList.GetCount() <= 0)
	{
		return NULL;
	}
	
	FOPRect rcHittest = FOPGenHitRect(point);
	
	double dGridX = (double) gfxData.szSelectCompHandleSize.cx * 2;
	
	ConvertToMapLogWithoutUIScale(FUNIT_POINTS,dGridX,FALSE);
	int nExpandSize = (int)dGridX;
	
	//	DWORD ti2 = GetTickCount();
	DoUpdateShapeInview();
	
	// 	if(gfxData.m_bWithAdvanceHit)
	// 	{
	// 	}
	// 	else
	FOPRect rcOver = GetAllVisibleObjBoundRect();
	if(rcHittest.IsOver(rcOver))
	{
		CFODrawShapeSet setHit;
		ShapesAtPt(&setHit, point, nExpandSize);
		
		CFODrawShapeList m_TempList;
		
		CFODrawShape* pObj1 = NULL;
		int xy = 0;
		for(xy = 0; xy < setHit.Count(); xy ++)
		{
			pObj1 = (CFODrawShape* )setHit.GetObject(xy);
			if(pObj1 != NULL && pObj1->m_bWithInView && pObj1->IsVisible())
			{
				if(HAS_BASE(pObj1, CFOVertMatherLineShape) ||
					HAS_BASE(pObj1, CFOMatherLineShape) ||
					HAS_BASE(pObj1, CFOMatherDotShape)
					)
				{
					if(HAS_BASE(pObj1, CFOVertMatherLineShape))
					{
						CFOVertMatherLineShape *pNode = static_cast<CFOVertMatherLineShape *>(pObj1);
						if(CFODrawHelper::Intersection(rcHittest,pNode->GetCurDrawRect()))
						{
							return pNode;
						}
					}
					else if(HAS_BASE(pObj1, CFOMatherLineShape))
					{
						CFOMatherLineShape *pNode = static_cast<CFOMatherLineShape *>(pObj1);
						if(CFODrawHelper::Intersection(rcHittest,pNode->GetCurDrawRect()))
						{
							return pNode;
						}
					}
					else if(HAS_BASE(pObj1, CFOMatherDotShape))
					{
						CFOMatherDotShape *pNode = static_cast<CFOMatherDotShape *>(pObj1);
						if(CFODrawHelper::Intersection(rcHittest,pNode->GetCurDrawRect()))
						{
							return pNode;
						}
					}
				}
				
			}
		}
	}
	
	return NULL;
}

void CExtTabModel::DoInitData()
{
	CFOTabPageModel::DoInitData();
	SetBackDrawComp(new CMyBackShape);
	//FOTO:Add you code here.
}

void CExtTabModel::NotifyObserver(LPARAM lHint, CObject*pHint)
{
	CFOTabPageModel::NotifyObserver(lHint,pHint);

	//FOTO:Add you code here.

}
 
CFODrawShape* CExtTabModel::AddLinkShape2(UINT m_drawshape,
										  CArray<CPoint,CPoint> *arPoints,
										  CFOPortShape *pFrom,
										  CFOPortShape *pTo,
										  int nArrowType)
{
	if(pFrom == NULL)// || pTo == NULL)
	{
		NotifyObserver(FO_HINT_EDIT_BACKGROUND);
		return NULL;
	}

	if(pTo == NULL)
	{
		CFOLinkShape *pHitLink = (CFOLinkShape *)HitTestOnLink(arPoints->GetAt(arPoints->GetSize() -1));
		if(pHitLink == NULL)
		{
			NotifyObserver(FO_HINT_EDIT_BACKGROUND);
			return NULL;
		}
	}

	CFOLinkShape *pReturn = (CFOLinkShape *) CFODataModel::AddLinkShape2(m_drawshape, arPoints, pFrom, pTo, nArrowType);
	
	if(pReturn != NULL)
	{
		pReturn->SetLineColor(RGB(255,0,0));
	}

	return pReturn;
}

void GetShapesIn(CFODrawShapeList &list, CFODrawShapeList *pChildList)
{
	CFODrawShape *pShape = NULL;
	POSITION pos = pChildList->GetHeadPosition();
	while(pos != NULL)
	{
		pShape = (CFODrawShape *)pChildList->GetNext(pos);
		if(pShape->IsKindOf(RUNTIME_CLASS(CFOCompositeShape)))
		{
			CFOCompositeShape *pComp = static_cast<CFOCompositeShape *>(pShape);
			GetShapesIn(list, pComp->GetCompList());
		}
		else
		{
			list.AddTail(pShape);
		}
	}
}

void CExtTabModel::DoInitCreateShape(CFODrawShape *pShape)
{
	if(HAS_BASE(pShape, CFOCompositeShape))
	{
		pShape->SetResizeProtect(TRUE);
		pShape->SetRotateProtect(TRUE);

		return;
	}

	CFODataModel::DoInitCreateShape(pShape);
	
}

void CExtTabModel::GetAllBasicShape(CFODrawShapeList &list)
{
	CFODrawShape *pShape = NULL;
	int xy = 0;
	for(xy = 0; xy < GetShapes()->Count(); xy ++)
	{
		pShape = (CFODrawShape *)GetShapes()->GetObject(xy);
		if(pShape->IsKindOf(RUNTIME_CLASS(CFOCompositeShape)))
		{
			CFOCompositeShape *pComp = static_cast<CFOCompositeShape *>(pShape);
			GetShapesIn(list, pComp->GetCompList());
		}
		else
		{
			list.AddTail(pShape);
		}
	}
}

void GetShapesIn2(CFODrawShapeList &list, CFODrawShapeList *pChildList)
{
	CFODrawShape *pShape = NULL;
	POSITION pos = pChildList->GetHeadPosition();
	while(pos != NULL)
	{
		pShape = (CFODrawShape *)pChildList->GetNext(pos);
		if(pShape->IsKindOf(RUNTIME_CLASS(CFOCompositeShape)) && !pShape->IsKindOf(RUNTIME_CLASS(CFOPSubGraphShape)))
		{
			list.AddTail(pShape);
			
		}
		else if(pShape->IsKindOf(RUNTIME_CLASS(CFOPSubGraphShape)))
		{
			CFOPSubGraphShape *pGraph = static_cast<CFOPSubGraphShape *>(pShape);
			GetShapesIn2(list, pGraph->GetCompList());
		}
	}
}

void CExtTabModel::GetAllComps2(CFODrawShapeList &list)
{
	CFODrawShape *pShape = NULL;
	int xy = 0;
	for(xy = 0; xy < GetShapes()->Count(); xy ++)
	{
		pShape = (CFODrawShape *)GetShapes()->GetObject(xy);
		if(pShape->IsKindOf(RUNTIME_CLASS(CFOCompositeShape)) && 
			!pShape->IsKindOf(RUNTIME_CLASS(CFOPSubGraphShape)))
		{
			list.AddTail(pShape);
			
		}
		else if(pShape->IsKindOf(RUNTIME_CLASS(CFOPSubGraphShape)))
		{
			CFOPSubGraphShape *pGraph = static_cast<CFOPSubGraphShape *>(pShape);
			GetShapesIn2(list, pGraph->GetCompList());
		}
	}
}

CFOPortShape *CExtTabModel::GetTopPort(CFODrawPortsShape *pComp)
{
	CFOPortShape *pReturn = pComp->GetPortByIndex(0);

	if(pReturn == NULL)
	{
		return pReturn;
	}
	
	CPoint ptStart = pReturn->GetLinkPoint();
	
	int nCur = 0;
	POSITION pos = pComp->GetPortsList()->GetHeadPosition();
	CFOPortShape *pShape = NULL;
	while(pos != NULL)
	{
		pShape = (CFOPortShape* )pComp->GetPortsList()->GetNext(pos);
		if(ptStart.y >= pShape->GetLinkPoint().y)
		{
			pReturn = pShape;
		}
		nCur ++;
	}
	
	return pReturn;
}

CFOPortShape *CExtTabModel::GetBottomPort(CFODrawPortsShape *pComp)
{
	CFOPortShape *pReturn = pComp->GetPortByIndex(0);
	
	if(pReturn == NULL)
	{
		return pReturn;
	}
	
	CPoint ptStart = pReturn->GetLinkPoint();
	
	int nCur = 0;
	POSITION pos = pComp->GetPortsList()->GetHeadPosition();
	CFOPortShape *pShape = NULL;
	while(pos != NULL)
	{
		pShape = (CFOPortShape* )pComp->GetPortsList()->GetNext(pos);
		if(ptStart.y <= pShape->GetLinkPoint().y)
		{
			pReturn = pShape;
		}
		nCur ++;
	}
	
	return pReturn;
}

CFOPortShape *CExtTabModel::GetLeftPort(CFODrawPortsShape *pComp)
{
	CFOPortShape *pReturn = pComp->GetPortByIndex(0);
	
	if(pReturn == NULL)
	{
		return pReturn;
	}
	
	CPoint ptStart = pReturn->GetLinkPoint();
	
	int nCur = 0;
	POSITION pos = pComp->GetPortsList()->GetHeadPosition();
	CFOPortShape *pShape = NULL;
	while(pos != NULL)
	{
		pShape = (CFOPortShape* )pComp->GetPortsList()->GetNext(pos);
		if(ptStart.x >= pShape->GetLinkPoint().x)
		{
			pReturn = pShape;
		}
		nCur ++;
	}
	
	return pReturn;
}

CFOPortShape *CExtTabModel::GetRightPort(CFODrawPortsShape *pComp)
{
	CFOPortShape *pReturn = pComp->GetPortByIndex(0);
	
	if(pReturn == NULL)
	{
		return pReturn;
	}
	
	CPoint ptStart = pReturn->GetLinkPoint();
	
	int nCur = 0;
	POSITION pos = pComp->GetPortsList()->GetHeadPosition();
	CFOPortShape *pShape = NULL;
	while(pos != NULL)
	{
		pShape = (CFOPortShape* )pComp->GetPortsList()->GetNext(pos);
		if(ptStart.x <= pShape->GetLinkPoint().x)
		{
			pReturn = pShape;
		}
		nCur ++;
	}
	
	return pReturn;
}

void CExtTabModel::InsertShape2(CFODrawShape* pShape)
{
	if(pShape != NULL)
	{
		if(!pShape->IsTabOrderProtect())
		{
			int nTabOrder = GetUniqueTabOrder();
			pShape->SetTabOrder( nTabOrder);
		}
		
		CFOObserver *pCore = GetFirstObserver();
		pShape->SetModel(this);
		pShape->SetParentWnd((CFOPCanvasCore *)pCore);
	
		{
			FOPRect rcShape = pShape->GetSimpleDrawRect();
			CFODrawShapeSet setHit;
			ShapesOutRect(&setHit, rcShape);

			CFOMatherLineShape *pCurSub = NULL;
			CFOVertMatherLineShape *pCurVertSub = NULL;
			CFOMatherDotShape *pCurDot = NULL;
			CFODrawShape *pShapeX = NULL;
			int xy = 0;
			BOOL bTopRightMode = TRUE;
			if(HAS_BASE(pShape, CFOCompositeShape) || 
				HAS_BASE(pShape, CFOMatherDotShape) ||
				HAS_BASE(pShape, CFOMatherLineShape) ||
				HAS_BASE(pShape, CFOVertMatherLineShape)
				)
			{
				
				for(xy = 0; xy < setHit.Count(); xy ++)
				{
					pShapeX = (CFODrawShape *)setHit.GetObject(xy);
					
					if(pShapeX->IsKindOf(RUNTIME_CLASS(CFOMatherDotShape)))
					{
						CFOMatherDotShape *pTemp = static_cast<CFOMatherDotShape *>(pShapeX);
						if(pTemp->BeWithIn(pShape->GetSnapRect()))
						{
							pCurDot= pTemp;
							
							break;
						}
					}
					else if(pShapeX->IsKindOf(RUNTIME_CLASS(CFOMatherLineShape)))
					{
						CFOMatherLineShape *pTemp = static_cast<CFOMatherLineShape *>(pShapeX);
						FOPRect rcSnap = pTemp->GetSnapRect();
						if(pTemp->BeWithIn(rcSnap))
						{
							pCurSub= pTemp;
							FOPPoint ptCheck = pShape->GetCenterPoint();
							if(ptCheck.y < rcSnap.Center().y)
							{
								bTopRightMode = FALSE;
							}
							break;
						}
					}
					else if(pShapeX->IsKindOf(RUNTIME_CLASS(CFOVertMatherLineShape)))
					{
						CFOVertMatherLineShape *pTemp = static_cast<CFOVertMatherLineShape *>(pShapeX);
						FOPRect rcSnap = pTemp->GetSnapRect();
						if(pTemp->BeWithIn(rcSnap))
						{
							pCurVertSub= pTemp;
							FOPPoint ptCheck = pShape->GetCenterPoint();
							if(ptCheck.x < rcSnap.Center().x)
							{
								bTopRightMode = FALSE;
							}
							break;
						}
					}
				}
			}

			if(pCurSub != NULL)
			{
				CFOPortShape *pPortTo = pCurSub->GetConnectPort();
				CFOPortShape *pPortFrom = GetTopPort((CFODrawPortsShape *)pShape);
				if(!bTopRightMode)
				{
					pPortFrom = GetBottomPort((CFODrawPortsShape *)pShape);
				}

				if(pPortTo != NULL && pPortFrom != NULL)
				{
					FOPRect rc = pCurSub->GetSnapRect();
					FOPRect rcnew = pShape->GetSnapRect();
					if(bTopRightMode)
					{
						pShape->MoveCenterTo(rcnew.CenterPoint().x, pPortTo->GetLinkPoint().y + 90 + rc.Height() /2);
					}
					else
					{
						CPoint ptCenter = CPoint(rcnew.CenterPoint().x, pPortTo->GetLinkPoint().y - 90 - rc.Height() /2);
						pShape->MoveCenterTo(ptCenter.x, ptCenter.y);

						if(!HAS_BASE(pShape, CFOMatherLineShape) && !HAS_BASE(pShape, CFOVertMatherLineShape))
							pShape->RotateShape(1800,ptCenter.x, ptCenter.y);
					}

				}
			}

			if(pCurVertSub != NULL)
			{
				CFOPortShape *pPortTo = pCurVertSub->GetConnectPort();
				CFOPortShape *pPortFrom = GetLeftPort((CFODrawPortsShape *)pShape);
				
				if(pPortTo != NULL && pPortFrom != NULL)
				{
					FOPRect rc = pCurVertSub->GetSnapRect();
					FOPRect rcnew = pShape->GetSnapRect();

					CPoint ptCenter;
					if(bTopRightMode)
					{
						ptCenter = CPoint(pPortTo->GetLinkPoint().x + 90 + rc.Width() / 2, rcnew.CenterPoint().y);
						pShape->MoveCenterTo(ptCenter.x, ptCenter.y);

						if(!HAS_BASE(pShape, CFOMatherLineShape) && !HAS_BASE(pShape, CFOVertMatherLineShape))
						pShape->RotateShape(-900,ptCenter.x, ptCenter.y);
					}
					else
					{
						ptCenter = CPoint(pPortTo->GetLinkPoint().x - 90 - rc.Width() / 2, rcnew.CenterPoint().y);
						pShape->MoveCenterTo(ptCenter.x, ptCenter.y);

						if(!HAS_BASE(pShape, CFOMatherLineShape) && !HAS_BASE(pShape, CFOVertMatherLineShape))
							pShape->RotateShape(-900 + 1800,ptCenter.x, ptCenter.y);
					}
					
					
					
				}
			}

			if(pCurDot != NULL)
			{
				CFOPortShape *pPortTo = pCurDot->GetConnectPort();
				CFOPortShape *pPortFrom = GetTopPort((CFODrawPortsShape *)pShape);
				
				if(pPortTo != NULL && pPortFrom != NULL)
				{
					FOPRect rc = pCurDot->GetSnapRect();
					FOPRect rcnew = pShape->GetSnapRect();
					pShape->MoveCenterTo(pPortTo->GetLinkPoint().x + 90 + rc.Width() / 2, rcnew.CenterPoint().y);
					
				}
			}
			
			CFODrawShapeList m_ListTemp;
			m_ListTemp.AddTail(pShape);

			if(pCurSub != NULL)
			{
				CFOPortShape *pPortTo = pCurSub->GetConnectPort();
				CFOPortShape *pPortFrom = GetTopPort((CFODrawPortsShape *)pShape);
				if(!bTopRightMode)
				{
					pPortFrom = GetBottomPort((CFODrawPortsShape *)pShape);
				}
				
				if(pPortTo != NULL && pPortFrom != NULL)
				{
					FOPRect rcCreate(0,0, 100,100);
					CFOLinkShape* pLink = (CFOLinkShape* )DoCreateShapeByType(FOP_COMP_TURNCORNERLINK,rcCreate,_T(""));
					if(pLink != NULL)
					{
						DoInitCreateShape(pLink);
						pPortFrom->AddLinkShape(pLink);
						pLink->SetFromPort(pPortFrom);
						
						pPortTo->AddLinkShape(pLink);
						pLink->SetToPort(pPortTo);
						pLink->RelayoutPoints();
						pLink->UpdateComp();
						m_ListTemp.AddTail(pLink);
						pLink->Release();
					}
					
				}
			}
			if(pCurVertSub != NULL)
			{
				CFOPortShape *pPortTo = pCurVertSub->GetConnectPort();
				CFOPortShape *pPortFrom = GetLeftPort((CFODrawPortsShape *)pShape);
				if(!bTopRightMode)
				{
					pPortFrom = GetRightPort((CFODrawPortsShape *)pShape);
				}
				if(pPortTo != NULL && pPortFrom != NULL)
				{
					FOPRect rcCreate(0,0, 100,100);
					CFOLinkShape* pLink = (CFOLinkShape* )DoCreateShapeByType(FOP_COMP_TURNCORNERLINK,rcCreate,_T(""));
					if(pLink != NULL)
					{
						DoInitCreateShape(pLink);
						pPortFrom->AddLinkShape(pLink);
						pLink->SetFromPort(pPortFrom);
						
						pPortTo->AddLinkShape(pLink);
						pLink->SetToPort(pPortTo);
						pLink->RelayoutPoints();
						pLink->UpdateComp();
						m_ListTemp.AddTail(pLink);
						pLink->Release();
					}
					
				}
			}

			if(pCurDot != NULL)
			{
				CFOPortShape *pPortTo = pCurDot->GetConnectPort();
				CFOPortShape *pPortFrom = GetTopPort((CFODrawPortsShape *)pShape);
				
				if(pPortTo != NULL && pPortFrom != NULL)
				{
					FOPRect rcCreate(0,0, 100,100);
					CFOLinkShape* pLink = (CFOLinkShape* )DoCreateShapeByType(FOP_COMP_TURNCORNERLINK,rcCreate,_T(""));
					if(pLink != NULL)
					{
						DoInitCreateShape(pLink);
						pPortFrom->AddLinkShape(pLink);
						pLink->SetFromPort(pPortFrom);
						
						pPortTo->AddLinkShape(pLink);
						pLink->SetToPort(pPortTo);
						pLink->RelayoutPoints();
						pLink->UpdateComp();
						m_ListTemp.AddTail(pLink);
						pLink->Release();
					}
					
				}
			}

			if(m_ListTemp.GetCount() > 0)
			{
				if(m_ListTemp.GetCount() == 1)
				{
					CFODrawShape *pCur = m_ListTemp.GetHead();
					if(HAS_BASE(pCur, CFOCompositeShape))
					{
						CPoint rcnew = pCur->GetSnapRect().CenterPoint();
						
						if(!HAS_BASE(pShape, CFOMatherLineShape) && !HAS_BASE(pShape, CFOVertMatherLineShape))
							pCur->RotateShape(-900 * m_nCurRotateAngle,rcnew.x, rcnew.y);
					}
					else if(HAS_BASE(pCur, CBPMActTaskShape))
					{
						CExtTabModelManager *pManager = (CExtTabModelManager *)GetManager();

						CString strTi = pManager->GetUniquePageCaption();

						CExtTabModel *pModel = (CExtTabModel *)pManager->MakeNew();
						pManager->m_ModelCache.AddTail(pModel);
						pModel->m_strCaption = strTi;

						CBPMActTaskShape *pNew = static_cast<CBPMActTaskShape *>(pCur);
						pNew->PutPropStringValue(P_ID_EXT_CONNECT_FORM, strTi);
						pNew->SetObjectCaption(strTi);
						CExtAddCompAction *pAction = new CExtAddCompAction(this, pNew);
						if(!Do(pAction, TRUE))
						{
							delete pAction;
						}
						SetModifiedFlag();
						return;
					}
				}
				CFOAddCompsAction *pAction = new CFOAddCompsAction(this, m_ListTemp);
				if(!Do(pAction, TRUE))
				{
					delete pAction;
				}
			}

			SetModifiedFlag();
		}
	}
}

CFODrawShape* CExtTabModel::AddShapeByType(UINT m_drawshape,CRect &rcCreate,CString strFileName)
{
	if(m_drawshape == FO_DROP_TOOLBOX_SHAPE_TYPE)
	{
		CFOToolBoxItem *pSelect = DoGetSelectToolboxItem();
		CFODrawShape *pObj = CreateShapeFromToolboxItem(pSelect);
		if(pObj != NULL)
		{
			FOPRect rc = rcCreate;
			rc.NormalizeRect();
			CPoint ptTrackX = rcCreate.CenterPoint();
			
			FOPRect rcShape = pObj->GetSnapRect();
			
			CSize sz = CSize(rcShape.Width(), rcShape.Height());
			rc.CreateFromCenter(ptTrackX, sz);
			
			
			if(rcShape.Width()<=10 && rcShape.Height()<20)
			{
				rc = CRect(ptTrackX.x-70,ptTrackX.y-70,ptTrackX.x+70,ptTrackX.y+70);
			}
			
			pObj->PositionShape(rc);
			DoInitCreateShape(pObj);
			
			InsertShape2(pObj);
			pObj->Release();
			
			SetModifiedFlag(TRUE);
			return pObj;
		}
	}
	else if(m_drawshape == IDR_D_1001 ||
		m_drawshape == IDR_D_1002 ||
		m_drawshape == IDR_D_1004 ||
		m_drawshape == IDR_D_1005 ||
		m_drawshape == IDR_D_1006 ||
		m_drawshape == IDR_D_1007 ||
		m_drawshape == IDR_D_1008 ||
		m_drawshape == IDR_D_1009 ||
		m_drawshape == IDR_D_1010 ||
		m_drawshape == IDR_D_1011 ||
		m_drawshape == IDR_D_1012 ||
		m_drawshape == IDR_D_1013 ||
		m_drawshape == IDR_D_1014 ||
		m_drawshape == IDR_D_1015 ||
		m_drawshape == IDR_D_1016 ||
		m_drawshape == IDR_D_1017 ||
		m_drawshape == IDR_D_1018 ||
		m_drawshape == IDR_D_1019 ||
		m_drawshape == IDR_D_1020 ||
		m_drawshape == IDR_D_130 ||
		m_drawshape == IDR_D_1031 ||
		m_drawshape == IDR_D_1032 ||
		m_drawshape == IDR_D_1033 ||
		m_drawshape == IDR_D_1034 ||
		m_drawshape == IDR_D_1003
		)
	{
		CFOCompositeShape *pReturn = NULL;
		FOPRect rc = rcCreate;
		
		pReturn = new CFOCompositeShape;
		pReturn->AddRef();
		pReturn->Create(rc,_T(""));
		pReturn->SetType(m_drawshape);
		
		{
			pReturn->LoadFromResource(m_drawshape);
		}
//		pReturn->SetPointSize(6);
		pReturn->SetWithLabelShow(TRUE);
		pReturn->SetShowLabelAtFirst(TRUE);
		pReturn->SetAspectRatio(TRUE);
		pReturn->SetObjectCaption(_T("Symbol"));
		rc.NormalizeRect();
		CPoint ptTrackX = rcCreate.CenterPoint();
		
		FOPRect rcShape = pReturn->GetSnapRect();
		
		CSize sz = CSize(rcShape.Width(), rcShape.Height());
		rc.CreateFromCenter(ptTrackX, sz);
		
		
		if(rcShape.Width()<=10 && rcShape.Height()<20)
		{
			rc = CRect(ptTrackX.x-70,ptTrackX.y-70,ptTrackX.x+70,ptTrackX.y+70);
		}
		
		pReturn->PositionShape(rc);
		DoInitCreateShape(pReturn);
		
		InsertShape2(pReturn);
		pReturn->Release();
		
		SetModifiedFlag(TRUE);
	}
	else if(m_drawshape == IDR_D_SYM_FILE
		)
	{
		CFOCompositeShape *pReturn = NULL;
		FOPRect rc = rcCreate;
		
		pReturn = new CFOCompositeShape;
		pReturn->AddRef();
		pReturn->Create(rc,_T(""));
		pReturn->SetType(m_drawshape);
		
		{
			pReturn->LoadFromFile(m_strSymFile);
		}
		//		pReturn->SetPointSize(6);
		pReturn->SetWithLabelShow(TRUE);
		pReturn->SetShowLabelAtFirst(TRUE);
		pReturn->SetAspectRatio(TRUE);
		pReturn->SetObjectCaption(_T("Symbol"));
		rc.NormalizeRect();
		CPoint ptTrackX = rcCreate.CenterPoint();
		
		FOPRect rcShape = pReturn->GetSnapRect();
		
		CSize sz = CSize(rcShape.Width(), rcShape.Height());
		rc.CreateFromCenter(ptTrackX, sz);
		
		
		if(rcShape.Width()<=10 && rcShape.Height()<20)
		{
			rc = CRect(ptTrackX.x-70,ptTrackX.y-70,ptTrackX.x+70,ptTrackX.y+70);
		}
		
		pReturn->PositionShape(rc);
		DoInitCreateShape(pReturn);
		
		InsertShape2(pReturn);
		pReturn->Release();
		
		SetModifiedFlag(TRUE);
	}
	else if(m_drawshape == IDR_SELECT_SHAPE
		)
	{
		CFOCompositeShape *pReturn = NULL;
		FOPRect rc = rcCreate;
		
		pReturn = (CFOCompositeShape *)m_pCurSelect->Copy();
		pReturn->AddRef();
	//	pReturn->Create(rc,_T(""));
		pReturn->SetType(m_drawshape);
		//		pReturn->SetPointSize(6);
		pReturn->SetWithLabelShow(FALSE);
		pReturn->SetShowLabelAtFirst(FALSE);
		pReturn->SetAspectRatio(TRUE);
		pReturn->UpdateHardWay();
		
		pReturn->SetObjectCaption(_T("Symbol"));
		rc.NormalizeRect();
		CPoint ptTrackX = rcCreate.CenterPoint();
		
		FOPRect rcShape = pReturn->GetSnapRect();
		pReturn->GenDefaultLabelPos(rcShape);
		CSize sz = CSize(rcShape.Width(), rcShape.Height());
		rc.CreateFromCenter(ptTrackX, sz);

		if(rcShape.Width()<=10 && rcShape.Height()<20)
		{
			rc = CRect(ptTrackX.x-70,ptTrackX.y-70,ptTrackX.x+70,ptTrackX.y+70);
		}
		
		pReturn->PositionShape(rc);
		DoInitCreateShape(pReturn);
		
	//	InsertShape2(pReturn);
		if(1)
		{
			CFOCompositeShape *pAdd = NULL;
			FOPRect rc = rcCreate;
			
			pAdd = new CFOCompositeShape;
			pAdd->AddRef();
			pAdd->Create(rc,_T(""));
			pAdd->SetType(m_drawshape);
			POSITION pos = pReturn->GetCompList()->GetHeadPosition();
			while (pos != NULL) 
			{
				CFODrawShape *pShape = pReturn->GetCompList()->GetNext(pos);
				pAdd->GetCompList()->AddTail(pShape);	
				pShape->SetMainShape(pAdd);
				pShape->SetModel(this);
				
				pShape->m_bWithInView = TRUE;
				pShape->m_bInModel = FALSE;
			}

			POSITION posP = pReturn->GetPortsList()->GetHeadPosition();
			while(posP != NULL)
			{
				CFOPortShape *pPortShape = (CFOPortShape *) pReturn->GetPortsList()->GetNext(posP);
				
				ASSERT(pPortShape != NULL);
				
				CFOPortShape *pPort = (CFOPortShape *) pPortShape->Copy();
				pPort->m_bInModel = FALSE;
				ASSERT(pPort != NULL);
				pPort->SetMainShape(pAdd);
				pPort->SetModel(this);
				pPort->SetParentComp(pAdd);
				pAdd->GetPortsList()->AddTail(pPort);
			}

			pAdd->SetModel(this);
			pAdd->UpdatePosition();
			pAdd->TrackUpdatePoints();

			CString strStateText = pReturn->GetStateString();
			if(!strStateText.IsEmpty())
			{
				CString strType = pReturn->GetStateType();
				if(!strType.IsEmpty())
				{
					pAdd->SetStateType(strType);
				}
			}
			pAdd->SetStateString(strStateText);
			DoInitCreateShape(pAdd);
			InsertShape2(pAdd);
			pAdd->Release();
		}
		pReturn->Release();
		
		SetModifiedFlag(TRUE);
	}
	else if(m_drawshape == MY_MATHER_SHORT_DOUBLE_H_SHAPE)
	{
		{
			CFODrawShape* pObj = DoCreateShapeByType(MY_MATHER_LINE_SHAPE,rcCreate,strFileName);
			if(pObj != NULL)
			{
				DoInitCreateShape(pObj);
				
				InsertShape(pObj);
				pObj->Release();
			}
		}
		rcCreate.OffsetRect(CPoint(0, 20));
		CFODrawShape* pObj = DoCreateShapeByType(MY_MATHER_LINE_SHAPE,rcCreate,strFileName);
		if(pObj != NULL)
		{
			DoInitCreateShape(pObj);
			
			InsertShape(pObj);
			pObj->Release();
		}
		
		SetModifiedFlag(TRUE);
		
		return pObj;
	}
	else if(m_drawshape == MY_MATHER_SHORT_3_H_SHAPE)
	{
		{
			CFODrawShape* pObj = DoCreateShapeByType(MY_MATHER_LINE_SHAPE,rcCreate,strFileName);
			if(pObj != NULL)
			{
				DoInitCreateShape(pObj);
				
				InsertShape(pObj);
				pObj->Release();
			}
		}
		{
			rcCreate.OffsetRect(CPoint(0, 20));
			CFODrawShape* pObj = DoCreateShapeByType(MY_MATHER_LINE_SHAPE,rcCreate,strFileName);
			if(pObj != NULL)
			{
				DoInitCreateShape(pObj);
				
				InsertShape(pObj);
				pObj->Release();
		}
		}

	
			rcCreate.OffsetRect(CPoint(0, 20));
			CFODrawShape* pObj = DoCreateShapeByType(MY_MATHER_LINE_SHAPE,rcCreate,strFileName);
			if(pObj != NULL)
			{
				DoInitCreateShape(pObj);
				
				InsertShape(pObj);
				pObj->Release();
			}
	
		
		
		SetModifiedFlag(TRUE);
		
		return pObj;
	}
	else if(m_drawshape == MY_MATHER_SHORT_DOUBLE_V_SHAPE)
	{
		{
			CFODrawShape* pObj = DoCreateShapeByType(MY_VERT_MATHER_LINE_SHAPE,rcCreate,strFileName);
			if(pObj != NULL)
			{
				DoInitCreateShape(pObj);
				
				InsertShape(pObj);
				pObj->Release();
			}
		}
		rcCreate.OffsetRect(CPoint(20, 0));
		CFODrawShape* pObj = DoCreateShapeByType(MY_VERT_MATHER_LINE_SHAPE,rcCreate,strFileName);
		if(pObj != NULL)
		{
			DoInitCreateShape(pObj);
			
			InsertShape(pObj);
			pObj->Release();
		}
		
		SetModifiedFlag(TRUE);
		
		return pObj;
	}
	else if(m_drawshape == MY_MATHER_SHORT_3_V_SHAPE)
	{
		{
			CFODrawShape* pObj = DoCreateShapeByType(MY_VERT_MATHER_LINE_SHAPE,rcCreate,strFileName);
			if(pObj != NULL)
			{
				DoInitCreateShape(pObj);
				
				InsertShape(pObj);
				pObj->Release();
			}
		}

		{
			rcCreate.OffsetRect(CPoint(20, 0));
			CFODrawShape* pObj = DoCreateShapeByType(MY_VERT_MATHER_LINE_SHAPE,rcCreate,strFileName);
			if(pObj != NULL)
			{
				DoInitCreateShape(pObj);
				
				InsertShape(pObj);
				pObj->Release();
		}
		}

	
			rcCreate.OffsetRect(CPoint(20, 0));
			CFODrawShape* pObj = DoCreateShapeByType(MY_VERT_MATHER_LINE_SHAPE,rcCreate,strFileName);
			if(pObj != NULL)
			{
				DoInitCreateShape(pObj);
				
				InsertShape(pObj);
				pObj->Release();
			}
			
		
		SetModifiedFlag(TRUE);
		
		return pObj;
	}
	else
	{
		CFODrawShape* pObj = DoCreateShapeByType(m_drawshape,rcCreate,strFileName);
		if(pObj != NULL)
		{
			DoInitCreateShape(pObj);
			
			InsertShape2(pObj);
			pObj->Release();
		}
		
		SetModifiedFlag(TRUE);
		
		return pObj;
	}
	
	
	
	return NULL;
}

CFOPortShape* CExtTabModel::HitTestPort(CPoint point,const BOOL &bUseExt, const int &nExpV)
{
	bUseExt;
	if(GetShapes()->GetCount() <= 0)
	{
		return NULL;
	}
	
	if(!m_bfoWithPort)
	{
		return NULL;
	}
	
	CFODrawShapeSet m_TempList;
	
	int dSpace = fo_DefaultSnapLineSizPix;
	int nExpandSize = (int)dSpace;
	
	int nExp = (int)(fo_DefaultSnapLineSizPix * nExpV);
	CRect rect;
	rect.left   = point.x - nExp;
	rect.top    = point.y - nExp;
	rect.right  = point.x + nExp;
	rect.bottom = point.y + nExp;
	
	FOPRect rcHittest = rect;
	DoUpdateShapeInview();
	
	// 	if(gfxData.m_bWithAdvanceHit)
	// 	{
	// 	}
	FOPRect rcOver = GetAllVisibleObjBoundRect();
	if(rcHittest.IsIntersection(rcOver))
	{
		CFODrawShapeSet setHit;
		ShapesAtPt(&setHit, point, nExp);
		
		CFODrawShape* pObj1 = NULL;
		int xy = 0;
		for(xy = 0; xy < setHit.Count(); xy ++)
		{
			pObj1 = (CFODrawShape* )setHit.GetObject(xy);
			
			if(pObj1 != NULL && pObj1->m_bWithInView && pObj1->IsVisible())
			{
				
				m_TempList.AddTail(pObj1);
				
			}
		}
	}
	
	float space = (float)(gfxData.m_nDefNearestPortDist * gfxData.m_nDefNearestPortDist);
	CFOPortShape* pPortHit = NULL;
	CFODrawShape* pObj = NULL;
	CFODrawPortsShape *pShapex = NULL;
	for(int xy = m_TempList.GetCount() - 1; xy >= 0 ; xy --)
	{
		pObj = (CFODrawShape* )m_TempList.GetObject(xy);
		
		if(pObj->IsVisible() && !pObj->IsSelectProtect())
		{
			// 			if(HAS_BASE(pObj, CFOMatherLineShape))
			// 			{
			// 				CFOMatherLineShape *pNode = static_cast<CFOMatherLineShape *>(pObj);
			// 				FOPRect rc = pNode->GetTrueSnapRect();
			// 				if(rc.PtInRect(point))
			// 				{
			// 					pPortHit = pNode->GetConnectPort();
			// 					break;
			// 				}
			// 			}
			// 			else if(HAS_BASE(pObj, CFOVertMatherLineShape))
			// 			{
			// 				CFOVertMatherLineShape *pNode = static_cast<CFOVertMatherLineShape *>(pObj);
			// 				FOPRect rc = pNode->GetTrueSnapRect();
			// 				if(rc.PtInRect(point))
			// 				{
			// 					pPortHit = pNode->GetConnectPort();
			// 					break;
			// 				}
			// 			}
			// 			else 
			if(pObj->IsKindOf(RUNTIME_CLASS(CFODrawPortsShape)))
			{
				pShapex = static_cast<CFODrawPortsShape *>(pObj);
				pPortHit = PickNearestPort1(pShapex, point, pPortHit, space);
			}
		}
	}
	
    if(pPortHit != NULL && pPortHit->IsVisible())
	{
        return pPortHit;
	}
	return NULL;
}

void CExtTabModel::UpdateTitle()
{
	CFOTabPageModel::UpdateTitle();

//	if(m_pOwner == NULL)
//	{
//		return;
//	}
//
//	if(m_pOwner->GetSafeHwnd() != NULL)
//	{
//		if(m_pOwner ->IsKindOf(RUNTIME_CLASS(CFODrawView)))
//		{
//			CFODrawView *pView = (CFODrawView *) m_pOwner;
//			CDocument *m_pDocument = (CDocument *)pView->GetDocument();
//			if(m_pDocument != NULL)
//			{
//				if (m_strTitleOrg.IsEmpty() && !m_pDocument->GetTitle().IsEmpty())
//					m_strTitleOrg = m_pDocument->GetTitle();
//				
//				if (!m_strTitleOrg.IsEmpty())
//				{
//					TCHAR szStr[256+_MAX_PATH];
//					_tcscpy(szStr, m_strTitleOrg);
//					if (IsDirty())
//					{
//						if(m_strTitleOrg.Find(_T("*"))<0)
//						{
//							lstrcat(szStr, _T(" *"));
//						}
//					}
//					if (m_pDocument->GetTitle() != szStr)
//					{
//						m_pDocument->SetTitle(szStr);
//						m_pDocument->UpdateFrameCounts();
//					}
//				}
//			}
//		}
//	}
}

void CExtTabModel::DoActionChange(const CFOBaseAction* pAction)
{
	CFOTabPageModel::DoActionChange(pAction);
	
	// FODO:Add your own specify code here.

}

CString CExtTabModel::CreateBaseName(UINT nType)
{
	CString strReturn;
	strReturn = "nLine";
	if(nType == MY_LINE_TYPE)
	{
		return strReturn;
	}
	else
	{
		return CFOTabPageModel::CreateBaseName(nType);
	}
}

CString CExtTabModel::CreateBaseCaption(UINT nType)
{
	CString strReturn;
	strReturn = "Line";
	if(nType == MY_LINE_TYPE)
	{
		return strReturn;
	}
	else
	{
		return CFOTabPageModel::CreateBaseCaption(nType);
	}

}

CString CExtTabModel::GetUniqueName(UINT nType)
{
	return CFOTabPageModel::GetUniqueName(nType);
}

CString CExtTabModel::GetUniqueCaption(UINT nType)
{

	return CFOTabPageModel::GetUniqueCaption(nType);
}


CFODrawShape *CExtTabModel::DoCreateShapeByType(UINT m_drawshape,
														CRect &rcCreate,
														CString strFileName,
														CFOToolBoxItem *pCurItem)
{
	CFODrawShape *pReturn = NULL;
	CString strCaption;
	CString strName;
	strCaption = "";
	strName = "";
	CPoint ptTrack = rcCreate.TopLeft();
	if(m_drawshape != FO_COMP_NONE)
	{
		CRect rc(rcCreate);
		rc.NormalizeRect();
		if(rc.IsRectEmpty()||(rc.Width()<=10 && rc.Height()<20))
		{
			switch(m_drawshape)
			{
// 			case MY_LINK_SHAPE:
// 				{
// 					rc = CRect(ptTrack.x-80,ptTrack.y-80,ptTrack.x+80,ptTrack.y+80);
// 				}
// 				break;
				
			case MY_MATHER_LINE_SHAPE:
				{
					rc = CRect(ptTrack.x-80,ptTrack.y-11,ptTrack.x+80,ptTrack.y+11);
				}
				break;

			case MY_MATHER_SHORT_H_SHAPE:
				{
					rc = CRect(ptTrack.x-30,ptTrack.y-11,ptTrack.x+30,ptTrack.y+11);
				}
				break;

			case MY_MATHER_SHORT_V_SHAPE:
				{
					rc = CRect(ptTrack.x-11,ptTrack.y-30,ptTrack.x+11,ptTrack.y+30);
				}
				break;

			case MY_VERT_MATHER_LINE_SHAPE:
				{
					rc = CRect(ptTrack.x-11,ptTrack.y-80,ptTrack.x+11,ptTrack.y+80);
				}
				break;

			case MY_MATHER_DOT_SHAPE:
				{
					rc = CRect(ptTrack.x-11,ptTrack.y-11,ptTrack.x+11,ptTrack.y+11);
				}
				break;

			case BPM_ACT_TASK_SHAPE:
				{
					rc = CRect(ptTrack.x-40,ptTrack.y-30,ptTrack.x+40,ptTrack.y+30);
				}
				break;
				
			default:
				{
				}
				break;
			}
		}

		switch(m_drawshape)
		{
// 		case MY_LINK_SHAPE:
// 			{
// 				pReturn = new CNewLinkShape;
// 				pReturn->AddRef();
// 				pReturn->Create(rc,_T(""));
// 				strCaption = GetUniqueCaption(pReturn->GetType());
// 				strName = GetUniqueName(pReturn->GetType());
// 				pReturn->SetObjectCaption(strCaption);
// 				pReturn->SetObjectName(strName);
// 			}
// 			break;

		case MY_MATHER_SHORT_H_SHAPE:
			{
				pReturn = new CFOMatherLineShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(MY_MATHER_LINE_SHAPE);
				strName = GetUniqueName(MY_MATHER_LINE_SHAPE);
				pReturn->SetObjectCaption(_T("Bus"));
				pReturn->SetPatternColor(RGB(255,255,255));
				pReturn->SetObjectName(strName);
			}
			break;

		case MY_MATHER_LINE_SHAPE:
			{
				pReturn = new CFOMatherLineShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(_T("Bus"));
				pReturn->SetPatternColor(RGB(255,255,255));
				pReturn->SetObjectName(strName);
			}
			break;

		case BPM_ACT_TASK_SHAPE:
			{
				pReturn = new CBPMActTaskShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				CString strCaption = _T("BusbarSystem");
				pReturn->SetObjectCaption(strCaption);
				
				pReturn->SetPolyObject(FALSE);
				//	pReturn->SetResizeProtect(TRUE);
				pReturn->SetRotateProtect(TRUE);
			}
			break;
			
		case MY_MATHER_DOT_SHAPE:
			{
				pReturn = new CFOMatherDotShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetPatternColor(RGB(255,255,255));
				pReturn->SetObjectName(strName);
			}
			break;
			
		case MY_MATHER_SHORT_V_SHAPE:
			{
				pReturn = new CFOVertMatherLineShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(_T("Bus"));
				pReturn->SetObjectName(strName);
				pReturn->SetPatternColor(RGB(255,255,255));
			}
			break;
			
		case MY_VERT_MATHER_LINE_SHAPE:
			{
				pReturn = new CFOVertMatherLineShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(_T("Bus"));
				pReturn->SetObjectName(strName);
				pReturn->SetPatternColor(RGB(255,255,255));
			}
			break;
			
		default:
			{
				pReturn = CFOTabPageModel::DoCreateShapeByType(m_drawshape,rcCreate,strFileName);
			}
			break;
		}
	}
	return pReturn;
}

CFOCompositeShape *CExtTabModel::DoCreateCompositeShapeByType(UINT m_drawshape,
																  CRect &rcCreate,
																  CArray<FOPORTVALUE,FOPORTVALUE> *arInitPorts,
																  CString strFileName,
																  UINT nResID,
																  CFOToolBoxItem *pCurItem)
{
	CFOCompositeShape *pReturn = CFOTabPageModel::DoCreateCompositeShapeByType(m_drawshape,
															rcCreate,
															arInitPorts,
															strFileName,
															nResID,
															pCurItem);
	// FODO: Add your own specify code here.

	return pReturn;
}


void CExtTabModel::SetModifiedFlag(BOOL b)
{
	CFOTabPageModel::SetModifiedFlag(b);
	
	//FOTO:Add you code here.

}

BOOL CExtTabModel::IsModified()
{

	//FOTO:Add you code here.

	return CFOTabPageModel::IsModified();
}

void CExtTabModel::Serialize(CArchive& ar)
{
	CFOTabPageModel::Serialize(ar);
	if(ar.IsStoring())
	{
		//FOTO:Add you code here.

	}
	else
	{
		//FOTO:Add you code here.

	}
}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CExtTabModel::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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

void CExtTabModel::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CExtTabModel::OpenDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		return FALSE;
	}
	strCurOpenFormFile = CString(lpszPathName);
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

BOOL CExtTabModel::SaveDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	
	if (pFile == NULL)
	{
		
		return FALSE;
	}
	strCurOpenFormFile = CString(lpszPathName);
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

COLORREF FOPXGetRandomColor54()
{
	return RGB(rand() % 255,rand() % 255,rand() % 255);
}

void CExtTabModel::OnDrawShape(CDC *pDC,const CRect &rcViewX)
{
	int nCountShape = m_setDraw.GetCount();
	if( nCountShape <= 0)
	{ 
		return;
	}
	
	if(rcViewX.IsRectEmpty())
	{
		return;
	}
	
#ifdef _DEBUG
	if(0)//!IsDesignMode())
	{
		FOPRect rcUpdate = rcViewX;
		COLORREF crCur = FOPXGetRandomColor54();
		CFODrawHelper::FillRectFast(pDC, rcUpdate, crCur);
		XDDraw()->GDI3dRect(pDC, rcUpdate, crCur, crCur);
	}
#endif

	FOPRect rcView = rcViewX;
	
	FOPRect rcAllView = m_rcFullView;
	if(!rcView.IsIntersection(rcAllView))
	{
		return;
	}
	
	if(!m_bNeedUpdate)
	{
		if(m_rcFullView.Size() != CSize(0,0))
		{
			if(rcView.IsIntersection(m_rcFullView))
				rcView.Intersection(m_rcFullView);
		}
	}
	
	if(!rcView.IsOver(GetAllVisibleObjBoundRect()))
	{
		return;
	}

	CFODrawShapeSet m_Mathers;
	CFODrawShapeSet m_Links;
	CRect rcTemp;
	CFODrawShape* pObj = NULL;
	int xy = 0;
	for(xy = 0; xy < m_setDraw.GetCount(); xy ++)
	{
		pObj = (CFODrawShape* )m_setDraw.GetObject(xy);
		if(pObj != NULL)
		{
			if(pObj->IsKindOf(RUNTIME_CLASS(CFOLinkShape)))
			{
				m_Links.AddTail(pObj);
			}

			if(!pObj->IsKindOf(RUNTIME_CLASS(CFOMatherLineShape)) && 
				!pObj->IsKindOf(RUNTIME_CLASS(CFOVertMatherLineShape)))
			{
				
					if(!(pDC->IsPrinting() && pObj->IsPrintProtect()))
					{
						// Old method: fix 2007.03.15
						//					if(gfxData.m_bUseLinkRoute)
						//					{
						//						if(HAS_BASE(pObj,CFOUpRightLinkShape))
						//						{
						//							CFOUpRightLinkShape *pLine = static_cast<CFOUpRightLinkShape *>(pObj);
						//							DoIntersectUpright(pLine,rcView);
						//						}
						//					}

						DoDrawPorts(pObj);
						pObj->OnDraw(pDC);
					}
			
			}
			else
			{
				m_Mathers.AddTail(pObj);
			}
		}
	}
	
	for(xy = 0; xy < m_Mathers.GetCount(); xy ++)
	{
		pObj = (CFODrawShape* )m_Mathers.GetObject(xy);
		if(pObj != NULL)
		{
 			if(pObj->IsKindOf(RUNTIME_CLASS(CFOMatherLineShape)) ||
 				pObj->IsKindOf(RUNTIME_CLASS(CFOVertMatherLineShape)))
			{
				rcTemp = pObj->GetBoundRect();
			
				if(CFODrawHelper::Intersection(rcTemp, rcView))
				{
					if(!(pDC->IsPrinting() && pObj->IsPrintProtect()))
					{					
						DoDrawPorts(pObj);
						pObj->OnDraw(pDC);
					}
				}
			}
		}
	}

	for(xy = 0; xy < m_Links.GetCount(); xy ++)
	{
		pObj = (CFODrawShape* )m_Links.GetObject(xy);
		if(pObj != NULL)
		{
			if(pObj->IsKindOf(RUNTIME_CLASS(CFOLinkShape)))
			{
				CFOLinkShape *pLink = static_cast<CFOLinkShape *>(pObj);
				rcTemp = pObj->GetBoundRect();
				
				if(CFODrawHelper::Intersection(rcTemp, rcView))
				{
					if(!(pDC->IsPrinting() && pObj->IsPrintProtect()))
					{
						pLink->OnDraw(pDC);
					}
				}
			}
		}
	}

}

void CExtTabModel::OnDrawBack(CDC *pDC,const CRect &rcClip)
{
	CFOTabPageModel::OnDrawBack(pDC,rcClip);
	//FOTO:Add you code here.

}


/////////////////////////////////////////////////////////////////////////////
// CExtTabModel diagnostics

#ifdef _DEBUG
void CExtTabModel::AssertValid() const
{
	CFOTabPageModel::AssertValid();
}

void CExtTabModel::Dump(CDumpContext& dc) const
{
	CFOTabPageModel::Dump(dc);
}
#endif //_DEBUG

BOOL CExtTabModel::IsNewUpRightLink(CFODrawShape *pShape)
{
	if(pShape != NULL)
	{
		if(HAS_BASE(pShape, CFOLinkShape))//!m_bWithDiagramMode && 
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

CFODrawShape* CExtTabModel::HitTest2(const CFODrawShapeList &m_TempList, CPoint point)
{
	if(m_TempList.GetCount() <= 0)
	{
		return NULL;
	}

	FOPRect rcHittest = FOPGenHitRect(point);
	if(1)
	{
		FOPRect rcOver = GetAllVisibleObjBoundRect();
		if(rcHittest.IsOver(rcOver))
		{
			int dSpace = fo_DefaultSnapLineSizPix;
			
			CFOArea rgn;
			CFOArea rgn2;
			CFODrawShape* pObj = NULL;
			POSITION pos = m_TempList.GetTailPosition();
			while (pos != NULL)
			{
				pObj = m_TempList.GetPrev(pos);
				if(pObj != NULL)
				{
					if(pObj->IsVisible() && !pObj->IsSelectProtect())
					{
						if(HAS_BASE(pObj, CFOVertMatherLineShape) ||
							HAS_BASE(pObj, CFOMatherLineShape)||
							HAS_BASE(pObj, CFOMatherDotShape)
							)
						{
							BOOL bHit = FALSE;
							if(pObj->IsKindOf(RUNTIME_CLASS(CFOPortShape)))
							{
								CFOPortShape *pPort = static_cast<CFOPortShape *>(pObj);
								if(pPort->HitTest(point,0))
								{
									return pPort;
								}
							}
							else if(DoAllowHitBorder(pObj))
							{
								FOPSimpleCompositePolygon aPathPolygon;
								pObj->GetPathSimplePolygon(aPathPolygon);
								int nPolyAnz = aPathPolygon.Count();
								for (int nPolyNum=0; nPolyNum < nPolyAnz && !bHit; nPolyNum++) 
								{
									FOPPolygon aPoly(FOPCreatePolygon(aPathPolygon[nPolyNum],NULL));
									bHit = CFODrawHelper::RectHitPoints(aPoly,rcHittest);
								}
								
								if(bHit)
								{
									return pObj;
								}
								else
								{
									if(pObj->HitLabelTextPos(point))
									{
										return pObj;
									}
								}
							}
							else
							{
								if (pObj->HitOnIt(point, (int)dSpace))
								{
									return pObj;
								}
							}
						}
					}
				}
			}
		}

	}

	if(1)
	{
		FOPRect rcOver = GetAllVisibleObjBoundRect();
		if(rcHittest.IsOver(rcOver))
		{
			int dSpace = fo_DefaultSnapLineSizPix;
			
			CFOArea rgn;
			CFOArea rgn2;
			CFODrawShape* pObj = NULL;
			POSITION pos = m_TempList.GetTailPosition();
			while (pos != NULL)
			{
				pObj = m_TempList.GetPrev(pos);
				if(pObj != NULL)
				{
					if(pObj->IsVisible() && !pObj->IsSelectProtect())
					{
						if(!IsNewUpRightLink(pObj))
						{
							BOOL bHit = FALSE;
							if(pObj->IsKindOf(RUNTIME_CLASS(CFOPortShape)))
							{
								CFOPortShape *pPort = static_cast<CFOPortShape *>(pObj);
								if(pPort->HitTest(point,0))
								{
									return pPort;
								}
							}
							else if(DoAllowHitBorder(pObj))
							{
								FOPSimpleCompositePolygon aPathPolygon;
								pObj->GetPathSimplePolygon(aPathPolygon);
								int nPolyAnz = aPathPolygon.Count();
								for (int nPolyNum=0; nPolyNum < nPolyAnz && !bHit; nPolyNum++) 
								{
									FOPPolygon aPoly(FOPCreatePolygon(aPathPolygon[nPolyNum],NULL));
									bHit = CFODrawHelper::RectHitPoints(aPoly,rcHittest);
								}
								
								if(bHit)
								{
									return pObj;
								}
								else
								{
									if(pObj->HitLabelTextPos(point))
									{
										return pObj;
									}
								}
							}
							else
							{
								if (pObj->HitOnIt(point, (int)dSpace))
								{
									return pObj;
								}
							}
						}
					}
				}
			}
		}
		
	}

	FOPRect rcOver = GetAllVisibleObjBoundRect();

	if(rcHittest.IsOver(rcOver))
	{
		int dSpace = fo_DefaultSnapLineSizPix;
		
		CFOArea rgn;
		CFOArea rgn2;
		CFODrawShape* pObj = NULL;
		POSITION pos = m_TempList.GetTailPosition();
		while (pos != NULL)
		{
			pObj = m_TempList.GetPrev(pos);
			if(pObj != NULL)
			{
				if(pObj->IsVisible() && !pObj->IsSelectProtect())
				{
#if 0
					if(HAS_BASE(pObj, CFOCompositeShape))
					{
						CFOCompositeShape *pComp = static_cast<CFOCompositeShape *>(pObj);
						CFODrawShape *pReturn = FODoHitComposite(pComp,point,rcHittest);
						if(pReturn != NULL)
						{
							return pReturn;
						}
					}
					else
#endif
					{
						BOOL bHit = FALSE;
						if(pObj->IsKindOf(RUNTIME_CLASS(CFOPortShape)))
						{
							CFOPortShape *pPort = static_cast<CFOPortShape *>(pObj);
							if(pPort->HitTest(point,0))
							{
								return pPort;
							}
						}
						else if(DoAllowHitBorder(pObj))
						{
							FOPSimpleCompositePolygon aPathPolygon;
							pObj->GetPathSimplePolygon(aPathPolygon);
							int nPolyAnz = aPathPolygon.Count();
							for (int nPolyNum=0; nPolyNum < nPolyAnz && !bHit; nPolyNum++) 
							{
								FOPPolygon aPoly(FOPCreatePolygon(aPathPolygon[nPolyNum],NULL));
								bHit = CFODrawHelper::RectHitPoints(aPoly,rcHittest);
							}
							
							if(bHit)
							{
								return pObj;
							}
							else
							{
								if(pObj->HitLabelTextPos(point))
								{
									return pObj;
								}
							}
						}
						else
						{
							if (pObj->HitOnIt(point, (int)dSpace))
							{
								return pObj;
								}
						}
					}
				}
			}
		}
	}

	return NULL;
}

void CExtTabModel::OnPrintShape(CDC *pDC,const CRect &rcView)
{
	CFODrawShapeSet m_Links;
	CRect rcTemp;
	CFODrawShape* pObj = NULL;
	int xy = 0;
	for(xy = 0; xy < m_setDraw.GetCount(); xy ++)
	{
		pObj = (CFODrawShape* )m_setDraw.GetObject(xy);
		if(pObj != NULL)
		{
			if(pObj->IsKindOf(RUNTIME_CLASS(CFOLinkShape)))
			{
				m_Links.AddTail(pObj);
			}
			
			if(!pObj->IsKindOf(RUNTIME_CLASS(CFOMatherLineShape)) &&
				!pObj->IsKindOf(RUNTIME_CLASS(CFOVertMatherLineShape))
				)
			{
				
				if(!(pDC->IsPrinting() && pObj->IsPrintProtect()))
				{
					// Old method: fix 2007.03.15
					//					if(gfxData.m_bUseLinkRoute)
					//					{
					//						if(HAS_BASE(pObj,CFOUpRightLinkShape))
					//						{
					//							CFOUpRightLinkShape *pLine = static_cast<CFOUpRightLinkShape *>(pObj);
					//							DoIntersectUpright(pLine,rcView);
					//						}
					//					}
					
					DoDrawPorts(pObj);
					pObj->OnDraw(pDC);
				}
				
			}
		}
	}
	
	for(xy = 0; xy < m_setDraw.GetCount(); xy ++)
	{
		pObj = (CFODrawShape* )m_setDraw.GetObject(xy);
		if(pObj != NULL)
		{
			if(pObj->IsKindOf(RUNTIME_CLASS(CFOMatherLineShape)) ||
				pObj->IsKindOf(RUNTIME_CLASS(CFOVertMatherLineShape)))
			{
				
				if(!(pDC->IsPrinting() && pObj->IsPrintProtect()))
				{
					// Old method: fix 2007.03.15
					//					if(gfxData.m_bUseLinkRoute)
					//					{
					//						if(HAS_BASE(pObj,CFOUpRightLinkShape))
					//						{
					//							CFOUpRightLinkShape *pLine = static_cast<CFOUpRightLinkShape *>(pObj);
					//							DoIntersectUpright(pLine,rcView);
					//						}
					//					}
					
					DoDrawPorts(pObj);
					pObj->OnDraw(pDC);
				}
				
			}
		}
	}
	
	for(xy = 0; xy < m_Links.GetCount(); xy ++)
	{
		pObj = (CFODrawShape* )m_Links.GetObject(xy);
		if(pObj != NULL)
		{
			if(pObj->IsKindOf(RUNTIME_CLASS(CFOLinkShape)))
			{
				CFOLinkShape *pLink = static_cast<CFOLinkShape *>(pObj);
				
				if(!(pDC->IsPrinting() && pObj->IsPrintProtect()))
				{						
					pLink->OnDraw(pDC);
				}
				
			}
		}
	}
}

CFODrawShape* CExtTabModel::HitTest(CPoint point)
{
	if(m_ShapeList.GetCount() <= 0)
	{
		return NULL;
	}

	double dGridX = (double) gfxData.szSelectCompHandleSize.cx * 2;
	
	ConvertToMapLogWithoutUIScale(FUNIT_POINTS,dGridX,FALSE);
	int nExpandSize = (int)dGridX;
		
	CFODrawShapeSet setHit;
	ShapesAtPt(&setHit, point, nExpandSize);
	FOPRect rcHittest = FOPGenHitRect(point);
	if(1)
	{
		
		FOPRect rcOver = GetAllVisibleObjBoundRect();
		if(rcHittest.IsOver(rcOver))
		{
			CFODrawShapeList m_TempList;
			
			CFODrawShape* pObj1 = NULL;
			int xy = 0;
			for(xy = 0; xy < setHit.Count(); xy ++)
			{
				pObj1 = (CFODrawShape* )setHit.GetObject(xy);
				if(pObj1 != NULL && pObj1->m_bWithInView && pObj1->IsVisible())
				{
					if(HAS_BASE(pObj1, CFOVertMatherLineShape) ||
						HAS_BASE(pObj1, CFOMatherLineShape) ||
					HAS_BASE(pObj1, CFOMatherDotShape)
						)
					{
						m_TempList.AddTail(pObj1);
					}
					
				}
			}
			
			int dSpace = fo_DefaultSnapLineSizPix;
			
			CFOArea rgn;
			CFOArea rgn2;
			CFODrawShape* pObj = NULL;
			POSITION pos = m_TempList.GetTailPosition();
			while (pos != NULL)
			{
				pObj = m_TempList.GetPrev(pos);
				if(pObj != NULL)
				{
					if(pObj->IsVisible() && !pObj->IsSelectProtect())
					{
						{
							BOOL bHit = FALSE;
							if(pObj->IsKindOf(RUNTIME_CLASS(CFOPortShape)))
							{
								CFOPortShape *pPort = static_cast<CFOPortShape *>(pObj);
								if(pPort->HitTest(point,0))
								{
									return pPort;
								}
							}
							else if(DoAllowHitBorder(pObj))
							{
								FOPSimpleCompositePolygon aPathPolygon;
								pObj->GetPathSimplePolygon(aPathPolygon);
								int nPolyAnz = aPathPolygon.Count();
								for (int nPolyNum=0; nPolyNum < nPolyAnz && !bHit; nPolyNum++) 
								{
									FOPPolygon aPoly(FOPCreatePolygon(aPathPolygon[nPolyNum],NULL));
									bHit = CFODrawHelper::RectHitPoints(aPoly,rcHittest);
								}
								
								if(bHit)
								{
									return pObj;
								}
								else
								{
									if(pObj->HitLabelTextPos(point))
									{
										return pObj;
									}
								}
							}
							else
							{
								if (pObj->HitOnIt(point, (int)dSpace))
								{
									return pObj;
								}
							}
						}
					}
				}
			}
		}

	}

	if(1)
	{
		
		FOPRect rcOver = GetAllVisibleObjBoundRect();
		if(rcHittest.IsOver(rcOver))
		{
			CFODrawShapeList m_TempList;
			
			CFODrawShape* pObj1 = NULL;
			int xy = 0;
			for(xy = 0; xy < setHit.Count(); xy ++)
			{
				pObj1 = (CFODrawShape* )setHit.GetObject(xy);
				if(pObj1 != NULL && pObj1->m_bWithInView && pObj1->IsVisible())
				{
					if(!IsNewUpRightLink(pObj1))
					{
						m_TempList.AddTail(pObj1);
					}
					
				}
			}
			
			int dSpace = fo_DefaultSnapLineSizPix;
			
			CFOArea rgn;
			CFOArea rgn2;
			CFODrawShape* pObj = NULL;
			POSITION pos = m_TempList.GetTailPosition();
			while (pos != NULL)
			{
				pObj = m_TempList.GetPrev(pos);
				if(pObj != NULL)
				{
					if(pObj->IsVisible() && !pObj->IsSelectProtect())
					{
						{
							BOOL bHit = FALSE;
							if(pObj->IsKindOf(RUNTIME_CLASS(CFOPortShape)))
							{
								CFOPortShape *pPort = static_cast<CFOPortShape *>(pObj);
								if(pPort->HitTest(point,0))
								{
									return pPort;
								}
							}
							else if(DoAllowHitBorder(pObj))
							{
								FOPSimpleCompositePolygon aPathPolygon;
								pObj->GetPathSimplePolygon(aPathPolygon);
								int nPolyAnz = aPathPolygon.Count();
								for (int nPolyNum=0; nPolyNum < nPolyAnz && !bHit; nPolyNum++) 
								{
									FOPPolygon aPoly(FOPCreatePolygon(aPathPolygon[nPolyNum],NULL));
									bHit = CFODrawHelper::RectHitPoints(aPoly,rcHittest);
								}
								
								if(bHit)
								{
									return pObj;
								}
								else
								{
									if(pObj->HitLabelTextPos(point))
									{
										return pObj;
									}
								}
							}
							else
							{
								if (pObj->HitOnIt(point, (int)dSpace))
								{
									return pObj;
								}
							}
						}
					}
				}
			}
		}

	}


	FOPRect rcOver = GetAllVisibleObjBoundRect();
	if(rcHittest.IsOver(rcOver))
	{
		CFODrawShapeList m_TempList;

		CFODrawShape* pObj1 = NULL;
		int xy = 0;
		for(xy = 0; xy < setHit.Count(); xy ++)
		{
			pObj1 = (CFODrawShape* )setHit.GetObject(xy);
			if(pObj1 != NULL && pObj1->m_bWithInView && pObj1->IsVisible())
			{
				m_TempList.AddTail(pObj1);
			}
		}

		int dSpace = fo_DefaultSnapLineSizPix;
		
		CFOArea rgn;
		CFOArea rgn2;
		CFODrawShape* pObj = NULL;
		POSITION pos = m_TempList.GetTailPosition();
		while (pos != NULL)
		{
			pObj = m_TempList.GetPrev(pos);
			if(pObj != NULL)
			{
				if(pObj->IsVisible() && !pObj->IsSelectProtect())
				{
#if 0
					if(HAS_BASE(pObj, CFOCompositeShape))
					{
						CFOCompositeShape *pComp = static_cast<CFOCompositeShape *>(pObj);
						CFODrawShape *pReturn = FODoHitComposite(pComp,point,rcHittest);
						if(pReturn != NULL)
						{
							return pReturn;
						}
					}
					else
#endif
					{
						BOOL bHit = FALSE;
						if(pObj->IsKindOf(RUNTIME_CLASS(CFOPortShape)))
						{
							CFOPortShape *pPort = static_cast<CFOPortShape *>(pObj);
							if(pPort->HitTest(point,0))
							{
								return pPort;
							}
						}
						else if(DoAllowHitBorder(pObj))
						{
							FOPSimpleCompositePolygon aPathPolygon;
							pObj->GetPathSimplePolygon(aPathPolygon);
							int nPolyAnz = aPathPolygon.Count();
							for (int nPolyNum=0; nPolyNum < nPolyAnz && !bHit; nPolyNum++) 
							{
								FOPPolygon aPoly(FOPCreatePolygon(aPathPolygon[nPolyNum],NULL));
								bHit = CFODrawHelper::RectHitPoints(aPoly,rcHittest);
							}
							
							if(bHit)
							{
								return pObj;
							}
							else
							{
								if(pObj->HitLabelTextPos(point))
								{
									return pObj;
								}
							}
						}
						else
						{
							if (pObj->HitOnIt(point, (int)dSpace))
							{
								return pObj;
							}
						}
					}
				}
			}
		}
	}

	return NULL;
}

CFODrawShape* CExtTabModel::FindShapeWithName(CString str)
{
	CFODrawShape* pObj = NULL;
	int xy = 0;
	for(xy = 0; xy < m_ShapeList.GetCount(); xy ++)
	{
		pObj = (CFODrawShape*)(m_ShapeList.GetObject(xy));
		if(pObj->GetObjectName() == str)
		{
			return pObj;
		}
	}
	
	return NULL;
	
}
