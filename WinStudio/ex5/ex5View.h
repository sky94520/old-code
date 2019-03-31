
// ex5View.h : Cex5View 类的接口
//

#pragma once


class Cex5View : public CView
{
protected: // 仅从序列化创建
	Cex5View();
	DECLARE_DYNCREATE(Cex5View)

// 特性
public:
	Cex5Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Cex5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ex5View.cpp 中的调试版本
inline Cex5Doc* Cex5View::GetDocument() const
   { return reinterpret_cast<Cex5Doc*>(m_pDocument); }
#endif

