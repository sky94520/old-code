
// CEx_BMPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CEx_BMP.h"
#include "CEx_BMPDlg.h"
#include "afxdialogex.h"

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


// CCEx_BMPDlg �Ի���



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


// CCEx_BMPDlg ��Ϣ�������

BOOL CCEx_BMPDlg::OnInitDialog()
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

	// ʹ�񻯰�ťһ��ʼ��Ч
	GetDlgItem(IDC_IMAGE_SHARP)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCEx_BMPDlg::OnPaint()
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
		CWnd*pWnd = GetDlgItem(IDC_DRAW);
		pWnd->UpdateWindow();
		this->drawPhoto();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	//�߿�֮��
	float scale = (float)bm.bmHeight/bm.bmWidth;
	CWnd*pWnd = GetDlgItem(IDC_DRAW);
	CDC*pDc = pWnd->GetDC();
	//����ͼ���С
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static LPCTSTR BASED_CODE szFliter = L"ͼƬ�ļ�(*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFliter);
	if(IDOK != dlg.DoModal())
		return ;
	m_hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dlg.GetPathName(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	//ʹ�񻯰�ť��Ч
	GetDlgItem(IDC_IMAGE_SHARP)->EnableWindow(TRUE);
	Invalidate();
}


void CCEx_BMPDlg::OnBnClickedImageSharp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sharpLaplacian[9] = {-1,-1,-1,-1,9,-1,-1,-1,-1};
	CWnd*pWnd = GetDlgItem(IDC_DRAW);
	CDC*pDC = pWnd->GetDC();
	pWnd->UpdateWindow();

	CRect rcClient;
	pWnd->GetClientRect(&rcClient);
	int nWidth = rcClient.Width();
	int nHeight = rcClient.Height();
	COLORREF bkPixel[400][300];
	//����ԭ��������
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
			//���������
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
