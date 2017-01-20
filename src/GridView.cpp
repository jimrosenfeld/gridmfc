// GridView.cpp : implementation of the CGridView class
//

#include "stdafx.h"
#include "Grid.h"

#include "GridDoc.h"
#include "GridView.h"
#include "ChangeSize.h"

#include <cstdlib>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridView

IMPLEMENT_DYNCREATE(CGridView, CView)

BEGIN_MESSAGE_MAP(CGridView, CView)
	//{{AFX_MSG_MAP(CGridView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ACTIONS_CLEAR, OnActionsClear)
	ON_COMMAND(ID_ACTIONS_GRID, OnActionsGrid)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_GRID, OnUpdateActionsGrid)
	ON_COMMAND(ID_ACTIONS_WRAP, OnActionsWrap)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_WRAP, OnUpdateActionsWrap)
	ON_COMMAND(ID_ACTIONS_RANDOMIZE, OnActionsRandomize)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ACTIONS_RUNNING, OnActionsRunning)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_RUNNING, OnUpdateActionsRunning)
	ON_WM_TIMER()
	ON_COMMAND(ID_ACTIONS_RULESET_RULE1, OnActionsRulesetRule1)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_RULESET_RULE1, OnUpdateActionsRulesetRule1)
	ON_COMMAND(ID_ACTIONS_RULESET_RULE2, OnActionsRulesetRule2)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_RULESET_RULE2, OnUpdateActionsRulesetRule2)
	ON_COMMAND(ID_ACTIONS_RULESET_RULE3, OnActionsRulesetRule3)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_RULESET_RULE3, OnUpdateActionsRulesetRule3)
	ON_COMMAND(ID_ACTIONS_COLOR_BLACK, OnChangeColor)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_COLOR_BLACK, OnUpdateColor)
	ON_COMMAND(ID_ACTIONS_CHANGESIZE, OnActionsChangesize)
	ON_COMMAND(ID_ACTIONS_COLOR_BLUE, OnChangeColor)
	ON_COMMAND(ID_ACTIONS_COLOR_GREEN, OnChangeColor)
	ON_COMMAND(ID_ACTIONS_COLOR_RED, OnChangeColor)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_COLOR_BLUE, OnUpdateColor)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_COLOR_GREEN, OnUpdateColor)
	ON_UPDATE_COMMAND_UI(ID_ACTIONS_COLOR_RED, OnUpdateColor)
	ON_COMMAND(ID_ACTIONS_COLOR_CUSTOM, OnActionsColorCustom)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_TIMER_RUNNING, OnUpdateStatusBarRunning)
	ON_UPDATE_COMMAND_UI(ID_OCCUPIED_CELLS, OnUpdateStatusBarCells)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridView construction/destruction

CGridView::CGridView()
{
	// seed random number generator
	srand((unsigned) time(NULL));

	// init variables
	m_GridDisplay = TRUE;					// display the grid
	m_WrapEnabled = FALSE;					// ...?
	m_TimerRunning = FALSE;					// timer is not running
	m_Timer = 0;							// no timer defined
	m_GridColor = ID_ACTIONS_COLOR_BLACK;	// grid lines are black
	m_CurrentRuleSet = ID_ACTIONS_RULESET_RULE1;			// ...?
	m_CustomColor = RGB(0, 0, 0);

}

CGridView::~CGridView()
{
}

BOOL CGridView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGridView drawing

