// chatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsock.h"
#include "chat.h"
#include "ConnectDlg.h"
#include "ClientSocket.h"
#include "ServerSocket.h"
#include "chatDlg.h"
#include "talkDlg.h"
#include "ServerInfoDllg.h"
#include "HowToUseDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CServerSocket serversock;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatDlg)
	m_Static_Status = _T("");
	m_Edit_Friend = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); 
	for(int i =0; i< MAXCLIENTS; i++)
	{
		m_ClientSock[i] = NULL;
		 
	}
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatDlg)
	DDX_Control(pDX, IDC_LIST_FRIENDS, m_list_friends);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_Static_Status);
	DDX_Text(pDX, IDC_EDIT_FRIEND, m_Edit_Friend);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	//{{AFX_MSG_MAP(CChatDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_EDIT_CONNECT, OnEditConnect)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONNECT, OnUpdateEditConnect)
	ON_COMMAND(ID_EDIT_DISCONNECT, OnEditDisconnect)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DISCONNECT, OnUpdateEditDisconnect)
	ON_EN_CHANGE(IDC_SEND, OnChangeSend)
	ON_EN_UPDATE(IDC_SEND, OnUpdateSend)
	ON_WM_VSCROLL()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_HELP_ABOUTCHAT, OnHelpAboutchat)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_COMMAND(ID_FILE_CHANGEMYSTATUS_AWAY, OnFileChangemystatusAway)
	ON_COMMAND(ID_FILE_CHANGEMYSTATUS_BUSY, OnFileChangemystatusBusy)
	ON_COMMAND(ID_FILE_CHANGEMYSTATUS_IDLE, OnFileChangemystatusIdle)
	ON_COMMAND(ID_FILE_CHANGEMYSTATUS_OFFLINE, OnFileChangemystatusOffline)
	ON_COMMAND(ID_FILE_CHANGEMYSTATUS_ONLINE, OnFileChangemystatusOnline)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_HIDE, OnViewHide)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TOOLS_SERVER, OnToolsServer)
	ON_LBN_SELCHANGE(IDC_LIST_FRIENDS, OnSelchangeListFriends)
	ON_LBN_DBLCLK(IDC_LIST_FRIENDS, OnDblclkListFriends)
	ON_COMMAND(ID_HELP_HOWTOUSE, OnHelpHowtouse)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDOK,OnOK)
	ON_MESSAGE(MY_MESSAGE_SHELLNOTIFY, OnShellNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg message handlers
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

BOOL CChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CMenu menu;
	menu.LoadMenu (IDR_CHAT);
	SetMenu(&menu);
	menu.Detach();	
/*	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_CHAT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.EnableWindow(TRUE);
	m_wndStatusBar.EnableWindow(TRUE);
 	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);*/
	/*CTreeCtrl *tctrl = (CTreeCtrl*)GetDlgItem(IDC_TREE_FRIENDS);
	TV_INSERTSTRUCT tvinsert;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 20;
	tvinsert.item.iSelectedImage = 1;
	tvinsert.item.lParam = 0;
	//top level
	tvinsert.item.pszText = "Friends";
	tvinsert.item.iImage = 2;
 
	HTREEITEM hFriends = tctrl->InsertItem(&tvinsert);*/
	NOTIFYICONDATA nicondata;
	char data[64] = "Chat by AVM RAO";
	 
	nicondata.hWnd = this->GetSafeHwnd();;
	nicondata.uID = 10;
	nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
	nicondata.cbSize = sizeof(nicondata);
	nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
	nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strcpy(nicondata.szTip,data);
	Shell_NotifyIcon(NIM_ADD,&nicondata);	 
	serversock.CreateServer();
	m_Static_Status.Format("Listening on port %d",m_ServerInfoDlg.m_port_number);
	UpdateData(FALSE);
	//second level
 	 
	 
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChatDlg::OnEditConnect() 
{
	// TODO: Add your command handler code here
 
} 
 

void CChatDlg::OnUpdateEditConnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CChatDlg::OnEditDisconnect() 
{
	// TODO: Add your command handler code here	  
}

void CChatDlg::OnUpdateEditDisconnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChatDlg::OnChangeSend() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here 
}

