#if !defined(AFX_CHANGESIZE_H__7632CAEC_A77B_4627_94D0_2D95C5FAC682__INCLUDED_)
#define AFX_CHANGESIZE_H__7632CAEC_A77B_4627_94D0_2D95C5FAC682__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeSize dialog

class CChangeSize : public CDialog
{
// Construction
public:
	CChangeSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeSize)
	enum { IDD = IDD_CHANGESIZE };
	int		m_Height;
	int		m_Width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeSize)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGESIZE_H__7632CAEC_A77B_4627_94D0_2D95C5FAC682__INCLUDED_)
