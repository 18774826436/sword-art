#pragma once
#include "afxwin.h"
#include "MyButton.h"
#include "Sword  Art.h"
#include "Sword  ArtDlg.h"
// login �Ի���
//��¼��������by�º���
class login : public CDialogEx
{
	DECLARE_DYNAMIC(login)
	
public:
	login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~login();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

private:  
     CFont m_Font; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CImage m_bkImage;
	bool judgment;
	CMyButton m_Button1;
	CMyButton m_Button2;
	CMyButton m_Button3;
	CStatic m_static1;
	CStatic m_static2;
	CString Username;
	CString Password;
	afx_msg void OnPaint();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButton3();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
