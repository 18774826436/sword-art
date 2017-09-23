// ServerSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "ServerSocket.h"
#include "ServerDlg.h"

// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数
 
void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
 
	CServerDlg *pDlg = (CServerDlg*)theApp.m_pMainWnd;
	if (pDlg == NULL)
	{
		return;
	}
 
	// 一个新的TCP连接
	int SockAddrLen = sizeof(pDlg->m_sessionAddr);
 
	if (Accept(pDlg->m_sessionSocket, (SOCKADDR*)&pDlg->m_sessionAddr, &SockAddrLen))
	{
		CString strTemp(::inet_ntoa(pDlg->m_sessionAddr.sin_addr));
		strTemp = _T("\r\n注意：客户端【") + strTemp + _T("】已连接到服务器！\r\n");
		pDlg->AppendShowText(strTemp);
		// 启用发送按钮
		pDlg->m_send.EnableWindow(TRUE);
	}
	CSocket::OnAccept(nErrorCode);
}