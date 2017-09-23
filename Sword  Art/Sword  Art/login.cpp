// login.cpp : ʵ���ļ�
/*
��ע�����һ������Ҫ��д��һ���̳���CButton���࣬
�԰�ť�����ػ��ƣ�ʹ�þ��а�͸��Ч��
by�º���
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
// login �Ի���

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


// login ��Ϣ�������


//��¼��������by�º���
BOOL login::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect temprect(0,0,730,437);//�Զ��崰�ڴ�С
	m_bkImage.LoadFromResource(AfxGetInstanceHandle(),IDB_BITMAP1);
	m_Button1.SetBkColor(0xE08600);
	m_Button2.SetBkColor(0xE08600);
	m_Button3.SetBkColor(0xE08600);
	//����Static����
	m_Font.CreatePointFont(120,_T( "����"), NULL);
	m_static1.SetFont(&m_Font, true);
	m_static1.SetWindowText(_T("�û���"));
	m_static2.SetFont(&m_Font, true);
	m_static2.SetWindowText(_T("��  ��"));
	// �쳣: OCX ����ҳӦ���� FALSE
	return true;
}

void login::OnPaint()
{
	
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CPaintDC dc(this);	//����dc
	CDC memdc;	
	CImage imagebg;
	imagebg.Load(_T("res\\��������3.bmp"));//���ر���ͼ
	imagebg.BitBlt(dc,0,0,ClientRect.Width(),ClientRect.Height(),0,0,SRCCOPY);	

		CDialogEx::OnPaint();
}


HBRUSH login::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
if((pWnd->GetDlgCtrlID() == IDC_STATIC_CC||pWnd->GetDlgCtrlID() == IDC_STATIC_C)||nCtlColor ==CTLCOLOR_EDIT)
	{
	 pDC->SetTextColor(RGB(255,255,255));//���þ�̬�ı���������ɫ
	pDC->SetBkMode(TRANSPARENT);//����Ϊ͸��
	return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
	}
	return hbr;
}


int login::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	
		// TODO:  �ڴ������ר�õĴ�������
	   //ȥ���������ͱ߿�2017-7-6
       SetWindowLong(m_hWnd,GWL_STYLE,WS_OVERLAPPED);  
        SetWindowLong(m_hWnd,GWL_EXSTYLE,WS_EX_LTRREADING);  
        SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);  
  
		return 0;
}

/*
void login::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	

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
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	
		//UpdateData(TRUE);
		////UpdateData(false);
		//if (Username == "")
		//{
		//	MessageBox("�������û���","��ʾ");
		//	return;
		//}
		//if (Password == "")
		//{
		//	MessageBox("����������","��ʾ");
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
		//	MessageBox(_T("�Բ�����������û���Ϣ����ȷ���޷���¼"));
		//}
	
	UpdateData(TRUE);
		//UpdateData(false);
		bool flag1 = false;
		while(!flag1)
		{
			if (Username == "")
		   {
			MessageBox(_T("�������û���","��ʾ"));
			break;
		    }
		    if (Password == "")
		    {
			MessageBox(_T("����������","��ʾ"));
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
			MessageBox(_T("�Բ�����������û���Ϣ����ȷ���޷���¼"));
		}
}


void login::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	signup dlg;
	dlg.DoModal();
}


void login::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ñ��������ж��Ƿ���˳����д���
	judgment = true;
	 EndDialog(IDCANCEL);//�رմ��� 
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
//����OnOK(),OnCancle()��ʹ���ڰ���Enter��esc��ʱ�����˳�
void login::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
}
void login::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
}
//Ϊ��¼�����������
void login::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HCURSOR hCur = (HCURSOR)LoadImage(NULL ,_T("res\\2.ani"), IMAGE_ICON,32,32,LR_LOADFROMFILE );
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	::SetCursor(hCur);
	CDialogEx::OnMouseMove(nFlags, point);
}
