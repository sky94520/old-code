
// CEx_ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CEx_Chat.h"
#include "CEx_ChatDlg.h"
#include "afxdialogex.h"

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


// CCEx_ChatDlg 对话框



CCEx_ChatDlg::CCEx_ChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCEx_ChatDlg::IDD, pParent)
	, m_strMsg(_T("")),m_bServer(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CCEx_ChatDlg::~CCEx_ChatDlg()
{
	WSACleanup();
}
void CCEx_ChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
}

BEGIN_MESSAGE_MAP(CCEx_ChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CCEx_ChatDlg::OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CCEx_ChatDlg::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDCANCEL, &CCEx_ChatDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CCEx_ChatDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CCEx_ChatDlg 消息处理程序

BOOL CCEx_ChatDlg::OnInitDialog()
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
	m_comboType.AddString(_T("服务器"));
	m_comboType.AddString(_T("客户端"));
	m_comboType.SetCurSel(0);
	this->OnCbnSelchangeComboType();
	//设置btn
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	//设置socket

	m_asServer.m_pDlg = this;
	m_asClient.m_pDlg = this;
	//初始化socket
	auto versionRequest = MAKEWORD(2,1);
	WSADATA data = {};
	auto ret = WSAStartup(versionRequest,&data);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCEx_ChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCEx_ChatDlg::OnPaint()
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
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCEx_ChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCEx_ChatDlg::OnCbnSelchangeComboType()
{
	//获取当前索引
	int nCurSelected = m_comboType.GetCurSel();
	if(nCurSelected == CB_ERR)
		return;
	CString str;
	m_comboType.GetLBText(nCurSelected,str);
	if(str == "服务器")
	{
		m_bServer = TRUE;
		GetDlgItem(IDC_BUTTON_RUN)->SetWindowText(L"运行");
	}
	else if(str == "客户端")
	{
		m_bServer = FALSE;
		GetDlgItem(IDC_BUTTON_RUN)->SetWindowText(L"连接");
	}
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
}
void CCEx_ChatDlg::onAccept()
{
	m_asServer.Accept(m_asClient);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
}
void CCEx_ChatDlg::onClose()
{
	if(m_bServer)
		m_asServer.Close();
	else
		m_asClient.Close();
	//终止对话框
	OnCancel();
	CDialogEx::OnClose();
}
void CCEx_ChatDlg::onConnect()
{
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
}
void CCEx_ChatDlg::onReceive()
{
	LPWSTR wstr = new WCHAR[1025];
	//char*wstr = new char[1025];
	CString strReceived;

	memset(wstr,'\0',sizeof(wstr));

	auto ret = m_asClient.Receive(wstr,1024);
	wstr[ret/2] = '\0';

	if(ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("无法接收消息"));
		return;
	}
	strReceived = wstr;

	if(m_bServer)
	{
		m_listMsg.AddString(_T("来自客户端发送的消息:"));
		m_listMsg.AddString(strReceived);
	}
	else
	{
		m_listMsg.AddString(_T("来自服务器发送的消息:"));
		m_listMsg.AddString(strReceived);
	}
	delete[] wstr;
}
void CCEx_ChatDlg::onSend()
{
}
void CCEx_ChatDlg::doClose()
{
	onClose();
}
void CCEx_ChatDlg::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON_RUN)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(FALSE);
	BOOL bRet = TRUE;
	//创建服务器，端口为1000
	if(m_bServer)
	{
		bRet = m_asServer.Create(1000);
		//侦听
		m_asServer.Listen();
	}
	else//客户机
	{
		bRet = m_asClient.Create();
		m_asClient.Connect(_T("localhost"),1000);
	}
	if(bRet == FALSE)
	{
		auto errorCode = GetLastError();
		MessageBox(L"error");
	}
}


void CCEx_ChatDlg::OnBnClickedCancel()
{
	doClose();
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CCEx_ChatDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_strMsg.IsEmpty())
		return;
	int length = m_strMsg.GetLength();
	int ret = m_asClient.Send(m_strMsg.GetString(),length*2);
	if(ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("消息发送失败"));
		return;
	}

	if(m_bServer)
	{
		m_listMsg.AddString(_T("来自服务器发送的消息："));
		m_listMsg.AddString(m_strMsg);
	}
	else
	{
		m_listMsg.AddString(_T("来自客户端发送的消息："));
		m_listMsg.AddString(m_strMsg);
	}
	m_strMsg.Empty();
	UpdateData(FALSE);
}
