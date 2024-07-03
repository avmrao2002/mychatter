// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "chat.h"
#include "MyEdit.h"
#include "ClientSocket.h"
#include "TalkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == '\n') //enter
	{
		((CTalkDlg*)GetParent())->OnOK(); 
	}
	else
	{
		((CTalkDlg*)GetParent())->SendData(nChar); 
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
