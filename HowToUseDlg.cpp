// HowToUseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chat.h"
#include "HowToUseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHowToUseDlg dialog


CHowToUseDlg::CHowToUseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHowToUseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHowToUseDlg)
	m_how_to_use = _T("");
	//}}AFX_DATA_INIT
}


void CHowToUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHowToUseDlg)
	DDX_Text(pDX, IDC_EDIT_HOW_TO_USE, m_how_to_use);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHowToUseDlg, CDialog)
	//{{AFX_MSG_MAP(CHowToUseDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHowToUseDlg message handlers

BOOL CHowToUseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_how_to_use = 
		"This is a chat software. Using this software, users can do chat with others who are in TCP/IP network and can chat with different users at the same time."
		"This software can be used as server or client.  When the Chat software is started,  it asks for server port number. Using this port number users can connect to do chat. This port number will be shown in status in the chat dialog. To chat with the your friend, enter the hostname in edit box, and click on Add button. The host name will be inserted in the list box. On clicking on the hostname, it will ask for server port number of the host name,"
		"then accept message will be displayed on the other user window,  if the user accepts, then connection will be established. It also displays a talk dialog window. "
		"The talk dialog consists various features like send instant message, write and send, send and close, hide, save, open etc.."
		"\r\n\r\nAny queries or comments send mail to raoavm@yahoo.com "
		"\r\n\r\nNo warranty or guarantee is available with this software"
		"\r\n\r\nThis software is free to use or distribute";

	UpdateData(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
