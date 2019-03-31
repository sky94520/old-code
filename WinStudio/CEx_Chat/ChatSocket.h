#pragma once
#include "afxsock.h"
class CCEx_ChatDlg;

class CChatSocket :
	public CAsyncSocket
{
public:
	CCEx_ChatDlg*m_pDlg;
public:
	CChatSocket(void);
	~CChatSocket(void);
protected:
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

