
// Ex_SDI1View.cpp : CEx_SDI1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CEx_SDI1View 构造/析构

CEx_SDI1View::CEx_SDI1View()
{
	// TODO: 在此处添加构造代码

}

CEx_SDI1View::~CEx_SDI1View()
{
}

BOOL CEx_SDI1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CEx_SDI1View 绘制

void CEx_SDI1View::OnDraw(CDC* /*pDC*/)
{
	CEx_SDI1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CEx_SDI1View 打印

BOOL CEx_SDI1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEx_SDI1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CEx_SDI1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CEx_SDI1View 诊断

#ifdef _DEBUG
void CEx_SDI1View::AssertValid() const
{
	CView::AssertValid();
}

void CEx_SDI1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx_SDI1Doc* CEx_SDI1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx_SDI1Doc)));
	return (CEx_SDI1Doc*)m_pDocument;
}
#endif //_DEBUG


// CEx_SDI1View 消息处理程序


void CEx_SDI1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//获取Frame的指针
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
