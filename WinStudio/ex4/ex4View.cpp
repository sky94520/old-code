
// ex4View.cpp : Cex4View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ex4.h"
#endif

#include "ex4Doc.h"
#include "ex4View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cex4View

IMPLEMENT_DYNCREATE(Cex4View, CView)

BEGIN_MESSAGE_MAP(Cex4View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
//	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// Cex4View ����/����

Cex4View::Cex4View()
{
	// TODO: �ڴ˴���ӹ������

}

Cex4View::~Cex4View()
{
}

BOOL Cex4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// Cex4View ����

void Cex4View::OnDraw(CDC* /*pDC*/)
{
	Cex4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// Cex4View ��ӡ

BOOL Cex4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Cex4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void Cex4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// Cex4View ���

#ifdef _DEBUG
void Cex4View::AssertValid() const
{
	CView::AssertValid();
}

void Cex4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cex4Doc* Cex4View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cex4Doc)));
	return (Cex4Doc*)m_pDocument;
}
#endif //_DEBUG


// Cex4View ��Ϣ�������


void Cex4View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame*mainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar*statusBar = mainFrame->getStatusBar();
	if(mainFrame->isShowMousePos())
	{
		CString text;
		text.Format(L"x:%d,y%d",point.x,point.y);
		statusBar->SetPaneText(0,text);
	}

	CView::OnMouseMove(nFlags, point);
}


//void Cex4View::OnContextMenu(CWnd* pWnd, CPoint point)
//{
//	// TODO: �ڴ˴������Ϣ����������
//}
