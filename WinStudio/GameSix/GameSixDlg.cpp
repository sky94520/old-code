
// GameSixDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameSix.h"
#include "GameSixDlg.h"
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


// CGameSixDlg 对话框



CGameSixDlg::CGameSixDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameSixDlg::IDD, pParent)
	, m_elpased(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CGameSixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIMER, m_elpased);
	DDX_Control(pDX, IDC_PICTURE, m_resultPicture);
}

BEGIN_MESSAGE_MAP(CGameSixDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameSixDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CGameSixDlg 消息处理程序

BOOL CGameSixDlg::OnInitDialog()
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

	srand(time(NULL));
	int temp[] = {0,1,2,3,4,5,6,7,8};
	for(int i=0;i<9;i++)
	m_picMap[i] = temp[i];
	//设置单选按钮
	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
	
	m_bitmap.LoadBitmap(IDB_RESOURCE);

	Invalidate();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGameSixDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGameSixDlg::OnPaint()
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
		CDialog::OnPaint();
		auto pWnd = GetDlgItem(IDC_CLIENT);
		pWnd->UpdateWindow();
		this->gamePaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameSixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CGameSixDlg::gamePaint()
{
	auto clientDlg = GetDlgItem(IDC_CLIENT);
	CDC*pDC = clientDlg->GetDC();
	//创建兼容cdc
	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);
	tempDC.SelectObject(m_bitmap);
	//根据当前数组进行渲染
	for(int i=0;i<9;i++)
	{
		//获取对应的id数
		auto id = m_picMap[i];
		//为0，表示不存在图片
		if(id == 8)
			continue;
		//获取渲染位置
		int destX = i%3 * 137;
		int destY = i/3 * 137;
		//资源位置
		int srcX = id%3*137;
		int srcY = id/3*137;

		pDC->StretchBlt(destX,destY,137,137,&tempDC,
			srcX,srcY,137,137,SRCCOPY);
	}
	//创建小的完整图

}

void CGameSixDlg::initlize(int counts)
{
	//保存着当前空的下标所在
	int emptyIndex = 8;

	while(counts > 0)
	{
		//找到它相邻的所有数
		auto neighborIndexs = this->getNeighborIndexs(emptyIndex);
		//随机抽出一个，进行交换
		int targetZ = neighborIndexs.at(rand()%neighborIndexs.size());
		//交换
		int temp = m_picMap[emptyIndex];
		m_picMap[emptyIndex] = m_picMap[targetZ];
		m_picMap[targetZ] = temp;

		emptyIndex = targetZ;

		counts --;
	}
}
vector<int> CGameSixDlg::getNeighborIndexs(int index)
{
	vector<int> indexs;

	int x = index%3;
	int y = index/3;

	int markX[] = {0,-1,1};
	for(int i=0;i<3;i++)
	{
		//x轴越界，跳过本次循环
		auto tempX = x + markX[i];
		if(tempX <0 || tempX > 2)
			continue;

		vector<int> markY;
		if(markX[i] == 0)
		{
			markY.push_back(-1);
			markY.push_back(1);
		}
		else
			markY.push_back(0);
		for(int j=0;j<markY.size();j++)
		{
			auto tempY = y + markY.at(j);
			if(tempY < 0 || tempY > 2)
				continue;
			auto tempZ = tempX + tempY*3;
			//若出界 跳过本次循环
			if(tempZ < 0 || tempZ > 8)
				continue;
			indexs.push_back(tempX + tempY*3);
		}
	}
	return indexs;
}
void CGameSixDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//获取当前客户区大小
	RECT clientRect;
	GetDlgItem(IDC_CLIENT)->GetClientRect(&clientRect);

	int width = 137,height=137;

	int x = point.x/width;
	int y = point.y/height;
	int z = x + y*3;
	//若点击的是空，则不响应
	if(m_picMap[z] == 8)
		return;
	//判断当前点击处附近是否为空，若为空，则互换图片id
	int targetZ = -1;//将要交换的z值位置
	auto indexs = this->getNeighborIndexs(z);
	auto iter = std::find_if(indexs.begin(),indexs.end(),[&](int n)
	{
		return m_picMap[n] == 8;
	});
	if(iter != indexs.end())
		targetZ = *iter;
	//找到对应的空白，则进行互换
	if(targetZ != -1)
	{
		auto temp = m_picMap[z];
		m_picMap[z] = m_picMap[targetZ];
		m_picMap[targetZ] = temp;
		Invalidate();
	}
	//判断达到赢的条件
	bool bRet = true;
	for(int i=0;i<9 && bRet;i++)
	{
		if(i != m_picMap[i])
			bRet = false;
	}
	if(bRet)
	{
		CString str;
		str.Append(L"恭喜你，过关啦！\n");
		str.AppendFormat(L"消耗时间：%d",m_elpased);
		//显示最终效果图
		m_resultPicture.ShowWindow(TRUE);
		//设置开始为可点击
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		//计时清0
		KillTimer(1);
		m_elpased = 0;
		UpdateData(FALSE);

		AfxMessageBox(str);
		
		m_resultPicture.ShowWindow(FALSE);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGameSixDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_elpased++;
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void CGameSixDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码

	//检测当前是初级还是中级
	int level = GetCheckedRadioButton(IDC_RADIO1,IDC_RADIO2);
	int counts = 0;
	if(level== IDC_RADIO1)
		counts = 40;
	else if(level == IDC_RADIO2)
		counts = 100;
	// 初始化图片位置
	int temp[] = {0,1,2,3,4,5,6,7,8};
	for(int i=0;i<9;i++)
		m_picMap[i] = temp[i];

	this->initlize(counts);
	//开始定时器
	SetTimer(1,1000,NULL);
	//开始按钮不可点击
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);

	Invalidate();
}
