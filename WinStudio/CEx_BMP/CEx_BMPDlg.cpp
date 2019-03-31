
// CEx_BMPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CEx_BMP.h"
#include "CEx_BMPDlg.h"
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

CAboutDlg::CAboutDlg() 
	: CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCEx_BMPDlg 对话框



CCEx_BMPDlg::CCEx_BMPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCEx_BMPDlg::IDD, pParent)
	,m_hBitmap(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCEx_BMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCEx_BMPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_IMAGE_OPEN, &CCEx_BMPDlg::OnBnClickedImageOpen)
	ON_BN_CLICKED(IDC_IMAGE_SHARP, &CCEx_BMPDlg::OnBnClickedImageSharp)
END_MESSAGE_MAP()


// CCEx_BMPDlg 消息处理程序

BOOL CCEx_BMPDlg::OnInitDialog()
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

	// 使锐化按钮一开始无效
	GetDlgItem(IDC_IMAGE_SHARP)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCEx_BMPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCEx_BMPDlg::OnPaint()
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
		CWnd*pWnd = GetDlgItem(IDC_DRAW);
		pWnd->UpdateWindow();
		this->drawPhoto();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCEx_BMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CCEx_BMPDlg::drawPhoto()
{
	if(m_hBitmap == nullptr)
		return;
	CBitmap bitmap;
	bitmap.Attach(m_hBitmap);
	BITMAP bm;
	bitmap.GetObject(sizeof(BITMAP),&bm);
	//高宽之比
	float scale = (float)bm.bmHeight/bm.bmWidth;
	CWnd*pWnd = GetDlgItem(IDC_DRAW);
	CDC*pDc = pWnd->GetDC();
	//调整图像大小
	CRect rcClient;
	int nWidth,nHeight,nX,nY;
	pWnd->GetClientRect(&rcClient);
	nWidth = rcClient.Width();
	nHeight = nWidth*scale;
	nX = 0;
	nY = (rcClient.Height() - nHeight)/2;

	if(nHeight > rcClient.Height())
	{
		nHeight = rcClient.Height();
		nWidth = nHeight/scale;
		nX = (rcClient.Width() - nWidth)/2;
		nY = 0;
	}
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDc);
	CBitmap*pOldbmp = dcMem.SelectObject(&bitmap);
	rcClient.DeflateRect(-1,-1);
	pDc->Rectangle(rcClient);
	pDc->StretchBlt(nX,nY,nWidth,nHeight,&dcMem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	dcMem.SelectObject(pOldbmp);
}


void CCEx_BMPDlg::OnBnClickedImageOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	static LPCTSTR BASED_CODE szFliter = L"图片文件(*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFliter);
	if(IDOK != dlg.DoModal())
		return ;
	m_hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dlg.GetPathName(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	//使锐化按钮有效
	GetDlgItem(IDC_IMAGE_SHARP)->EnableWindow(TRUE);
	Invalidate();
}


void CCEx_BMPDlg::OnBnClickedImageSharp()
{
	// TODO: 在此添加控件通知处理程序代码
	int sharpLaplacian[9] = {-1,-1,-1,-1,9,-1,-1,-1,-1};
	CWnd*pWnd = GetDlgItem(IDC_DRAW);
	CDC*pDC = pWnd->GetDC();
	pWnd->UpdateWindow();

	CRect rcClient;
	pWnd->GetClientRect(&rcClient);
	int nWidth = rcClient.Width();
	int nHeight = rcClient.Height();
	COLORREF bkPixel[400][300];
	//备份原来的数据
	for(int bi=0;bi<nWidth;bi++)
		for(int bj=0;bj<nHeight;bj++)
			bkPixel[bi][bj] = pDC->GetPixel(bi,bj);
	int i,j;
	for(i=1;i<nWidth-1;i++)
	{
		for(j=1;j<nHeight-1;j++)
		{
			int rr=0,gg=0,bb=0,index=0;
			for(int col=-1;col<=1;col++)
			{
				for(int row=-1;row<=1;row++)
				{
					COLORREF clr = bkPixel[i+row][j+col];
					rr += GetRValue(clr)*sharpLaplacian[index];
					gg += GetGValue(clr)*sharpLaplacian[index];
					bb += GetBValue(clr)*sharpLaplacian[index];
				}
			}
			//处理溢出点
			if(rr > 255) rr = 255;
			else if(rr < 0) rr = -rr;
			if(gg > 255) gg = 255;
			else if(gg < 0) gg = -gg;

			if(bb > 255) bb = 255;
			else if(bb < 0) bb = -bb;
			pDC->SetPixelV(i,j,RGB(rr,gg,bb));
		}
	}
}
