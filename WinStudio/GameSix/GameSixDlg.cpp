
// GameSixDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameSix.h"
#include "GameSixDlg.h"
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


// CGameSixDlg �Ի���



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


// CGameSixDlg ��Ϣ�������

BOOL CGameSixDlg::OnInitDialog()
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

	srand(time(NULL));
	int temp[] = {0,1,2,3,4,5,6,7,8};
	for(int i=0;i<9;i++)
	m_picMap[i] = temp[i];
	//���õ�ѡ��ť
	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
	
	m_bitmap.LoadBitmap(IDB_RESOURCE);

	Invalidate();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameSixDlg::OnPaint()
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
		CDialog::OnPaint();
		auto pWnd = GetDlgItem(IDC_CLIENT);
		pWnd->UpdateWindow();
		this->gamePaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGameSixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CGameSixDlg::gamePaint()
{
	auto clientDlg = GetDlgItem(IDC_CLIENT);
	CDC*pDC = clientDlg->GetDC();
	//��������cdc
	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);
	tempDC.SelectObject(m_bitmap);
	//���ݵ�ǰ���������Ⱦ
	for(int i=0;i<9;i++)
	{
		//��ȡ��Ӧ��id��
		auto id = m_picMap[i];
		//Ϊ0����ʾ������ͼƬ
		if(id == 8)
			continue;
		//��ȡ��Ⱦλ��
		int destX = i%3 * 137;
		int destY = i/3 * 137;
		//��Դλ��
		int srcX = id%3*137;
		int srcY = id/3*137;

		pDC->StretchBlt(destX,destY,137,137,&tempDC,
			srcX,srcY,137,137,SRCCOPY);
	}
	//����С������ͼ

}

void CGameSixDlg::initlize(int counts)
{
	//�����ŵ�ǰ�յ��±�����
	int emptyIndex = 8;

	while(counts > 0)
	{
		//�ҵ������ڵ�������
		auto neighborIndexs = this->getNeighborIndexs(emptyIndex);
		//������һ�������н���
		int targetZ = neighborIndexs.at(rand()%neighborIndexs.size());
		//����
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
		//x��Խ�磬��������ѭ��
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
			//������ ��������ѭ��
			if(tempZ < 0 || tempZ > 8)
				continue;
			indexs.push_back(tempX + tempY*3);
		}
	}
	return indexs;
}
void CGameSixDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡ��ǰ�ͻ�����С
	RECT clientRect;
	GetDlgItem(IDC_CLIENT)->GetClientRect(&clientRect);

	int width = 137,height=137;

	int x = point.x/width;
	int y = point.y/height;
	int z = x + y*3;
	//��������ǿգ�����Ӧ
	if(m_picMap[z] == 8)
		return;
	//�жϵ�ǰ����������Ƿ�Ϊ�գ���Ϊ�գ��򻥻�ͼƬid
	int targetZ = -1;//��Ҫ������zֵλ��
	auto indexs = this->getNeighborIndexs(z);
	auto iter = std::find_if(indexs.begin(),indexs.end(),[&](int n)
	{
		return m_picMap[n] == 8;
	});
	if(iter != indexs.end())
		targetZ = *iter;
	//�ҵ���Ӧ�Ŀհף�����л���
	if(targetZ != -1)
	{
		auto temp = m_picMap[z];
		m_picMap[z] = m_picMap[targetZ];
		m_picMap[targetZ] = temp;
		Invalidate();
	}
	//�жϴﵽӮ������
	bool bRet = true;
	for(int i=0;i<9 && bRet;i++)
	{
		if(i != m_picMap[i])
			bRet = false;
	}
	if(bRet)
	{
		CString str;
		str.Append(L"��ϲ�㣬��������\n");
		str.AppendFormat(L"����ʱ�䣺%d",m_elpased);
		//��ʾ����Ч��ͼ
		m_resultPicture.ShowWindow(TRUE);
		//���ÿ�ʼΪ�ɵ��
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		//��ʱ��0
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_elpased++;
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void CGameSixDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��⵱ǰ�ǳ��������м�
	int level = GetCheckedRadioButton(IDC_RADIO1,IDC_RADIO2);
	int counts = 0;
	if(level== IDC_RADIO1)
		counts = 40;
	else if(level == IDC_RADIO2)
		counts = 100;
	// ��ʼ��ͼƬλ��
	int temp[] = {0,1,2,3,4,5,6,7,8};
	for(int i=0;i<9;i++)
		m_picMap[i] = temp[i];

	this->initlize(counts);
	//��ʼ��ʱ��
	SetTimer(1,1000,NULL);
	//��ʼ��ť���ɵ��
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);

	Invalidate();
}
