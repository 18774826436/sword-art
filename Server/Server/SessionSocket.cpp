// SessionSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "SessionSocket.h"
#include "ServerDlg.h"

// CSessionSocket

CSessionSocket::CSessionSocket()
{
}
CSessionSocket::~CSessionSocket()
{
}
// CSessionSocket 成员函数
void CSessionSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CServerDlg *pDlg = (CServerDlg*)theApp.m_pMainWnd;
	if (pDlg == NULL)
	{
		return;
	}
	char str[128] = "";
	Receive(str, sizeof(str), 0);
	CString strTemp(str);
	strTemp = strTemp;
	pDlg->AppendShowText(strTemp);
 
	CSocket::OnReceive(nErrorCode);
}
void CSessionSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
 
	CServerDlg *pDlg = (CServerDlg*)theApp.m_pMainWnd;
	if (pDlg != NULL)
	{
		pDlg->m_sessionSocket.Close();
		CString strTemp(inet_ntoa(pDlg->m_sessionAddr.sin_addr));
		strTemp = _T("\r\n注意：客户端【") + strTemp + _T("】与服务器的连接已断开！\r\n");
		pDlg->AppendShowText(strTemp);
	}
 
	CSocket::OnClose(nErrorCode);
}