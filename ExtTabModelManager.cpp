// ExtTabModelManager.cpp: implementation of the CExtTabModelManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExtTabModelManager.h"
#include <afxpriv.h>
#include "ChildFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// CExtTabModelManager construction/destruction

IMPLEMENT_SERIAL(CExtTabModelManager, CFOTabModelManager, 0)
CExtTabModelManager::CExtTabModelManager()
{
	//FOTO:Add you code here.
}

CExtTabModelManager::~CExtTabModelManager()
{
	//FOTO:Add you code here.
	POSITION pos = m_ModelCache.GetHeadPosition();
	while(pos != NULL)
	{
		delete m_ModelCache.GetNext(pos);
	}

	m_ModelCache.RemoveAll();
}

void CExtTabModelManager::Serialize(CArchive& ar)
{
	CFOTabModelManager::Serialize(ar);
	if(ar.IsStoring())
	{
		//FOTO:Add you code here.

	}
	else
	{
		//FOTO:Add you code here.

	}
}

CExtTabModel *CExtTabModelManager::FindOnly(const CString &strCap)
{
	if(strCap.IsEmpty())
		return NULL;
	
	for (int i = 0; i < m_nTabs; i++)
	{
		CExtTabModel *pObj = (CExtTabModel *)m_arTabs[i];
		if(pObj != NULL)
		{
			if(CFODrawHelper::IsTwoStringEq(pObj->m_strCaption , strCap))
			{
				return pObj;
			}
		}
		
	}

	return NULL;
}

