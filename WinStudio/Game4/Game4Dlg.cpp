
// Game4Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Game4.h"
#include "Game4Dlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CGame4Dlg �Ի���



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


// CGame4Dlg ��Ϣ�������

BOOL CGame4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	srand(time(NULL));
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGame4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGame4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGame4Dlg::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void CGame4Dlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_count < 1)
	{
		AfxMessageBox(_T("���ӵ���Ŀ����С��1"));
		return;
	}
	if(m_count > 14)
	{
		AfxMessageBox(_T("���ӵ���Ŀ���ܴ���14"));
		return;
	}
	//���ԭ�ȵı���
	this->clear();
	//todo
	GetDlgItem(ID_BUTTON_START)->EnableWindow(FALSE);
	Invalidate();
	//���ɺ�ŵ����
	m_pHead = new TreeNode(m_count,'A','C');
	queue<TreeNode*> queue;
	queue.push(m_pHead);

	while(!queue.empty())
	{
		auto p = queue.front();
		queue.pop();
		//�ж��Ƿ�Ӧ���˳�ѭ��
		if(p->n - 1 <= 0)
			break;
		//��ȡ�ӽڵ�
		auto with = getWith(p->from,p->to);
		auto leftChild = new TreeNode(p->n-1,p->from,with);
		auto rightChild = new TreeNode(p->n-1,with,p->to);
		//��ֵ
		leftChild->parent = p;
		rightChild->parent = p;

		p->left = leftChild;
		p->right = rightChild;
		//�������
		queue.push(leftChild);
		queue.push(rightChild);
	}
	//��ֵ
	m_ptr = m_pHead;
	//��ȡ�ͻ�����С
	RECT clientRect = {};
	GetDlgItem(IDC_CLIENT)->GetClientRect(&clientRect);
	auto perWidth = (clientRect.right - clientRect.left)/3.f;

	//����ͼ��
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
	//���ö�ʱ��
	SetTimer(1,1000,NULL);
	//��ʾ ��ť
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("��ͣ"));

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
	//��ȡ�ͻ���
	auto clientDlg = GetDlgItem(IDC_CLIENT);
	RECT clientRect = {};
	clientDlg->GetClientRect(&clientRect);

	CDC*pDC = clientDlg->GetDC();
	//��������cdc
	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);
	//��������
	//��x����ȷֳ�����
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
	//������
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
		//����
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
	//���������
	m_ptr = nullptr;
	m_pHead = nullptr;
	//���tower
}
void CGame4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TreeNode*node = this->getMoveableNode();
	if(node == nullptr)
	{
		KillTimer(1);
		AfxMessageBox(_T("��ʾ���"));
		//�ָ���ť
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
		//��ȡ�ͻ�����С
		RECT clientRect = {};
		GetDlgItem(IDC_CLIENT)->GetClientRect(&clientRect);
		auto perWidth = (clientRect.right - clientRect.left)/3.f;

		auto tower = *iter;
		char to = node->to;

		long x = 0L;

		tower->loc = to;
		tower->position.x = perWidth*(to - 'A') + tower->size.cy/2.f*(m_count - tower->n);
		//����y�� ��⵱ǰ��to���Ƿ����ͼ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bRunning = !m_bRunning;
	if(m_bRunning)
	{
		SetTimer(1,1000,NULL);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("��ͣ"));
	}
	else
	{
		KillTimer(1);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("�ָ�"));
	}
}
