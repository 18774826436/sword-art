
// ServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ServerSocket.h"
#include "SessionSocket.h"

// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	CServerSocket m_serverSocket; // 监听套接字对象
 
public:
	CSessionSocket m_sessionSocket; // 会话套接字对象
	SOCKADDR_IN m_sessionAddr;	// 用于保存客户端地址信息
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
	void AppendShowText(CString str);
	CEdit m_edit_show;
	CEdit m_edit_input;
	CButton m_send;
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
};
