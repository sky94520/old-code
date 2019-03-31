
// ex5View.cpp : Cex5View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ex5.h"
#endif

#include "ex5Doc.h"
#include "ex5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cex5View

IMPLEMENT_DYNCREATE(Cex5View, CView)

BEGIN_MESSAGE_MAP(Cex5View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Cex5View 构造/析构

Cex5View::Cex5View()
{
	// TODO: 在此处添加构造代码

}

Cex5View::~Cex5View()
{
}

BOOL Cex5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cex5View 绘制

void Cex5View::OnDraw(CDC* pDC)
{
	Cex5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	
	pDC->Ellipse(10,10,110,110);
	pDC->Rectangle(200,10,280,60);
	pDC->TextOut(100,100,L"南京工程学院",6);
}


// Cex5View 打印

BOOL Cex5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cex5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cex5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// Cex5View 诊断

#ifdef _DEBUG
void Cex5View::AssertValid() const
{
	CView::AssertValid();
}

void Cex5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cex5Doc* Cex5View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cex5Doc)));
	return (Cex5Doc*)m_pDocument;
}
#endif //_DEBUG


// Cex5View 消息处理程序
