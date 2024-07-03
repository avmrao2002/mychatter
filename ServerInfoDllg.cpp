// ServerInfoDllg.cpp : implementation file
//

#include "stdafx.h"
#include "chat.h"
#include "ServerInfoDllg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerInfoDllg dialog


CServerInfoDllg::CServerInfoDllg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerInfoDllg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerInfoDllg)
	m_port_number = 55555;
	//}}AFX_DATA_INIT
}


void CServerInfoDllg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerInfoDllg)
	DDX_Text(pDX, IDC_EDIT_PORT_NUMBER, m_port_number);
	DDV_MinMaxInt(pDX, m_port_number, 1, 65525);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerInfoDllg, CDialog)
	//{{AFX_MSG_MAP(CServerInfoDllg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerInfoDllg message handlers