void CChatDlg::OnOK()
{
	OnButtonAdd(); 
}
 
 

void CChatDlg::OnUpdateSend() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	 
}
 

void CChatDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CChatDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
 	/*	if(m_ClientSocket != NULL)
		{
		 	m_ClientSocket->ShutDown(2);
			m_ClientSocket->Close();
			delete m_ClientSocket;
			m_ClientSocket = NULL;
		}*/

	EndDialog(TRUE);
}


void CChatDlg::OnHelpAboutchat() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CChatDlg::OnMyAdd()
{
	OnButtonAdd();
}

void CChatDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CListBox *tctrl = (CListBox*)GetDlgItem(IDC_LIST_FRIENDS);

	/*TV_INSERTSTRUCT tvinsert;	 
	tvinsert.hParent = tctrl->GetRootItem();	 
	if(tctrl->ItemHasChildren(tvinsert.hParent) == TRUE)
	{		 
		HTREEITEM hItem = NULL;
		hItem = tctrl->GetChildItem(tvinsert.hParent);
		while(hItem != NULL)
		{	 
			if(m_Edit_Friend == tctrl->GetItemText(hItem))
			{
				CString str = m_Edit_Friend + " Already exists";
				AfxMessageBox(str);
				return;
			}
			hItem = tctrl->GetNextItem(hItem,TVGN_NEXT);
		}
	} 
	 
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 20;
	tvinsert.item.iSelectedImage = 1;
	tvinsert.item.lParam = 0;

	tvinsert.hParent = tctrl->GetRootItem();	 
 
	char *data = m_Edit_Friend.GetBuffer(0); 
 
	tvinsert.item.pszText =   data;
	//m_Edit_Friend.ReleaseBuffer(0);
 	tvinsert.item.iImage = 3;
	tctrl->InsertItem(&tvinsert);
	Invalidate();
	UpdateData(FALSE);
	*/

    if(tctrl->FindStringExact(-1,m_Edit_Friend) == LB_ERR)
	{
		tctrl->AddString(m_Edit_Friend); 
	}
	else
	{
		CString str;
		str.Format("%s alread exists",m_Edit_Friend);
		AfxMessageBox(str);
	}
 
}

void CChatDlg::OnButtonDelete() 
{
 	UpdateData(TRUE);
	/*CTreeCtrl *tctrl = (CTreeCtrl*)GetDlgItem(IDC_TREE_FRIENDS);
	HTREEITEM hSelected = tctrl->GetSelectedItem();
	 
	if(hSelected != NULL)
	{
		if(hSelected != tctrl->GetRootItem())
		{
			tctrl->DeleteItem(hSelected);
		}
	}
	UpdateData(FALSE);*/

	int index;
	if((index =m_list_friends.GetCurSel())>=0)
	{		 
		CString name;
		m_list_friends.GetText(m_list_friends.GetCurSel(),name);
		for(int i =0; i< MAXCLIENTS; i++)
		{
			if(m_ClientSock[i] != NULL && ((CClientSocket*)m_ClientSock[i])->GetStatus() != 1)
			{					 
				CTalkDlg* dlg =(CTalkDlg*)((CClientSocket*)m_ClientSock[i])->GetDlgPtr();					 
				if(dlg != NULL)
				{
					if(dlg->GetClientName() == name)
					{						 
						dlg->ShowWindow(SW_HIDE);			 
						m_ClientSock[i]->Close();
						m_ClientSock[i]->ShutDown(2);
						
						break;
					}
				}
			}			
		}		 
	}
	m_list_friends.DeleteString(index);
	m_list_friends.SetCurSel(0);
	UpdateData(FALSE);	     
	 
}

