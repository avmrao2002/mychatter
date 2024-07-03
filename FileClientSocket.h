#if !defined(AFX_FILECLIENTSOCKET_H__92D230A5_10B1_4B5D_895E_A922E05D651B__INCLUDED_)
#define AFX_FILECLIENTSOCKET_H__92D230A5_10B1_4B5D_895E_A922E05D651B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CFileClientSocket command target

class CFileClientSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CFileClientSocket();
	virtual ~CFileClientSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CFileClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILECLIENTSOCKET_H__92D230A5_10B1_4B5D_895E_A922E05D651B__INCLUDED_)
