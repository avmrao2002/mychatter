#if !defined(AFX_TALKDLG_H__732AF14E_7648_44AB_BC00_EC065EB0BE3F__INCLUDED_)
#define AFX_TALKDLG_H__732AF14E_7648_44AB_BC00_EC065EB0BE3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TalkDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTalkDlg dialog

class CTalkDlg : public CDialog
{
private:
	CString m_ClientName;
// Construction
public:
	CTalkDlg(CWnd* pParent = NULL);   // standard constructor
	void SetData(char *byte,int length);
	void SetClientPtr(CAsyncSocket* psock);
	void SetClientStatus(int status);
	void SendData(UINT data);
	CClientSocket *m_ClientSocket;
	 
	void SetClientName(CString clientname);
	CString GetClientName();
	void DoBuzzDialog();
	void SendSockData(unsigned char*,int);
	void OnOK();
 
	// Dialog Data
	//{{AFX_DATA(CTalkDlg)
	enum { IDD = IDD_TALK_DIALOG };
	CMyEdit	m_receiveCtrl;
	CMyEdit	m_sentCtrl;
	CString	m_receive;
	BOOL	m_Check_Direct;
	BOOL	m_Check_Send_Close;
	CString	m_static_status;
	BOOL	m_Check_Hide;
	CString	m_send;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTalkDlg)
	afx_msg void OnCheckDirect();
	afx_msg void OnButtonSend();
	afx_msg void OnCheckSendClose();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckHide();
	afx_msg void OnFileTalkExit();
	afx_msg void OnFileTalkOpen();
	afx_msg void OnFileTalkSave();
	afx_msg void OnToolsBuzz();
	afx_msg void OnChangeSend();
	afx_msg void OnToolsCleansend();
	afx_msg void OnToolsClearreceive();
	afx_msg void OnToolsVoice();
	afx_msg void OnFileSendmessage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALKDLG_H__732AF14E_7648_44AB_BC00_EC065EB0BE3F__INCLUDED_)
