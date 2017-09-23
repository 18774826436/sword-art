#pragma once
#include "afxwin.h"
#include "MyButton2.h"
//注册界面美化by陈海林
// signup 对话框

class signup : public CDialogEx
{
	DECLARE_DYNAMIC(signup)

public:
	signup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~signup();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };
private:  
     CFont m_Font; 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
