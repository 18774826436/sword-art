// MySocket.cpp : ʵ���ļ�by�º���
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


// CMySocket ��Ա����


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	chatroom *pDlg = m_dlg3;//����һ��ָ�����촰�ڵ�ָ��
	if(pDlg == NULL)
	{
		return;
	}
	char str[128] = "";
	Receive(str,sizeof(str),0);
	CString strTemp(str);
	strTemp = (_T("��������:")) + strTemp;
	pDlg->AppendShowText(strTemp);
	CSocket::OnReceive(nErrorCode);
}
