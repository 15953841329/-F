// linfo.cpp: 实现文件
//

#include "pch.h"
#include "JinYiGuis.h"
#include "linfo.h"
#include "afxdialogex.h"


// linfo 对话框

IMPLEMENT_DYNAMIC(linfo, CDialogEx)

linfo::linfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

linfo::~linfo()
{
}

void linfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(linfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &linfo::OnBnClickedButton2)
END_MESSAGE_MAP()


// linfo 消息处理程序


void linfo::OnBnClickedButton2()
{
   

	this->OnOK();
	// TODO: 在此添加控件通知处理程序代码
}
