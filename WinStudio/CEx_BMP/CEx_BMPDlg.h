
// CEx_BMPDlg.h : ͷ�ļ�
//

#pragma once


// CCEx_BMPDlg �Ի���
class CCEx_BMPDlg : public CDialogEx
{
// ����
public:
	CCEx_BMPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CEX_BMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
