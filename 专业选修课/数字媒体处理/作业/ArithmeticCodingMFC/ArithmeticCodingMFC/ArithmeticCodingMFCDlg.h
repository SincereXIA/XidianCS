
// ArithmeticCodingMFCDlg.h: 头文件
//

#pragma once


// CArithmeticCodingMFCDlg 对话框
class CArithmeticCodingMFCDlg : public CDialogEx
{
// 构造
public:
	CArithmeticCodingMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARITHMETICCODINGMFC_DIALOG };
#endif

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
public:
	// 输入待编码字符串
	CString strinput;
	afx_msg void OnBnClickedencodebutton();
	afx_msg void OnBnClickeddecodeButton();
	void ShowStatusMsg(CString msg);
	CString m_Status_Info;
	afx_msg void OnBnClickedButtonInputfile();
	CString inputFilePath;
	CString outputFilePath;
	afx_msg void OnBnClickedButtonCompress();
	void deCompress();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedFreq();
};
