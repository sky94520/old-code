
// CEx_ChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CEx_Chat.h"
#include "CEx_ChatDlg.h"
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


// CCEx_ChatDlg �Ի���



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


// CCEx_ChatDlg ��Ϣ�������

BOOL CCEx_ChatDlg::OnInitDialog()
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
	m_comboType.AddString(_T("������"));
	m_comboType.AddString(_T("�ͻ���"));
	m_comboType.SetCurSel(0);
	this->OnCbnSelchangeComboType();
	//����btn
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	//����socket

	m_asServer.m_pDlg = this;
	m_asClient.m_pDlg = this;
	//��ʼ��socket
	auto versionRequest = MAKEWORD(2,1);
	WSADATA data = {};
	auto ret = WSAStartup(versionRequest,&data);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCEx_ChatDlg::OnPaint()
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
HCURSOR CCEx_ChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCEx_ChatDlg::OnCbnSelchangeComboType()
{
	//��ȡ��ǰ����
	int nCurSelected = m_comboType.GetCurSel();
	if(nCurSelected == CB_ERR)
		return;
	CString str;
	m_comboType.GetLBText(nCurSelected,str);
	if(str == "������")
	{
		m_bServer = TRUE;
		GetDlgItem(IDC_BUTTON_RUN)->SetWindowText(L"����");
	}
	else if(str == "�ͻ���")
	{
		m_bServer = FALSE;
		GetDlgItem(IDC_BUTTON_RUN)->SetWindowText(L"����");
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
	//��ֹ�Ի���
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
		AfxMessageBox(_T("�޷�������Ϣ"));
		return;
	}
	strReceived = wstr;

	if(m_bServer)
	{
		m_listMsg.AddString(_T("���Կͻ��˷��͵���Ϣ:"));
		m_listMsg.AddString(strReceived);
	}
	else
	{
		m_listMsg.AddString(_T("���Է��������͵���Ϣ:"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_RUN)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(FALSE);
	BOOL bRet = TRUE;
	//�������������˿�Ϊ1000
	if(m_bServer)
	{
		bRet = m_asServer.Create(1000);
		//����
		m_asServer.Listen();
	}
	else//�ͻ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CCEx_ChatDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_strMsg.IsEmpty())
		return;
	int length = m_strMsg.GetLength();
	int ret = m_asClient.Send(m_strMsg.GetString(),length*2);
	if(ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��Ϣ����ʧ��"));
		return;
	}

	if(m_bServer)
	{
		m_listMsg.AddString(_T("���Է��������͵���Ϣ��"));
		m_listMsg.AddString(m_strMsg);
	}
	else
	{
		m_listMsg.AddString(_T("���Կͻ��˷��͵���Ϣ��"));
		m_listMsg.AddString(m_strMsg);
	}
	m_strMsg.Empty();
	UpdateData(FALSE);
}
