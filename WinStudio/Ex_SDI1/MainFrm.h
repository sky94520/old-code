
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
private:
	bool m_bShowMouse;//�Ƿ���ʾ�������
public:
	afx_msg void OnUpdateViewMouse(CCmdUI *pCmdUI);
	afx_msg void OnViewMouse();
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	
	CStatusBar& getStatusBar()
	{
		return m_wndStatusBar;
	}
	bool isShowMouse()const
	{
		return m_bShowMouse;
	}
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


