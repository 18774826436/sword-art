// signup.cpp : ʵ���ļ�


#include "stdafx.h"
#include "Sword  Art.h"
#include "signup.h"
#include "login.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// signup �Ի���

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


// signup ��Ϣ�������


void signup::OnPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	CPaintDC dc(this); // device context for painting
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CImage imagebg;	
	imagebg.Load(_T("res\\��������2.png"));
	imagebg.BitBlt(dc,0,0,ClientRect.Width(),ClientRect.Height(),0,0,SRCCOPY);
	CDialogEx::OnPaint();
}


BOOL signup::OnInitDialog()
{
	CDialogEx::OnInitDialog();
    m_bkImage2.LoadFromResource(AfxGetInstanceHandle(),IDB_BITMAP2);
	m_ButtonOk2.SetBkColor(0xC06000);
	m_ButtonCancel2.SetBkColor(0xC06000);
	//����Static����
	m_Font.CreatePointFont(110, _T("����"), NULL);
	m_s1.SetFont(&m_Font, true);
	m_s1.SetWindowText(_T("�û���"));
	m_s2.SetFont(&m_Font, true);
	m_s2.SetWindowText(_T("��  ��"));
	m_s3.SetFont(&m_Font, true);
	m_s3.SetWindowText(_T("��  ��"));

	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH signup::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->GetDlgCtrlID() == IDC_STATIC1|| pWnd->GetDlgCtrlID() == IDC_STATIC2||pWnd->GetDlgCtrlID() == IDC_STATIC3||nCtlColor ==CTLCOLOR_EDIT)
	{
	pDC->SetTextColor(RGB(255,255,255));//���þ�̬�ı���������ɫ
	pDC->SetBkMode(TRANSPARENT);//����Ϊ͸��
	return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
	}
	return hbr;
}


int signup::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

		// TODO:  �ڴ������ר�õĴ�������

        SetWindowLong(m_hWnd,GWL_STYLE,WS_OVERLAPPED);  
        SetWindowLong(m_hWnd,GWL_EXSTYLE,WS_EX_LTRREADING);  
        SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);  
		return 0;
}
void signup::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	  CRect rect1;
      GetDlgItem(IDC_EDIT1)->GetWindowRect(rect1);
      ScreenToClient(&rect1);
      InvalidateRect(&rect1,TRUE);

}
void signup::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	 CRect rect2;
      GetDlgItem(IDC_EDIT2)->GetWindowRect(rect2);
      ScreenToClient(&rect2);
      InvalidateRect(&rect2,TRUE);
}

void signup::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
			
			MessageBox("�������û���","��ʾ"); 
		
		}
		else if(u == username)
		{
			
			MessageBox("���û����Ѵ���","��ʾ");  
			
		}
		else if(u != username && password== "")
		{
			
			MessageBox("����������","��ʾ");
		
		}
		else if(u != username && name == "")
		{
			
			MessageBox("�������ǳ�","��ʾ");  
			 
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
	MessageBox(_T("ע��ɹ�"));
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
			MessageBox("�������û���","��ʾ"); 
			return;
		}
	if(name == "")
		{
			MessageBox("�������ǳ�","��ʾ");  
			return;
		}
	if(password== "")
		{
			MessageBox("����������","��ʾ");
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
			MessageBox("���û����Ѵ���");  
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
	    inout2 << username << " " << 280 << " " <<  280 << " " << 600 << " " << 0 << " " << 5280 <<endl;  //����д��keepname,x,x2,y,direct,orignal
	    inout2.close();
	    MessageBox(_T("ע��ɹ�"));
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rc;
	GetClientRect(&rc);
	m_bkImage2.BitBlt(pDC->GetSafeHdc(),rc,CPoint(0,0),SRCCOPY);
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
	
	//return CDialogEx::OnEraseBkgnd(pDC);
}
