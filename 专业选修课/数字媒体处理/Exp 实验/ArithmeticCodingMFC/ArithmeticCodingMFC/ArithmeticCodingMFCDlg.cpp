
// ArithmeticCodingMFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ArithmeticCodingMFC.h"
#include "ArithmeticCodingMFCDlg.h"
#include "afxdialogex.h"
#include "ACC.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <bitset>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char fileBuffer[100000];


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CArithmeticCodingMFCDlg 对话框



CArithmeticCodingMFCDlg::CArithmeticCodingMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARITHMETICCODINGMFC_DIALOG, pParent)
	, strinput(_T(""))
	, m_Status_Info(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	inputFilePath = _T("");
	outputFilePath = _T("");
}

void CArithmeticCodingMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STRInput, strinput);
	DDX_Text(pDX, IDC_Status_Info, m_Status_Info);
}

BEGIN_MESSAGE_MAP(CArithmeticCodingMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_encode_button, &CArithmeticCodingMFCDlg::OnBnClickedencodebutton)
	ON_BN_CLICKED(IDC_decode_BUTTON, &CArithmeticCodingMFCDlg::OnBnClickeddecodeButton)
	ON_BN_CLICKED(IDC_BUTTON_InputFile, &CArithmeticCodingMFCDlg::OnBnClickedButtonInputfile)
	ON_BN_CLICKED(IDC_BUTTON_Compress, &CArithmeticCodingMFCDlg::OnBnClickedButtonCompress)
	ON_BN_CLICKED(IDC_BUTTON2, &CArithmeticCodingMFCDlg::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_Freq, &CArithmeticCodingMFCDlg::OnStnClickedFreq)
END_MESSAGE_MAP()


// CArithmeticCodingMFCDlg 消息处理程序

BOOL CArithmeticCodingMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CArithmeticCodingMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CArithmeticCodingMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CArithmeticCodingMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString byte_to_hex(const char* str, int len) //transfer string to hex-string
{
	std::string result = "";
	std::string tmp;
	std::stringstream ss;
	len = len > 10000 ? 10000 : len;
	for (int i = 0; i <len; i++)
	{
		ss << std::setfill('0')<< std::setw(2) << std::hex << (unsigned int)(unsigned char)str[i] << std::endl;
		ss >> tmp;
		result += tmp;
		result += " ";
	}
	CString cstr(result.c_str());
	return cstr;
}

double byte_to_double(const char* str, int len) {

	len = len > 50 ? 50 : len;
	double res = 0.0;
	int p = 1;
	for (int i = 0; i < len; i++)
	{
		if (str[i] & 0b00000001) res += pow(0.5, p);
		p++;
		if (str[i] & 0b00000010) res += pow(0.5, p);
		p++;
		if (str[i] & 0b00000100) res += pow(0.5, p);
		p++;
		if (str[i] & 0b00001000) res += pow(0.5, p);
		p++;
		if (str[i] & 0b00010000) res += pow(0.5, p);
		p++;
		if (str[i] & 0b00100000) res += pow(0.5, p);
		p++;
		if (str[i] & 0b01000000) res += pow(0.5, p);
		p++;
		if (str[i] & 0b10000000) res += pow(0.5, p);
		p++;
	}
	return res;
}



void CArithmeticCodingMFCDlg::OnBnClickedencodebutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	CString text;
	USES_CONVERSION;
	GetDlgItemText(IDC_STRInput, text);
	int strLength = text.GetLength()+1;
	char *str = new char[strLength];
	strncpy_s(str, strLength, text, strLength);
	encode((BYTE *)str, strLength);

	// 频谱输出
	CString freqstr("");
	CString tmp;
	for (int i = 0; i < No_of_symbols; i++) {
		tmp.Format(_T("%x:\t%d\n"), i - 1, freq[i]);
		freqstr += tmp;
	}
	SetDlgItemText(IDC_Freq, freqstr);

	char *destr = new char[strLength];
	CString show_code = byte_to_hex(code, code_index);
	//AfxMessageBox(show_code);
	CString msg;
	msg.Format(_T("原始长度：%d\n编码长度：%d"), strLength, code_index);
	AfxMessageBox(msg);
	double num = byte_to_double(code, code_index);
	msg.Format(_T("算术压缩结果:\n%.30lf"), num);

	AfxMessageBox(msg);
	
	SetDlgItemText(IDC_STRoutput, show_code);
}


void CArithmeticCodingMFCDlg::OnBnClickeddecodeButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowStatusMsg(_T("解码中..."));
	decode();
	ShowStatusMsg(_T("解码完成！"));
	CString res = CString((char *)DecodeRS);
	SetDlgItemText(IDC_STRoutput, res);
}

void CArithmeticCodingMFCDlg::ShowStatusMsg(CString msg) {
	SetDlgItemText(IDC_Status_Info, msg);
}


