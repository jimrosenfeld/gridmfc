// GridView.h : interface of the CGridView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDVIEW_H__E83E9917_A09B_490A_9536_81B59A3A4863__INCLUDED_)
#define AFX_GRIDVIEW_H__E83E9917_A09B_490A_9536_81B59A3A4863__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGridView : public CView
{
protected: // create from serialization only
	CGridView();
	DECLARE_DYNCREATE(CGridView)

// Attributes
public:
	CGridDoc* GetDocument();

	BOOL m_GridDisplay;
	BOOL m_WrapEnabled;
	BOOL m_TimerRunning;
	int  m_Timer;
	COLORREF m_CustomColor;

	// changed from enum to UINT - using resource ID's for current color
	// so that it's easier to use update UI function
	UINT m_GridColor;
	// may do the same thing with the rulesets - will wait to see how they
	// are used
	UINT m_CurrentRuleSet;
	

// Operations
public:
	void ClearGrid(bool **theArray);
	void LifeStep();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGridView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnActionsClear();
	afx_msg void OnActionsGrid();
	afx_msg void OnUpdateActionsGrid(CCmdUI* pCmdUI);
	afx_msg void OnActionsWrap();
	afx_msg void OnUpdateActionsWrap(CCmdUI* pCmdUI);
	afx_msg void OnActionsRandomize();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnActionsRunning();
	afx_msg void OnUpdateActionsRunning(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnActionsRulesetRule1();
	afx_msg void OnUpdateActionsRulesetRule1(CCmdUI* pCmdUI);
	afx_msg void OnActionsRulesetRule2();
	afx_msg void OnUpdateActionsRulesetRule2(CCmdUI* pCmdUI);
	afx_msg void OnActionsRulesetRule3();
	afx_msg void OnUpdateActionsRulesetRule3(CCmdUI* pCmdUI);
	afx_msg void OnChangeColor();
	afx_msg void OnUpdateColor(CCmdUI* pCmdUI);
	afx_msg void OnActionsChangesize();
	afx_msg void OnActionsColorCustom();
	//}}AFX_MSG
	afx_msg void OnUpdateStatusBarRunning(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatusBarCells(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GridView.cpp
inline CGridDoc* CGridView::GetDocument()
   { return (CGridDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDVIEW_H__E83E9917_A09B_490A_9536_81B59A3A4863__INCLUDED_)
