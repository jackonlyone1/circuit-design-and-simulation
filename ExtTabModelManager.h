#if !defined(AFX_EXTTABMODELMANAGER_H__955604C6_297A_414D_8A20_86A380FE10A2__INCLUDED_)
#define AFX_EXTTABMODELMANAGER_H__955604C6_297A_414D_8A20_86A380FE10A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtTabModelManager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtTabModelManager window
#include "ExtTabModel.h"
#include "BPMActTaskShape.h"
 
//===========================================================================
// Summary:
//     The CExtTabModelManager class derived from CFOTabModelManager
//      Extend Tab Model Manager
//===========================================================================

class CExtTabModelManager : public CFOTabModelManager
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CExtTabModelManager---Extend Tab Model Manager, Specifies a CExtTabModelManager object.
	DECLARE_SERIAL(CExtTabModelManager);
public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Extend Tab Model Manager, Constructs a CExtTabModelManager object.
	//		Returns A  value.
	CExtTabModelManager();
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Extend Tab Model Manager, Destructor of class CExtTabModelManager
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CExtTabModelManager();

public:

	// Delete a tab.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Delete Tab, Deletes the given object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nTab---nTab, Specifies A integer value.
	virtual void		DeleteTab(int nTab);

	CExtDataModelList m_ModelCache;

	// Find model in cache.
	CExtTabModel *FindInCache(const CString &strTitle);

	// Remove from cache.
	void RemoveCache(const CString &strTitle);

	// Find only model.
	CExtTabModel *FindOnly(const CString &str);

	//----------------------------------------------------------------------
	// Summary:
	// Get All Basic Shapes, Returns the specified value.
	// Parameters:
	//		&list---Specifies a E-XD++ CFODrawShapeList &list object.
	void GetAllBasicShapes(CFODrawShapeList &list);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get All Component Shapes, Returns the specified value.
	// Parameters:
	//		&listNor---&listNor, Specifies a E-XD++ CFODrawShapeList &listNor object.
	void GetAllCompShapes(CFODrawShapeList &listNor);
	
	// find the caption of a model
	// strCap -- the caption of page model.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Model Caption, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns BOOLvalue, TRUE on success; FALSE otherwise.  
	// Parameters:
	//		strCap---strCap, Specifies A CString type value.
	virtual BOOL		FindModelCaption(CString strCap);

	//-----------------------------------------------------------------------
	// Summary:
	// Get All Link Shapes, Returns the specified value.
	// Parameters:
	//		&listLink---&listLink, Specifies a E-XD++ CFODrawShapeList &listLink object.
	void GetAllLinkShapes(CFODrawShapeList &listLink);

	CFOTabPageModel* MakeNew();

	// Insert a new tab.
	// szLabel -- label of tab sheet.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Insert Tab, Inserts a child object at the given index..
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFOTabPageModel,or NULL if the call failed  
	// Parameters:
	//		szLabel---szLabel, Specifies A CString type value.
	virtual CFOTabPageModel* InsertTab(CString szLabel = _T(""));

	// Insert a new tab.
	// pModel -- a pointer to a new tab page model.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Insert Tab, Inserts a child object at the given index..
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFOTabPageModel,or NULL if the call failed  
	// Parameters:
	//		CFOTabPageModel*pModel---F O Tab Page Model*p Model, A pointer to the CFOTabPageModel or NULL if the call failed.
	virtual CFOTabPageModel* InsertTab(CFOTabPageModel*pModel);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&ar---Specifies a CArchive &ar object.
	virtual void Serialize(CArchive &ar);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Document, Call this function to save the specify data to a file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL SaveDocument(LPCTSTR lpszPathName);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Document, Open document from specify file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OpenDocument(LPCTSTR lpszPathName);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get File, Returns the specified value.
	//		Returns a pointer to the object CFile ,or NULL if the call failed  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		nOpenFlags---Open Flags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pError---pError, A pointer to the CFileException or NULL if the call failed.
	CFile *GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Release File, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pFile---pFile, A pointer to the CFile or NULL if the call failed.  
	//		bAbort---bAbort, Specifies A Boolean value.
	virtual void ReleaseFile(CFile* pFile, BOOL bAbort);