BOOL CExtTabModelManager::FindModelCaption(CString strCap)
{
	if(strCap.IsEmpty())
		return FALSE;
	
	for (int i = 0; i < m_nTabs; i++)
	{
		CFOTabPageModel *pObj = (CFOTabPageModel *)m_arTabs[i];
		if(pObj != NULL)
		{
			if(CFODrawHelper::IsTwoStringEq(pObj->m_strCaption , strCap))
			{
				return TRUE;
			}
		}
		
	}

	POSITION pos = m_ModelCache.GetHeadPosition();
	while(pos != NULL)
	{
		CExtTabModel *pObj = (CExtTabModel *) m_ModelCache.GetNext(pos);
		if(pObj != NULL)
		{
			if(CFODrawHelper::IsTwoStringEq(pObj->m_strCaption , strCap))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Serialization
CFile* CExtTabModelManager::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
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

void CExtTabModelManager::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CExtTabModelManager::OpenDocument(LPCTSTR lpszPathName)
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

BOOL CExtTabModelManager::SaveDocument(LPCTSTR lpszPathName)
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

void CExtTabModelManager::DeleteTab(int nTab)
{
	if(nTab >= m_nTabs)
	{
		return;
	}
	
	if(nTab < 0)
	{
		return;
	}
	
	if (m_nCurrent == nTab)
	{
		m_nCurrent = 0;
		m_nFirstTab = 0;
	}
	
	CFOTabPageModel *pObj = (CFOTabPageModel *)m_arTabs[nTab];
	if(pObj != NULL)
	{
		pObj->RemoveAllObserver();
		m_ModelCache.AddTail((CExtTabModel *)m_arTabs[nTab]);
	}
	
	
	m_arTabs.RemoveAt(nTab);
	m_nTabs--;
	
	if (m_nFirstTab >= m_nTabs)
	{
		m_nFirstTab = max(0, m_nTabs-1);
	}
	
	if(m_nCurrent >= 0)
	{
		CObject *pObject = static_cast<CObject *>(&GetTab(m_nCurrent));
		NotifyObserver(0,pObject);
	}
	
}

void CExtTabModelManager::RemoveCache(const CString &strTitle)
{
	if(strTitle.IsEmpty())
	{
		return;
		
	}

	POSITION posFind = NULL;

	POSITION pos = m_ModelCache.GetHeadPosition();
	while(pos != NULL)
	{
		POSITION posCur = pos;
		
		CExtTabModel *pObj = (CExtTabModel *) m_ModelCache.GetNext(pos);
		if(pObj != NULL)
		{
			if(CFODrawHelper::IsTwoStringEq(pObj->m_strCaption , strTitle))
			{
				posFind = posCur;
				break;
			}
		}
	}

	if(posFind != NULL)
	{
		m_ModelCache.RemoveAt(posFind);
	}

}

CExtTabModel *CExtTabModelManager::FindInCache(const CString &strTitle)
{
	if(strTitle.IsEmpty())
	{
		return NULL;

	}

	POSITION pos = m_ModelCache.GetHeadPosition();
	while(pos != NULL)
	{
		CExtTabModel *pObj = (CExtTabModel *) m_ModelCache.GetNext(pos);
		if(pObj != NULL)
		{
			if(CFODrawHelper::IsTwoStringEq(pObj->m_strCaption , strTitle))
			{
	//			m_ModelCache.RemoveAt(pos);
				return pObj;
			}
		}
	}

	return NULL;
}

void CExtTabModelManager::GetAllBasicShapes(CFODrawShapeList &list)
{
	list.RemoveAll();
	// TODO: Add your command handler code here
	for(int i = 0;i < m_arTabs.GetSize(); i++)
	{
		CExtTabModel *pModel = (CExtTabModel *)m_arTabs.GetAt(i);
		if(pModel != NULL)
		{
			pModel->GetAllBasicShape(list);
		}
	}
}

void CExtTabModelManager::GetAllCompShapes(CFODrawShapeList &list)
{
	list.RemoveAll();
	// TODO: Add your command handler code here
	for(int i = 0;i < m_arTabs.GetSize(); i++)
	{
		CExtTabModel *pModel = (CExtTabModel *)m_arTabs.GetAt(i);
		if(pModel != NULL)
		{
			pModel->GetAllComps2(list);
		}
	}
}

void CExtTabModelManager::GetAllLinkShapes(CFODrawShapeList &listLink)
{
	listLink.RemoveAll();
	
	CFODrawShapeList listAll;
	GetAllBasicShapes(listAll);
	
	POSITION pos = listAll.GetHeadPosition();
	while (pos)
	{
		CFODrawShape *pObj = listAll.GetNext(pos);
		if (TRUE == pObj->IsKindOf(RUNTIME_CLASS(CFOLinkShape))) 
		{
			CFOLinkShape *pLink = static_cast<CFOLinkShape *>(pObj);
			ASSERT(pLink);
			listLink.AddTail(pLink);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CExtTabModelManager diagnostics

#ifdef _DEBUG
void CExtTabModelManager::AssertValid() const
{
	CFOTabModelManager::AssertValid();
}

void CExtTabModelManager::Dump(CDumpContext& dc) const
{
	CFOTabModelManager::Dump(dc);
}
#endif //_DEBUG

CFOTabPageModel* CExtTabModelManager::MakeNew()
{
	CExtTabModel* pInfo = new CExtTabModel;
	
	pInfo->SetDataManager(this);
	
	SetModifiedFlag();
	
	NotifyObserver(0,STATIC_DOWNCAST(CObject,(CObject*)pInfo));
	
	return pInfo;
}

CFOTabPageModel* CExtTabModelManager::InsertTab(CString szLabel)
{
	if(szLabel.IsEmpty())
	{
		szLabel = GetUniquePageCaption();
	}

	for (int i = 0; i < m_nTabs; i++)
	{
		CFOTabPageModel *pObj = (CFOTabPageModel *)m_arTabs[i];
		if(pObj != NULL)
		{
			if(CFODrawHelper::IsTwoStringEq(pObj->m_strCaption , szLabel))
			{
				return pObj;
			}
		}
		
	}

	CExtTabModel* pInfo = new CExtTabModel;

	pInfo->SetDataManager(this);

	pInfo->m_strCaption = szLabel;
	
	if (m_nCurrent == -1)
	{
		m_arTabs.SetAtGrow(m_nTabs, pInfo);
	}
	else
	{
		m_arTabs.InsertAt(m_nCurrent, pInfo, 1);
	}
	m_nTabs++;

	SetModifiedFlag();
	
	NotifyObserver(0,STATIC_DOWNCAST(CObject,(CObject*)pInfo));

	return pInfo;
}

CFOTabPageModel* CExtTabModelManager::InsertTab(CFOTabPageModel* pInfo)
{
	ASSERT(pInfo != NULL);

	for (int i = 0; i < m_nTabs; i++)
	{
		CFOTabPageModel *pObj = (CFOTabPageModel *)m_arTabs[i];
		if(pObj != NULL)
		{
			if(pObj == pInfo)
			{
				return pObj;
			}
		}
		
	}

	if(pInfo->m_strCaption.IsEmpty())
	{
		pInfo->m_strCaption = GetUniquePageCaption();
	}

	pInfo->SetDataManager(this);

	if (m_nCurrent == -1)
	{
		m_arTabs.SetAtGrow(m_nTabs, pInfo);
	}
	else
	{
		m_arTabs.InsertAt(m_nCurrent, pInfo, 1);
	}
	m_nTabs++;

	SetModifiedFlag();

	NotifyObserver(0,STATIC_DOWNCAST(CObject,(CObject*)pInfo));

	return pInfo;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(CExtRemoveCompAction, CFOAction, EXT_ACTION_REMOVESHAPE)
CExtRemoveCompAction::CExtRemoveCompAction(CFODataModel* pModel, CBPMActTaskShape* pShape) : 
	CFOAction(pModel)
{ 
	m_pShape = pShape; 
	pShape->AddRef();
	m_nIndex = -1;
}


CExtRemoveCompAction::~CExtRemoveCompAction()
{
	m_pShape->Release();
}

int CExtRemoveCompAction::GetIndexWithin(CBPMActTaskShape *pShape, CFODrawShapeSet* pCompList)
{
	for(int x = 0; x < pCompList->GetCount(); x++)
	{
		CBPMActTaskShape *pComp = (CBPMActTaskShape *)pCompList->GetObject(x);
		if(pComp == pShape)
		{
			return x;
		}
	}
	
	return -1;
}

int CExtRemoveCompAction::GetIndexWithin(CBPMActTaskShape *pShape, CFODrawShapeList* pCompList)
{
	pShape;
	pCompList;
	return -1;
}

CRect CExtRemoveCompAction::GetMaxPosition()
{
	CFODrawShapeList m_list;
	m_list.AddTail(m_pShape);
	
	GetModel()->GetAllLinkedShape(m_list, m_list);
	CRect rcReturn;
	rcReturn.SetRectEmpty();
	BOOL bAtFirst = TRUE;
	CFODrawShape *pShape = NULL;
	POSITION pos = m_list.GetHeadPosition();
	while(pos != NULL)
	{
		pShape = m_list.GetNext(pos);
		if(pShape != NULL)
		{
			CRect rcTemp = pShape->GetBoundRect();
			int nBorder = pShape->CalcExtraBorder();
			rcTemp.InflateRect(nBorder,nBorder,nBorder,nBorder);
			if(bAtFirst)
			{
				rcReturn = rcTemp;
				bAtFirst = FALSE;
			}
			
			if(rcTemp.left<rcReturn.left)
			{
				rcReturn.left = rcTemp.left;
			}
			if(rcTemp.right > rcReturn.right)
			{
				rcReturn.right = rcTemp.right;
			}
			if(rcTemp.top < rcReturn.top)
			{
				rcReturn.top = rcTemp.top;
			}
			if(rcTemp.bottom > rcReturn.bottom)
			{
				rcReturn.bottom = rcTemp.bottom;
			}
		}
	}
	return rcReturn;
}

BOOL CExtRemoveCompAction::Execute()
{
	ASSERT_VALID(m_pShape);

	SetSaveUpdateRect(GetMaxPosition());
	m_nIndex = GetIndexWithin(m_pShape, m_pModel->GetShapes());
	CExtTabModelManager *pManager = (CExtTabModelManager *)((CExtTabModel *)m_pModel)->GetManager();

	CString strMethod = _T("");
	m_pShape->GetPropStringValue(strMethod, P_ID_EXT_CONNECT_FORM);
	if(!strMethod.IsEmpty() && pManager != NULL)
	{
		CFOPMDIChildWnd* pChildFrame = (CFOPMDIChildWnd *)((CMDIFrameWnd*)::AfxGetMainWnd())->MDIGetActive();
		if (pChildFrame)
		{
			CChildFrame *child = static_cast<CChildFrame *>(pChildFrame);
			child->DeleteTab(strMethod);
		}
		pManager->DeleteTabNew(strMethod);
	}

	return m_pModel->RemoveShape(m_pShape);
}

CFOBaseAction* CExtRemoveCompAction::GetUndoAction() const
{
	CExtAddCompAction *pAction = new CExtAddCompAction(m_pModel, m_pShape);
	pAction->SetIndex(m_nIndex);
	return pAction; 
}

CFOBaseAction* CExtRemoveCompAction::GetRedoAction() const
{
	CExtRemoveCompAction *pAction = new CExtRemoveCompAction(m_pModel, m_pShape);
	pAction->m_nIndex = m_nIndex;
	return pAction;
}

void CExtRemoveCompAction::Sprint(CString& strLabel) const
{ 
	strLabel.LoadString(IDS_CMD_REMOVE_COMP); 
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_ACTION(CExtAddCompAction, CFOAction, EXT_ACTION_ADDSHAPE)
CExtAddCompAction::CExtAddCompAction(CFODataModel* pModel, CBPMActTaskShape* pShape) : 
	CFOAction(pModel)
{ 
	m_pShape = pShape; 
	pShape->AddRef();
	m_nIndex	= -1;
}


CExtAddCompAction::~CExtAddCompAction()
{
	m_pShape->Release();
}

//  Set shape member variable m_pShape to the pointer of pShape
void CExtAddCompAction::SetShape(CBPMActTaskShape *pShape)
{
	if (m_pShape != pShape)
	{
		if (m_pShape != NULL)
		{
			m_pShape->Release();
		}
		
		m_pShape = pShape;
		
		if (m_pShape != NULL)
		{
			m_pShape->AddRef();
		}
	}
}

CRect CExtAddCompAction::GetMaxPosition()
{
	CFODrawShapeList m_list;
	m_list.AddTail(m_pShape);
	
	GetModel()->GetAllLinkedShape(m_list, m_list);
	CRect rcReturn;
	rcReturn.SetRectEmpty();
	BOOL bAtFirst = TRUE;
	CFODrawShape *pShape = NULL;
	POSITION pos = m_list.GetHeadPosition();
	while(pos != NULL)
	{
		pShape = m_list.GetNext(pos);
		if(pShape != NULL)
		{
			pShape->UpdateHardWay();
			CRect rcTemp = pShape->GetBoundRect();
			int nBorder = pShape->CalcExtraBorder();
			
			rcTemp.InflateRect(nBorder,nBorder,nBorder,nBorder);
			if(bAtFirst)
			{
				rcReturn = rcTemp;
				bAtFirst = FALSE;
			}
			
			if(rcTemp.left<rcReturn.left)
			{
				rcReturn.left = rcTemp.left;
			}
			if(rcTemp.right > rcReturn.right)
			{
				rcReturn.right = rcTemp.right;
			}
			if(rcTemp.top < rcReturn.top)
			{
				rcReturn.top = rcTemp.top;
			}
			if(rcTemp.bottom > rcReturn.bottom)
			{
				rcReturn.bottom = rcTemp.bottom;
			}
		}
	}
	return rcReturn;
}

BOOL CExtAddCompAction::Execute()
{
	ASSERT_VALID(m_pShape);
	SetSaveUpdateRect(GetMaxPosition());
	
	CExtTabModelManager *pManager = (CExtTabModelManager *)((CExtTabModel *)m_pModel)->GetManager();
	
	CString strMethod = _T("");
	m_pShape->GetPropStringValue(strMethod, P_ID_EXT_CONNECT_FORM);
	if(!strMethod.IsEmpty() && pManager != NULL)
	{
		CExtTabModel *pNewModel = pManager->FindInCache(strMethod);
		if(pNewModel != NULL)
		{
			pManager->InsertTab(pNewModel);
			CFOPMDIChildWnd* pChildFrame = (CFOPMDIChildWnd *)((CMDIFrameWnd*)::AfxGetMainWnd())->MDIGetActive();
			if (pChildFrame)
			{
				CChildFrame *child = static_cast<CChildFrame *>(pChildFrame);
				child->AddNew(pNewModel);
			}
			pManager->RemoveCache(strMethod);
		}
	}

	if(m_nIndex >= 0)
	{
		return m_pModel->InsertShapeAt(m_pShape, m_nIndex);
	}
	else
	{
		return m_pModel->AddShape(m_pShape);
	}
	
}

CFOBaseAction* CExtAddCompAction::GetUndoAction() const
{
	CExtRemoveCompAction *pAction = new CExtRemoveCompAction(m_pModel, m_pShape);
	return pAction; 
}

CFOBaseAction* CExtAddCompAction::GetRedoAction() const
{
	CExtAddCompAction *pAction = new CExtAddCompAction(m_pModel, m_pShape);
	pAction->SetIndex(m_nIndex);
	return pAction; 
}
void CExtAddCompAction::Sprint(CString& strLabel) const
{ 
	strLabel.LoadString(IDS_CMD_ADDCOMP); 
}
