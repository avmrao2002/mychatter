// TalkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chat.h"
#include "ClientSocket.h"
#include "chatDlg.h"
#include "MyEdit.h"
#include "TalkDlg.h"
#include "MyStatic.h"
#include "mmsystem.h"
  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
UINT VoiceChatThread(void* arg)
{
	CTalkDlg *talkdlg = (CTalkDlg*)arg;
	CFile file("dau8.wav",CFile::modeRead | CFile::typeBinary );
	unsigned char* buff = new unsigned char[file.GetLength()+2] ;
	file.Read(&buff[2],file.GetLength()); 
	CString str;
	str.Format("length %d",file.GetLength());
	AfxMessageBox(str);
	buff[0] = VOICE;
	buff[1] = VOICE_DATA;	 
	talkdlg->SendSockData(buff,file.GetLength()+2);
	 
	return 0;
	
}
/////////////////////////////////////////////////////////////////////////////
// CTalkDlg dialog


CTalkDlg::CTalkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTalkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTalkDlg)
	m_receive = _T("");
	m_Check_Direct = FALSE;
	m_Check_Send_Close = FALSE;
	m_static_status = _T("");
	m_Check_Hide = FALSE;
	m_send = _T("");
	//}}AFX_DATA_INIT
	m_Check_Direct = TRUE;
	m_ClientName = "";
	m_ClientSocket = NULL;

}


void CTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTalkDlg)
	DDX_Control(pDX, IDC_RECEIVE, m_receiveCtrl);
	DDX_Control(pDX, IDC_SEND, m_sentCtrl);
	DDX_Text(pDX, IDC_RECEIVE, m_receive);
	DDX_Check(pDX, IDC_CHECK_DIRECT, m_Check_Direct);
	DDX_Check(pDX, IDC_CHECK_SEND_CLOSE, m_Check_Send_Close);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_static_status);
	DDX_Check(pDX, IDC_CHECK_HIDE, m_Check_Hide);
	DDX_Text(pDX, IDC_SEND, m_send);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTalkDlg, CDialog)
	//{{AFX_MSG_MAP(CTalkDlg)
	ON_BN_CLICKED(IDC_CHECK_DIRECT, OnCheckDirect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_CHECK_SEND_CLOSE, OnCheckSendClose)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_HIDE, OnCheckHide)
	ON_COMMAND(ID_FILE_TALK_EXIT, OnFileTalkExit)
	ON_COMMAND(ID_FILE_TALK_OPEN, OnFileTalkOpen)
	ON_COMMAND(ID_FILE_TALK_SAVE, OnFileTalkSave)
	ON_COMMAND(ID_TOOLS_BUZZ, OnToolsBuzz)
	ON_EN_CHANGE(IDC_SEND, OnChangeSend)
	ON_COMMAND(ID_TOOLS_CLEANSEND, OnToolsCleansend)
	ON_COMMAND(ID_TOOLS_CLEARRECEIVE, OnToolsClearreceive)
	ON_COMMAND(ID_TOOLS_VOICE, OnToolsVoice)
	ON_COMMAND(ID_FILE_SENDMESSAGE, OnFileSendmessage)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDOK,OnOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTalkDlg message handlers

void CTalkDlg::OnCheckDirect() 
{
	// TODO: Add your control notification handler code here
	CButton *btn = (CButton*)GetDlgItem(IDC_CHECK_DIRECT);
	if(btn->GetCheck() == 1)
	{
		m_Check_Direct = TRUE;
	}
	else
	{
		m_Check_Direct = FALSE;
	}	 
	m_send = "";
	UpdateData(FALSE);
}

void CTalkDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	 
	CButton *btn = (CButton*)GetDlgItem(IDC_CHECK_DIRECT);
	if(btn->GetCheck() == 1)
	{
		//SendData('\n');	 
	}
	else
	{
		if(m_send.GetLength() <=0)
		{
			return;
		}
		SendData(255);
		if(m_Check_Send_Close == TRUE)
		{
			this->ShowWindow(SW_HIDE);
		}
	}

}