void CChatDlg::OnFileChangemystatusAway() 
{
	// TODO: Add your command handler code here
	CMenu menu;
	menu.LoadMenu(IDR_CHAT);
	CMenu *pContextMenu1 = menu.GetSubMenu(0);
	CMenu *pContextMenu = pContextMenu1->GetSubMenu(0);
	pContextMenu->CheckMenuItem(0,MF_CHECKED | MF_BYPOSITION  );
	m_Static_Status = "Away";
	UpdateData(FALSE);
	serversock.SendStatusToClients(AWAY);
}

void CChatDlg::OnFileChangemystatusBusy() 
{
	// TODO: Add your command handler code here
	 
	m_Static_Status = "Busy";
	UpdateData(FALSE);
	serversock.SendStatusToClients(BUSY);
}

void CChatDlg::OnFileChangemystatusIdle() 
{
	// TODO: Add your command handler code here
	m_Static_Status = "Idle";
	UpdateData(FALSE);
	serversock.SendStatusToClients(IDLE);
}

void CChatDlg::OnFileChangemystatusOffline() 
{
	// TODO: Add your command handler code here
	m_Static_Status = "Offline";
	UpdateData(FALSE);
	serversock.SendStatusToClients(OFFLINE);
}

void CChatDlg::OnFileChangemystatusOnline() 
{
	// TODO: Add your command handler code here
	m_Static_Status = "Online";
	UpdateData(FALSE);
	serversock.SendStatusToClients(ONLINE);
}
  
void CChatDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	NOTIFYICONDATA nicondata;
	char data[64] = "Chat by AVM RAO";
	 
	nicondata.hWnd = this->GetSafeHwnd();;
	nicondata.uID = 10;
	nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
	nicondata.cbSize = sizeof(nicondata);
	nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
	nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strcpy(nicondata.szTip,data);
	Shell_NotifyIcon(NIM_DELETE,&nicondata);	     
	
	CDialog::OnClose();
}

void CChatDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	NOTIFYICONDATA nicondata;
	char data[64] = "Chat by AVM RAO";
	 
	nicondata.hWnd = this->GetSafeHwnd();;
	nicondata.uID = 10;
	nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
	nicondata.cbSize = sizeof(nicondata);
	nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
	nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strcpy(nicondata.szTip,data);
	Shell_NotifyIcon(NIM_DELETE,&nicondata);	     
	// TODO: Add your message handler code here
	
}


