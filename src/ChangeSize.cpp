// ChangeSize.cpp : implementation file
//

#include "stdafx.h"
#include "Grid.h"
#include "ChangeSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeSize dialog


CChangeSize::CChangeSize(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeSize)
	m_Height = 0;
	m_Width = 0;
	//}}AFX_DATA_INIT
}


void CChangeSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeSize)
	DDX_Text(pDX, IDC_EDITBOX_HEIGHT, m_Height);
	DDV_MinMaxInt(pDX, m_Height, 1, 100);
	DDX_Text(pDX, IDC_EDITBOX_WIDTH, m_Width);
	DDV_MinMaxInt(pDX, m_Width, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeSize, CDialog)
	//{{AFX_MSG_MAP(CChangeSize)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeSize message handlers
