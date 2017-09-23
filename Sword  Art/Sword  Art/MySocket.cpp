// MySocket.cpp : 实现文件by陈海林
//

#include "stdafx.h"
#include "Sword  Art.h"
#include "MySocket.h"
#include "chatroom.h"
extern chatroom *m_dlg3;
// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket 成员函数


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	chatroom *pDlg = m_dlg3;//设置一个指向聊天窗口的指针
	if(pDlg == NULL)
	{
		return;
	}
	char str[128] = "";
	Receive(str,sizeof(str),0);
	CString strTemp(str);
	strTemp = (_T("服务器端:")) + strTemp;
	pDlg->AppendShowText(strTemp);
	CSocket::OnReceive(nErrorCode);
}
