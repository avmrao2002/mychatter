#if !defined(AFX_SERVERINFODLLG_H__5C224974_3F0E_486F_981F_DDF870FDED6F__INCLUDED_)
#define AFX_SERVERINFODLLG_H__5C224974_3F0E_486F_981F_DDF870FDED6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerInfoDllg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServerInfoDllg dialog

class CServerInfoDllg : public CDialog
{
// Construction
public:
	CServerInfoDllg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServerInfoDllg)
	enum { IDD = IDD_DIALOG_SERVER };
	int		m_port_number;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerInfoDllg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServerInfoDllg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERINFODLLG_H__5C224974_3F0E_486F_981F_DDF870FDED6F__INCLUDED_)
