/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_EDITTREECTRL_H__508278DE_BE33_4505_80FE_51C64B2B3EBB__INCLUDED_)
#define AFX_EDITTREECTRL_H__508278DE_BE33_4505_80FE_51C64B2B3EBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditTreeCtrl.h : header file
//

#pragma warning(4:4786)		// identifier too long in debug...

//---------------------------------------------------------------------------
// CEditTreeCtrl window

class CDragData;

/////////////////////////////////////////////////////////////////////////////
// CMyRenameDlg dialog

 
//===========================================================================
// Summary:
//     The CMyRenameDlg class derived from CDialog
//      My Rename Dialog
//===========================================================================

class CMyRenameDlg : public CDialog
{
	
	// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// My Rename Dialog, Constructs a CMyRenameDlg object.
	//		Returns A  value.  
	// Parameters:
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CMyRenameDlg(CWnd* pParent = NULL);   // standard constructor
	
	
	// Dialog Data
	//{{AFX_DATA(CMyRenameDlg)
	enum { IDD = IDD_FO_TAB_RENAME };
 
	// m_strCaption, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString	m_strCaption;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRenameDlg)
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
	//{{AFX_MSG(CMyRenameDlg)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Change Edit1, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
};

 
//===========================================================================
// Summary:
//     The CEditTreeCtrl class derived from CFOPExtTreeCtrl
//      Edit Tree 
//===========================================================================

class CEditTreeCtrl : public CFOPExtTreeCtrl
{
	protected:
		enum EDropHint {
			DROP_BELOW,
			DROP_ABOVE,
			DROP_CHILD,
			DROP_NODROP
		};

		typedef bool (CEditTreeCtrl::*method)(HTREEITEM);

		// dragging
 
	// Drag Data, This member maintains a pointer to the object CDragData.  
		CDragData *	m_pDragData;

	// Construction
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Edit Tree , Constructs a CEditTreeCtrl object.
	//		Returns A  value.
		CEditTreeCtrl();

	// Attributes
	public:

	// Operations
	public:

			// Override this to control the behavior when a user wants to
			// edit an item's text. The default implementation always returns true.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Can Edit Label, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		hItem---hItem, Specifies a HTREEITEM hItem object.
		virtual bool	CanEditLabel(HTREEITEM hItem);

			// Override to control the setting of text for a label. Check the
			// pszText member of the TVITEM structure. The default implementation
			// always returns true. The <item> contains the new text.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Can Set Label Text, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		item---Specifies a TVITEM & item object.
		virtual bool	CanSetLabelText(TVITEM & item);

			// Is it allowed to delete this item?
			// The default implementation always returns true.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Can Delete Item, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		hItem---hItem, Specifies a HTREEITEM hItem object.
		virtual bool	CanDeleteItem(HTREEITEM hItem);

			// Is it OK to add a child item to this item?
			// <hParent> == NULL means top-level
			// The default implementation always returns true.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Can Insert Item, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		hParent---hParent, Specifies a HTREEITEM hParent object.
		virtual bool	CanInsertItem(HTREEITEM hParent);

			// Can we sort the level, the given item lies in?
			// This is called from the default implementation
			// of SortCurrentLevel() (see below)
			// if hItem is NULL, the root level is meant.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Can Sort Level, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		hItem---hItem, Specifies a HTREEITEM hItem object.
		virtual bool	CanSortLevel(HTREEITEM hItem);
		
			// Override to (dis-)allow dragging of an item.
			// The default implementation always allows dragging.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Can Drag Item, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		item---Specifies a TVITEM & item object.
		virtual bool	CanDragItem(TVITEM & item);

			// Override to (dis-)allow dropping an item at this specific point.
			// The default implementation always allows dropping.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Can Drop Item, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		hDrag---hDrag, Specifies a HTREEITEM hDrag object.  
	//		hDrop---hDrop, Specifies a HTREEITEM hDrop object.  
	//		hint---Specifies A integer value.
		virtual bool	CanDropItem(HTREEITEM hDrag, HTREEITEM hDrop, EDropHint hint);

