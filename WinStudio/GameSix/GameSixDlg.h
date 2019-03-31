
// GameSixDlg.h : 头文件
//

#pragma once
#include<cmath>
#include<vector>
#include<ctime>
#include<algorithm>
#include "afxwin.h"
using namespace std;

// CGameSixDlg 对话框
class CGameSixDlg : public CDialogEx
{
// 构造
public:
	CGameSixDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GAMESIX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	int m_picMap[9];//保存着当前图片的顺序 0~7 8是空的
	CBitmap m_bitmap;
private:
	void gamePaint();
	//逆推打乱图片
	void initlize(int counts);
	//根据当前下标获取所有临近下标
	vector<int> getNeighborIndexs(int index);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	long m_elpased;

	CStatic m_resultPicture;
	afx_msg void OnBnClickedButtonStart();
};
