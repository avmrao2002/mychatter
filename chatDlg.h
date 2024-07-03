// chatDlg.h : header file
//

#if !defined(AFX_CHATDLG_H__4D1D0987_7079_11D5_8A58_0000E21285CA__INCLUDED_)
#define AFX_CHATDLG_H__4D1D0987_7079_11D5_8A58_0000E21285CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog
#include "MyStatic.h"
struct DATAPACKET
{
	char type;
	unsigned int length;
	char* data;
};
#define MESSAGE			0
#define BUZZ			1
#define STATUS			2
#define ACTION			3
#define TYPING			4
#define DIRECT			5
#define FILE			6
#define VOICE			7
#define VOICE_YES		8
#define VOICE_NO		9
#define VOICE_REQUEST	10
#define VOICE_DATA		11



//STATUS
#define ONLINE		100
#define OFFLINE		101
#define IDLE		102
#define AWAY		103
#define BUSY		104

#define ONLINE_STR		"Online" 
#define OFFLINE_STR		"Offline"
#define IDLE_STR		"Idle"
#define AWAY_STR		"Away"
#define BUSY_STR		"Bysy"

#include "MyEdit.h"
#include "ServerInfoDllg.h"
class CChatDlg : public CDialog
{
// Construction
	CAsyncSocket *m_ClientSock[MAXCLIENTS];
public:
	CChatDlg(CWnd* pParent = NULL);	// standard constructor	 
	void OnOK(); 
	LRESULT OnShellNotify(WPARAM wParam,LPARAM lParam);
	void OnMyAdd();
	void SetClientState(CString name, CString state);
// Dialog Data
	//{{AFX_DATA(CChatDlg)
	enum { IDD = IDD_CHAT_DIALOG };
	CListBox	m_list_friends;
	CString	m_Static_Status;
	CString	m_Edit_Friend;
	CServerInfoDllg m_ServerInfoDlg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;	 

	// Generated message map functions
	//{{AFX_MSG(CChatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEditConnect();
	afx_msg void OnUpdateEditConnect(CCmdUI* pCmdUI);
	afx_msg void OnEditDisconnect();
	afx_msg void OnUpdateEditDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnChangeSend();
	afx_msg void OnUpdateSend();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnFileExit();
	afx_msg void OnHelpAboutchat();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnFileChangemystatusAway();
	afx_msg void OnFileChangemystatusBusy();
	afx_msg void OnFileChangemystatusIdle();
	afx_msg void OnFileChangemystatusOffline();
	afx_msg void OnFileChangemystatusOnline();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnViewHide();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnToolsServer();
	afx_msg void OnSelchangeListFriends();
	afx_msg void OnDblclkListFriends();
	afx_msg void OnHelpHowtouse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 
	 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATDLG_H__4D1D0987_7079_11D5_8A58_0000E21285CA__INCLUDED_)
