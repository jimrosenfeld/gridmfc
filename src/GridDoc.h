// GridDoc.h : interface of the CGridDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDDOC_H__98B7F917_3D60_4A2F_B23F_71D4E59DE5C8__INCLUDED_)
#define AFX_GRIDDOC_H__98B7F917_3D60_4A2F_B23F_71D4E59DE5C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGridDoc : public CDocument
{
protected: // create from serialization only
	CGridDoc();
	DECLARE_DYNCREATE(CGridDoc)

// Attributes
public:
	// dimensions of the grid
	struct GRID
	{
		int x;
		int y;
	} gridDimensions, currentSquare;

	// two dimensional dynamic array to hold grid
	bool **gridArray;
	bool **gridArrayA;
	bool **gridArrayB;
	// occupied cell count
	unsigned int gridOccupied;
	// space between horizontal and vertical lines, used to draw lines
	// and determine click position in grid array
	int spaceHorizontalLines;
	int spaceVerticalLines;

// Operations
public:
	void CreateGrid(bool newGrid = true, int newDimensionX = 30, int newDimensionY = 20);
	void DestroyGrid();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGridDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDDOC_H__98B7F917_3D60_4A2F_B23F_71D4E59DE5C8__INCLUDED_)
