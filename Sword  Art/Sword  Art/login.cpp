// login.cpp : 实现文件
/*
和注册界面一样，主要是写了一个继承自CButton的类，
对按钮进行重绘制，使得具有半透明效果
by陈海林
*/
#include "stdafx.h"
//#include "Sword  Art.h"
#include "login.h"
#include "signup.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//#include "register.h"
// login 对话框

IMPLEMENT_DYNAMIC(login, CDialogEx)
hero MyHero;
login::login(CWnd* pParent /*=NULL*/)
	: CDialogEx(login::IDD, pParent)
	, Username(_T(""))
	, Password(_T(""))
{

}

login::~login()
{
}

void login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_C, m_static1);
	DDX_Control(pDX, IDC_STATIC_CC, m_static2);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_BUTTON3, m_Button3);
	DDX_Text(pDX, IDC_EDIT1, Username);
	DDX_Text(pDX, IDC_EDIT2, Password);
}


BEGIN_MESSAGE_MAP(login, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT1, &signup::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &signup::OnEnChangeEdit2)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &login::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &login::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &login::OnBnClickedButton3)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// login 消息处理程序


//登录界面美化by陈海林
BOOL login::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect temprect(0,0,730,437);//自定义窗口大小
	m_bkImage.LoadFromResource(AfxGetInstanceHandle(),IDB_BITMAP1);
	m_Button1.SetBkColor(0xE08600);
	m_Button2.SetBkColor(0xE08600);
	m_Button3.SetBkColor(0xE08600);
	//设置Static字体
	m_Font.CreatePointFont(120,_T( "宋体"), NULL);
	m_static1.SetFont(&m_Font, true);
	m_static1.SetWindowText(_T("用户名"));
	m_static2.SetFont(&m_Font, true);
	m_static2.SetWindowText(_T("密  码"));
	// 异常: OCX 属性页应返回 FALSE
	return true;
}

void login::OnPaint()
{
	
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CPaintDC dc(this);	//窗口dc
	CDC memdc;	
	CImage imagebg;
	imagebg.Load(_T("res\\刀剑神域3.bmp"));//加载背景图
	imagebg.BitBlt(dc,0,0,ClientRect.Width(),ClientRect.Height(),0,0,SRCCOPY);	

		CDialogEx::OnPaint();
}


HBRUSH login::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
if((pWnd->GetDlgCtrlID() == IDC_STATIC_CC||pWnd->GetDlgCtrlID() == IDC_STATIC_C)||nCtlColor ==CTLCOLOR_EDIT)
	{
	 pDC->SetTextColor(RGB(255,255,255));//设置静态文本框字体颜色
	pDC->SetBkMode(TRANSPARENT);//设置为透明
	return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
	}
	return hbr;
}


int login::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	
		// TODO:  在此添加您专用的创建代码
	   //去掉标题栏和边框2017-7-6
       SetWindowLong(m_hWnd,GWL_STYLE,WS_OVERLAPPED);  
        SetWindowLong(m_hWnd,GWL_EXSTYLE,WS_EX_LTRREADING);  
        SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);  
  
		return 0;
}

/*
void login::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	x = point.x;
	y = point.y;
	
	if((x >= 20 && x <= 120)&&(y >=287 && y <= 323 ))
	{
		OnBnClickedButton1();
	}
	else if((x >= 216 && x <= 316)&&(y >=287 && y <= 323 ))
	{
		OnBnClickedButton2();
	}
	else if((x >= 600 && x <= 670)&&(y >=0 && y <= 36 ))
	{
		OnBnClickedButton3();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
*/

void login::OnBnClickedButton1()
{
		// TODO: 在此添加控件通知处理程序代码
	
		//UpdateData(TRUE);
		////UpdateData(false);
		//if (Username == "")
		//{
		//	MessageBox("请输入用户名","提示");
		//	return;
		//}
		//if (Password == "")
		//{
		//	MessageBox("请输入密码","提示");
		//	return;
		//}
		//fstream  inout;
		//inout.open("user.txt", ios::in | ios::out);
		//bool flag = false;
		//string n, u, p;
		//string username = Username.GetBuffer(0);
		//string password = Password.GetBuffer(0);
		//while (!inout.eof())
		//{
		//	inout >> u >> p >> n;
		//	if (username == u && password == p)
		//	{
		//		flag = true;
		//		CDialogEx::OnOK();
		//	}

		//}
		//if (!flag)
		//{
		//	MessageBox(_T("对不起，您输入的用户信息不正确，无法登录"));
		//}
	
	UpdateData(TRUE);
		//UpdateData(false);
		bool flag1 = false;
		while(!flag1)
		{
			if (Username == "")
		   {
			MessageBox(_T("请输入用户名","提示"));
			break;
		    }
		    if (Password == "")
		    {
			MessageBox(_T("请输入密码","提示"));
			break;
		    }
			flag1 = true;
		}

		fstream  inout;
		inout.open("user.txt", ios::in | ios::out);
		bool flag = false;
		string n, u, p;
		string username = Username.GetBuffer(0);
		string password = Password.GetBuffer(0);
		while (!inout.eof())
		{
			inout >> u >> p >> n;
			if (username == u && password == p)
			{
				flag = true;
	            fstream inout2;
	            inout2.open(username + ".txt",ios::in );
				//inout2.open("4.txt",ios::in );
	            inout2 >> MyHero.keepname >> MyHero.x >> MyHero.x2 >> MyHero.y >> MyHero.direct >> MyHero.orignal;
	            inout2.close();
				CDialogEx::OnOK();
				break;
			}

		}
		if (!flag)
		{
			MessageBox(_T("对不起，您输入的用户信息不正确，无法登录"));
		}
}


void login::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	signup dlg;
	dlg.DoModal();
}


void login::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//该变量用来判断是否该退出所有窗口
	judgment = true;
	 EndDialog(IDCANCEL);//关闭窗口 
	CDialogEx::OnClose();
}

BOOL login::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);
	m_bkImage.BitBlt(pDC->GetSafeHdc(),rc,CPoint(0,0),SRCCOPY);
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}
//重载OnOK(),OnCancle()，使得在按下Enter和esc键时不会退出
void login::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
}
void login::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
}
//为登录界面设置鼠标
void login::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HCURSOR hCur = (HCURSOR)LoadImage(NULL ,_T("res\\2.ani"), IMAGE_ICON,32,32,LR_LOADFROMFILE );
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::SetCursor(hCur);
	CDialogEx::OnMouseMove(nFlags, point);
}
