
// JinYiGuiDlg.h: 头文件
//

#pragma once

#include"ctab1.h"
#include"ctab2.h"
// CJinYiGuiDlg 对话框
class CJinYiGuiDlg : public CDialogEx
{
// 构造
public:
	CJinYiGuiDlg(CWnd* pParent = nullptr);	// 标准构造函数
	void initlist();
	void inittab();
	ctab1 t1;
	ctab2 t2;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JINYIGUI_DIALOG };
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
	CListCtrl vlist;
	CTabCtrl vtab;
	afx_msg void OnBnClickedButton1();
};