	// Overridables
	protected:
			// Override if you want to use other keys than the default.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Handle Key Down, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		wParam---wParam, Provides additional information used in processing the message. The parameter value depends on the message.  
	//		lParam---lParam, Specifies A lparam value.
		virtual bool	HandleKeyDown(WPARAM wParam, LPARAM lParam);

			// The following will be called whenever the user wants to insert a new item.
			// You might override this method to change the default text or other
			// settings for the new item.
			// Returns true, if the item could be added, false if not.
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Item, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		ins---Specifies a TVINSERTSTRUCT & ins object.
		virtual bool	NewItem(TVINSERTSTRUCT & ins);

		// The following will be called whenever the user wants to insert a new item.
		// You might override this method to change the default text or other
		// settings for the new item.
		// Returns true, if the item could be added, false if not.
	
	//-----------------------------------------------------------------------
	// Summary:
	// New Item2, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		ins---Specifies a TVINSERTSTRUCT & ins object.
		virtual bool	NewItem2(TVINSERTSTRUCT & ins);

	
	//-----------------------------------------------------------------------
	// Summary:
	// On New Item, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		hItem---hItem, Specifies a HTREEITEM hItem object.
			// OnNewItem() is called by the default implementation of NewItem()
			// after the new item was created and made the selected one and
			// before the editor is started to rename the item.
		virtual void	OnNewItem(HTREEITEM hItem);

			// The default-implementation creates the cursor-map
			// from the bit-masks described in "CursorDef.h".
			// You might override this method to provide other
			// cursors.
			// Note that this function will only be called once per session!
			// All CEditTreeCtrl objects will use the same cursor map!
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Cursor Map, You construct a CEditTreeCtrl object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	CreateCursorMap();

			// Sort the level, the given item is member of.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Sort Current Level, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		hItem---hItem, Specifies a HTREEITEM hItem = 0 object.
		virtual void	SortCurrentLevel(HTREEITEM hItem = 0);

			// Sort the level, the given item is member of, and all sublevels.
			// With hItem set to zero, the entire tree will be sorted.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Sort Current Level And Below, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		hItem---hItem, Specifies a HTREEITEM hItem = 0 object.
		virtual void	SortCurrentLevelAndBelow(HTREEITEM hItem = 0);

			// The default implementation will popup a context menu that offers
			// most of the tree's functionality.
			// 'point' is in screen coordinates
	
	//-----------------------------------------------------------------------
	// Summary:
	// Display Context Menu, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		point---Specifies A CPoint type value.
		virtual void	DisplayContextMenu(CPoint & point);

			// For your own context menu you have two choices:
			// 1. override "DisplayContextMenu()" to support a completly different menu
	
	//-----------------------------------------------------------------------
	// Summary:
	// Extend Context Menu, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		menu---Specifies a CMenu & menu object.
			// 2. override "ExtendContextMenu()" to provide additional functionality
			// The default implementation simply does nothing.
		virtual void	ExtendContextMenu(CMenu & menu);

	// Dragging
	protected:
			// Start dragging an item.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Start, None Description.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	DragStart();

			// Move the dragging item.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Move, None Description.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	DragMove();

			// End dragging the item.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag End, None Description.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	DragEnd();

			// Reset dragging.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Stop, None Description.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	DragStop();

			// Set the dragcursor.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Drag Cursor, Sets a specify value to current class CEditTreeCtrl
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		hDropTarget---Drop Target, Specifies a HTREEITEM hDropTarget object.  
	//		hint---Specifies A integer value.
		virtual void	SetDragCursor(HTREEITEM hDropTarget, EDropHint hint);

			// Move (or copy) an item to its new position.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Move Item, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		hDrag---hDrag, Specifies a HTREEITEM hDrag object.  
	//		hDrop---hDrop, Specifies a HTREEITEM hDrop object.  
	//		hint---Specifies A integer value.  
	//		bCopy---bCopy, Specifies A Boolean value.
		virtual void	DragMoveItem(HTREEITEM hDrag, HTREEITEM hDrop, EDropHint hint, bool bCopy);

			// When right-dragging an item, we display a context menu as soon as
			// the user releases the right mouse button.
			// 'point' is in screen coordinates
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Display Context Menu, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		point---Specifies A CPoint type value.
		virtual void	DragDisplayContextMenu(CPoint & point);

