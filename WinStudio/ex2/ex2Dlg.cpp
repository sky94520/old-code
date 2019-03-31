
// ex2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ex2.h"
#include "ex2Dlg.h"
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cex2Dlg �Ի���



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


// Cex2Dlg ��Ϣ�������

BOOL Cex2Dlg::OnInitDialog()
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
	this->CheckRadioButton(IDC_RADIO1,IDC_RADIO3,IDC_RADIO2);
	this->CheckRadioButton(IDC_RADIO4,IDC_RADIO5,IDC_RADIO4);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cex2Dlg::OnPaint()
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
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cex2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cex2Dlg::OnBnClickedOk()
{
	CString str1,str2,str;
	//ȷ������
	UpdateData(true);
	switch(r1)
	{
	case 0:GetDlgItemText(IDC_RADIO1,str1);break;
	case 1:GetDlgItemText(IDC_RADIO2,str1);break;
	case 2:GetDlgItemText(IDC_RADIO3,str1);break;
	}
	str1.Append(L"\n");
	//ȷ���Ա�
	switch(r2)
	{
	case 0:GetDlgItemText(IDC_RADIO4,str2);break;
	case 1:GetDlgItemText(IDC_RADIO5,str2);break;
	}
	str2.Append(L"\n");

	str.Append(str1);
	str.Append(str2);
	//ȷ������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
