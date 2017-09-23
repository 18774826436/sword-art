#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MySocket.h"
// chatroom 对话框
/*聊天窗口
by陈海林
*/
class chatroom : public CDialogEx
{
	CMySocket m_mySocket;//客户端套接字
	DECLARE_DYNAMIC(chatroom)

public:
	chatroom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~chatroom();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void AppendShowText(CString str);
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_edit_show;
	CEdit m_edit_input;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSend();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	CFont m_font2;
	afx_msg void OnEnChangeEditInput();
	afx_msg void OnEnChangeEditShow();
};
