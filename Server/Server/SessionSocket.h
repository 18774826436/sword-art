#pragma once

// CSessionSocket 命令目标
//会话套接字
class CSessionSocket : public CSocket
{
public:
	CSessionSocket();
	virtual ~CSessionSocket();
		virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


