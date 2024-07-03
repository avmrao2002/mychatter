// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "chat.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyStatic

MyStatic::MyStatic()
{
}

MyStatic::~MyStatic()
{
}


BEGIN_MESSAGE_MAP(MyStatic, CStatic)
	//{{AFX_MSG_MAP(MyStatic)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyStatic message handlers

void MyStatic::OnContextMenu(CWnd* pWnd, CPoint point) 
{
 
	CMenu menu;
	menu.LoadMenu(IDR_STATUS);
	CMenu *pContextMenu = menu.GetSubMenu(0);	 
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN |
		TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x,point.y,this);
		return;
 
}
