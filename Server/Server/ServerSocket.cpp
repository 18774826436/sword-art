// ServerSocket.cpp : ʵ���ļ�
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


// CServerSocket ��Ա����
 
void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
 
	CServerDlg *pDlg = (CServerDlg*)theApp.m_pMainWnd;
	if (pDlg == NULL)
	{
		return;
	}
 
	// һ���µ�TCP����
	int SockAddrLen = sizeof(pDlg->m_sessionAddr);
 
	if (Accept(pDlg->m_sessionSocket, (SOCKADDR*)&pDlg->m_sessionAddr, &SockAddrLen))
	{
		CString strTemp(::inet_ntoa(pDlg->m_sessionAddr.sin_addr));
		strTemp = _T("\r\nע�⣺�ͻ��ˡ�") + strTemp + _T("�������ӵ���������\r\n");
		pDlg->AppendShowText(strTemp);
		// ���÷��Ͱ�ť
		pDlg->m_send.EnableWindow(TRUE);
	}
	CSocket::OnAccept(nErrorCode);
}