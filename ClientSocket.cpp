// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "chat.h"

#include "ClientSocket.h"
#include "myedit.h"
#include "TalkDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
	status = 0;
	m_TalkDlg = NULL;
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

void CClientSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString msg = (CString)"Disconnected from " + (CString)((CTalkDlg*)m_TalkDlg)->GetClientName();

	AfxMessageBox(msg);
//	((CChatDlg*)m_ChatDlg)->m_status = "Disconnected...";*/
	ShutDown(2);
	Close();
	((CTalkDlg*)m_TalkDlg)->UpdateData(FALSE);
	((CTalkDlg*)m_TalkDlg)->SetClientStatus(TRUE);
	((CTalkDlg*)m_TalkDlg)->SetClientPtr(NULL);	 
	m_TalkDlg = NULL;
	status = 0;
	CAsyncSocket::OnClose(nErrorCode);
}

void CClientSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char* data= NULL;
	if(m_length > 0)
	{		 
		 
		data = (char*)malloc(m_length+1);
		if(data == NULL)
		{
			m_length = 0;
			return;
		}
		memset(data,'\0',m_length+1);
		int bytesread = Receive(data,m_length);	 
		if(m_TalkDlg != NULL)
		{	 
			((CTalkDlg*)m_TalkDlg)->SetData(data,m_length);
		}
		m_length = 0;
	}
	else
	{
		char byte[4]; 
		Receive(byte,4);
		memcpy(&m_length,byte,4);
	//m_length = ntohs(m_length);
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

int CClientSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
}

int CClientSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CAsyncSocket::Send(lpBuf, nBufLen, nFlags);
}

int CClientSocket::GetStatus()
{
	return status;
}
void CClientSocket::SetStatus(int stat)
{
	status = stat;
}
void CClientSocket::SetDlgPtr(CDialog* dlg)
{
	m_TalkDlg = dlg;

}
CDialog* CClientSocket::GetDlgPtr()
{
	return m_TalkDlg;
}
void CClientSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(nErrorCode != 0)
	{
		AfxMessageBox("Connection could not be established");
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