void CTalkDlg::OnCheckSendClose() 
{// notification handler code here
	CButton *btn = (CButton*)GetDlgItem(IDC_CHECK_SEND_CLOSE);
	if(btn->GetCheck() == 1)
	{
		m_Check_Send_Close = TRUE;
	}
	else
	{
		m_Check_Send_Close = FALSE;
	}
	 
	UpdateData(FALSE);
}
void CTalkDlg::SetClientPtr(CAsyncSocket* psock)
{
	m_ClientSocket = (CClientSocket*)psock;
}
void CTalkDlg::SetClientStatus(int status)
{
	m_ClientSocket->SetStatus(status);
}
void CTalkDlg::SetData(char *data,int length)
{
	UpdateData(TRUE);	
	/*if(byte == 8)
	{
		if(m_receive.GetLength() > 0)
		{
				m_receive = m_receive.Left(m_receive.GetLength()-1);
		}
	}
	else if(byte == '\r' || byte == '\n')
	{
		m_receive += "\r\n";
		CEdit *pedit = (CEdit*)GetDlgItem(IDC_RECEIVE);		 
	}
	else
	{
		m_receive += byte;
	}*/
	if(data[0] == MESSAGE)
	{
		m_receive = m_receive + &data[1] + "\r\n";
		m_static_status = "received message";
	}
	else if(data[0] == BUZZ)
	{
		DoBuzzDialog();
		m_receive = m_receive + & data[1] + "\r\n";
		m_static_status = "";
	}
	else if(data[0] == ACTION)
	{
		if(data[1] == TYPING)
		{
			m_static_status = (CString)&data[2] + (CString)" is typing";
		}	 
	}
	else if(data[0] == DIRECT)
	{ 
		if(data[1] == 8)
		{
			if(m_receive.GetLength() > 0)
			{
					m_receive = m_receive.Left(m_receive.GetLength()-1);
			}
		}
		else if(data[1] == '\r' || data[1] == '\n')
		{
			m_receive += "\r\n";			 
		}
		else
		{			 
			m_receive += (CString)data[1];
		}	
		 
	}
	else if(data[0] == FILE)
	{
		if(AfxMessageBox("Received FILE data, want to store in a file",MB_YESNO) == IDYES)
		{
			CFileDialog fdlg(FALSE);
			m_static_status = "Receiving file";
			UpdateData(FALSE);
			if(fdlg.DoModal() == IDOK)
			{
				CString filepath = fdlg.GetPathName();	 
	 			CFile cfile( filepath, CFile::modeCreate| CFile::modeWrite | CFile::typeBinary );
				cfile.Write(&data[1],length -1);
				cfile.Close();
				m_static_status = "Received file";				 

			}
		}	 
		 
	}
	else if(data[0] == STATUS)
	{
		/*switch(data[1])
		{
			case ONLINE:
				((CChatDlg*)GetParent())->SetClientState(&data[2],ONLINE_STR);
				break;
			case OFFLINE:
				((CChatDlg*)GetParent())->SetClientState(&data[2],OFFLINE_STR);
				break;
			case IDLE:
				((CChatDlg*)GetParent())->SetClientState(&data[2],IDLE_STR);
				break;
			case AWAY:
				((CChatDlg*)GetParent())->SetClientState(&data[2],AWAY_STR);
				break;
			case BUSY:
				((CChatDlg*)GetParent())->SetClientState(&data[2],BUSY_STR);
				break;
		}*/
	}
	else if(data[0] = VOICE)
	{
		switch(data[1])
		{
			case VOICE_YES:
				AfxMessageBox("Accepted for voice chat");
				AfxBeginThread(VoiceChatThread,this);
				break;
			case VOICE_NO:
				AfxMessageBox("Rejected for voice chat");
				break;
			case VOICE_REQUEST:
			{
				CString str = &data[1] + (CString) " has requeste for voice chat, Accept";
				if(AfxMessageBox(str,MB_YESNO) == IDYES)
				{
					char clength[5];
					int length = 2;
					memcpy(clength,&length,4);			 			 
					m_ClientSocket->Send(clength,4);
					CString temp;
					temp.Format("%c %s",(char)VOICE,VOICE_YES);;
					m_ClientSocket->Send(temp,temp.GetLength());
				}
				else
				{
					char clength[5];
					int length = 2;
					memcpy(clength,&length,4);			 			 
					m_ClientSocket->Send(clength,4);
					CString temp;
					temp.Format("%c %s",(char)VOICE,VOICE_NO);
					m_ClientSocket->Send(temp,temp.GetLength());
				}
			}
				break;
			case VOICE_DATA:
				//CMemFile file((unsigned char*)&data[2],length -2,0);
				CString str;
				str.Format("lengthi is %d, playing sound",length);
				AfxMessageBox(str);

				CFile file("test.wav",CFile::modeCreate | CFile::modeWrite| CFile::typeBinary);
				 
				file.Write(&data[2],length -2);
				file.Close();
				//PlaySound("test.wav",NULL,SND_FILENAME);
				//PlaySound(NULL,NULL,NULL);
				break;
		}
		 
	}


	free(data);
	data = NULL;
	CEdit *pedit = (CEdit*)GetDlgItem(IDC_RECEIVE);
	pedit->PostMessage(WM_VSCROLL,SB_BOTTOM,0); 
	/*&CEdit *pedit = (CEdit*)GetDlgItem(IDC_RECEIVE);
	pedit->PostMessage(WM_CHAR,byte,0);
//	AfxMessageBox((CString)byte);*/
	UpdateData(FALSE);
}
void CTalkDlg::SendData(UINT data)
{
	 
	if(m_ClientSocket != NULL&&m_Check_Direct == TRUE)
	{		 			 
			char clength[5];
			int length = 2;
			memcpy(clength,&length,4);			 			 
			m_ClientSocket->Send(clength,4);
			CString temp;
			temp.Format("%c %d",(char)DIRECT,data);;
			m_ClientSocket->Send(temp ,2);
	}
	else
	{
		if(data == 255)
		{

			CString temp = m_ClientName + ":  " + m_send;			 
			m_receive  = m_receive + temp + "\r\n";
			m_send = temp;
			CEdit *pedit = (CEdit*)GetDlgItem(IDC_RECEIVE);
			pedit->PostMessage(WM_VSCROLL,SB_BOTTOM,0);
			UpdateData(FALSE);
			char clength[5];
			int length = m_send.GetLength()+1;
			memcpy(clength,&length,4);			 			 
			m_ClientSocket->Send(clength,4);
			temp = (char)MESSAGE + m_send;
			m_send = temp;
			m_ClientSocket->Send(m_send,m_send.GetLength());
			m_send = "";
			UpdateData(FALSE);			 
		}
		else
		{
			CString str;
			str.Format("%d",data);
			m_send += str;
		}
	}

}

void CTalkDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(m_ClientSocket != NULL)
	{
		m_ClientSocket->OnClose(0);		 
	}
	CDialog::OnClose();
}

void CTalkDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	if(m_ClientSocket != NULL)
	{
		m_ClientSocket->Close();
		 
	}
	// TODO: Add your message handler code here
	
}

BOOL CTalkDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CButton* btn = (CButton*)GetDlgItem(IDC_CHECK_DIRECT);
	btn->SetCheck(TRUE);
	CMenu menu;
	menu.LoadMenu (IDR_TALK);
	SetMenu(&menu);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTalkDlg::OnCheckHide() 
{
	m_Check_Hide = FALSE;	
	this->ShowWindow(SW_HIDE);	
	UpdateData(FALSE);
}
void CTalkDlg::SetClientName(CString clientname)
{
	m_ClientName = clientname;
}
CString  CTalkDlg::GetClientName()
{
	return m_ClientName;
}

void CTalkDlg::OnFileTalkExit() 
{
	// TODO: Add your command handler code here
	SendMessage(WM_CLOSE,0,0);
	
}

void CTalkDlg::OnFileTalkOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog fd(TRUE);
	if(fd.DoModal()==IDOK)
	{
		CString filepath;
		filepath = fd.GetPathName();
	 
	 		CFile cfile( filepath, CFile::modeRead );
			char *buffer = new char[cfile.GetLength() + 1];
			if(buffer != NULL)
			{
				int nBytesRead = cfile.Read(&buffer[1],cfile.GetLength());
				 
				char clength[5];
				int length = cfile.GetLength() + 1;
				cfile.Close();
				memcpy(clength,&length,4);			 			 
				m_ClientSocket->Send(clength,4);				 
				buffer[0] = FILE;
				int byteswritten = 0;
				while(byteswritten <length)
				{
					int sentbytes = m_ClientSocket->Send(buffer+byteswritten,length - byteswritten);
					byteswritten += sentbytes;
				}
				 
				m_send = "";
				UpdateData(FALSE);
				 
			}
			delete[] buffer;
			buffer = NULL;
	}
	UpdateData(TRUE);	
}

