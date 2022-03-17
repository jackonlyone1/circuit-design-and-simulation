#if !defined(FO_BPMACTTASKSHAPE_H__0C7C6112_6C54_4467_9BA5_A65E1AECA21E__INCLUDED_)
#define FO_BPMACTTASKSHAPE_H__0C7C6112_6C54_4467_9BA5_A65E1AECA21E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------
// Description
// Author: Author Name.
//------------------------------------------------------

#define BPM_ACT_TASK_SHAPE		FO_COMP_CUSTOM + 20

 
//===========================================================================
// Summary:
//     The CBPMActTaskShape class derived from CFORectShape
//      B P M Activate Task Shape
//===========================================================================

class CBPMActTaskShape : public CFORectShape  
{
protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ S E R I A L, None Description.
	//		Returns A  value.  
	// Parameters:
	//		CBPMActTaskShape---B P M Activate Task Shape, Specifies a CBPMActTaskShape object.
	DECLARE_SERIAL(CBPMActTaskShape);
public:

	// constructor
	
	//-----------------------------------------------------------------------
	// Summary:
	// B P M Activate Task Shape, Constructs a CBPMActTaskShape object.
	//		Returns A  value.
	CBPMActTaskShape();

	// Copy constructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// B P M Activate Task Shape, Constructs a CBPMActTaskShape object.
	//		Returns A  value.  
	// Parameters:
	//		src---Specifies a const CBPMActTaskShape& src object.
	CBPMActTaskShape(const CBPMActTaskShape& src);

	// Destructor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// C B P M Activate Task Shape, Destructor of class CBPMActTaskShape
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CBPMActTaskShape();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Create, You construct a CBPMActTaskShape object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&rcPos---&rcPos, Specifies A CRect type value.  
	//		strCaption---strCaption, Specifies A CString type value.
	// Creates the button shape from a CRect object.
	virtual void Create(CRect &rcPos,CString strCaption = _T(""));

	// Search and add new property object.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Add Custom Property, Search and add new property object.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void DoAddCustProp();

	// Do sub menu change.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Child Menu Change, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&nMenuItem---Menu Item, Specifies A integer value.  
	//		&strState---&strState, Specifies A CString type value.
	virtual void DoSubMenuChange(const int &nMenuItem, const CString &strState);

	// Calc the label start position.
	// pDC -- pointer of the DC.
	// bFullSize -- using full size or not.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Calculate Label Position, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a CRect type value.  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&bFullSize---Full Size, Specifies A Boolean value.
	virtual CRect CalcLabelPosition(CDC *pDC,BOOL &bFullSize) const;
	
	// Compute current area.
	// pArea -- area pointer
	
	//-----------------------------------------------------------------------
	// Summary:
	// Extend Geometry Updated, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pArea---pArea, A pointer to the CFOArea or NULL if the call failed.
	virtual void  ExtGeometryUpdated(CFOArea* pArea);

public:

	// Assignment operator.
	
	//-----------------------------------------------------------------------
	// Summary:
	// None Description.
	//		Returns A CBPMActTaskShape& value.  
	// Parameters:
	//		src---Specifies a const CBPMActTaskShape& src object.
	CBPMActTaskShape& operator=(const CBPMActTaskShape& src);

	// Draws the Text status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Text And Edit, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.  
	//		&rcText---&rcText, Specifies A CRect type value.  
	//		&bFullSize---Full Size, Specifies A Boolean value.
	virtual void OnDrawTextAndEdit(CDC *pDC,const CRect &rcText,const BOOL &bFullSize = TRUE);

	//-----------------------------------------------------------------------
	// Summary:
	// Is Selected, Determines if the given value is correct or exist.
	//		Returns TRUE on success; FALSE otherwise.
	BOOL IsSelected();

	//-----------------------------------------------------------------------
	// Summary:
	// Copy, Create a duplicate copy of this object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CFODrawShape,or NULL if the call failed
	// Creates a copy of this shape.
	virtual CFODrawShape* Copy() const;

	//Generate Shape Area
	
	//-----------------------------------------------------------------------
	// Summary:
	// Geometry Updated, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pRgn---pRgn, A pointer to the CFOArea or NULL if the call failed.
	virtual void GeometryUpdated(CFOArea* pRgn);

public:
	
	// WM_LBUTTONDOWN message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Down, Called when the user presses the left mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnLButtonDown(UINT nFlags, CPoint point); 

	// WM_LBUTTONUP message.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Up, Called when the user releases the left mouse button.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
	virtual void OnLButtonUp(UINT nFlags, CPoint point);

	// Get plus spots
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Plus Spot Location, Returns the specified value.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		lstHandle---lstHandle, Specifies a E-XD++ CFOPHandleList& lstHandle object.
	virtual void GetPlusSpotLocation(CFOPHandleList& lstHandle);
	
	// Draws the truely shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDraw(CDC *pDC);

public:

	
	//-----------------------------------------------------------------------
	// Summary:
	// Serialize, Reads or writes this object from or to an archive.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		&ar---Specifies a CArchive &ar object.
	// Serializes the data.
	virtual void Serialize(CArchive &ar);
	
	// Save document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Document, Call this function to save the specify data to a file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL SaveDocument(LPCTSTR lpszPathName);

	// Open document.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Open Document, Open document from specify file.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		lpszPathName---Path Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.
	virtual BOOL OpenDocument(LPCTSTR lpszPathName);
	
	// Get file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get File, Returns the specified value.
	//		Returns a pointer to the object CFile ,or NULL if the call failed  
	// Parameters:
	//		lpszFileName---File Name, Specifies A 32-bit pointer to a constant character string that is portable for Unicode and DBCS.  
	//		nOpenFlags---Open Flags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		pError---pError, A pointer to the CFileException or NULL if the call failed.
	CFile *GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError);
	
	// Release file.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Release File, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pFile---pFile, A pointer to the CFile or NULL if the call failed.  
	//		bAbort---bAbort, Specifies A Boolean value.
	virtual void ReleaseFile(CFile* pFile, BOOL bAbort);

public:

	//Draw flat status.

	// Draws custom tracker.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Track Custom, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawTrackCustom(CDC *pDC);

	// Creates GDI objects and sets up the device context for drawing. 
	
	//-----------------------------------------------------------------------
	// Summary:
	// Prepare D C, Creates GDI objects and sets up the device context for drawing.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	virtual void PrepareDC(CDC* pDC);

	// Draws the flat status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Flat, Draws the flat status of the shape.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawFlat(CDC *pDC);

	// Draws shadow of shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw Shadow, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDrawShadow(CDC *pDC);

	// Draws the 3D status of the shape.
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Draw3d, Draws the 3d status of the shape.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		*pDC---D C, A pointer to the CDC  or NULL if the call failed.
	virtual void OnDraw3d(CDC *pDC);

	// Frees GDI objects and restores the state of the device context.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear D C, Remove the specify data from the list.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDC---D C, A pointer to the CDC or NULL if the call failed.
	virtual void ClearDC(CDC* pDC);
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


#endif // !defined(FO_BPMACTTASKSHAPE_H__0C7C6112_6C54_4467_9BA5_A65E1AECA21E__INCLUDED_)
