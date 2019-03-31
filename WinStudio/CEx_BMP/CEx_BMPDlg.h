
// CEx_BMPDlg.h : 头文件
//

#pragma once


// CCEx_BMPDlg 对话框
class CCEx_BMPDlg : public CDialogEx
{
// 构造
public:
	CCEx_BMPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CEX_BMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	HBITMAP m_hBitmap;
	void drawPhoto();
public:
	afx_msg void OnBnClickedImageOpen();
	afx_msg void OnBnClickedImageSharp();
};
