
// ex4View.cpp : Cex4View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
//	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// Cex4View 构造/析构

Cex4View::Cex4View()
{
	// TODO: 在此处添加构造代码

}

Cex4View::~Cex4View()
{
}

BOOL Cex4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cex4View 绘制

void Cex4View::OnDraw(CDC* /*pDC*/)
{
	Cex4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// Cex4View 打印

BOOL Cex4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cex4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cex4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// Cex4View 诊断

#ifdef _DEBUG
void Cex4View::AssertValid() const
{
	CView::AssertValid();
}

void Cex4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cex4Doc* Cex4View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cex4Doc)));
	return (Cex4Doc*)m_pDocument;
}
#endif //_DEBUG


// Cex4View 消息处理程序


void Cex4View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
//	// TODO: 在此处添加消息处理程序代码
//}
