#pragma once
#include "afxwin.h"
#include "MyButton2.h"
//ע���������by�º���
// signup �Ի���

class signup : public CDialogEx
{
	DECLARE_DYNAMIC(signup)

public:
	signup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~signup();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };
private:  
     CFont m_Font; 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_str; 
	CMyButton2 m_ButtonOk2;
	CMyButton2 m_ButtonCancel2;
	CStatic m_s1;
	CStatic m_s2;
	CStatic m_s3;
	CString cusername;
	CString cpassword;
	CString cname;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CImage m_bkImage2;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