			// If you derive your own version of the CDragData class (see below)
			// you have to override this method.
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Drag Data, You construct a CEditTreeCtrl object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns a pointer to the object CDragData ,or NULL if the call failed  
	// Parameters:
	//		hDragItem---Drag Item, Specifies a HTREEITEM hDragItem object.  
	//		bRightDrag---Right Drag, Specifies A Boolean value.
		virtual CDragData *	CreateDragData(HTREEITEM hDragItem, bool bRightDrag);

	// Keymapper
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Edit Label, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		HTREEITEM---T R E E I T E M, Specifies a HTREEITEM object.
		virtual bool	DoEditLabel(HTREEITEM);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Insert Sibling, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		HTREEITEM---T R E E I T E M, Specifies a HTREEITEM object.
		virtual bool	DoInsertSibling(HTREEITEM);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Insert Child, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		HTREEITEM---T R E E I T E M, Specifies a HTREEITEM object.
		virtual bool	DoInsertChild(HTREEITEM);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Delete Item, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		HTREEITEM---T R E E I T E M, Specifies a HTREEITEM object.
		virtual bool	DoDeleteItem(HTREEITEM);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Delete Scp Item, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		HTREEITEM---T R E E I T E M, Specifies a HTREEITEM object.
		virtual bool	DoDeleteScpItem(HTREEITEM);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Sort Current Level, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		HTREEITEM---T R E E I T E M, Specifies a HTREEITEM object.
		virtual bool	DoSortCurrentLevel(HTREEITEM);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Sort Current Level And Below, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		HTREEITEM---T R E E I T E M, Specifies a HTREEITEM object.
		virtual bool	DoSortCurrentLevelAndBelow(HTREEITEM);

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CEditTreeCtrl)
		public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Translate Message, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pMsg---pMsg, A pointer to the MSG or NULL if the call failed.
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		//}}AFX_VIRTUAL

	// Implementation
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Edit Tree , Destructor of class CEditTreeCtrl
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
		virtual ~CEditTreeCtrl();

	protected:
			// Generate a drop hint from the HitTest()-flags
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Drop Hint, Returns the specified value.
	//		Returns a int type value.  
	// Parameters:
	//		flags---Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
		EDropHint	GetDropHint(UINT flags);

			// Get the drop target item
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Drop Target, Returns the specified value.
	//		Returns A HTREEITEM value.  
	// Parameters:
	//		hint---Specifies A integer value.
		HTREEITEM	GetDropTarget(EDropHint & hint);
		
			// Create a copy of the item <hOrig> and put it under <hParent> at
			// position <hInsertAfter>.
			// This method copies children, too!
	
	//-----------------------------------------------------------------------
	// Summary:
	// Copy Item, Create a duplicate copy of this object.
	//		Returns A HTREEITEM value.  
	// Parameters:
	//		hOrig---hOrig, Specifies a HTREEITEM hOrig object.  
	//		hParent---hParent, Specifies a HTREEITEM hParent object.  
	//		hInsertAfter---Insert After, Specifies a HTREEITEM hInsertAfter object.
		HTREEITEM	CopyItem(HTREEITEM hOrig, HTREEITEM hParent, HTREEITEM hInsertAfter);

			// is <hItem> a direct ancestor of <hCheck>?
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Ancestor, Determines if the given value is correct or exist.
	//		Returns A Boolean value.  
	// Parameters:
	//		hItem---hItem, Specifies a HTREEITEM hItem object.  
	//		hCheck---hCheck, Specifies a HTREEITEM hCheck object.
		bool		IsAncestor(HTREEITEM hItem, HTREEITEM hCheck) const;

		// Generated message map functions
		//{{AFX_MSG(CEditTreeCtrl)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Beginlabeledit, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
		afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Endlabeledit, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
		afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Begindrag, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
		afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Mouse Move, Called when the mouse cursor moves.
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On L Button Up, Called when the user releases the left mouse button.
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Context Menu, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pWnd---pWnd, A pointer to the CWnd or NULL if the call failed.  
	//		point---Specifies A CPoint type value.
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Rclick, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
		afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Beginrdrag, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
		afx_msg void OnBeginrdrag(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On R Button Up, Called when the user releases the right mouse button.
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
		afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On R Button Down, Called when the user presses the right mouse button.
	// Parameters:
	//		nFlags---nFlags, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	//		point---Specifies A CPoint type value.
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Selchanging, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Double click, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		pNMHDR---N M H D R, A pointer to the NMHDR or NULL if the call failed.  
	//		pResult---pResult, A pointer to the LRESULT or NULL if the call failed.
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	
	//-----------------------------------------------------------------------
	// Summary:
	// On Context Cmd, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		uID---I D, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
		afx_msg void	OnContextCmd(UINT uID);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Drag Context Cmd, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		uID---I D, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
		afx_msg void	OnDragContextCmd(UINT uID);

	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
		DECLARE_MESSAGE_MAP()
};


