// ServerDlg.cpp : 实现文件
#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
/*
服务器端主窗口
by陈海林
2017/7/10
*/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg 对话框



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_edit_show);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edit_input);
	DDX_Control(pDX, IDC_BTN_SEND, m_send);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CServerDlg::OnBnClickedBtnSend)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//创建服务器端流式套接字，端口为8888，
	if (m_serverSocket.Create(8888, SOCK_STREAM))
	{
		m_serverSocket.Listen();
		AppendShowText(_T("正在监听..."));
	}
	else
	{
		AfxMessageBox(_T("创建监听套接字失败！"));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CServerDlg::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strInput;
	m_edit_input.GetWindowText(strInput);
	if (strInput.IsEmpty())
	{
		AfxMessageBox(_T("消息不能为空！"));
	}
	else
	{
		USES_CONVERSION;
		char *chInput = T2A(strInput);
		m_sessionSocket.Send(chInput, strlen(chInput) + 1, 0);
 
		AppendShowText(_T("服务器端：")+ strInput);
 
		// 清空
		m_edit_input.SetSel(0, -1);
		m_edit_input.Clear();
	}
}
void CServerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
m_serverSocket.Close();
	CDialogEx::OnClose();
}
BOOL CServerDlg::PreTranslateMessage(MSG* pMsg)
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
//此函数将消息显示在公频窗口
void CServerDlg::AppendShowText(CString str)
{
	str = _T("\r\n") + str + _T("\r\n");
	m_edit_show.SetSel(-1);
	m_edit_show.ReplaceSel(str);
}
//重写OnOk(),按Enter键时不会退出窗口
void CServerDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

}
