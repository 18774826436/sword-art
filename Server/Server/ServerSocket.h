#pragma once

// CServerSocket ÃüÁîÄ¿±ê
//¼àÌıÌ×½Ó×Ö
class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
		virtual void OnAccept(int nErrorCode);
};