//---------------------------------------------------------------------------
// helper class CDragData

// If you want your own drag-data container, derive a class from CDragData and
// override the 'CreateDragData()' member of your derived CEditTreeCtrl class.

 
//===========================================================================
// Summary:
//      To use a CDragData object, just call the constructor.
//      Drag Data
//===========================================================================

class CDragData {
	protected:
 
	// m_Owner, This member specify CEditTreeCtrl & object.  
		CEditTreeCtrl &	m_Owner;
 
	// Orig Cursor, This member specify HCURSOR object.  
		HCURSOR			m_hOrigCursor;	// Original cursor (when not in dragging mode)
 
	// Item Drag, This member specify HTREEITEM object.  
		HTREEITEM		m_hItemDrag;	// The item being dragged
 
	// Last Drop, This member specify HTREEITEM object.  
		HTREEITEM		m_hLastDrop;	// The point where the last DragMove() occured
 
	// No Move, This member specify USHORT object.  
		USHORT			m_usNoMove;		// helper to auto-expand a collapsed node while dragging an item over it
 
	// Drag Img, This member is a collection of same-sized images.  
		CImageList *	m_pDragImg;		// image of the item being dragged
 
	// Right Drag, Specify A Boolean value.  
		bool			m_bRightDrag;	// Are we dragging the item with the right mouse button?
 
	// Drop Hint, This variable specifies a 32-bit signed integer on 32-bit platforms.  
		int				m_nDropHint;	// How to drop the item being dragged?

	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Data, Constructs a CDragData object.
	//		Returns A  value.  
	// Parameters:
	//		tree---Specifies a CEditTreeCtrl & tree object.  
	//		hItem---hItem, Specifies a HTREEITEM hItem object.  
	//		bRightDrag---Right Drag, Specifies A Boolean value.
		CDragData(CEditTreeCtrl & tree, HTREEITEM hItem, bool bRightDrag)
			: m_Owner(tree)
			, m_hOrigCursor(::GetCursor())
	
	//-----------------------------------------------------------------------
	// Summary:
	// Item Drag, None Description.
	//		Returns A , value.  
	// Parameters:
	//		hItem---hItem, Specifies a hItem object.
			, m_hItemDrag(hItem)
	
	//-----------------------------------------------------------------------
	// Summary:
	// Last Drop, None Description.
	//		Returns A , value.  
	// Parameters:
	//		0---Specifies a 0 object.
			, m_hLastDrop(0)
	
	//-----------------------------------------------------------------------
	// Summary:
	// No Move, None Description.
	//		Returns A , value.  
	// Parameters:
	//		0---Specifies a 0 object.
			, m_usNoMove(0)
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Img, None Description.
	//		Returns A , value.  
	// Parameters:
	//		0---Specifies a 0 object.
			, m_pDragImg(0)
	
	//-----------------------------------------------------------------------
	// Summary:
	// Right Drag, None Description.
	//		Returns A , value.  
	// Parameters:
	//		bRightDrag---Right Drag, Specifies a bRightDrag object.
			, m_bRightDrag(bRightDrag)
	
