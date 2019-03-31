
// Ex_SDI1View.cpp : CEx_SDI1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Ex_SDI1.h"
#endif

#include "Ex_SDI1Doc.h"
#include "Ex_SDI1View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx_SDI1View

IMPLEMENT_DYNCREATE(CEx_SDI1View, CView)

BEGIN_MESSAGE_MAP(CEx_SDI1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CEx_SDI1View ����/����

CEx_SDI1View::CEx_SDI1View()
{
	// TODO: �ڴ˴���ӹ������

}

CEx_SDI1View::~CEx_SDI1View()
{
}

BOOL CEx_SDI1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CEx_SDI1View ����

void CEx_SDI1View::OnDraw(CDC* /*pDC*/)
{
	CEx_SDI1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CEx_SDI1View ��ӡ

BOOL CEx_SDI1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CEx_SDI1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CEx_SDI1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CEx_SDI1View ���

#ifdef _DEBUG
void CEx_SDI1View::AssertValid() const
{
	CView::AssertValid();
}

void CEx_SDI1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx_SDI1Doc* CEx_SDI1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx_SDI1Doc)));
	return (CEx_SDI1Doc*)m_pDocument;
}
#endif //_DEBUG


// CEx_SDI1View ��Ϣ�������


void CEx_SDI1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡFrame��ָ��
	CMainFrame*mainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar&statusBar = mainFrame->getStatusBar();
	if(mainFrame->isShowMouse())
	{
		CString str;
		str.Format(L"x=%d,y=%d",point.x,point.y);
		statusBar.SetPaneText(0,str.GetString());
	}

	CView::OnMouseMove(nFlags, point);
}
