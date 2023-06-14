
// JinYiGuisDlg.h: 头文件
//

#pragma once


// CJinYiGuisDlg 对话框
class CJinYiGuisDlg : public CDialogEx
{
// 构造
public:
	CJinYiGuisDlg(CWnd* pParent = nullptr);	// 标准构造函数
	
	void initlist();
	void initwinsock();
	SOCKET socketserv1;
	sockaddr_in addrServ1;
	SOCKET socketClient1;
	SOCKET socketclient2;
	sockaddr_in addrServS2;
	void split(CString *pt,CString tmp,int num,char c)
	{
		for (int i = 0; i < num; i++) 
		{
			AfxExtractSubString(pt[i], tmp, i, c); // 得到 ip
		}
	}
	CString  trans(SOCKET socketClient1,SOCKET socketclient2,char * pt)
	{
		//char tmp[10] = {0};
		char szBuffer[MAXBYTE] = { 0 };
		//memset(szBuffer, 0, sizeof(szBuffer));
		send(socketClient1, pt, strlen(pt), 0);
		int t=recv(socketclient2, szBuffer, MAXBYTE, 0);

		//CString tmp[10];
		//CString temp(szBuffer);
		//
		//AfxExtractSubString(tmp[0], temp, 0, ';'); // 得到 ip
		//AfxExtractSubString(tmp[1], temp, 1, ';'); // 得到 端口
		//AfxExtractSubString(tmp[2], temp, 2, ';'); // 得到 hijk
		//AfxExtractSubString(csTemp, (LPCTSTR)szBuffer, 3, '-'); // 得到 lmn

	/*	MessageBox(tmp[0]);
		MessageBox(tmp[1]);
		MessageBox(tmp[2]);*/

		CString nook(szBuffer);
		MessageBox(nook);
		return nook;
	}
	int listdeal(CString *tmp,int row) 
	{
		static int num_line_list = 0;
		//static int num_col_list = 0;
		vlist.InsertItem(num_line_list, tmp[0]);
		for (int i = 1; i < row; i++) 
			vlist.SetItemText(num_line_list, i, tmp[i]);
		//	vlist.InsertItem(num_line_list,tmp[i]);
		num_line_list++;
		return 0;
	};
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JINYIGUIS_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	CListCtrl vlist;
	WSADATA wsaData;
	afx_msg void OnBnClickedButton2();
};
