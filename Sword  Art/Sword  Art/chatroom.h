#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MySocket.h"
// chatroom �Ի���
/*���촰��
by�º���
*/
class chatroom : public CDialogEx
{
	CMySocket m_mySocket;//�ͻ����׽���
	DECLARE_DYNAMIC(chatroom)

public:
	chatroom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~chatroom();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