void CGridView::OnDraw(CDC* pDC)
{
	CGridDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int i;
	
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap memBitmap;

	// create compatible bitmap and DC and paint background
	memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&memBitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	CBrush* oldBrush;
	CPen*   oldPen;
	CBrush  blackBrush(RGB(256, 256, 256));
	CPen	blackPen(PS_SOLID, 1, RGB(256, 256, 256));
	CPen	gridPen;

	// determine grid color and select appropriate pen
	switch (m_GridColor) {
	case ID_ACTIONS_COLOR_BLACK:
		gridPen.CreatePen(PS_SOLID, 1, RGB(256, 256, 256));
		break;
	case ID_ACTIONS_COLOR_RED:
		gridPen.CreatePen(PS_SOLID, 1, RGB(128, 0, 0));
		break;
	case ID_ACTIONS_COLOR_GREEN:
		gridPen.CreatePen(PS_SOLID, 1, RGB(0, 128, 0));
		break;
	case ID_ACTIONS_COLOR_BLUE:
		gridPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 128));
		break;
	case ID_ACTIONS_COLOR_CUSTOM:
		gridPen.CreatePen(PS_SOLID, 1, m_CustomColor);
		break;
	}

	// save existing object pointers
	oldBrush = memDC.SelectObject(&blackBrush);
	oldPen = memDC.SelectObject(&gridPen);

	// set line spacing according to client area
	pDoc->spaceHorizontalLines = rect.bottom / pDoc->gridDimensions.y;
	pDoc->spaceVerticalLines = rect.right / pDoc->gridDimensions.x;
	int dcPosition = 0;

	// if the lines are supposed to be drawn, draw them
	if (m_GridDisplay) {
		for (i = 0; i < pDoc->gridDimensions.y; i++) {
			dcPosition += pDoc->spaceHorizontalLines;
			memDC.MoveTo(0, dcPosition);
			memDC.LineTo(rect.right, dcPosition);
		}

		dcPosition = 0;
		for (i = 0; i < pDoc->gridDimensions.x; i++) {
			dcPosition += pDoc->spaceVerticalLines;
			memDC.MoveTo(dcPosition, 0);
			memDC.LineTo(dcPosition, rect.bottom);
		}
	}

	// select a black pen for drawing the black ellipses
	memDC.SelectObject(&blackPen);
	
	// parse through the array and draw ellipses accordingly
	for (i = 0; i < pDoc->gridDimensions.x; i++) {
		for (int j = 0; j < pDoc->gridDimensions.y; j++) {
			if (pDoc->gridArray[i][j] == true) {
				memDC.Ellipse(pDoc->spaceVerticalLines * i,
							 pDoc->spaceHorizontalLines * j,
							 pDoc->spaceVerticalLines * (i + 1),
							 pDoc->spaceHorizontalLines * (j + 1));
			}
		}
	}
	
	// restore original object references
	memDC.SelectObject(oldBrush);
	memDC.SelectObject(oldPen);

	// copy memory DC to screen
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

}

/////////////////////////////////////////////////////////////////////////////
// CGridView diagnostics

#ifdef _DEBUG
void CGridView::AssertValid() const
{
	CView::AssertValid();
}

void CGridView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGridDoc* CGridView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGridDoc)));
	return (CGridDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridView message handlers

void CGridView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CGridDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// get the mouse!
	SetCapture();

	// determine where we are in the array
	int j = point.x / pDoc->spaceVerticalLines;
	int k = point.y / pDoc->spaceHorizontalLines;

	// set member variables to allow us to keep track of which square we're in
	// so that we don't set and unset it every time the mouse moves
	pDoc->currentSquare.x = j;
	pDoc->currentSquare.y = k;

	// if-else block prevents access violation if area outside grid is clicked and
	// array subscripts are out of bounds - learned the hard way
	
	// '!' the value in the array position we're in and update occupied count
	if (j < pDoc->gridDimensions.x && k < pDoc->gridDimensions.y && j >= 0 && k >= 0) {
		// TRACE("before: gridArray[%d][%d] = %d\tgridOccupied: %d\n", j, k, pDoc->gridArray[j][k],
		//	pDoc->gridOccupied);
		TRACE("click: %d %d  array: %d %d\n", point.x, point.y, j, k);
		
		pDoc->gridArray[j][k] = !(pDoc->gridArray[j][k]);
		
		if (pDoc->gridArray[j][k])
			pDoc->gridOccupied++;
		else
			pDoc->gridOccupied--;

		TRACE("after: gridArray[%d][%d] = %d\t gridOccupied: %d\n", j, k, pDoc->gridArray[j][k],
			pDoc->gridOccupied);
	}
	else {
		TRACE("Clicked outside grid area!\n");
	}


	// force repaint to reflect change
	Invalidate(FALSE);

	CView::OnLButtonDown(nFlags, point);
}

void CGridView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// release the mouse!
	::ReleaseCapture();
	
	CView::OnLButtonUp(nFlags, point);
}



void CGridView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// call function to clear grid
	// originally this function was in here, but it's probably better to have
	// message handlers and menu handlers calling user functions than vice
	// versa
	CGridDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ClearGrid(pDoc->gridArray);

	CView::OnLButtonDblClk(nFlags, point);
}

