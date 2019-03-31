
// GameSixDlg.h : ͷ�ļ�
//

#pragma once
#include<cmath>
#include<vector>
#include<ctime>
#include<algorithm>
#include "afxwin.h"
using namespace std;

// CGameSixDlg �Ի���
class CGameSixDlg : public CDialogEx
{
// ����
public:
	CGameSixDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GAMESIX_DIALOG };

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
private:
	int m_picMap[9];//�����ŵ�ǰͼƬ��˳�� 0~7 8�ǿյ�
	CBitmap m_bitmap;
private:
	void gamePaint();
	//���ƴ���ͼƬ
	void initlize(int counts);
	//���ݵ�ǰ�±��ȡ�����ٽ��±�
	vector<int> getNeighborIndexs(int index);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	long m_elpased;

	CStatic m_resultPicture;
	afx_msg void OnBnClickedButtonStart();
};