void CTalkDlg::OnFileTalkSave() 
{
	// TODO: Add your command handler code here
		// TODO: Add your command handler code here
	UpdateData(TRUE);
	CFileDialog fd(FALSE);
	if(fd.DoModal()==IDOK)
	{
	 	CString filepath;
		filepath = fd.GetPathName();
		CFile cfile( filepath, CFile::modeCreate | CFile::modeWrite );
		CString str("******************Sent Message ************\n");
	 	cfile.Write(m_receive, m_receive.GetLength() );
		cfile.Close();
	}
	
}
 

void CTalkDlg::OnToolsBuzz() 
{
	// TODO: Add your command handler code here
	char clength[5];
	CString temp;
	temp.Format("%c %s:hello are you there??",BUZZ,m_ClientName);	 
	int length = temp.GetLength();
	memcpy(clength,&length,4);			 			 
	m_ClientSocket->Send(clength,4);	 
	m_ClientSocket->Send(temp,temp.GetLength());	 
	UpdateData(FALSE);	
}
void CTalkDlg::DoBuzzDialog()
{	 
	CRect rect;
	GetWindowRect(&rect);
	 
	for(int i = -10; i <  20;i+=2)
	{
		for( int j = -10; j < 20 ; j+=2)
		{
			this->MoveWindow(rect.left + i,rect.top + j ,rect.right - rect.left,rect.bottom -rect.top,TRUE);
			this->ShowWindow(SW_SHOW);
		}
		 
	}
	this->MoveWindow(rect,TRUE);
	this->ShowWindow(SW_SHOW);
}

void CTalkDlg::OnChangeSend() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if(m_Check_Direct != TRUE)
	{
		char clength[5];
		int length = 2 + m_ClientName.GetLength();;
		memcpy(clength,&length,4);			 			 
		m_ClientSocket->Send(clength,4);
		CString temp = (CString)((char)ACTION) + (CString)((char)TYPING) + m_ClientName;	 
		m_ClientSocket->Send(temp,temp.GetLength());	 	
	}
	// TODO: Add your control notification handler code here
	
}

void CTalkDlg::OnToolsCleansend() 
{
	// TODO: Add your command handler code here
	m_send = "";
	UpdateData(FALSE);
}

void CTalkDlg::OnToolsClearreceive() 
{
	 m_receive = "";
	 UpdateData(FALSE);
}

void CTalkDlg::OnToolsVoice() 
{
	// TODO: Add your command handler code here
	char clength[5];
	int length = 2 + m_ClientName.GetLength();;
	memcpy(clength,&length,4);			 			 
	m_ClientSocket->Send(clength,4);
	CString temp;
	temp.Format("%c %s %s",(char)VOICE, VOICE_REQUEST,m_ClientName);	 
	m_ClientSocket->Send(temp,temp.GetLength());	 	
}
void CTalkDlg::SendSockData(unsigned char *data,int length)
{
	char clength[5];	 
	memcpy(clength,&length,4);			 			 
	m_ClientSocket->Send(clength,4);	 
	m_ClientSocket->Send(data,length);	 	
}

void CTalkDlg::OnFileSendmessage() 
{
	// TODO: Add your command handler code here
	OnButtonSend();	
}
void CTalkDlg::OnOK()
{
	OnButtonSend();	 
}