// Implementation
public:
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
};

//////////////////////////////////////////////////////////////////////////////////
// CExtRemoveCompAction -- action that remove component from canvas.

 
//===========================================================================
// Summary:
//     The CExtRemoveCompAction class derived from CFOAction
//      F O Remove Component Action
//===========================================================================

class CExtRemoveCompAction : public CFOAction
{
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ A C T I O N, .
	//		Returns A  value (Object).  
	// Parameters:
	//		CExtRemoveCompAction---F O Remove Component Action, Specifies a E-XD++ CExtRemoveCompAction object (Value).
	DECLARE_ACTION(CExtRemoveCompAction)
public:
	
	// Constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// F O Remove Component Action, Constructs a CExtRemoveCompAction object.
	//		Returns A  value (Object).  
	// Parameters:
	//		pModel---pModel, A pointer to the CExtTabModel or NULL if the call failed.  
	//		pShape---pShape, A pointer to the CBPMActTaskShape or NULL if the call failed.
	CExtRemoveCompAction(CFODataModel* pModel, CBPMActTaskShape* pShape);

	// Destructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C F O Remove Component Action, Destructor of class CExtRemoveCompAction
	//		Returns A  value (Object).
	~CExtRemoveCompAction();

// Overrides
public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Execute, Executes the action.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns BOOLvalue, TRUE on success; FALSE otherwise.
	// Execute the action.
	virtual BOOL Execute();

	// Return the inverse action of this one
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Undo Action, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFOBaseAction,or NULL if the call failed
	virtual CFOBaseAction* GetUndoAction() const;

	// Return a copy of this action
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Redo Action, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFOBaseAction,or NULL if the call failed
	virtual CFOBaseAction* GetRedoAction() const;

	// Get the name of this action.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Sprint, .
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		strLabel---strLabel, Specifies A CString type value.
	virtual void Sprint(CString& strLabel) const;

	// Set shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Shape, Sets a specify value to current class CExtRemoveCompAction
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CBPMActTaskShape  or NULL if the call failed.
	virtual void SetShape(CBPMActTaskShape *pShape);
	
	// Get the pointer of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Shape, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CBPMActTaskShape ,or NULL if the call failed
	virtual CBPMActTaskShape *GetShape();


	// Obtain index within list.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Index Within, Returns the specified value.
	//		Returns a int type value.  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CBPMActTaskShape  or NULL if the call failed.  
	//		pCompList---Component List, A pointer to the CFODrawShapeSet or NULL if the call failed.
	int GetIndexWithin(CBPMActTaskShape *pShape, CFODrawShapeSet* pCompList);

	// Obtain index within list.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Index Within, Returns the specified value.
	//		Returns a int type value.  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CBPMActTaskShape  or NULL if the call failed.  
	//		pCompList---Component List, A pointer to the CFODrawShapeList or NULL if the call failed.
	int GetIndexWithin(CBPMActTaskShape *pShape, CFODrawShapeList* pCompList);


	// Obtain maximize position.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Maximize Position, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CRect type value.
	virtual CRect GetMaxPosition();

	// Attributes
protected:

	// The pointer of shape
 
	// Shape, This member maintains a pointer to the object CBPMActTaskShape.  
	CBPMActTaskShape* m_pShape;

	// Current index within.
 
	// Index, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int			m_nIndex;

	// F O P Canvas Core, This member specify friend class object.  
	friend class CFOPCanvasCore;
};

_FOLIB_INLINE void CExtRemoveCompAction::SetShape(CBPMActTaskShape *pShape)
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
	