/*void CChatDlg::OnSelchangingTreeFriends(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	 
	CTreeCtrl *tctrl = (CTreeCtrl*)GetDlgItem(IDC_TREE_FRIENDS);
	HTREEITEM hSelected = (HTREEITEM)pNMTreeView->itemNew.hItem;	
	 
	if(hSelected == NULL)
	{
		
		AfxMessageBox("seleced is null");
	}
	if(hSelected != tctrl->GetRootItem())
	{
		char strText[20];
		TV_ITEM item;
		item.mask = TVIF_HANDLE | TVIF_TEXT;
		item.hItem = hSelected;
		item.pszText = strText;
		item.cchTextMax = 20;
		tctrl->GetItem(&item);
		CString name = item.pszText;
	 
		if(name.GetLength() < 1)
		{
			CString str;
			str.Format("Enter valid host name",name);
			AfxMessageBox(str);
			return;
		}
		struct hostent *hent = (struct hostent*)gethostbyname(name);
		if(hent == NULL)
		{
			CString str;
			str.Format("%s not found",name);
			AfxMessageBox(str);
		}
		else
		{
			SOCKADDR_IN sock_addr;
			sock_addr.sin_family = AF_INET;
			sock_addr.sin_port = 55555;
//			sock_addr.sin_addr. = inet_addr(hent->h_addr_list[0]);
//sock_addr.sin_zero = sizeof(SOCKADDR);			 

			 
			int i=0;
			int foundFlag = -1;
			for(i =0; i< MAXCLIENTS; i++)
			{
				if(m_ClientSock[i] != NULL && ((CClientSocket*)m_ClientSock[i])->GetStatus() != 1)
				{					 
					CTalkDlg* dlg =(CTalkDlg*)((CClientSocket*)m_ClientSock[i])->GetDlgPtr();					 
					if(dlg != NULL)
					{
						if(dlg->GetClientName() == name)
						{						 
							dlg->ShowWindow(SW_SHOW);			 
							foundFlag = 1;
							break;
						}
					}
				}			
			}		 
			for(i =0; i< MAXCLIENTS; i++)
			{				 
				CTalkDlg* dlg =(CTalkDlg*)((CClientSocket&)serversock.GetClientSocket(i)).GetDlgPtr();
				if(dlg == NULL)
					continue;
				 
				if(dlg->GetClientName() == name)
				{						 
					dlg->ShowWindow(SW_SHOW);			 
					foundFlag = 1;
					break;
				}
			 
			}		 
			 
			if(foundFlag == -1) 
			{
				for(i =0; i< MAXCLIENTS; i++)
				{
					if(m_ClientSock[i] == NULL)
					{
						foundFlag = 1;
						break;
					}
				}
				 
				if(foundFlag == 1)
				{
					CServerInfoDllg dlg;
					if(dlg.DoModal()== IDOK && dlg.m_port_number != m_ServerInfoDlg.m_port_number)
					{
						CTalkDlg *tlkDlg = (CTalkDlg*)serversock.CheckIfClientAlreadExists(name);//new CTalkDlg(this);			
						m_ClientSock[i] = new CClientSocket(); 
						((CClientSocket*)m_ClientSock[i])->SetDlgPtr(tlkDlg);
						m_ClientSock[i]->Create();
						tlkDlg->SetClientPtr(m_ClientSock[i]);
						m_ClientSock[i]->AsyncSelect(FD_READ | FD_CLOSE);
						tlkDlg->SetClientName(name);						 
					
						if(m_ClientSock[i]->Connect(name,dlg.m_port_number) !=0 || GetLastError() == 10035)
						{
								m_ClientSock[i]->AsyncSelect(FD_READ | FD_CONNECT| FD_CLOSE | FD_WRITE);
								//m_status = "Connected...";
								UpdateData(FALSE);
								//tlkDlg->Create(IDD_TALK_DIALOG,this);
								tlkDlg->ShowWindow(SW_SHOW);
								UpdateData(FALSE);	
						}
						else
						{
								((CClientSocket*)m_ClientSock[i])->SetDlgPtr(NULL);
		 						m_ClientSock[i] = NULL;
							//_status = "Not Connected...";
								CString str;
								str.Format("Not Connected.. %d",GetLastError());
								AfxMessageBox(str);
								UpdateData(FALSE);
						}
					}
					else
					{
						AfxMessageBox("can't connect to self server");
					}
					
				}
			}
			 
		}
	
	}
	UpdateData(FALSE);
	*pResult = 0;
}*/
LRESULT CChatDlg::OnShellNotify(WPARAM wParam,LPARAM lParam)
{
	 
	switch(lParam)
	{
		case WM_LBUTTONDOWN:
			//if(this->IsIconic() == TRUE)
				this->ShowWindow(SW_SHOW);
			break;
		case WM_RBUTTONDOWN:
				this->ShowWindow(SW_HIDE);
			break;
	}
	return 0;
}

void CChatDlg::OnViewHide() 
{
	this->ShowWindow(SW_HIDE);	
}

void CChatDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CStatic* stk = (CStatic*)GetDlgItem(IDC_STATIC_STATUS1);
	CRect rect;
	stk->GetWindowRect(rect);
	if(rect.PtInRect(point))
	{
		CMenu menu;
		menu.LoadMenu(IDR_CHAT);
		CMenu *pContextMenu1 = menu.GetSubMenu(0);	 
		CMenu *pContextMenu = pContextMenu1->GetSubMenu(0);	 		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN |
			TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x,point.y,this);
			return;
	}
}
void CChatDlg::SetClientState(CString name, CString state)
{
}
 

void CChatDlg::OnToolsServer() 
{
	// TODO: Add your command handler code here

	m_ServerInfoDlg.DoModal();
}


