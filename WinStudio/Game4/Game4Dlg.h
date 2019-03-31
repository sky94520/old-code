
// Game4Dlg.h : 头文件
//

#pragma once
#include<stack>
#include<queue>
#include<vector>
#include<cmath>
#include<ctime>
using namespace std;
//汉诺塔节点
typedef struct TreeNode
{
	int n;
	char from;
	char to;
	TreeNode*left;
	TreeNode*right;
	TreeNode*parent;
public:
	TreeNode(int n,char from,char to)
		:n(n),from(from),to(to),left(nullptr),right(nullptr),parent(nullptr)
	{
	}
	TreeNode(int n,char from,char to,TreeNode*left,TreeNode*right,TreeNode*parent)
		:n(n),from(from),to(to),left(left),right(right),parent(parent){}
}TreeNode;
//汉诺塔绘制节点
typedef struct Tower
{
	int n;//指示代表第几个图形
	POINT position;//位置所在
	COLORREF color;//绘制颜色
	SIZE size;//大小
	char loc;//当前所在位置
}Tower;
// CGame4Dlg 对话框
class CGame4Dlg : public CDialogEx
{
// 构造
public:
	CGame4Dlg(CWnd* pParent = NULL);	// 标准构造函数
	~CGame4Dlg();
// 对话框数据
	enum { IDD = IDD_GAME4_DIALOG };

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
public:
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonStart();
private:
	int m_count;
	//二叉树根节点
	TreeNode*m_pHead;
	//保存着当前的汉诺塔栈区，便于下一次寻值
	stack<TreeNode*> m_stack;
	TreeNode*m_ptr;
	//图形
	vector<Tower*> m_towers;
	//当前模拟是否正在进行
	bool m_bRunning ;
private:
	//计算中间值
	int getWith(char from,char to);
	//获取下一次的运动节点
	TreeNode*getMoveableNode();
	//绘图
	void gamePaint();
	//清除内存
	void clear();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPause();
};
