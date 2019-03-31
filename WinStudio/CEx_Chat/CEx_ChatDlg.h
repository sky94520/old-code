
// CEx_ChatDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "ChatSocket.h"

// CCEx_ChatDlg �Ի���
class CCEx_ChatDlg : public CDialogEx
{
// ����
public:
	CCEx_ChatDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CCEx_ChatDlg();

// �Ի�������
	enum { IDD = IDD_CEX_CHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
private:
	CComboBox m_comboType;
	CListBox m_listMsg;
	bool m_bServer;//�Ƿ��Ƿ�����
	CString m_strMsg;
public:
	CChatSocket m_asServer;
	CChatSocket m_asClient;
public:
	afx_msg void OnCbnSelchangeComboType();
	void onAccept();
	void onClose();
	void onConnect();
	void onReceive();
	void onSend();
	void doClose();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSend();
};
