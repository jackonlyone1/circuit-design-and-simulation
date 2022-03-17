#if !defined(FO_EXTTABMODEL_H__AEC0777D_A0DB_4ABA_88AD_1D0440F4B50B__INCLUDED_)
#define AFC_EXTTABMODEL_H__AEC0777D_A0DB_4ABA_88AD_1D0440F4B50B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------
// Description
// Author: Author Name.
//------------------------------------------------------


#define IDR_D_SYM_FILE                      78
#define IDR_SELECT_SHAPE					79

//===========================================================================
// Summary:
//     The CExtTabModel class derived from CFOTabPageModel
//      Extend Tab Model
//===========================================================================

class CExtTabModel : public CFOTabPageModel
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CExtTabModel---Extend Tab Model, Specifies a CExtTabModel object.
	DECLARE_SERIAL(CExtTabModel);

public:
	// Constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Extend Tab Model, Constructs a CExtTabModel object.
	//		Returns A  value.
	CExtTabModel();

	// Copy constructor. 
	
	//-----------------------------------------------------------------------
	// Summary:
	// Extend Tab Model, Constructs a CExtTabModel object.
	//		Returns A  value.  
	// Parameters:
	//		source---Specifies a const CExtTabModel& source object.
	CExtTabModel(const CExtTabModel& source);

	// Deconstructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Extend Tab Model, Destructor of class CExtTabModel
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CExtTabModel();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear All shapes from the data model.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear All, Remove the specify data from the list.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void			ClearAll();

	
	// Obtain the top most port.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Top Port, Returns the specified value.
	//		Returns a pointer to the object CFOPortShape ,or NULL if the call failed  
	// Parameters:
	//		*pComp---*pComp, A pointer to the CFODrawPortsShape  or NULL if the call failed.
	CFOPortShape *GetTopPort(CFODrawPortsShape *pComp);
	
	// Obtain the Bottom most port.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Bottom Port, Returns the specified value.
	//		Returns a pointer to the object CFOPortShape ,or NULL if the call failed  
	// Parameters:
	//		*pComp---*pComp, A pointer to the CFODrawPortsShape  or NULL if the call failed.
	CFOPortShape *GetBottomPort(CFODrawPortsShape *pComp);
	
	// Obtain the left most port.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Top Port, Returns the specified value.
	//		Returns a pointer to the object CFOPortShape ,or NULL if the call failed  
	// Parameters:
	//		*pComp---*pComp, A pointer to the CFODrawPortsShape  or NULL if the call failed.
	CFOPortShape *GetLeftPort(CFODrawPortsShape *pComp);
	
	
	// Obtain the left most port.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Top Port, Returns the specified value.
	//		Returns a pointer to the object CFOPortShape ,or NULL if the call failed  
	// Parameters:
	//		*pComp---*pComp, A pointer to the CFODrawPortsShape  or NULL if the call failed.
	CFOPortShape *GetRightPort(CFODrawPortsShape *pComp);
	//-----------------------------------------------------------------------
	// Summary:
	// Hit Test Port,ports are the shapes that link together.
	// return the pointer of current shape's port shape.
	// point -- HitTest logical point.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit Test Port, Hit test on this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFOPortShape,or NULL if the call failed  
	// Parameters:
	//		point---Specifies A CPoint type value.  
	//		&bUseExt---Use Extend, Specifies A Boolean value.  
	//		&nExp---&nExp, Specifies A integer value.
	virtual CFOPortShape*   HitTestPort(
		// Mouse hit point.
		CPoint point,
		// Use extend border hit or not
		const BOOL &bUseExt = TRUE,
		// Hit expand value.
		const int &nExp = 30
		);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Insert new shape.
	// pShape -- the pointer of shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Insert Shape2, Inserts a child object at the given index..
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pShape---pShape, A pointer to the CFODrawShape or NULL if the call failed.
	virtual void			InsertShape2(CFODrawShape* pShape);
	
	// Do create a new shape.
	// m_drawshape -- Shape Type id start from FO_COMP_CUSTOM
	// rcCreate -- init position of shape.
	// strFileName -- if being image shape,this is the image file name.
	// pCurItem -- if being drag and drop from toolbox,this is the pointer of current toolbox item.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Create Shape By Type, Do create a new shape,override this method to add your own custom shape creating.See sample UserDefine shows.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape ,or NULL if the call failed  
	// Parameters:
	//		m_drawshape---Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		&rcCreate---&rcCreate, Specifies A CRect type value.  
	//		strFileName---File Name, Specifies A CString type value.  
	//		*pCurItem---Current Item, A pointer to the CFOToolBoxItem  or NULL if the call failed.
	virtual CFODrawShape *DoCreateShapeByType(UINT m_drawshape,CRect &rcCreate,CString strFileName = _T(""),CFOToolBoxItem *pCurItem = NULL);

	//-----------------------------------------------------------------------
	// Summary:
	// Copy, Create a duplicate copy of this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODataModel,or NULL if the call failed
	// Create a duplicate copy of this object. 
	virtual CFODataModel* Copy() const;

	// Obtain all the shapes on the canvas,it will return a pointer to the list of child shapes on the canvas.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get All Basic Shape, Returns the specified value.
	// Parameters:
	//		&list---Specifies a E-XD++ CFODrawShapeList &list object.
	void		GetAllBasicShape(CFODrawShapeList &list);
	
	// Call before create shape new shape.
	// pShape -- the pointer of shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Create Shape, Call before create shape new shape,this method will be called after each new shape is created, You can override this method to do something before shape created.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pShape---*pShape, A pointer to the CFODrawShape  or NULL if the call failed.
	virtual void DoInitCreateShape(CFODrawShape *pShape);

	// Obtain all the shapes on the canvas,it will return a pointer to the list of child shapes on the canvas.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get All Comps2, Returns the specified value.
	// Parameters:
	//		&list---Specifies a E-XD++ CFODrawShapeList &list object.
	void		GetAllComps2(CFODrawShapeList &list);

	//Add Link Shape
	// m_drawshape -- Shape Type id start from FO_COMP_CUSTOM
	// arPoints -- Init position of link shape.
	// pFrom -- start link port shape pointer.
	// pTo -- end link port shape pointer.
	// nArrowType -- if being true,it has an arrow else it doesn't has an arrow.
	//			 0-None arrow.
	//			 1-One arrow at the end.
	//			 2- Two arrow,start arrow and end arrow.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Link Shape2, Adds an object to the specify list.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed  
	// Parameters:
	//		m_drawshape---Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		CArray<CPoint---Array< C Point, Specifies A array.  
	//		*arPoints---*arPoints, A pointer to the CPoint>  or NULL if the call failed.  
	//		*pFrom---*pFrom, A pointer to the CFOPortShape  or NULL if the call failed.  
	//		*pTo---*pTo, A pointer to the CFOPortShape  or NULL if the call failed.  
	//		nArrowType---Arrow Type, Specifies A integer value.
	virtual CFODrawShape*		AddLinkShape2(UINT m_drawshape,
		CArray<CPoint,CPoint> *arPoints,
		CFOPortShape *pFrom = NULL,
		CFOPortShape *pTo = NULL,
		int nArrowType = 0);

