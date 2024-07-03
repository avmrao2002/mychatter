; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chat.h"

ClassCount=12
Class1=CChatApp
Class2=CChatDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_TALK_DIALOG
Resource2=IDD_ABOUTBOX
Class4=CServerSocket
Class5=CClientSocket
Resource3=IDR_TALK
Resource4=IDD_DIALOG_HOW_TO_USE
Class6=CConnectDlg
Class7=CMyEdit
Resource5=IDR_CHAT
Class8=CTalkDlg
Class9=MyStatic
Class10=CFileClientSocket
Resource6=IDD_CHAT_DIALOG
Class11=CServerInfoDllg
Resource7=IDD_DIALOG_SERVER
Class12=CHowToUseDlg
Resource8=IDR_MAINFRAME

[CLS:CChatApp]
Type=0
HeaderFile=chat.h
ImplementationFile=chat.cpp
Filter=N
LastObject=CChatApp

[CLS:CChatDlg]
Type=0
HeaderFile=chatDlg.h
ImplementationFile=chatDlg.cpp
Filter=D
LastObject=CChatDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=chatDlg.h
ImplementationFile=chatDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_CHAT_DIALOG]
Type=1
Class=CChatDlg
ControlCount=7
Control1=IDC_BUTTON_ADD,button,1342242816
Control2=IDC_BUTTON_DELETE,button,1342242816
Control3=IDC_EDIT_FRIEND,edit,1350631552
Control4=IDC_STATIC_STATUS,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_STATUS1,static,1342308352
Control7=IDC_LIST_FRIENDS,listbox,1352728835

[CLS:CServerSocket]
Type=0
HeaderFile=ServerSocket.h
ImplementationFile=ServerSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CServerSocket

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CClientSocket

[MNU:IDR_CHAT]
Type=1
Class=?
Command1=ID_FILE_EXIT
Command2=ID_VIEW_HIDE
Command3=ID_HELP_ABOUTCHAT
Command4=ID_HELP_HOWTOUSE
CommandCount=4

[CLS:CConnectDlg]
Type=0
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CConnectDlg
VirtualFilter=dWC

[CLS:CMyEdit]
Type=0
HeaderFile=MyEdit.h
ImplementationFile=MyEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=CMyEdit

[DLG:IDD_TALK_DIALOG]
Type=1
Class=CTalkDlg
ControlCount=7
Control1=IDC_BUTTON_SEND,button,1342242816
Control2=IDC_SEND,edit,1352728580
Control3=IDC_CHECK_HIDE,button,1342242819
Control4=IDC_CHECK_DIRECT,button,1342242819
Control5=IDC_CHECK_SEND_CLOSE,button,1342242819
Control6=IDC_STATIC_STATUS,static,1342308352
Control7=IDC_RECEIVE,edit,1352734788

[CLS:CTalkDlg]
Type=0
HeaderFile=TalkDlg.h
ImplementationFile=TalkDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTalkDlg

[MNU:IDR_TALK]
Type=1
Class=?
Command1=ID_FILE_SENDMESSAGE
Command2=ID_FILE_TALK_OPEN
Command3=ID_FILE_TALK_SAVE
Command4=ID_FILE_TALK_EXIT
Command5=ID_TOOLS_CLEARRECEIVE
Command6=ID_TOOLS_CLEANSEND
Command7=ID_TOOLS_BUZZ
CommandCount=7

[CLS:MyStatic]
Type=0
HeaderFile=MyStatic.h
ImplementationFile=MyStatic.cpp
BaseClass=CStatic
Filter=W
LastObject=MyStatic
VirtualFilter=WC

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_TOOLS_BUZZ
Command2=ID_TOOLS_CLEANSEND
Command3=ID_VIEW_HIDE
Command4=ID_FILE_SENDMESSAGE
Command5=ID_FILE_OPEN
Command6=ID_TOOLS_CLEARRECEIVE
Command7=ID_FILE_SAVE
Command8=ID_TOOLS_VOICE
CommandCount=8

[CLS:CFileClientSocket]
Type=0
HeaderFile=FileClientSocket.h
ImplementationFile=FileClientSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CFileClientSocket

[DLG:IDD_DIALOG_SERVER]
Type=1
Class=CServerInfoDllg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_PORT_NUMBER,edit,1350631552
Control3=IDC_STATIC,static,1342308352

[CLS:CServerInfoDllg]
Type=0
HeaderFile=ServerInfoDllg.h
ImplementationFile=ServerInfoDllg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_PORT_NUMBER
VirtualFilter=dWC

[DLG:IDD_DIALOG_HOW_TO_USE]
Type=1
Class=CHowToUseDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_HOW_TO_USE,edit,1352730628

[CLS:CHowToUseDlg]
Type=0
HeaderFile=HowToUseDlg.h
ImplementationFile=HowToUseDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_HELP_HOWTOUSE