	//-----------------------------------------------------------------------
	// Summary:
	// Drop Hint, None Description.
	//		Returns A , value.  
	// Parameters:
	//		0---Specifies a 0 object.
			, m_nDropHint(0)
		{
			// all real initialization is done in StartDrag() (see below)
		}

	
	//-----------------------------------------------------------------------
	// Summary:
	// C Drag Data, Destructor of class CDragData
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
		virtual ~CDragData() {
					ASSERT(m_pDragImg == 0);
				}

	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Start Drag, None Description.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	StartDrag() {
							CreateDragImage();
							m_Owner.SetCapture();
						}

	
	//-----------------------------------------------------------------------
	// Summary:
	// End Drag, None Description.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	EndDrag() {
							ReleaseDragImage();
							m_Owner.SelectDropTarget(0);
							m_Owner.EnsureVisible(m_Owner.GetSelectedItem());
							::SetCursor(m_hOrigCursor);
							::ReleaseCapture();
						}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Drag Image, You construct a CDragData object in two steps. First call the constructor, then call Create, which creates the object.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	CreateDragImage() {
							ASSERT(m_pDragImg == 0);
							m_pDragImg = m_Owner.CreateDragImage(m_hItemDrag);
							if(m_pDragImg) {
								CPoint pt;
								::GetCursorPos(&pt);
								m_Owner.ScreenToClient(&pt);
								m_pDragImg->DragShowNolock(TRUE);  // lock updates and show drag image
								m_pDragImg->SetDragCursorImage(0,CPoint(0,0));  // define the hot spot for the new cursor image
								m_pDragImg->BeginDrag(0,CPoint(0,0));
								m_pDragImg->DragEnter(&m_Owner,pt);
								m_pDragImg->DragMove(pt);
							}
						}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Release Drag Image, None Description.
	// This member function is also a virtual function, you can Override it if you need,
		virtual void	ReleaseDragImage() {
							if(m_pDragImg) {
								DragLeave();
								m_pDragImg->EndDrag();
								delete m_pDragImg;
							}
							m_pDragImg = 0;
						}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Drag Item, Returns the specified value.
	//		Returns A HTREEITEM value.
		HTREEITEM		GetDragItem() const { return m_hItemDrag; }
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Drop Target, Returns the specified value.
	//		Returns A HTREEITEM value.
		HTREEITEM		GetDropTarget() const { return m_hLastDrop; }
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Drop Target, Sets a specify value to current class CDragData
	// Parameters:
	//		hItem---hItem, Specifies a HTREEITEM hItem object.
		void			SetDropTarget(HTREEITEM hItem) { m_hLastDrop = hItem; }
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Drop Hint, Returns the specified value.
	//		Returns a int type value.
		int				GetDropHint() const { return m_nDropHint; }
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Drop Hint, Sets a specify value to current class CDragData
	// Parameters:
	//		hint---Specifies A integer value.
		void			SetDropHint(int hint) { m_nDropHint = hint; }
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Right Dragging, Determines if the given value is correct or exist.
	//		Returns A Boolean value.
		bool			IsRightDragging() const { return m_bRightDrag; }

	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Leave, None Description.

		void			DragLeave() {
							if(m_pDragImg)
								m_pDragImg->DragLeave(&m_Owner);
						}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Drag Enter, None Description.
	// Parameters:
	//		pt---Specifies A CPoint type value.
		void			DragEnter(CPoint & pt) {
							if(m_pDragImg)
								m_pDragImg->DragEnter(&m_Owner, pt);
						}

	
	//-----------------------------------------------------------------------
	// Summary:
	// Check Expand, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A Boolean value.  
	// Parameters:
	//		hDrop---hDrop, Specifies a HTREEITEM hDrop object.
		virtual bool	CheckExpand(HTREEITEM hDrop) {
							if(hDrop == m_hLastDrop) {
								if(++m_usNoMove >= 15) {
									// mouse position unchanged for at least 15 circles.
									// If we're standing on a collapsed node - expand it now
									m_usNoMove = 0;
									return true;
								}
							} else {
								m_usNoMove = 0;	// reset counter if mouse really moved...
								m_hLastDrop = hDrop;
							}
							return false;
						}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTREECTRL_H__508278DE_BE33_4505_80FE_51C64B2B3EBB__INCLUDED_)