void CGridView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// if the left button is down...
	if (GetCapture() == this) {
		CGridDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		// figure out where we're at
		int j = point.x / pDoc->spaceVerticalLines;
		int k = point.y / pDoc->spaceHorizontalLines;
		// TRACE("j = %d, k = %d \t cs.x = %d, cs.y = %d\n", j, k, pDoc->currentSquare.x,
		//	     pDoc->currentSquare.y);
		
		// if you && these conditions, it draws diagonal lines...very annoying
		if (pDoc->currentSquare.x != j || pDoc->currentSquare.y != k) {
			pDoc->currentSquare.x = j;
			pDoc->currentSquare.y = k;
			// probably not the best idea to call the message handler...oh well...
			// ...it works.
			OnLButtonDown(nFlags, point);
		}
	}

	CView::OnMouseMove(nFlags, point);
}

void CGridView::ClearGrid(bool **theArray)
{
	CGridDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for (int i = 0; i < pDoc->gridDimensions.x; i++) {
		for (int j = 0; j < pDoc->gridDimensions.y; j++) {
			theArray[i][j] = false;
		}
	}

	pDoc->gridOccupied = 0;

	if (m_Timer == 0)
		TRACE("Grid cleared.\n");

	Invalidate(FALSE);
	UpdateWindow();
}

void CGridView::OnActionsClear() 
{
	CGridDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ClearGrid(pDoc->gridArray);
}

void CGridView::OnActionsGrid() 
{
	CGridApp *myApp;
	CFrameWnd *myFrame;
	CMenu *myMenu, *subMenu;
	
	
	m_GridDisplay = !m_GridDisplay;

	myApp = (CGridApp*) AfxGetApp();
	myFrame = (CFrameWnd*) myApp->m_pMainWnd;
	myMenu = myFrame->GetMenu();

	subMenu = myMenu->GetSubMenu(2);

	if (m_GridDisplay) {
		subMenu->EnableMenuItem(4, MF_BYPOSITION | MF_ENABLED);
	} 
	else {
		subMenu->EnableMenuItem(4, MF_BYPOSITION | MF_GRAYED);
	}

	Invalidate(FALSE);
	
}

void CGridView::OnUpdateActionsGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_GridDisplay);
}

void CGridView::OnActionsWrap() 
{
	m_WrapEnabled = !m_WrapEnabled;
	
}

void CGridView::OnUpdateActionsWrap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_WrapEnabled);

}

void CGridView::OnActionsRandomize() 
{
	CGridDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->gridOccupied = 0;

	for (int i = 0; i < pDoc->gridDimensions.x; i++) {
		for (int j = 0; j < pDoc->gridDimensions.y; j++) {
			if (rand() % 2) {
				pDoc->gridArray[i][j] = true;
				pDoc->gridOccupied++;
			}
			else {
				pDoc->gridArray[i][j] = false;
			}
		}
	}

	TRACE("Randomized: gridOccupied = %d - %.2f%%\n", pDoc->gridOccupied,
			(((float)pDoc->gridOccupied / (float)(pDoc->gridDimensions.x * pDoc->gridDimensions.y)) * 100));

	Invalidate(FALSE);
}


