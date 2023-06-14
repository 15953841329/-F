// show.cpp: 实现文件
//

#include "pch.h"
#include "JinYiGuis.h"
#include "show.h"
#include "afxdialogex.h"


// show 对话框

IMPLEMENT_DYNAMIC(show, CDialogEx)

show::show(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

show::~show()
{
}

void show::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, pic);
}


BEGIN_MESSAGE_MAP(show, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &show::OnBnClickedButton1)
END_MESSAGE_MAP()


// show 消息处理程序


void show::OnBnClickedButton1()
{
	CDC* pdc = CDC::FromHandle(::GetDC(nullptr));
	
	
	CDC tmp;
	tmp.CreateCompatibleDC(pdc);

	int xScreen = ::GetSystemMetrics(SM_CXSCREEN);
	int yScreen = ::GetSystemMetrics(SM_CYSCREEN);

	CBitmap bitmapScreen;
	bitmapScreen.CreateCompatibleBitmap(pdc, xScreen, yScreen);

	auto oldBitmap = tmp.SelectObject(bitmapScreen);
	tmp.BitBlt(0, 0, xScreen, yScreen, pdc, 0, 0, SRCCOPY);

	CDC* showDC = CDC::FromHandle(::GetDC(GetDlgItem(IDC_STATIC)->m_hWnd));

	CDC memDC;
	memDC.CreateCompatibleDC(showDC);
	memDC.SelectObject(bitmapScreen);

	showDC->BitBlt(0,0,xScreen,yScreen,&memDC,0,0,SRCCOPY);

}