_FOLIB_INLINE CBPMActTaskShape *CExtRemoveCompAction::GetShape()
{
	return m_pShape;
}

#define		EXT_ACTION_ADDSHAPE				FO_ACTION_CUSTOM+2	//CExtAddCompAction
#define		EXT_ACTION_REMOVESHAPE			FO_ACTION_CUSTOM+3	//CExtRemoveCompAction

#define		EXT_ACTION_ADDSHAPES				FO_ACTION_CUSTOM+4	//CExtAddCompsAction
#define		EXT_ACTION_REMOVESHAPES			FO_ACTION_CUSTOM+5	//CExtRemoveCompsAction

//===========================================================================
// Summary:
//     The CExtAddCompAction class derived from CFOAction
//      F O Add Component Action
//===========================================================================

class CExtAddCompAction : public CFOAction
{
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ A C T I O N, .
	//		Returns A  value (Object).  
	// Parameters:
	//		CExtAddCompAction---F O Add Component Action, Specifies a E-XD++ CExtAddCompAction object (Value).
	DECLARE_ACTION(CExtAddCompAction)

public:
	// member
	// Constructor. 
	
	//-----------------------------------------------------------------------
	// Summary:
	// F O Add Component Action, Constructs a CExtAddCompAction object.
	//		Returns A  value (Object).  
	// Parameters:
	//		pModel---pModel, A pointer to the CExtTabModel or NULL if the call failed.  
	//		pShape---pShape, A pointer to the CBPMActTaskShape or NULL if the call failed.
	CExtAddCompAction(CFODataModel* pModel, CBPMActTaskShape* pShape);

	// member
	// Destructor. 
	
	//-----------------------------------------------------------------------
	// Summary:
	// C F O Add Component Action, Destructor of class CExtAddCompAction
	//		Returns A  value (Object).
	~CExtAddCompAction();

// Overrides
public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Execute, Executes the action.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns BOOLvalue, TRUE on success; FALSE otherwise.
	//Executes the action
	virtual BOOL		Execute();

	// Return the inverse action of this one
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Undo Action, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFOBaseAction,or NULL if the call failed
	virtual CFOBaseAction* GetUndoAction() const;

	// Return a copy of this action
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Redo Action, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFOBaseAction,or NULL if the call failed
	virtual CFOBaseAction* GetRedoAction() const;

	// Get the name of the action, override this method to generate text of action.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Sprint, .
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		strLabel---strLabel, Specifies A CString type value.
	virtual void Sprint(CString& strLabel) const;

    // Set shape member variable m_pShape to the pointer of pShape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Shape, Sets a specify value to current class CExtAddCompAction
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CBPMActTaskShape  or NULL if the call failed.
	virtual void SetShape(CBPMActTaskShape *pShape);
	
	//  Returns a pointer to the Shape
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Shape, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CBPMActTaskShape ,or NULL if the call failed
	virtual CBPMActTaskShape *GetShape();

	// Set index.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Index, Sets a specify value to current class CExtAddCompAction
	// Parameters:
	//		&nIndex---&nIndex, Specifies A integer value.
	void SetIndex(const int &nIndex) { m_nIndex = nIndex; }

	// Obtain maximize position.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Maximize Position, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CRect type value.
	virtual CRect GetMaxPosition();

// Attributes
protected:

	// a pointer to the Shape
 
	// Shape, This member maintains a pointer to the object CBPMActTaskShape.  
	CBPMActTaskShape*	m_pShape;

	// Current index within.
 
	// Index, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int			m_nIndex;

	// Declare friend class CFOPCanvasCore
 
	// F O P Canvas Core, This member specify friend class object.  
	friend class CFOPCanvasCore;
};

//  Returns a pointer to the Shape	
_FOLIB_INLINE CBPMActTaskShape *CExtAddCompAction::GetShape()
{
	return m_pShape;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTTABMODELMANAGER_H__955604C6_297A_414D_8A20_86A380FE10A2__INCLUDED_)