void CGridView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CGridApp *myApp;
	CFrameWnd *myFrame;
	CMenu *myMenu, *subMenu;

	myApp = (CGridApp*) AfxGetApp();
	myFrame = (CFrameWnd*) myApp->m_pMainWnd;
	myMenu = myFrame->GetMenu();
	
	subMenu = myMenu->GetSubMenu(2);

	if (m_GridDisplay) {
		subMenu->EnableMenuItem(4, MF_BYPOSITION | MF_ENABLED);
		subMenu->CheckMenuItem(ID_ACTIONS_GRID, MF_CHECKED);
	} 
	else {
		subMenu->EnableMenuItem(4, MF_BYPOSITION | MF_GRAYED);
		subMenu->CheckMenuItem(ID_ACTIONS_GRID, MF_UNCHECKED);
	}

	if (m_TimerRunning)
		subMenu->CheckMenuItem(ID_ACTIONS_RUNNING, MF_CHECKED);
	else
		subMenu->CheckMenuItem(ID_ACTIONS_RUNNING, MF_UNCHECKED);

	if (m_WrapEnabled)
		subMenu->CheckMenuItem(ID_ACTIONS_WRAP, MF_CHECKED);
	else
		subMenu->CheckMenuItem(ID_ACTIONS_WRAP, MF_UNCHECKED);

	subMenu->CheckMenuItem(ID_ACTIONS_COLOR_BLACK, MF_UNCHECKED);
	subMenu->CheckMenuItem(ID_ACTIONS_COLOR_RED, MF_UNCHECKED);
	subMenu->CheckMenuItem(ID_ACTIONS_COLOR_GREEN, MF_UNCHECKED);
	subMenu->CheckMenuItem(ID_ACTIONS_COLOR_BLUE, MF_UNCHECKED);

	switch (m_GridColor) {
	case ID_ACTIONS_COLOR_BLACK:
		subMenu->CheckMenuItem(ID_ACTIONS_COLOR_BLACK, MF_CHECKED);
		break;
	case ID_ACTIONS_COLOR_RED:
		subMenu->CheckMenuItem(ID_ACTIONS_COLOR_RED, MF_CHECKED);
		break;
	case ID_ACTIONS_COLOR_GREEN:
		subMenu->CheckMenuItem(ID_ACTIONS_COLOR_GREEN, MF_CHECKED);
		break;
	case ID_ACTIONS_COLOR_BLUE:
		subMenu->CheckMenuItem(ID_ACTIONS_COLOR_BLUE, MF_CHECKED);
		break;
	}

	subMenu->CheckMenuItem(ID_ACTIONS_RULESET_RULE1, MF_UNCHECKED);
	subMenu->CheckMenuItem(ID_ACTIONS_RULESET_RULE2, MF_UNCHECKED);
	subMenu->CheckMenuItem(ID_ACTIONS_RULESET_RULE3, MF_UNCHECKED);

	switch (m_CurrentRuleSet) {
	case ID_ACTIONS_RULESET_RULE1:
		subMenu->CheckMenuItem(ID_ACTIONS_RULESET_RULE1, MF_CHECKED);
		break;
	case ID_ACTIONS_RULESET_RULE2:
		subMenu->CheckMenuItem(ID_ACTIONS_RULESET_RULE2, MF_CHECKED);
		break;
	case ID_ACTIONS_RULESET_RULE3:
		subMenu->CheckMenuItem(ID_ACTIONS_RULESET_RULE3, MF_CHECKED);
		break;
	}

	subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);

}

void CGridView::OnActionsRunning() 
{
	if (!m_Timer) {
		m_Timer = SetTimer(1, 100, NULL);
	}
	else {
		KillTimer(m_Timer);
		m_Timer = 0;
	}
	m_TimerRunning = !m_TimerRunning;
	
}

void CGridView::OnUpdateActionsRunning(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TimerRunning);
	
}

void CGridView::OnTimer(UINT nIDEvent) 
{
	CGridDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	/* static int count = 0;
	count++;

	TRACE("%.2f%% occupied, count: %d\n",
		((float)pDoc->gridOccupied / (float)(pDoc->gridDimensions.x * pDoc->gridDimensions.y)) * 100,
		count);
	
	if (m_CurrentRuleSet == RULESET3)
		OnActionsRandomize();
	*/

	LifeStep();
	Invalidate(FALSE);

	CView::OnTimer(nIDEvent);
}

void CGridView::OnActionsRulesetRule1() 
{
	m_CurrentRuleSet = ID_ACTIONS_RULESET_RULE1;
	
}

void CGridView::OnUpdateActionsRulesetRule1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_CurrentRuleSet == ID_ACTIONS_RULESET_RULE1);
	
}

void CGridView::OnActionsRulesetRule2() 
{
	m_CurrentRuleSet = ID_ACTIONS_RULESET_RULE2;
	
}

void CGridView::OnUpdateActionsRulesetRule2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_CurrentRuleSet == ID_ACTIONS_RULESET_RULE2);
	
}

void CGridView::OnActionsRulesetRule3() 
{
	m_CurrentRuleSet = ID_ACTIONS_RULESET_RULE3;
	
}

void CGridView::OnUpdateActionsRulesetRule3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_CurrentRuleSet == ID_ACTIONS_RULESET_RULE3);
	
}

void CGridView::OnChangeColor() 
{
	static const MSG *msg;
	msg = GetCurrentMessage();

	m_GridColor = msg->wParam;

	Invalidate(FALSE);
}

