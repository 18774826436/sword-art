// SessionSocket.cpp : ʵ���ļ�
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
// CSessionSocket ��Ա����
void CSessionSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ����ר�ô����/����û���
 
	CServerDlg *pDlg = (CServerDlg*)theApp.m_pMainWnd;
	if (pDlg != NULL)
	{
		pDlg->m_sessionSocket.Close();
		CString strTemp(inet_ntoa(pDlg->m_sessionAddr.sin_addr));
		strTemp = _T("\r\nע�⣺�ͻ��ˡ�") + strTemp + _T("����������������ѶϿ���\r\n");
		pDlg->AppendShowText(strTemp);
	}
 
	CSocket::OnClose(nErrorCode);
}