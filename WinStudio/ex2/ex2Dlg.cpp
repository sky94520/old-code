
// ex2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ex2.h"
#include "ex2Dlg.h"
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


// Cex2Dlg 对话框



Cex2Dlg::Cex2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cex2Dlg::IDD, pParent)
	, r1(0)
	, r2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cex2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, r1);
	DDX_Radio(pDX, IDC_RADIO4, r2);
	DDX_Control(pDX, IDC_CHECK1, c1);
	DDX_Control(pDX, IDC_CHECK2, c2);
	DDX_Control(pDX, IDC_CHECK3, c3);
}

BEGIN_MESSAGE_MAP(Cex2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cex2Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Cex2Dlg 消息处理程序

BOOL Cex2Dlg::OnInitDialog()
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
	this->CheckRadioButton(IDC_RADIO1,IDC_RADIO3,IDC_RADIO2);
	this->CheckRadioButton(IDC_RADIO4,IDC_RADIO5,IDC_RADIO4);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cex2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cex2Dlg::OnPaint()
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
HCURSOR Cex2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cex2Dlg::OnBnClickedOk()
{
	CString str1,str2,str;
	//确定年龄
	UpdateData(true);
	switch(r1)
	{
	case 0:GetDlgItemText(IDC_RADIO1,str1);break;
	case 1:GetDlgItemText(IDC_RADIO2,str1);break;
	case 2:GetDlgItemText(IDC_RADIO3,str1);break;
	}
	str1.Append(L"\n");
	//确定性别
	switch(r2)
	{
	case 0:GetDlgItemText(IDC_RADIO4,str2);break;
	case 1:GetDlgItemText(IDC_RADIO5,str2);break;
	}
	str2.Append(L"\n");

	str.Append(str1);
	str.Append(str2);
	//确定爱好
	if(c1.GetCheck())
	{
		CString text;
		GetDlgItemText(IDC_CHECK1,text);
		str.Append(text);
		str.Append(L",");
	}
	if(c2.GetCheck())
	{
		CString text;
		GetDlgItemText(IDC_CHECK2,text);
		str.Append(text);
		str.Append(L",");
	}
	if(c3.GetCheck())
	{
		CString text;
		GetDlgItemText(IDC_CHECK3,text);
		str.Append(text);
	}
	this->MessageBox(str);
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
