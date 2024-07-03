// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "chat.h"
 
 
#include "ClientSocket.h"
#include "ServerSocket.h"
#include "MyEdit.h"
#include "ChatDlg.h"
#include "TalkDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
 
}

CServerSocket::~CServerSocket()
{
}
 

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions

void CServerSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	int i=-1;
	while( (i = GetFreeClient()) < 0)
	{
		Sleep(1000);
	}
	Accept(m_ClientSocket[i]);
	CString name; unsigned int port;
	m_ClientSocket[i].GetPeerName(name,port);
	CString msg;
	msg.Format(" requested for chat, Accept");
	msg = name+ msg;
	if(AfxMessageBox(msg,MB_YESNO) == IDYES)
	{
		CTalkDlg *dlg = NULL;//= new CTalkDlg(AfxGetApp()->m_pMainWnd); 
		dlg = (CTalkDlg*)CheckIfClientAlreadExists(name);
		m_ClientSocket[i].SetDlgPtr(dlg);
		dlg->SetClientPtr(&m_ClientSocket[i]);	 
		struct hostent *hent = gethostbyaddr(name,50,0);
	 
		if(hent != NULL)
		{
			 
			dlg->SetClientName(hent->h_name);
			((CChatDlg*)AfxGetApp()->m_pMainWnd)->m_Edit_Friend = hent->h_name;
			((CChatDlg*)AfxGetApp()->m_pMainWnd)->UpdateData(FALSE);
			 
		}
		else
		{
			AfxMessageBox("host name not found");
			dlg->SetClientName(name);
			((CChatDlg*)AfxGetApp()->m_pMainWnd)->m_Edit_Friend = name;
			((CChatDlg*)AfxGetApp()->m_pMainWnd)->UpdateData(FALSE);
	 
		}
		 
		((CChatDlg*)AfxGetApp()->m_pMainWnd)->OnMyAdd();		 
		dlg->ShowWindow(SW_SHOW);
	//	dlg->m_status = "Connected..";
		dlg->UpdateData(FALSE);
		m_ClientSocket[i].AsyncSelect(FD_READ | FD_CLOSE);
		 
	}
	else
	{
		m_ClientSocket[i].Close();
	}
	CAsyncSocket::OnAccept(nErrorCode);
 
}

void CServerSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	ShutDown(2);
	Close();
	CAsyncSocket::OnClose(nErrorCode);
}

void CServerSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnReceive(nErrorCode);
}

int CServerSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
}

int CServerSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CAsyncSocket::Send(lpBuf, nBufLen, nFlags);
}
void CServerSocket::CreateServer()
{	
	char defaultBuf[40];
	char ChatPort[10];
	char CurrentDir[100];
	GetCurrentDirectory(100,CurrentDir);
	((CChatDlg*)AfxGetApp()->m_pMainWnd)->m_ServerInfoDlg.DoModal();
	//strcat(CurrentDir,"\\chat.ini");
 	//GetPrivateProfileString("Chat","ChatPort",defaultBuf,ChatPort,10,CurrentDir);
 	int Port = ((CChatDlg*)AfxGetApp()->m_pMainWnd)->m_ServerInfoDlg.m_port_number;
	if(	this->Create(Port) == 0)
	{
		AfxMessageBox("Chat server is already running");
		exit(0);
	}
	Listen();
	AsyncSelect(FD_ACCEPT | FD_CLOSE);
	for(int i = 0; i < MAXCLIENTS; i++)
	{
		m_TalkDlg[i] = new CTalkDlg(AfxGetApp()->m_pMainWnd); 
		((CTalkDlg*)m_TalkDlg[i])->Create(IDD_TALK_DIALOG,AfxGetApp()->m_pMainWnd);
	}
}
int CServerSocket::GetFreeClient()
{
	int i;
	for(i = 0; i < MAXCLIENTS; i++)
	{
 		int status = m_ClientSocket[i].GetStatus();
 		if(1 != status)
		{
			m_ClientSocket[i].SetStatus(1);
 			return i;
		}
	}
	return -1;
}
CClientSocket& CServerSocket::GetClientSocket(int i)
{
	 
	return m_ClientSocket[i];
}
void CServerSocket::SendStatusToClients(char client_status)
{
	/*for(int i;i< MAXCLIENTS; i++)
	{
		int status = m_ClientSocket[i].GetStatus();
 		if(1 == status)
		{
			char clength[5];
			CTalkDlg *dlg = (CTalkDlg*)(m_ClientSocket[i].GetDlgPtr());
			if(dlg != NULL)
			{
				CString temp = (CString)((char)STATUS);// + (CString)client_status +  dlg->GetClientName();
				int length = temp.GetLength();; 
				memcpy(clength,&length,4);			 			 
				m_ClientSocket[i].Send(clength,4);
				m_ClientSocket[i].Send(temp,temp.GetLength());

			}
		}
	}*/
}
CDialog* CServerSocket::CheckIfClientAlreadExists(CString name)
{
	for(int i = 0; i< MAXCLIENTS; i++)
	{
		if(name == ((CTalkDlg*)m_TalkDlg[i])->GetClientName())
		{
			return m_TalkDlg[i];
		}
	}
	for(int i = 0; i< MAXCLIENTS; i++)
	{
		if(((CTalkDlg*)m_TalkDlg[i])->GetClientName() == "")
		{
			return m_TalkDlg[i];
		}
	}
	return NULL;
}
