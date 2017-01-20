// GridDoc.cpp : implementation of the CGridDoc class
//

#include "stdafx.h"
#include "Grid.h"

#include "GridDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridDoc

IMPLEMENT_DYNCREATE(CGridDoc, CDocument)

BEGIN_MESSAGE_MAP(CGridDoc, CDocument)
	//{{AFX_MSG_MAP(CGridDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridDoc construction/destruction

CGridDoc::CGridDoc()
{
	// initialize occupied cell count to 0
	gridOccupied = 0;

	CreateGrid();
}

CGridDoc::~CGridDoc()
{
	DestroyGrid();
}

BOOL CGridDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGridDoc serialization

void CGridDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGridDoc diagnostics

#ifdef _DEBUG
void CGridDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGridDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridDoc commands

void CGridDoc::CreateGrid(bool newGrid, int newDimensionX, int newDimensionY)
{
	if (!newGrid)
		DestroyGrid();

	gridDimensions.x = newDimensionX;
	gridDimensions.y = newDimensionY;

	// create two-dimemsional dynamic array
	// using gridDimensions struct
	gridArrayA = new bool* [gridDimensions.x];
	for (int i = 0; i < gridDimensions.x; i++) {
		gridArrayA[i] = new bool[gridDimensions.y];
		for (int j = 0; j < gridDimensions.y; j++) {
			gridArrayA[i][j] = false;
		}
	}

	gridArrayB = new bool* [gridDimensions.x];
	for (int i = 0; i < gridDimensions.x; i++) {
		gridArrayB[i] = new bool[gridDimensions.y];
		for (int j = 0; j < gridDimensions.y; j++) {
			gridArrayB[i][j] = false;
		}
	}

	gridArray = gridArrayA;

	currentSquare.x = 0;
	currentSquare.y = 0;
}

void CGridDoc::DestroyGrid()
{
	// delete gridArray from heap
	for (int i = 0; i < gridDimensions.x; i++) {
		delete [] gridArrayA[i];
	}
	delete [] gridArrayA;

	for (int i = 0; i < gridDimensions.x; i++) {
		delete [] gridArrayB[i];
	}
	delete [] gridArrayB;
}
