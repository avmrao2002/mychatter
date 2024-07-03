#if !defined(AFX_HOWTOUSEDLG_H__D8C47F47_ED32_4032_8ABE_C2A31AF68396__INCLUDED_)
#define AFX_HOWTOUSEDLG_H__D8C47F47_ED32_4032_8ABE_C2A31AF68396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HowToUseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHowToUseDlg dialog

class CHowToUseDlg : public CDialog
{
// Construction
public:
	CHowToUseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHowToUseDlg)
	enum { IDD = IDD_DIALOG_HOW_TO_USE };
	CString	m_how_to_use;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHowToUseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHowToUseDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOWTOUSEDLG_H__D8C47F47_ED32_4032_8ABE_C2A31AF68396__INCLUDED_)
