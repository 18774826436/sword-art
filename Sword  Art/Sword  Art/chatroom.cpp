// chatroom.cpp : ʵ���ļ�
//by�º���

#include "stdafx.h"
#include "Sword  Art.h"
#include "Sword  ArtDlg.h"
#include "chatroom.h"
#include "afxdialogex.h"
#include "signup.h"
//����һ��ȫ�ֱ���
HACCEL hACCEnter;
// chatroom �Ի���
extern hero MyHero;
IMPLEMENT_DYNAMIC(chatroom, CDialogEx)

chatroom::chatroom(CWnd* pParent /*=NULL*/)
	: CDialogEx(chatroom::IDD, pParent)
{

}

chatroom::~chatroom()
{
}

void chatroom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_edit_show);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edit_input);
}


BEGIN_MESSAGE_MAP(chatroom, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SEND, &chatroom::OnBnClickedBtnSend)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT_INPUT, &chatroom::OnEnChangeEditInput)
	ON_EN_CHANGE(IDC_EDIT_SHOW, &chatroom::OnEnChangeEditShow)
END_MESSAGE_MAP()


// chatroom ��Ϣ�������

//�˴���ͼû��˫���壬��Ϊ��ˢ�����⣬���ڱ���һֱ��Ϳ�ɺ�ɫ
void chatroom::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//CDC memdc;	
	CRect rc2;
	GetClientRect(&rc2);
	CImage imagebg;
	//CBitmap hBmpbg;		//λͼ
	imagebg.Load(_T("res\\BG.jpg"));//���ر���ͼ
	//hBmpbg.CreateCompatibleBitmap(&dc,rc2.Width(),rc2.Height());
	//memdc.CreateCompatibleDC(&dc);//����c����dc���ڴ�dc
	//CBitmap* OldBitmap=memdc.SelectObject(&hBmpbg);//����λͼ
	//memdc.FillSolidRect(0,0,rc2.Width(),rc2.Height(),RGB(255,255,255));
	imagebg.BitBlt(dc,0,0,rc2.Width(),rc2.Height(),0,0,SRCCOPY);
	//dc.BitBlt(0,0,rc2.Width(),rc2.Height(),&memdc,0,0,SRCCOPY);
		// TODO: �ڴ˴������Ϣ����������
	//memdc.DeleteDC();
	CDialogEx::OnPaint();
}
void chatroom::AppendShowText(CString str)
{
	str = _T("\n") + str + _T("\n");
	m_edit_show.SetSel(-1);
	m_edit_show.ReplaceSel(str);
}
//͸���ؼ�
HBRUSH chatroom::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor ==CTLCOLOR_EDIT)
	{
	pDC->SetTextColor(RGB(255,160,0));//���þ�̬�ı���������ɫ
	pDC->SetBkMode(TRANSPARENT);//����Ϊ͸��
	return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
	
	}
return hbr;
}

//������Ϸʱ�����ӷ����������������촰������
BOOL chatroom::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_mySocket.Create();
	hACCEnter=LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_BTN_SEND));
	m_mySocket.Connect(_T("127.0.0.1"),8888);
	m_edit_input.EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
	AppendShowText(_T("����Ƶ����"));
	m_font2.CreatePointFont(125,"΢���ź�",NULL);
	m_edit_show.SetFont(&m_font2,TRUE);
	m_edit_input.SetFont(&m_font2,TRUE);
	// �쳣: OCX ����ҳӦ���� FALSE
	return true;
}


void chatroom::OnBnClickedBtnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
		CString strInput;
		m_edit_input.GetWindowText(strInput);
		//���û�������Ϣһ����ʾ
		CString m_str = MyHero.keepname.c_str() + CString(_T(":")) + strInput;
		 char *chInput = m_str.GetBuffer();
		m_mySocket.Send(chInput,strlen(chInput) + 1,0);
		//AppendShowText(MyHero.keepname + CString(_T(":"))+ strInput);
		AppendShowText(m_str);
		//�����Ϣ�༭��
		m_edit_input.SetSel(0,-1);
		m_edit_input.Clear();
}
//��д
void chatroom::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
}
//Ϊ���Ͱ�ť���ÿ�ݼ�Enter��
BOOL chatroom::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
		if(VK_RETURN == pMsg->wParam && pMsg->message == WM_KEYDOWN)
	{
		HWND hWnd = ::GetFocus();//ֻ�е����۽���ָ���༭��ʱ���ŶԷ��ͣ�Enter������Ӧ
		if (::GetDlgCtrlID(hWnd) == IDC_EDIT_INPUT)
		{
			OnBnClickedBtnSend();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
void chatroom::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_mySocket.Close();
	CDialogEx::OnClose();
}
//ˢ�±༭��
void chatroom::OnEnChangeEditInput()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CRect rect1;
	GetDlgItem(IDC_EDIT_INPUT)->GetWindowRect(rect1);
	ScreenToClient(&rect1);
	InvalidateRect(&rect1,TRUE);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
void chatroom::OnEnChangeEditShow()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CRect rect2;
	GetDlgItem(IDC_EDIT_SHOW)->GetWindowRect(rect2);
	ScreenToClient(&rect2);
	InvalidateRect(&rect2,TRUE);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