public:

	// Init model data.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Initial Data, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,
	virtual void DoInitData();

	// Set modified flag.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Modified Flag, Sets a specify value to current class CExtTabModel
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		bModified---bModified, Specifies A Boolean value.
	virtual void SetModifiedFlag(BOOL bModified = TRUE);

	// Is modified.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Modified, Determines if the given value is correct or exist.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL IsModified();

	// Notify observer wnd.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Notify Observer, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		lHint---lHint, Specifies A lparam value.  
	//		CObject*pHint---Object*p Hint, A pointer to the CObject or NULL if the call failed.
	virtual void NotifyObserver(LPARAM lHint, CObject*pHint = NULL);

	// Update Title
	
	//-----------------------------------------------------------------------
	// Summary:
	// Update Title, Call this member function to update the object.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void UpdateTitle();

	// Do action change.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Action Change, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pAction---pAction, A pointer to the const CFOBaseAction or NULL if the call failed.
	virtual void DoActionChange(const CFOBaseAction* pAction);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Shape By Type to the canvas,this is a system method,by default,you need not override this method.
	// m_drawshape -- Shape Type id start from FO_COMP_CUSTOM
	// rcCreate -- init position of shape.
	// strFileName -- if being image shape,this is the image file name.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Add Shape By Type, Adds an object to the specify list.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed  
	// Parameters:
	//		m_drawshape---Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		&rcCreate---&rcCreate, Specifies A CRect type value.  
	//		strFileName---File Name, Specifies A CString type value.
	virtual CFODrawShape*		AddShapeByType(UINT m_drawshape,
		CRect &rcCreate,
		CString strFileName = _T(""));

	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit test, return the hit test shape pointer.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit Test, Hit test on this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape ,or NULL if the call failed  
	// Parameters:
	//		point---Specifies A CPoint type value.
	// point -- HitTest logical point.
	virtual CFODrawShape *	HitTest(
		// Mouse hit point.
		CPoint point
		);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is New Up Right Link, Determines if the given value is correct or exist.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		*pObj---*pObj, A pointer to the CFODrawShape  or NULL if the call failed.
	BOOL IsNewUpRightLink(CFODrawShape *pObj);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit test, return the hit test shape pointer.
	// point -- HitTest logical point.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit Test2, Hit test on this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape ,or NULL if the call failed  
	// Parameters:
	//		&m_TempList---Temp List, Specifies a const CFODrawShapeList &m_TempList object.  
	//		point---Specifies A CPoint type value.
	virtual CFODrawShape *	HitTest2(
		// Previous list.
		const CFODrawShapeList &m_TempList,
		// Mouse hit point.
		CPoint point
		);

	
	// Print all the shapes on the canvas to printer.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Print Shape, Print all the shapes on the canvas to printer.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&rcView---&rcView, Specifies A CRect type value.
	virtual void			OnPrintShape(
		// DC.
		CDC *pDC,
		// Client rectangle of view
		const CRect &rcView
		);


	// Do create a new shape shape.
	// m_drawshape -- Shape Type id start from FO_COMP_CUSTOM
	// rcCreate -- init position of shape.
	// strFileName -- if being image shape,this is the image file name.
	// pCurItem -- if being drag and drop from toolbox,this is the pointer of current toolbox item.
	virtual CFOCompositeShape *DoCreateCompositeShapeByType(UINT m_drawshape,CRect &rcCreate,
		CArray<FOPORTVALUE,FOPORTVALUE> *arInitPorts,
		CString strFileName = _T(""),
		UINT nResID = 0,
		CFOToolBoxItem *pCurItem = NULL);

	// Draw shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Shape, Draw all the shapes on the canvas to device.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&rcView---&rcView, Specifies A CRect type value.
	virtual void OnDrawShape(CDC *pDC,const CRect &rcView);

	// Draw Back ground.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Back, Draw the background of this canvas.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&rcClip---&rcClip, Specifies A CRect type value.
	virtual void OnDrawBack(CDC *pDC,const CRect &rcClip);

	// Get Unique Name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Unique Name, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual CString GetUniqueName(UINT nType);

	// Get Unique Caption
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Unique Caption, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual CString GetUniqueCaption(UINT nType);

	// Get base shape name.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Base Name, You construct a CExtTabModel object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual CString CreateBaseName(UINT nType);

	// Get base shape caption.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Base Caption, You construct a CExtTabModel object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CString type value.  
	// Parameters:
	//		nType---nType, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	virtual CString CreateBaseCaption(UINT nType);

	// Find shape with name.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Shape With Name, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed  
	// Parameters:
	//		str---Specifies A CString type value.
	CFODrawShape* FindShapeWithName(CString str);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit test, return the hit test shape pointer.
	// point -- HitTest logical point.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Hit Test On Bus, Hit test on this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed  
	// Parameters:
	//		point---Specifies A CPoint type value.
	virtual CFODrawShape*	HitTestOnBus(
		// Mouse hit point.
		CPoint point
		);
	
public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&ar---Specifies a CArchive &ar object.
	// Serialize data to file.
	virtual void Serialize(CArchive &ar);

	// Save Document to a specify file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Document, Call this function to save the specify data to a file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL SaveDocument(LPCTSTR lpszPathName);

	// Open Document from a specify file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Document, Open document from specify file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OpenDocument(LPCTSTR lpszPathName);

	// Get the pointer of File.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get File, Returns the specified value.
	//		Returns a pointer to the object CFile ,or NULL if the call failed  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		nOpenFlags---Open Flags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pError---pError, A pointer to the CFileException or NULL if the call failed.
	CFile *		 GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError);

	// Release File from memory.
	
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
	
	// Current rotate angle.
	int m_nCurRotateAngle;
	
	// Current symbols file.
	CString m_strSymFile;
	
	// Current select shape.
	CFOCompositeShape *m_pCurSelect;
};


// Data model list.
typedef CTypedPtrList<CObList, CExtTabModel*> CExtDataModelList;

#endif // !defined(AFC_EXTTABMODEL_H__AEC0777D_A0DB_4ABA_88AD_1D0440F4B50B__INCLUDED_)
