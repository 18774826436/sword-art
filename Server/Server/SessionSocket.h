#pragma once

// CSessionSocket ����Ŀ��
//�Ự�׽���
class CSessionSocket : public CSocket
{
public:
	CSessionSocket();
	virtual ~CSessionSocket();
		virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


