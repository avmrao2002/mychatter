#if !defined(AFX_MYSTATIC_H__DA776DBA_E0BB_4A3B_86A2_6CCDF176F77D__INCLUDED_)
#define AFX_MYSTATIC_H__DA776DBA_E0BB_4A3B_86A2_6CCDF176F77D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyStatic window

class MyStatic : public CStatic
{
// Construction
public:
	MyStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyStatic)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__DA776DBA_E0BB_4A3B_86A2_6CCDF176F77D__INCLUDED_)
