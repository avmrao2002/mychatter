#if !defined(AFX_SERVERSOCKET_H__4D1D098F_7079_11D5_8A58_0000E21285CA__INCLUDED_)
#define AFX_SERVERSOCKET_H__4D1D098F_7079_11D5_8A58_0000E21285CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target
 
class CClientSocket;
class CServerSocket : public CAsyncSocket
{
// Attributes
 	 
	CClientSocket m_ClientSocket[MAXCLIENTS];
	CDialog *m_TalkDlg[MAXCLIENTS];
// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();
	void CreateServer();
	int GetFreeClient();
	CClientSocket& GetClientSocket(int i);
	void SendStatusToClients(char client_status);
	CDialog* CheckIfClientAlreadExists(CString name);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__4D1D098F_7079_11D5_8A58_0000E21285CA__INCLUDED_)
