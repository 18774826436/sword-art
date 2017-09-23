// chatroom.cpp : 实现文件
//by陈海林

#include "stdafx.h"
#include "Sword  Art.h"
#include "Sword  ArtDlg.h"
#include "chatroom.h"
#include "afxdialogex.h"
#include "signup.h"
//声明一个全局变量
HACCEL hACCEnter;
// chatroom 对话框
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


// chatroom 消息处理程序

//此处贴图没用双缓冲，因为画刷的问题，窗口背景一直被涂成黑色
void chatroom::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//CDC memdc;	
	CRect rc2;
	GetClientRect(&rc2);
	CImage imagebg;
	//CBitmap hBmpbg;		//位图
	imagebg.Load(_T("res\\BG.jpg"));//加载背景图
	//hBmpbg.CreateCompatibleBitmap(&dc,rc2.Width(),rc2.Height());
	//memdc.CreateCompatibleDC(&dc);//关联c窗口dc与内存dc
	//CBitmap* OldBitmap=memdc.SelectObject(&hBmpbg);//设置位图
	//memdc.FillSolidRect(0,0,rc2.Width(),rc2.Height(),RGB(255,255,255));
	imagebg.BitBlt(dc,0,0,rc2.Width(),rc2.Height(),0,0,SRCCOPY);
	//dc.BitBlt(0,0,rc2.Width(),rc2.Height(),&memdc,0,0,SRCCOPY);
		// TODO: 在此处添加消息处理程序代码
	//memdc.DeleteDC();
	CDialogEx::OnPaint();
}
void chatroom::AppendShowText(CString str)
{
	str = _T("\n") + str + _T("\n");
	m_edit_show.SetSel(-1);
	m_edit_show.ReplaceSel(str);
}
//透明控件
HBRUSH chatroom::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor ==CTLCOLOR_EDIT)
	{
	pDC->SetTextColor(RGB(255,160,0));//设置静态文本框字体颜色
	pDC->SetBkMode(TRANSPARENT);//设置为透明
	return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
	
	}
return hbr;
}

//进入游戏时即连接服务器，可以在聊天窗口聊天
BOOL chatroom::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_mySocket.Create();
	hACCEnter=LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_BTN_SEND));
	m_mySocket.Connect(_T("127.0.0.1"),8888);
	m_edit_input.EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
	AppendShowText(_T("世界频道："));
	m_font2.CreatePointFont(125,"微软雅黑",NULL);
	m_edit_show.SetFont(&m_font2,TRUE);
	m_edit_input.SetFont(&m_font2,TRUE);
	// 异常: OCX 属性页应返回 FALSE
	return true;
}


void chatroom::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	
		CString strInput;
		m_edit_input.GetWindowText(strInput);
		//将用户名和消息一起显示
		CString m_str = MyHero.keepname.c_str() + CString(_T(":")) + strInput;
		 char *chInput = m_str.GetBuffer();
		m_mySocket.Send(chInput,strlen(chInput) + 1,0);
		//AppendShowText(MyHero.keepname + CString(_T(":"))+ strInput);
		AppendShowText(m_str);
		//清空消息编辑框
		m_edit_input.SetSel(0,-1);
		m_edit_input.Clear();
}
//重写
void chatroom::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
}
//为发送按钮设置快捷键Enter键
BOOL chatroom::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
		if(VK_RETURN == pMsg->wParam && pMsg->message == WM_KEYDOWN)
	{
		HWND hWnd = ::GetFocus();//只有当光标聚焦到指定编辑框时，才对发送（Enter键）响应
		if (::GetDlgCtrlID(hWnd) == IDC_EDIT_INPUT)
		{
			OnBnClickedBtnSend();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
void chatroom::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_mySocket.Close();
	CDialogEx::OnClose();
}
//刷新编辑框
void chatroom::OnEnChangeEditInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CRect rect1;
	GetDlgItem(IDC_EDIT_INPUT)->GetWindowRect(rect1);
	ScreenToClient(&rect1);
	InvalidateRect(&rect1,TRUE);

	// TODO:  在此添加控件通知处理程序代码
}
void chatroom::OnEnChangeEditShow()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CRect rect2;
	GetDlgItem(IDC_EDIT_SHOW)->GetWindowRect(rect2);
	ScreenToClient(&rect2);
	InvalidateRect(&rect2,TRUE);

	// TODO:  在此添加控件通知处理程序代码
}
