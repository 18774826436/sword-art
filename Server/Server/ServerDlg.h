
// ServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ServerSocket.h"
#include "SessionSocket.h"

// CServerDlg �Ի���
class CServerDlg : public CDialogEx
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	CServerSocket m_serverSocket; // �����׽��ֶ���
 
public:
	CSessionSocket m_sessionSocket; // �Ự�׽��ֶ���
	SOCKADDR_IN m_sessionAddr;	// ���ڱ���ͻ��˵�ַ��Ϣ
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
