
// Ex_SDI1View.h : CEx_SDI1View ��Ľӿ�
//

#pragma once


class CEx_SDI1View : public CView
{
protected: // �������л�����
	CEx_SDI1View();
	DECLARE_DYNCREATE(CEx_SDI1View)

// ����
public:
	CEx_SDI1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CEx_SDI1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Ex_SDI1View.cpp �еĵ��԰汾
inline CEx_SDI1Doc* CEx_SDI1View::GetDocument() const
   { return reinterpret_cast<CEx_SDI1Doc*>(m_pDocument); }
#endif

