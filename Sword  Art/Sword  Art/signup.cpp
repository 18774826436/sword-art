// signup.cpp : 实现文件


#include "stdafx.h"
#include "Sword  Art.h"
#include "signup.h"
#include "login.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// signup 对话框

IMPLEMENT_DYNAMIC(signup, CDialogEx)
extern hero MyHero;
signup::signup(CWnd* pParent /*=NULL*/)
	: CDialogEx(signup::IDD, pParent)
	, cusername(_T(""))
	, cpassword(_T(""))
	, cname(_T(""))
{

}

signup::~signup()
{
}

void signup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_s1);
	DDX_Control(pDX, IDC_STATIC2, m_s2);
	DDX_Control(pDX, IDC_STATIC3, m_s3);
	DDX_Text(pDX, IDC_EDIT1, cusername);
	DDX_Text(pDX, IDC_EDIT2, cpassword);
	DDX_Text(pDX, IDC_EDIT3, cname);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel2);
	DDX_Control(pDX, IDOK, m_ButtonOk2);
}


BEGIN_MESSAGE_MAP(signup, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_EDIT1, &signup::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &signup::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &signup::OnEnChangeEdit3)
	ON_BN_CLICKED(IDOK, &signup::OnBnClickedOk)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// signup 消息处理程序


void signup::OnPaint()
{
	// TODO: 在此处添加消息处理程序代码
	CPaintDC dc(this); // device context for painting
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CImage imagebg;	
	imagebg.Load(_T("res\\刀剑神域2.png"));
	imagebg.BitBlt(dc,0,0,ClientRect.Width(),ClientRect.Height(),0,0,SRCCOPY);
	CDialogEx::OnPaint();
}


BOOL signup::OnInitDialog()
{
	CDialogEx::OnInitDialog();
    m_bkImage2.LoadFromResource(AfxGetInstanceHandle(),IDB_BITMAP2);
	m_ButtonOk2.SetBkColor(0xC06000);
	m_ButtonCancel2.SetBkColor(0xC06000);
	//设置Static字体
	m_Font.CreatePointFont(110, _T("宋体"), NULL);
	m_s1.SetFont(&m_Font, true);
	m_s1.SetWindowText(_T("用户名"));
	m_s2.SetFont(&m_Font, true);
	m_s2.SetWindowText(_T("密  码"));
	m_s3.SetFont(&m_Font, true);
	m_s3.SetWindowText(_T("昵  称"));

	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH signup::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->GetDlgCtrlID() == IDC_STATIC1|| pWnd->GetDlgCtrlID() == IDC_STATIC2||pWnd->GetDlgCtrlID() == IDC_STATIC3||nCtlColor ==CTLCOLOR_EDIT)
	{
	pDC->SetTextColor(RGB(255,255,255));//设置静态文本框字体颜色
	pDC->SetBkMode(TRANSPARENT);//设置为透明
	return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
	}
	return hbr;
}


int signup::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

		// TODO:  在此添加您专用的创建代码

        SetWindowLong(m_hWnd,GWL_STYLE,WS_OVERLAPPED);  
        SetWindowLong(m_hWnd,GWL_EXSTYLE,WS_EX_LTRREADING);  
        SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);  
		return 0;
}
void signup::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	  CRect rect1;
      GetDlgItem(IDC_EDIT1)->GetWindowRect(rect1);
      ScreenToClient(&rect1);
      InvalidateRect(&rect1,TRUE);

}
void signup::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	 CRect rect2;
      GetDlgItem(IDC_EDIT2)->GetWindowRect(rect2);
      ScreenToClient(&rect2);
      InvalidateRect(&rect2,TRUE);
}

void signup::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	 CRect rect3;
      GetDlgItem(IDC_EDIT3)->GetWindowRect(rect3);
      ScreenToClient(&rect3);
      InvalidateRect(&rect3,TRUE);
}

void signup::OnBnClickedOk()
{
	/*UpdateData(TRUE);
	fstream inout;
	inout.open("user.txt", ios::in);
	string name = cname.GetBuffer(0);
	string password = cpassword.GetBuffer(0);
	string username = cusername.GetBuffer(0);
	bool t = false;
	while (!inout.eof())
	{
		string n, u, p;
		inout >> u >> p >> n;
		if(username == "")
		{
			
			MessageBox("请输入用户名","提示"); 
		
		}
		else if(u == username)
		{
			
			MessageBox("此用户名已存在","提示");  
			
		}
		else if(u != username && password== "")
		{
			
			MessageBox("请输入密码","提示");
		
		}
		else if(u != username && name == "")
		{
			
			MessageBox("请输入昵称","提示");  
			 
		}
		else if(u != username && name != "" && password != "" && u != "")
		{
			t = true;
		}
	}
	inout.close();
	inout.open("user.txt",ios::out | ios::app );
	inout << username << " " << password << " " << name << endl;
	if(t == true)
	{
	MessageBox(_T("注册成功"));
	}
	inout.close();
	CDialogEx::OnOK();*/
	UpdateData(TRUE);
	string name = cname.GetBuffer(0);
	string password = cpassword.GetBuffer(0);
	string username = cusername.GetBuffer(0);
    bool flag1 = false;
	while(!flag1)
	{
			if(username == "")
		{
			MessageBox("请输入用户名","提示"); 
			return;
		}
	if(name == "")
		{
			MessageBox("请输入昵称","提示");  
			return;
		}
	if(password== "")
		{
			MessageBox("请输入密码","提示");
			return;
		}
	flag1 = true;
	}

	bool flag2 = true;
	fstream inout;
	inout.open("user.txt", ios::in);
	while (!inout.eof())
	{
		string n, u, p;
		inout >> u >> p >> n;
		if(u == username)
		{
			MessageBox("此用户名已存在");  
			flag2 = false;
			return;
		}

	}
	inout.close();
	if(flag2 == true)
	{
		inout.open("user.txt",ios::out | ios::app );
	    inout << username << " " << password << " " << name << endl;
	    fstream inout2;
	    inout2.open(username + ".txt",ios::out);
	    inout2 << username << " " << 280 << " " <<  280 << " " << 600 << " " << 0 << " " << 5280 <<endl;  //依次写入keepname,x,x2,y,direct,orignal
	    inout2.close();
	    MessageBox(_T("注册成功"));
	}
	
//	GetDlgItem(IDC_EDIT3)->GetWindowText(m_str);  
	CDialogEx::OnOK();
}

void signup::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL signup::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	GetClientRect(&rc);
	m_bkImage2.BitBlt(pDC->GetSafeHdc(),rc,CPoint(0,0),SRCCOPY);
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
	
	//return CDialogEx::OnEraseBkgnd(pDC);
}
