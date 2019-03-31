
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
protected:
	bool m_bShowMousePos;
public:
	afx_msg void OnMousePos();
	afx_msg void OnUpdateMousePos(CCmdUI *pCmdUI);
public:
	bool isShowMousePos(){return m_bShowMousePos;}
	CStatusBar* getStatusBar(){return &m_wndStatusBar;}
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


