#include "stdafx.h"
#include "ChatSocket.h"
#include "CEx_ChatDlg.h"


CChatSocket::CChatSocket(void)
	:m_pDlg(nullptr)
{
}


CChatSocket::~CChatSocket(void)
{
}
void CChatSocket::OnAccept(int nErrorCode)
{
	if(nErrorCode == 0)
		m_pDlg->onAccept();
}
void CChatSocket::OnSend(int nErrorCode)
{
	if(nErrorCode == 0)
		m_pDlg->onSend();
}
void CChatSocket::OnClose(int nErrorCode)
{
	if(nErrorCode == 0)
		m_pDlg->doClose();
}
void CChatSocket::OnConnect(int nErrorCode)
{
	if(nErrorCode == 0)
		m_pDlg->onConnect();
}
void CChatSocket::OnReceive(int nErrorCode)
{
	if(nErrorCode == 0)
		m_pDlg->onReceive();
}