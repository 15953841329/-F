#pragma once


// ctab2 对话框

class ctab2 : public CDialogEx
{
	DECLARE_DYNAMIC(ctab2)

public:
	ctab2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ctab2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