void CArithmeticCodingMFCDlg::OnBnClickedButtonInputfile()
{
	BOOL isOpen = TRUE;		//是否打开(否则为保存)
	CString defaultDir = _T("");	//默认打开的文件路径
	CString fileName = _T("");			//默认打开的文件名
	CString filter = _T("");	//文件过虑的类型
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = _T("E:\\FileTest\\test.doc");
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	inputFilePath = filePath;
	SetDlgItemText(IDC_EDIT_InputFile, filePath);
}


CString GetFileType(CString filename)
{
	CString type;
	filename.MakeReverse();//颠倒字符串顺序
	int pos = filename.Find('.');//找到小数点的位置
	type = filename.Left(pos);//获取小数点左边的字符串
	type.MakeReverse();//颠倒字符串顺序
	return type;
}


void CArithmeticCodingMFCDlg::OnBnClickedButtonCompress()
{
	// 点击压缩\解压按钮
	// 刷新选定的文件信息
	UpdateData(TRUE);
	if (inputFilePath == "") return;
	// 判断是否为待解压文件
	if (GetFileType(inputFilePath) == "acc") {
		ShowStatusMsg(_T("ACC 文件"));
		deCompress(); // 执行解压流程
		return;
	}
	/**
	*	执行压缩流程
	*/
	char * buffer;
	// 二进制方式打开
	std::ifstream inputfile(inputFilePath, std::ios::binary|std::ios::ate);
	auto size = inputfile.tellg();  // 获取文件大小
	inputfile.seekg(0, std::ios::beg);  // 返回文件头

	buffer = new char[size];	// 建立缓冲区
	inputfile.read(buffer, size);
	/*
		压缩后的编码存入 code[]
	*/
	encode((BYTE *)buffer, size);

	// 频谱输出
	CString freqstr("");
	CString tmp;
	for (int i = 1; i < No_of_symbols; i++) {
		tmp.Format(_T("%x:\t%d\n"),i-1, freq[i]);
		freqstr += tmp;
	}
	SetDlgItemText(IDC_Freq, freqstr);

	// 压缩后的二进制输出
	CString show_code = byte_to_hex(code, code_index);
	SetDlgItemText(IDC_STRoutput, show_code);
	CString msg;
	msg.Format(_T("编码长度\t%ld\n原始长度\t%ld\n"),code_index, size);
	AfxMessageBox(msg);

	// 将压缩后的数据存入文件
	if (outputFilePath == "") return;
	std::ofstream outputfile(outputFilePath, std::ios::binary );
	for (int i = 0; i < No_of_symbols; i++) {  // 存入频谱字典 解压用
		outputfile << freq[i] << " ";
	}
	outputfile.close();
	outputfile.open(outputFilePath, std::ios::binary | std::ios::app);
	// 写入压缩数据
	outputfile.write(code, code_index);
	outputfile.close();
}

void CArithmeticCodingMFCDlg::deCompress() {
	if (inputFilePath == "") return;
	
	std::ifstream inputfile(inputFilePath ,std::ios::binary | std::ios::ate);
	long filesize = inputfile.tellg();
	
	inputfile.seekg(0, std::ios::beg);
	auto bstartsize = inputfile.tellg();
	for (int i = 0; i < No_of_symbols; i++) {
		inputfile >> freq[i];
		bstartsize = inputfile.tellg();
	}
	bstartsize = inputfile.tellg();

	CString freqstr("");
	CString tmp;
	for (int i = 0; i < No_of_symbols; i++) {
		tmp.Format(_T("%x:\t%d\n"), i - 1, freq[i]);
		freqstr += tmp;
	}
	SetDlgItemText(IDC_Freq, freqstr);

	//inputfile.seekg(2, std::ios::cur);
	inputfile.get();

	bstartsize = inputfile.tellg();
	long size = filesize - bstartsize;
	int i = 0;
	inputfile.close();

	inputfile.open(inputFilePath, std::ios::binary);
	inputfile.seekg(bstartsize, std::ios::beg);
	inputfile.read(code, size);
	bstartsize = inputfile.tellg();
	inputfile.close();
	CString show_code = byte_to_hex(code, size);
	SetDlgItemText(IDC_STRoutput, show_code);
	/*
	while (1) {
		auto ch = inputfile.get();
		if (ch == -1) break;
		code[i++] = ch;
	}
	*/


	start_model();
	decode();
	ShowStatusMsg(_T("解码完成！"));


	if (outputFilePath == "") return;
	std::ofstream outputfile(outputFilePath, std::ios::binary);
	outputfile.write((const char *)DecodeRS, decode_length);
	outputfile.close();
}


void CArithmeticCodingMFCDlg::OnBnClickedButton2()
{
	BOOL isOpen = FALSE;		//是否打开(否则为保存)
	CString defaultDir = _T("");	//默认打开的文件路径
	CString fileName = _T("file.acc");			//默认打开的文件名
	CString filter = _T("算术压缩文件 (*.acc)||其他文件 (*.*)");	//文件过虑的类型
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = _T("E:\\FileTest\\test.doc");
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	CWnd::SetDlgItemText(IDC_EDIT_OutputFile, filePath);
	outputFilePath = filePath;

}


void CArithmeticCodingMFCDlg::OnStnClickedFreq()
{
	// TODO: 在此添加控件通知处理程序代码
}
