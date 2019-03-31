
// Game4Dlg.h : ͷ�ļ�
//

#pragma once
#include<stack>
#include<queue>
#include<vector>
#include<cmath>
#include<ctime>
using namespace std;
//��ŵ���ڵ�
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
//��ŵ�����ƽڵ�
typedef struct Tower
{
	int n;//ָʾ����ڼ���ͼ��
	POINT position;//λ������
	COLORREF color;//������ɫ
	SIZE size;//��С
	char loc;//��ǰ����λ��
}Tower;
// CGame4Dlg �Ի���
class CGame4Dlg : public CDialogEx
{
// ����
public:
	CGame4Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CGame4Dlg();
// �Ի�������
	enum { IDD = IDD_GAME4_DIALOG };

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
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonStart();
private:
	int m_count;
	//���������ڵ�
	TreeNode*m_pHead;
	//�����ŵ�ǰ�ĺ�ŵ��ջ����������һ��Ѱֵ
	stack<TreeNode*> m_stack;
	TreeNode*m_ptr;
	//ͼ��
	vector<Tower*> m_towers;
	//��ǰģ���Ƿ����ڽ���
	bool m_bRunning ;
private:
	//�����м�ֵ
	int getWith(char from,char to);
	//��ȡ��һ�ε��˶��ڵ�
	TreeNode*getMoveableNode();
	//��ͼ
	void gamePaint();
	//����ڴ�
	void clear();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPause();
};