void CGridView::OnUpdateColor(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_GridColor == pCmdUI->m_nID);
	
}

void CGridView::OnUpdateStatusBarRunning(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_TimerRunning);
}

void CGridView::OnUpdateStatusBarCells(CCmdUI *pCmdUI)
{
	CGridDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CString string;
	string.Format("Occupied Cells: %d", pDoc->gridOccupied);
	
	pCmdUI->SetText(string);
}

void CGridView::LifeStep()
{
	CGridDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	bool **inputGrid, **outputGrid;
	int neighbors, adjx, adjy;

	if (pDoc->gridArray == pDoc->gridArrayA) {
		inputGrid = pDoc->gridArrayA;
		outputGrid = pDoc->gridArrayB;
	}
	else {
		inputGrid = pDoc->gridArrayB;
		outputGrid = pDoc->gridArrayA;
	}

	ClearGrid(outputGrid);

	for (int i = 0; i < pDoc->gridDimensions.x; i++) {
		for (int j = 0; j < pDoc->gridDimensions.y; j++) {
			neighbors = 0;
			for (int k = -1; k <= 1; k++) {
				for (int m = -1; m <= 1; m++) {
					switch (m_CurrentRuleSet) {
					case ID_ACTIONS_RULESET_RULE1:
					case ID_ACTIONS_RULESET_RULE3:
						if (m_WrapEnabled) {
							adjx = (i+k+pDoc->gridDimensions.x) % pDoc->gridDimensions.x;
							adjy = (j+m+pDoc->gridDimensions.y) % pDoc->gridDimensions.y;
							if (inputGrid[adjx][adjy] && !(k == 0 && m == 0))
								neighbors++;
						}
						else {
							if (i + k >= 0 && j + m >= 0
								&& i + k < pDoc->gridDimensions.x
								&& j + m < pDoc->gridDimensions.y
								&& !(k == 0 && m == 0)) {
								if (inputGrid[i+k][j+m])
									neighbors++;
							}
						}
						break;
					case ID_ACTIONS_RULESET_RULE2:
							if (m_WrapEnabled) {
							adjx = (i+k+pDoc->gridDimensions.x) % pDoc->gridDimensions.x;
							adjy = (j+m+pDoc->gridDimensions.y) % pDoc->gridDimensions.y;
							if (inputGrid[adjx][adjy])
								neighbors++;
						}
						else {
							if (i + k >= 0 && j + m >= 0
								&& i + k < pDoc->gridDimensions.x
								&& j + m < pDoc->gridDimensions.y) {
								if (inputGrid[i+k][j+m])
									neighbors++;
							}
						}
						break;
					}
				}
			}


			if (neighbors > 0 && inputGrid[i][j])
				TRACE("gridArray[%d][%d]: neighbors = %d\n", i, j, neighbors);

			if (inputGrid[i][j] && (neighbors == 2 || neighbors == 3)) {
				outputGrid[i][j] = true;
				pDoc->gridOccupied++;
			}
			if (!inputGrid[i][j] && neighbors == 3) {
				outputGrid[i][j] = true;
				pDoc->gridOccupied++;
			}
			if (m_CurrentRuleSet == ID_ACTIONS_RULESET_RULE3) {
				if (!inputGrid[i][j] && neighbors == 0 && (rand() % 100 == 0)) {
					outputGrid[i][j] = true;
					pDoc->gridOccupied++;
				}

				if (inputGrid[i][j] && outputGrid[i][j] && (rand() % 100 == 0)) {
					outputGrid[i][j] = false;
					pDoc->gridOccupied--;
				}
			}
		}
	}

	pDoc->gridArray = outputGrid;
}

void CGridView::OnActionsChangesize() 
{
	CGridDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CChangeSize theDialog;
	theDialog.m_Height = pDoc->gridDimensions.x;
	theDialog.m_Width = pDoc->gridDimensions.y;

	if (theDialog.DoModal() == IDOK) {
		pDoc->CreateGrid(false, theDialog.m_Height, theDialog.m_Width);
		Invalidate(FALSE);
	}
}

void CGridView::OnActionsColorCustom() 
{
	CColorDialog theDialog;
	
	if (theDialog.DoModal() == IDOK) {
		m_CustomColor = theDialog.GetColor();
		m_GridColor = ID_ACTIONS_COLOR_CUSTOM;

		Invalidate(FALSE);
	}
}
