
// ex2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// Cex2Dlg �Ի���
class Cex2Dlg : public CDialogEx
{
// ����
public:
	Cex2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EX2_DIALOG };

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
	int r1;
public:
	afx_msg void OnBnClickedOk();
protected:
	int r2;
	CButton c1;
	CButton c2;
	CButton c3;
};
