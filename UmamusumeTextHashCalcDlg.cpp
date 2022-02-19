
// UmamusumeTextHashCalcDlg.cpp: 实现文件
//
#pragma warning(disable : 4996)
#include "pch.h"
#include "framework.h"
#include "UmamusumeTextHashCalc.h"
#include "UmamusumeTextHashCalcDlg.h"
#include "afxdialogex.h"
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <conio.h>
using namespace std;

// #include "json/json.h"

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


// CUmamusumeTextHashCalcDlg 对话框



CUmamusumeTextHashCalcDlg::CUmamusumeTextHashCalcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UMAMUSUMETEXTHASHCALC_DIALOG, pParent)
	, m_text(_T(""))
	, m_result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUmamusumeTextHashCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDX_Text(pDX, IDC_EDIT2, m_result);
	DDX_Text(pDX, IDC_EDIT3, m_result2);
}

BEGIN_MESSAGE_MAP(CUmamusumeTextHashCalcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUmamusumeTextHashCalcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUmamusumeTextHashCalcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUmamusumeTextHashCalcDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CUmamusumeTextHashCalcDlg 消息处理程序

BOOL CUmamusumeTextHashCalcDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUmamusumeTextHashCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUmamusumeTextHashCalcDlg::OnPaint()
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
HCURSOR CUmamusumeTextHashCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUmamusumeTextHashCalcDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	std::wstring str = m_text.GetString();
	std::wstring _str = L"";
	for (int i = 0; i < str.length(); i++)
		if (str[i] != '\r' && str[i] != ',')
			_str += str[i];
	// m_result = to_string(_str.length()).c_str();
	auto result = std::hash<wstring>{}(_str);

	_str = L"";
	for (int i = 0; i < str.length(); i++)
		if (str[i] != '\r' && str[i] != ',' && str[i] != '\n')
			_str += str[i];
	auto result2 = std::hash<wstring>{}(_str);

	m_result = to_string(result).c_str();
	m_result2 = to_string(result2).c_str();
	UpdateData(FALSE);
}


void CUmamusumeTextHashCalcDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	m_text = L"";
	UpdateData(FALSE);
}


void TcharToChar(const TCHAR* tchar, char* _char)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char    
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}


char* getfileAll(char* fname)
{
	FILE* fp;
	char* str;
	char txt[1000];
	int filesize;
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("open file %s fail \n", fname);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);

	filesize = ftell(fp);
	str = (char*)malloc(filesize);
	str[0] = 0;

	rewind(fp);
	while ((fgets(txt, 1000, fp)) != NULL) {
		strcat(str, txt);
	}
	fclose(fp);
	return str;
}

int writefileAll(char* fname, const char* data)
{
	FILE* fp;
	if ((fp = fopen(fname, "w")) == NULL)
	{
		printf("open file %s fail \n", fname);
		return 1;
	}

	fprintf(fp, "%s", data);
	fclose(fp);

	return 0;
}


wstring towstring(string str)
{
	const char* ptr = str.c_str();
	wstring result;
	mbstate_t state;
	memset(&state, 0, sizeof state);
	const char* end = ptr + strlen(ptr);
	int len;
	wchar_t wc;
	while ((len = mbrtowc(&wc, ptr, end - ptr, &state)) > 0) {

		result.append(1, wc);
		ptr += len;
	}
	return result;
}

template<typename T> string toString(const T& t) {
	return to_string(t);
}

wstring UTF8ToUnicode(const string& str)
{
	int len = 0;
	len = str.length();
	int unicodeLen = ::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	wstring rt;
	rt = (wchar_t*)pUnicode;
	delete pUnicode;
	return rt;
}


void CUmamusumeTextHashCalcDlg::OnBnClickedButton3()
{
	// AllocConsole();
	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = _T("请选择文本文件, 一行一条文本, 换行符使用\"\\n\"代替");
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
	{
		return;
	}
	SHGetPathFromIDList(idl, szBuffer);
	// _cwprintf(L"%ls\n", szBuffer);
	char* fname = (char*)malloc(100 * sizeof(char));
	TcharToChar(szBuffer, fname);
	_cprintf("%s\n", fname);

	// 读取配置

	ifstream in(fname);
	string line;
	string out = "";
	string _tmp = "";
	long lcount = 0;
	bool rp_flg = false;
	std::map<string, int> in_hash;

	while (getline(in, line)) {
		_tmp = "";
		lcount++;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == '\\') {
				rp_flg = true;
				continue;
			}
			else if (rp_flg && line[i] == 'n') {
				rp_flg = false;
				_tmp += '\n';
			}
			else {
				rp_flg = false;
				_tmp += line[i];
			}

		}

		auto hash = std::hash<wstring>{}(UTF8ToUnicode(_tmp));
		string hash_str = toString(hash);

		if (in_hash.find(hash_str) == in_hash.end()) {
			out += "\"" + hash_str + "\": \"" + line + "\",\n";
			in_hash.insert({hash_str, 1});
		}
	}
	out = out.substr(0, out.length() - 2);
	out = "{\n" + out + "\n}\n";

	char* save_name = "_save.json";
	save_name = strcat(fname, save_name);
	writefileAll(save_name, out.c_str());

	stringstream fmt;
	fmt << "已输出至: " << save_name << "\n共转换了 " << lcount << "条文本";
	MessageBoxA(NULL, fmt.str().c_str(), "转换完成", MB_OK);

	/*
	char* jsondata = getfileAll(fname);
	Json::Reader reader;
	Json::Value root;


	Json::FastWriter writer;
	Json::Value out_value;


	if (reader.parse(jsondata, root)) {
		Json::Value::Members mem = root.getMemberNames();
		Json::Value::Members::iterator it;
		size_t hash = 0;


		for (it = mem.begin(); it != mem.end(); it++)
		{

			if (root[*it].type() == Json::stringValue)
			{
				hash = std::hash<wstring>{}(towstring(root[*it].asString()));
				out_value[toString(hash)] = root[*it].asString();
			}
			else {
				_cprintf("%s\n", "yinyinyin");
			}

		}
	}

	_cprintf("%s\n", "load_json_fin");

	string out_data = writer.write(out_value);
	writefileAll("C:/Users/Y7000/Desktop/out.json", out_data.c_str());
	*/
}
