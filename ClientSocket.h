#if !defined(AFX_CLIENTSOCKET_H__4D1D0990_7079_11D5_8A58_0000E21285CA__INCLUDED_)
#define AFX_CLIENTSOCKET_H__4D1D0990_7079_11D5_8A58_0000E21285CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CAsyncSocket
{
// Attributes
	int status;
	CDialog* m_TalkDlg;
	int m_length;
public:

// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();
	int GetStatus();
	void SetStatus(int status);
	void SetDlgPtr(CDialog* dlg);
	CDialog* GetDlgPtr();
	 
	 
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__4D1D0990_7079_11D5_8A58_0000E21285CA__INCLUDED_)