void CChatDlg::OnSelchangeListFriends() 
{
	// TODO: Add your control notification handler code here
	
}

void CChatDlg::OnDblclkListFriends() 
{			 		
		CString name;
		m_list_friends.GetText(m_list_friends.GetCurSel(),name);
	 
		if(name.GetLength() < 1)
		{
			CString str;
			str.Format("Enter valid host name",name);
			AfxMessageBox(str);
			return;
		}
		struct hostent *hent = (struct hostent*)gethostbyname(name);
		if(hent == NULL)
		{
			CString str;
			str.Format("%s not found",name);
			AfxMessageBox(str);
		}
		else
		{
			SOCKADDR_IN sock_addr;
			sock_addr.sin_family = AF_INET;
			sock_addr.sin_port = 55555;
			int i=0;
			int foundFlag = -1;
			for(i =0; i< MAXCLIENTS; i++)
			{
				if(m_ClientSock[i] != NULL && ((CClientSocket*)m_ClientSock[i])->GetStatus() != 1)
				{					 
					CTalkDlg* dlg =(CTalkDlg*)((CClientSocket*)m_ClientSock[i])->GetDlgPtr();					 
					if(dlg != NULL)
					{
						if(dlg->GetClientName() == name)
						{						 
							dlg->ShowWindow(SW_SHOW);			 
							foundFlag = 1;
							break;
						}
					}
				}			
			}		 
			for(i =0; i< MAXCLIENTS; i++)
			{				 
				CTalkDlg* dlg =(CTalkDlg*)((CClientSocket&)serversock.GetClientSocket(i)).GetDlgPtr();
				if(dlg == NULL)
					continue;
				 
				if(dlg->GetClientName() == name)
				{						 
					dlg->ShowWindow(SW_SHOW);			 
					foundFlag = 1;
					break;
				}
			 
			}		 
			 
			if(foundFlag == -1) 
			{
				for(i =0; i< MAXCLIENTS; i++)
				{
					if(m_ClientSock[i] == NULL)
					{
						foundFlag = 1;
						break;
					}
				}
				 
				if(foundFlag == 1)
				{
					CServerInfoDllg dlg;
					if(dlg.DoModal()== IDOK && dlg.m_port_number != m_ServerInfoDlg.m_port_number)
					{
						CTalkDlg *tlkDlg = (CTalkDlg*)serversock.CheckIfClientAlreadExists(name);//new CTalkDlg(this);			
						m_ClientSock[i] = new CClientSocket(); 
						((CClientSocket*)m_ClientSock[i])->SetDlgPtr(tlkDlg);
						m_ClientSock[i]->Create();
						tlkDlg->SetClientPtr(m_ClientSock[i]);
						m_ClientSock[i]->AsyncSelect(FD_READ | FD_CLOSE);
						tlkDlg->SetClientName(name);						 
					
						if(m_ClientSock[i]->Connect(name,dlg.m_port_number) !=0 || GetLastError() == 10035)
						{
								m_ClientSock[i]->AsyncSelect(FD_READ | FD_CONNECT| FD_CLOSE | FD_WRITE);
								//m_status = "Connected...";
								UpdateData(FALSE);
								//tlkDlg->Create(IDD_TALK_DIALOG,this);
								tlkDlg->ShowWindow(SW_SHOW);
								UpdateData(FALSE);	
						}
						else
						{
								((CClientSocket*)m_ClientSock[i])->SetDlgPtr(NULL);
		 						m_ClientSock[i] = NULL;
							//_status = "Not Connected...";
								CString str;
								str.Format("Not Connected.. %d",GetLastError());
								AfxMessageBox(str);
								UpdateData(FALSE);
						}
					}
					else
					{
						AfxMessageBox("can't connect to self server");
					}
					
				}
			}
			 
		}
 
	UpdateData(FALSE);
}

void CChatDlg::OnHelpHowtouse() 
{
	CHowToUseDlg dlg;
	dlg.DoModal();
}
