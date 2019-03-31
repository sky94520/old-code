
// Game4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Game4.h"
#include "Game4Dlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGame4Dlg 对话框



CGame4Dlg::CGame4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGame4Dlg::IDD, pParent)
	, m_count(0),m_pHead(nullptr),m_ptr(nullptr)
	,m_bRunning(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CGame4Dlg::~CGame4Dlg()
{
	clear();
}
void CGame4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_count);
}

BEGIN_MESSAGE_MAP(CGame4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CGame4Dlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(ID_BUTTON_START, &CGame4Dlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGame4Dlg::OnBnClickedButtonPause)
END_MESSAGE_MAP()


// CGame4Dlg 消息处理程序

BOOL CGame4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	srand(time(NULL));
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGame4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGame4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		auto pWnd = GetDlgItem(IDC_CLIENT);
		pWnd->UpdateWindow();
		this->gamePaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGame4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGame4Dlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CGame4Dlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_count < 1)
	{
		AfxMessageBox(_T("盘子的数目不能小于1"));
		return;
	}
	if(m_count > 14)
	{
		AfxMessageBox(_T("盘子的数目不能大于14"));
		return;
	}
	//清除原先的变量
	this->clear();
	//todo
	GetDlgItem(ID_BUTTON_START)->EnableWindow(FALSE);
	Invalidate();
	//生成汉诺塔树
	m_pHead = new TreeNode(m_count,'A','C');
	queue<TreeNode*> queue;
	queue.push(m_pHead);

	while(!queue.empty())
	{
		auto p = queue.front();
		queue.pop();
		//判断是否应该退出循环
		if(p->n - 1 <= 0)
			break;
		//获取子节点
		auto with = getWith(p->from,p->to);
		auto leftChild = new TreeNode(p->n-1,p->from,with);
		auto rightChild = new TreeNode(p->n-1,with,p->to);
		//赋值
		leftChild->parent = p;
		rightChild->parent = p;

		p->left = leftChild;
		p->right = rightChild;
		//放入队列
		queue.push(leftChild);
		queue.push(rightChild);
	}
	//赋值
	m_ptr = m_pHead;
	//获取客户区大小
	RECT clientRect = {};
	GetDlgItem(IDC_CLIENT)->GetClientRect(&clientRect);
	auto perWidth = (clientRect.right - clientRect.left)/3.f;

	//创建图形
	for(int i = m_count;i > 0;i--)
	{
		Tower*t = new Tower();
		t->n = i;
		t->size.cy = 15.f/m_count * 10;
		t->size.cx =perWidth - (m_count - i)*t->size.cy;

		t->position.x = (m_count - i)*t->size.cy/2.f;
		t->position.y = (clientRect.bottom - clientRect.top) - (m_count - i + 1)*t->size.cy;

		long number = pow(2,sizeof(long)*4) - 1;
		t->color = rand()%number;
		t->loc = 'A';

		m_towers.push_back(t);
	}
	//设置定时器
	SetTimer(1,1000,NULL);
	//显示 按钮
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("暂停"));

	m_bRunning = true;
}
int CGame4Dlg::getWith(char from,char to)
{
	string str = "ABC";
	for(auto iter = str.begin();iter != str.end();++iter)
	{
		auto ch = *iter;
		if(ch != from && ch != to)
			return ch;
	}
	return -1;
}
TreeNode* CGame4Dlg::getMoveableNode()
{
	TreeNode*p = nullptr;
	//auto p = m_pHead;
	while(m_ptr != nullptr || !m_stack.empty())
	{
		while(m_ptr)
		{
			m_stack.push(m_ptr);
			m_ptr = m_ptr->left;
		}
		m_ptr = m_stack.top();
		m_stack.pop();

		p = m_ptr;
		//cout<<p->n<<p->from<<"-->"<<p->to<<endl;
		m_ptr = m_ptr->right;

		return p;
	}
	return nullptr;
}
void CGame4Dlg::gamePaint()
{
	//获取客户区
	auto clientDlg = GetDlgItem(IDC_CLIENT);
	RECT clientRect = {};
	clientDlg->GetClientRect(&clientRect);

	CDC*pDC = clientDlg->GetDC();
	//创建兼容cdc
	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);
	//创建背景
	//把x轴均匀分成三份
	auto perWidth = (clientRect.right - clientRect.left)/3.f;
	
	for(int i=0;i< 3;i++)
	{
		auto x = i*perWidth + clientRect.left + perWidth/2;
		auto y = 0;

		RECT r = {x,y,x+1,clientRect.bottom};
		pDC->Rectangle(&r);
	}
	RECT r = {clientRect.left,clientRect.bottom-1,clientRect.right,clientRect.bottom};
	pDC->Rectangle(&r);
	//绘制塔
	for(int i=0;i<m_towers.size();i++)
	{
		auto tower = m_towers.at(i);
		RECT r = {};
		r.left = tower->position.x;
		r.right = r.left + tower->size.cx;
		r.top = tower->position.y;
		r.bottom = r.top + tower->size.cy;

		CBrush brush(tower->color);
		pDC->SelectObject(brush);
		//绘制
		pDC->Rectangle(&r);
	}
}
void CGame4Dlg::clear()
{
	for(auto iter = m_towers.begin();iter != m_towers.end();)
	{
		auto tower = *iter;
		delete tower;
		iter = m_towers.erase(iter);
	}
	m_stack = stack<TreeNode*>();
	//清除二叉树
	m_ptr = nullptr;
	m_pHead = nullptr;
	//清除tower
}
void CGame4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TreeNode*node = this->getMoveableNode();
	if(node == nullptr)
	{
		KillTimer(1);
		AfxMessageBox(_T("演示完成"));
		//恢复按钮
		GetDlgItem(ID_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);

		return;
	}
	auto iter = std::find_if(m_towers.begin(),m_towers.end(),[&](Tower*t)
	{
		return t->n == node->n;
	});
	if(iter != m_towers.end())
	{
		//获取客户区大小
		RECT clientRect = {};
		GetDlgItem(IDC_CLIENT)->GetClientRect(&clientRect);
		auto perWidth = (clientRect.right - clientRect.left)/3.f;

		auto tower = *iter;
		char to = node->to;

		long x = 0L;

		tower->loc = to;
		tower->position.x = perWidth*(to - 'A') + tower->size.cy/2.f*(m_count - tower->n);
		//设置y轴 检测当前的to上是否存在图块
		int count = 0;
		for(auto it = m_towers.begin();it != m_towers.end();it++)
		{
			auto t = *it;
			if(t == tower)
				continue;
			if(t->loc == tower->loc)
				count ++;
		}
		tower->position.y = (clientRect.bottom - clientRect.top) - (count + 1)*tower->size.cy;
		
		Invalidate();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGame4Dlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bRunning = !m_bRunning;
	if(m_bRunning)
	{
		SetTimer(1,1000,NULL);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("暂停"));
	}
	else
	{
		KillTimer(1);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("恢复"));
	}
}
