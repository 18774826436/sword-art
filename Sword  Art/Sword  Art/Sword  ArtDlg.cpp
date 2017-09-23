

// Sword  ArtDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sword  Art.h"
#include "Sword  ArtDlg.h"
#include "afxdialogex.h"
#include "login.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "chatroom.h"
#include <windows.h>
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")//导入声音头文件库

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800
//定时器的名称用宏定义
#define TIMER_PAINT 1
#define TIMER_HEROMOVE 2
#define TIMER_NPCMOVE 3
//人物的四个方向
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3
//两个人物动作
#define STAB 5
#define CUT 12
#define SHEAR 13
#define	HACK 14
//六个抬起动作
#define DOMNUP 6
#define LEFTUP 7
#define RIGHTUP 8
#define UPUP 9
#define STABUP 15
#define CUTUP 16
#define SHEARUP 17
#define	HACKUP 18
//全局计数变量
int count1 = 0;
//人物距离窗口最左端的距离
static int  orignal = 0;

//全局鼠标变量
int xx;
int yy;

int t = 0;
int t2 = 0;
int k1 = 1;
int k2 = 1;

//精准跳转
bool flag = true;///*控制雪花是否停止
bool flag3 = false;///*精确传送
int flag2 = 1;   ///*播放开关
int flag4 = 1;
int flag21 = 1;   ///*播放开关
int flag41 = 1;
int flag22 = 1;   ///*播放开关
int flag42 = 1;
bool flag5 = true; //*图片开关变量
bool flag6 = true;
bool flag7 = true;
int flag8 = 0;//转场相关
bool flag9 = true;
bool flag10 = true;
bool flag11 = true;
bool flagbg = true;
extern hero MyHero;//by 马宇
chatroom *m_dlg3;//一个指向聊天窗口的指针
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

// CSwordArtDlg 对话框

CSwordArtDlg::CSwordArtDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSwordArtDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSwordArtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CSwordArtDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_MOVING()
END_MESSAGE_MAP()

//将png贴图透明
void TransparentPNG(CImage *png)
{
	for(int i = 0; i <png->GetWidth(); i++)
	{
		for(int j = 0; j <png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(png->GetPixelAddress(i , j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}
//by 马宇
// CSwordArtDlg 消息处理程序

BOOL CSwordArtDlg::OnInitDialog()
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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1); //为我们的游戏设置一个图标by陈海林
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//NPC
	//加载背景
	//加载背景
	m_bg.Load("picture\\bg\\bg4.png");
	m_bg1.Load("picture\\bg\\bg41.png");
	m_bg2.Load("picture\\bg\\bg5.png");///*新的背景
	m_bg21.Load("picture\\bg\\bg51.png");  //*背景蒙版
	m_bg3.Load("picture\\bg\\bg6.png");///*新的背景
	m_bg31.Load("picture\\bg\\bg61.png");
	m_bg4.Load("picture\\bg\\bg7.png");///*新的背景
	m_bg41.Load("picture\\bg\\bg71.png");
	m_bg5.Load("picture\\bg\\bg8.png");///*新的背景
	m_bg51.Load("picture\\bg\\bg81.png");
	m_side.Load("picture\\2.png");
	door.Load("picture\\bg\\door.png");///*门
	(npc1.npc).Load("picture\\npc\\NPC1.png");
	npc2.npc.Load("picture\\npc\\npc2.png");
	npc3.npc.Load("picture\\npc\\npc3.png");
	npc4.npc.Load("picture\\npc\\npc4.png");
	npc5.npc.Load("picture\\npc\\npc5.png");
	npcb.npc.Load("picture\\npc\\npcb.png");
	npc7.npc.Load("picture\\npc\\npc7.png");
	npc8.npc.Load("picture\\npc\\npc8.png");
	//获取背景地图的宽度
	m_mapWidth=m_bg.GetWidth();
	//加载英雄图片
		
	MyHero.heroR.Load("picture\\hero\\standRR.png");
	MyHero.heroL.Load("picture\\hero\\standLL.png");
	MyHero.heroRight.Load("picture\\hero\\heroMoveRight.png");
	MyHero.heroLeft.Load("picture\\hero\\heroMoveLeft.png");
	MyHero.heroJumpLeft.Load("picture\\hero\\heroJumpLeft.png");
	MyHero.heroRStab.Load("picture\\hero\\stabR.png");
	MyHero.heroLStab.Load("picture\\hero\\stabL.png");
	MyHero.heroRS.Load("picture\\skill\\1.png");
	MyHero.heroLCut.Load("picture\\hero\\cutL.png");
	MyHero.heroRCut.Load("picture\\hero\\cutR.png");
	MyHero.heroRC.Load("picture\\skill\\2.png");
	MyHero.heroLShear.Load("picture\\hero\\shearL.png");
	MyHero.heroRShear.Load("picture\\hero\\shearR.png");
	MyHero.heroRS2.Load("picture\\skill\\sw.png");
	MyHero.heroLHack.Load("picture\\hero\\hackL.png");
	MyHero.heroRHack.Load("picture\\hero\\HackR.png");
	MyHero.heroRH.Load("picture\\skill\\sw2.png");

	arm.Load("picture\\arm\\case.png");
	arm1.Load("picture\\arm\\arm1.png");
	arm2.Load("picture\\arm\\arm2.png");
	arm3.Load("picture\\arm\\arm3.png");
	armC.Load("picture\\arm\\cool.png");
	skillBox.Load("picture\\skill\\skillBox.png");
	building.Load("picture\\arm\\building.png");
	//加载对话框
	//加载UI
	UI1.Load("picture\\UI\\UI11.png");
	UI2.Load("picture\\UI\\UI22.png");
	UI3.Load("picture\\UI\\UI33.png");
	UI4.Load("picture\\UI\\UI44.png");
	UI5.Load("picture\\UI\\UI55.png");
	//加载对话框
	saber1.Load("picture\\box\\saber1.png");
	chuyin1.Load("picture\\box\\chuyin1.png");
	saber2.Load("picture\\box\\saber2.png");
	saber3.Load("picture\\box\\saber3.png");
	chuyin2.Load("picture\\box\\chuyin2.png");
	chuyin3.Load("picture\\box\\chuyin3.png");
	niu1.Load("picture\\box\\ntr1.png");
	niu2.Load("picture\\box\\ntr2.png");
	box.Load("picture\\box\\box.png");//NPC对话框
	button.Load("picture\\box\\button.png");
	//透明化一些图片
	TransparentPNG(&MyHero.heroR);
	TransparentPNG(&MyHero.heroRight);
	//初始化英雄状态
	MyHero.frame=0;
	MyHero.direct=-1;
	//设置英雄初始位置
	MyHero.x=180;    
	MyHero.x2=180;
	orignal = 180;
	MyHero.y=500;
	MyHero.width = 100;	//英雄宽度高度
	MyHero.height = 150;
	npc1.frame=0;		//初始化npc的运动帧数
	bool direct2 = true;//人物的左右方向

	 char buf[20];  
    for(int i=0;i<7;i++)    //加载七种图像  
    {  
        sprintf_s(buf,"picture\\Snow//%d.png",i);  
        m_snowMap[i].Load(buf);  
    }  
    //初始化雪花粒子  
    for(int i=0;i<SNOW_NUMBER;i++)  
    {  
        Snow[i].x=rand()% WINDOW_WIDTH;   //最初雪花在水平方向上随机出现  
        Snow[i].y=rand()% WINDOW_HEIGHT; //垂直方向上也是随机出现  
        Snow[i].number=rand()%7;         //七种雪花中的一种  
    }  
	//by 马宇
	CRect temprect(0,0,1600,800);//自定义窗口大小
	CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	//新建一个聊天窗口并随着游戏窗口一起启动 by 陈海林
	m_dlg3 = new chatroom;
	m_dlg3->Create(IDD_DIALOG3);
	m_dlg3->SetWindowPos(NULL,1752,115,200,791,SWP_SHOWWINDOW);  
	m_dlg3->ShowWindow(SW_SHOW);
	//SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
	//SetLayeredWindowAttributes(0,200,LWA_ALPHA);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void changeMusic(int x)	//根据场景的不同自动切换背景音乐
{
	if (x >= 4000&&x <8000)
	{
		if (flag2 == 0)
		{
		}
		else if (flag2 == 1)
		{
			flag2 = 0;
			mciSendString(_T("open music\\happy.mp3 alias bgMusic "), NULL, 0, NULL);
			mciSendString(_T("play bgMusic repeat"), NULL, 0, NULL);
		}
	}
	else if(x<4000)
	{
		if (flag4 == 0)
		{
			if (x >= 3950)
			{
				mciSendString(_T("close bgMusic"), 0, 0, 0);
				mciSendString(_T("stop bgMusic"), 0, 0, 0);
			}
		}
		else if (flag4 == 1)
		{
			flag4 = 0;
			mciSendString(_T("open music\\background.mp3 alias bgMusic "), NULL, 0, NULL);
			mciSendString(_T("play bgMusic"), NULL, 0, NULL);
		}
	}
	if (x >= 8200&&x<11750)
	{
		if (flag21 == 0)
		{
		}
		else if (flag21 == 1)
		{
			flag21 = 0;
			mciSendString(_T("open music\\mei.mp3 alias bgMusic "), NULL, 0, NULL);
			mciSendString(_T("play bgMusic repeat"), NULL, 0, NULL);
		}
	}
	else if(x < 8200)
	{
		if (flag41 == 0)
		{
			if (x >= 8150)
			{
				mciSendString(_T("close bgMusic"), 0, 0, 0);
				mciSendString(_T("stop bgMusic"), 0, 0, 0);
			}
		}
		else if (flag41 == 1)
		{
			flag41 = 0;
			mciSendString(_T("open music\\happy.mp3 alias bgMusic "), NULL, 0, NULL);
			mciSendString(_T("play bgMusic"), NULL, 0, NULL);
		}
	}

	if (x >= 11750)
	{
		if (flag22 == 0)
		{
		}
		else if (flag22 == 1)
		{
			flag22 = 0;
			mciSendString(_T("open music\\end.mp3 alias bgMusic "), NULL, 0, NULL);
			mciSendString(_T("play bgMusic repeat"), NULL, 0, NULL);
		}
	}
	else
	{
		if (flag42 == 0)
		{
			if (x >= 11650)
			{
				mciSendString(_T("close bgMusic"), 0, 0, 0);
				mciSendString(_T("stop bgMusic"), 0, 0, 0);
			}
		}
		else if (flag41 == 1)
		{
			flag42 = 0;
			mciSendString(_T("open music\\mei.mp3 alias bgMusic "), NULL, 0, NULL);
			mciSendString(_T("play bgMusic"), NULL, 0, NULL);
		}
	}

}
//by 马宇


void CSwordArtDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSwordArtDlg::OnPaint()
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
		//获取窗口DC指针
	CDC *cDC=this->GetDC();
	//获取窗口大小
	GetClientRect(&m_client);
	//创建缓冲DC
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(cDC,m_client.Width(),m_client.Height());
	m_cacheDC.SelectObject(&m_cacheCBitmap);
	//计算背景地图起始位置
	//————————————————————开始绘制——————————————————————
	//贴背景,现在贴图就是贴在缓冲DC：m_cache中了1
	if (count1 <= 0)
	{
		count1 = 0;
	}
		m_bg.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, count1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		if (flag)
			m_bg1.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, count1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		UI1.Draw(m_cacheDC, 1, 595, 149, 204, 0, 0, 149, 204);
		UI2.Draw(m_cacheDC, 94, 596, 125, 120, 0, 0, 125, 120);
		UI3.Draw(m_cacheDC, 164, 580, 76, 66, 0, 0, 76, 66);
		UI4.Draw(m_cacheDC, 243, 640, 214, 75, 0, 0, 214, 75);
		UI5.Draw(m_cacheDC, 90, 620, 133, 113, 0, 0, 113, 113);
		skillBox.Draw(m_cacheDC, 900, 680, 183, 50, 0, 0, 283, 70);//666
		MyHero.heroRC.Draw(m_cacheDC, 900, 680, 67, 67, 0, 0, 64, 64);//666
		MyHero.heroRS.Draw(m_cacheDC, 970, 680, 67, 67, 0, 0, 64, 64);//666
		MyHero.heroRS2.Draw(m_cacheDC, 1048, 680, 67, 67, 0, 0, 64, 64);//666
		MyHero.heroRH.Draw(m_cacheDC, 1108, 680, 67, 67, 0, 0, 64, 64);//666
		npc1.npc.Draw(m_cacheDC,1180-count1,450,80,120,npc1.frame*263,0,263,393);//*
	if(orignal>=3000)
	{
		m_side.Draw(m_cacheDC,800,400,50,50,0,0,50,50);
	}

	if (orignal >= 4000)
	{
		if (orignal <= 4700)
			count1 = 0;
		if (orignal <= 7300)
		{
			if (MyHero.direct==RIGHT&&!flag3)
			{
				count1 += 5;
				orignal += 5;
			}
			else if(orignal >= 4700&&MyHero.direct==LEFT && !flag3)
			{
				count1 -= 5;
				orignal -= 5;
			}
			else
			{
			}
		}
		if (flag)
		m_bg31.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, count1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		m_bg3.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, count1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		UI1.Draw(m_cacheDC, 1, 595, 149, 204, 0, 0, 149, 204);
		UI2.Draw(m_cacheDC, 94, 596, 125, 120, 0, 0, 125, 120);
		UI3.Draw(m_cacheDC, 164, 580, 76, 66, 0, 0, 76, 66);
		UI4.Draw(m_cacheDC, 243, 640, 214, 75, 0, 0, 214, 75);
		UI5.Draw(m_cacheDC, 90, 620, 133, 113, 0, 0, 113, 113);
		if (!flag5)
			arm1.Draw(m_cacheDC, 248, 645, 64, 64, 0, 0, 64, 64);
		if (!flag6)
			arm2.Draw(m_cacheDC, 322, 645, 64, 64, 0, 0, 64, 64);
		if (!flag7)
			arm3.Draw(m_cacheDC, 386, 645, 64, 64, 0, 0, 64, 64);
		npc2.npc.Draw(m_cacheDC, 1380 - count1, 450, 150, 150, 0, 0, 142, 140);//*//666
		npc3.npc.Draw(m_cacheDC, 3280 - count1, 350, 100, 150, 0, 0, 135, 189);//666
		building.Draw(m_cacheDC, 1480 - count1, 300, 500, 350, 0, 0, 1728, 896);
		skillBox.Draw(m_cacheDC, 900,680, 183, 66, 0, 0, 283, 70);//666
		MyHero.heroRC.Draw(m_cacheDC, 900,680, 67, 67, 0, 0, 64, 64);//666
		MyHero.heroRS.Draw(m_cacheDC, 970, 680, 67, 67, 0, 0, 64, 64);//666
		MyHero.heroRS2.Draw(m_cacheDC, 1048, 680, 67, 67, 0, 0, 64, 64);//666
		MyHero.heroRH.Draw(m_cacheDC, 1108, 680, 67, 67, 0, 0, 64, 64);//666
	}

	if (orignal >= 3990 && orignal <= 4010)
		flag9 = false;
	if (orignal <= 3990 || orignal >= 4010)
		flag9 = true;

	if (orignal >= 8140 && orignal <= 8200)
		flag10 = false;
	if (orignal <= 8140 || orignal >= 8200)
		flag10 = true;

	if (orignal >= 8170)
	{
			if (orignal <= 8700)
				count1 = 0;
			if (orignal <= 10800)
			{
				if (MyHero.direct == RIGHT)
				{
					count1 += 5;
					orignal += 5;
				}
				else if (orignal >= 8700 && MyHero.direct == LEFT)
				{
					count1 -= 5;
					orignal -= 5;
				}
				else
				{
				}
			}
		m_bg41.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, count1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		m_bg4.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, count1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		UI1.Draw(m_cacheDC, 1, 595, 149, 204, 0, 0, 149, 204);
		UI2.Draw(m_cacheDC, 94, 596, 125, 120, 0, 0, 125, 120);
		UI3.Draw(m_cacheDC, 164, 580, 76, 66, 0, 0, 76, 66);
		UI4.Draw(m_cacheDC, 243, 640, 214, 75, 0, 0, 214, 75);
		UI5.Draw(m_cacheDC, 90, 620, 133, 113, 0, 0, 113, 113);
		arm1.Draw(m_cacheDC, 248, 645, 64, 64, 0, 0, 64, 64);
		arm2.Draw(m_cacheDC, 322, 645, 64, 64, 0, 0, 64, 64);
		arm3.Draw(m_cacheDC, 386, 645, 64, 64, 0, 0, 64, 64);
		npc4.npc.Draw(m_cacheDC, 1280 - count1, 350, 100, 141, 0, 0, 100, 141);//666
		npc5.npc.Draw(m_cacheDC, 3180 - count1, 400, 100, 161,0, 0, 100, 161);//*
		skillBox.Draw(m_cacheDC, 900, 680, 183, 66, 0, 0, 283, 70);
		MyHero.heroRC.Draw(m_cacheDC, 900, 680, 67, 67, 0, 0, 64, 64);
		MyHero.heroRS.Draw(m_cacheDC, 970, 680, 67, 67, 0, 0, 64, 64);
		MyHero.heroRS2.Draw(m_cacheDC, 1048, 680, 67, 67, 0, 0, 64, 64);
		MyHero.heroRH.Draw(m_cacheDC, 1108, 680, 67, 67, 0, 0, 64, 64);
	}

	if (orignal >= 11660 && orignal <= 11780)
		flag11 = false;
	if (orignal <= 11660 || orignal >= 11780)
		flag11 = true;

	if (orignal >= 11700)
	{
		if (orignal <= 12700)
			count1 = 0;
		if (orignal <= 14800)
		{
			if (MyHero.direct == RIGHT)
			{
				count1 +=5;
				orignal += 5;
			}
			else if (orignal >= 12700 && MyHero.direct == LEFT)
			{
				count1 -= 5;
				orignal -= 5;
			}
			else
			{
			}
		}
		m_bg51.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, count1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		m_bg5.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, count1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		UI1.Draw(m_cacheDC, 1, 595, 149, 204, 0, 0, 149, 204);
		UI2.Draw(m_cacheDC, 94, 596, 125, 120, 0, 0, 125, 120);
		UI3.Draw(m_cacheDC, 164, 580, 76, 66, 0, 0, 76, 66);
		UI4.Draw(m_cacheDC, 243, 640, 214, 75, 0, 0, 214, 75);
		UI5.Draw(m_cacheDC, 90, 620, 133, 113, 0, 0, 113, 113);
		arm1.Draw(m_cacheDC, 248, 645, 64, 64, 0, 0, 64, 64);
		arm2.Draw(m_cacheDC, 322, 645, 64, 64, 0, 0, 64, 64);
		arm3.Draw(m_cacheDC, 386, 645, 64, 64, 0, 0, 64, 64);
		npc7.npc.Draw(m_cacheDC, 1280 - count1, 350, 150, 150, 0, 0, 150, 157);//666
		npc8.npc.Draw(m_cacheDC, 3180 - count1, 500, 180, 150, 0, 0, 170, 170);//*
		skillBox.Draw(m_cacheDC, 900, 680, 183, 66, 0, 0, 283, 70);
		MyHero.heroRC.Draw(m_cacheDC, 900, 680, 67, 67, 0, 0, 64, 64);
		MyHero.heroRS.Draw(m_cacheDC, 970,680, 67, 67, 0, 0, 64, 64);
		MyHero.heroRS2.Draw(m_cacheDC, 1048, 680, 67, 67, 0, 0, 64, 64);
		MyHero.heroRH.Draw(m_cacheDC, 1108, 680, 67, 67, 0, 0, 64, 64);
	}

	//有关门的操作
	if (orignal >= 6800&&orignal<=7650)
	{
		door.Draw(m_cacheDC, 3200-count1, 320, 120, 180, MyHero.frame * 366, 0, 366, 527);
			if (MyHero.y <= 350 && orignal >= 6000)
			{
				flag3 = true;
				flag = false;
			}
			if (flag3)
			{
				flagbg = false;
				m_bg21.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
				m_bg2.Draw(m_cacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
				UI1.Draw(m_cacheDC, 1, 595, 149, 204, 0, 0, 149, 204);
		        UI2.Draw(m_cacheDC, 94, 596, 125, 120, 0, 0, 125, 120);
		        UI3.Draw(m_cacheDC, 164, 580, 76, 66, 0, 0, 76, 66);
		        UI4.Draw(m_cacheDC, 243, 640, 214, 75, 0, 0, 214, 75);
		        UI5.Draw(m_cacheDC, 90, 620, 133, 113, 0, 0, 113, 113);
				door.Draw(m_cacheDC, 1050, 400, 120, 180, MyHero.frame * 366, 0, 366, 527);
				npcb.npc.Draw(m_cacheDC, 700, 550, 120, 180, MyHero.frame * 172, 0, 172, 193);
				//door.Draw(m_cacheDC, 300, 600, 120, 180, MyHero.frame * 366, 0, 366, 527);
				if (flag5)
					arm1.Draw(m_cacheDC, 600, 500, 64, 64, 0, 0, 64, 64);
				if (flag6)
					arm2.Draw(m_cacheDC, 700, 500, 64, 64, 0, 0, 64, 64);
				if (flag7)
					arm3.Draw(m_cacheDC, 800, 500, 64, 64, 0, 0, 64, 64);
				if (xx > 600 && xx < 650 && yy>500 && yy < 550 || !flag5)
				{
					flag5 = false;
					arm1.Draw(m_cacheDC, 248, 645, 64, 64, 0, 0, 64, 64);
				}
				if (xx > 700 && xx < 750 && yy>500 && yy < 550 || !flag6)
				{
					flag6 = false;
					arm2.Draw(m_cacheDC, 322, 645, 64, 64, 0, 0, 64, 64);
				}
				if (xx > 800 && xx < 850 && yy>500 && yy < 550 || !flag7)
				{
					flag7 = false;
					arm3.Draw(m_cacheDC, 386, 645, 64, 64, 0, 0, 64, 64);
				}

				armC.Draw(m_cacheDC, 600, 400, 100, 300, MyHero.frame * 104, 0, 104, 304);

				if (xx < 810 && xx>730 && yy <680 && yy>540) 
		        {
			          box.Draw(m_cacheDC, 365, 520, 870, 210, 0, 0, 870, 210);
					  if (t2 == 1)
			          {
						saber2.Draw(m_cacheDC, 450, 121, 266, 400, 0, 0, 266, 400);
						niu1.Draw(m_cacheDC, 800, 111, 380, 410, 0, 0, 380, 410);
						HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
						COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
						m_cacheDC.SetBkMode(TRANSPARENT);                             //透明字的背景
						SelectObject(m_cacheDC, Font);
						TextOut(m_cacheDC, 390,535, _T("我能帮你什么忙吗？"), 18);
						Font = CreateFont(20, 8, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
						SelectObject(m_cacheDC, Font);
						TextOut(m_cacheDC, 390, 585, _T("按E键继续..."), 12);
					  }
					  if (t2 == 2)
			          {
						saber3.Draw(m_cacheDC, 450, 121, 388, 400, 0, 0, 388, 400);
						niu1.Draw(m_cacheDC, 800, 111, 380,410, 0, 0, 380,410);
						HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
						COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
						m_cacheDC.SetBkMode(TRANSPARENT);                             //透明字的背景
						SelectObject(m_cacheDC, Font);
						TextOut(m_cacheDC, 390,535, _T("您好，我想买些装备"), 25);
						Font = CreateFont(20, 8, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
						SelectObject(m_cacheDC, Font);
						TextOut(m_cacheDC, 390, 585, _T("按E键继续..."), 12);
					  }
					  if (t2 == 3)
			          {
						saber3.Draw(m_cacheDC, 450, 121, 388, 400, 0, 0, 388, 400);
						niu2.Draw(m_cacheDC, 800, 101, 475,420, 0, 0, 475,420);
						HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
						COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
						m_cacheDC.SetBkMode(TRANSPARENT);                             //透明字的背景
						SelectObject(m_cacheDC, Font);
						TextOut(m_cacheDC, 390,535, _T("请随意挑选。"), 12);
						Font = CreateFont(20, 8, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
						SelectObject(m_cacheDC, Font);
						TextOut(m_cacheDC, 390, 585, _T("按E键结束..."), 12);
					  }

				  }
				
			}
	}

	changeMusic(orignal);//执行切换背景音乐的

	//英雄移动的相关判断
	if(MyHero.direct==LEFT)
	{
		if(MyHero.keyUp==RIGHTUP)
		{
			MyHero.heroL.Draw(m_cacheDC,MyHero.x,MyHero.y,100,150,MyHero.frame*88,0,88,140);
		}else
		{
			MyHero.heroLeft.Draw(m_cacheDC, MyHero.x, MyHero.y, 110, 160, MyHero.frame * 110, 0, 110, 149);
		}
	}else if(MyHero.direct==UP&&MyHero.direct2)
	{
		if(MyHero.keyUp==UPUP)
		{
			MyHero.heroR.Draw(m_cacheDC,MyHero.x,MyHero.y,100,150,MyHero.frame*88,0,88,140);
		}else
		{
			MyHero.heroRight.Draw(m_cacheDC, MyHero.x, MyHero.y, 110, 160, MyHero.frame * 110, 0, 110, 149);
		}
	}
	else if (MyHero.direct == UP&&!MyHero.direct2)
	{
		if (MyHero.keyUp == UPUP)
		{
			MyHero.heroL.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
		}
		else
		{
			MyHero.heroLeft.Draw(m_cacheDC, MyHero.x, MyHero.y, 110, 160, MyHero.frame * 110, 0, 110, 149);
		}
	}
	 else if(MyHero.direct==RIGHT)
	{
		
		if(MyHero.keyUp==LEFTUP||MyHero.keyUp==DOMNUP)
		{
			MyHero.heroR.Draw(m_cacheDC,MyHero.x,MyHero.y,100,150,MyHero.frame*88,0,88,140);
		}else
		{
			MyHero.heroRight.Draw(m_cacheDC, MyHero.x, MyHero.y, 110, 160, MyHero.frame * 110, 0, 110, 149);
		}
	}else if(MyHero.direct==DOWN&&MyHero.direct2)
	{
		if(MyHero.keyUp==DOMNUP)
		{
			MyHero.heroR.Draw(m_cacheDC,MyHero.x,MyHero.y,100,150,MyHero.frame*88,0,88,140);
		}else
		{
			MyHero.heroRight.Draw(m_cacheDC, MyHero.x, MyHero.y, 110, 160, MyHero.frame * 110, 0, 110, 149);
		}
	}
	else if (MyHero.direct == DOWN&&!MyHero.direct2)
	{
		if (MyHero.keyUp == DOMNUP)
		{
			MyHero.heroL.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
		}
		else
		{
			MyHero.heroLeft.Draw(m_cacheDC, MyHero.x, MyHero.y, 110, 160, MyHero.frame * 110, 0, 110, 149);
		}
	}
	else if(MyHero.direct==STAB&&!MyHero.direct2)
	{
		MyHero.heroLStab.Draw(m_cacheDC,MyHero.x-70,MyHero.y-70,198,255,MyHero.frame*278,0,278,200);
	}
	else if (STABUP == MyHero.direct)
	{
		MyHero.heroL.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	else if (MyHero.direct == STAB&&MyHero.direct2)
	{
		MyHero.heroRStab.Draw(m_cacheDC, MyHero.x-70, MyHero.y-70, 195, 253, MyHero.frame * 279, 0, 279, 200);
	}
	else if (STABUP == MyHero.direct)
	{
		MyHero.heroR.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	else if (MyHero.direct == CUT && !MyHero.direct2)
	{
		MyHero.heroLCut.Draw(m_cacheDC, MyHero.x - 50, MyHero.y - 10, 200, 160, MyHero.frame * 265, 0, 265, 115);
	}
	else if (CUTUP == MyHero.direct)
	{
		MyHero.heroL.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	else if (MyHero.direct == CUT&&MyHero.direct2)
	{
		MyHero.heroRCut.Draw(m_cacheDC, MyHero.x - 50, MyHero.y - 10, 200, 160, MyHero.frame * 265, 0, 265, 115);
	}
	else if (CUTUP == MyHero.direct)
	{
		MyHero.heroR.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	else if (MyHero.direct == SHEAR && !MyHero.direct2)
	{
		MyHero.heroLShear.Draw(m_cacheDC, MyHero.x - 40, MyHero.y - 40, 200, 210, MyHero.frame * 265, 0, 265, 160);
	}
	else if (SHEARUP == MyHero.direct)
	{
		MyHero.heroL.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	else if (MyHero.direct ==SHEAR&&MyHero.direct2)
	{
		MyHero.heroRShear.Draw(m_cacheDC, MyHero.x - 40, MyHero.y - 40, 200, 210, MyHero.frame * 265, 0, 265, 160);
	}
	else if (SHEARUP == MyHero.direct)
	{
		MyHero.heroR.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	//最后将缓冲DC内容输出到窗口DC中
	else if (MyHero.direct == HACK && !MyHero.direct2)
	{
		MyHero.heroLHack.Draw(m_cacheDC, MyHero.x - 110, MyHero.y - 100, 258, 350, MyHero.frame * 305, 0, 305, 290);
	}
	else if (HACKUP == MyHero.direct)
	{
		MyHero.heroL.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	else if (MyHero.direct == HACK&&MyHero.direct2)
	{
		MyHero.heroRHack.Draw(m_cacheDC, MyHero.x - 110, MyHero.y - 100, 258, 350, MyHero.frame * 305, 0, 305, 290);
	}
	else if (HACKUP == MyHero.direct)
	{
		MyHero.heroR.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	else
	{
		MyHero.heroR.Draw(m_cacheDC, MyHero.x, MyHero.y, 100, 150, MyHero.frame * 88, 0, 88, 140);
	}
	
	if(orignal >= 8200&&orignal <= 11750)
	{
	for(int i=0;i<SNOW_NUMBER;i++)  
      {  
        //画出粒子  1
       m_snowMap[Snow[i].number].Draw(m_cacheDC,Snow[i].x,Snow[i].y,15,15);  
        //对粒子的位置进行更新  
        Snow[i].y+=1;  
        if(Snow[i].y>=700)    //当落到最下面后，再回到最上面去  
            Snow[i].y=0;  
        //为了更自然，在水平方向上也发生位移，就像有风一样  
        if(rand()%2==0)  
            Snow[i].x+=1;  
        else   
            Snow[i].x-=1;  
        if(Snow[i].x<0)  
            Snow[i].x= WINDOW_WIDTH;      //水平方向上出界后到另一边去  
        else if(Snow[i].x>= WINDOW_WIDTH)
            Snow[i].x=0;  
      }  
	}
	if (orignal< 1279&& orignal>850 && MyHero.y < 600 && MyHero.y>325)
	{
		if (xx < 956 && xx>650 && yy < 767 && yy>363) 
		{
			box.Draw(m_cacheDC, 365,520, 870, 210, 0, 0, 870, 210);
			if (t == 1)
			{
				
				saber1.Draw(m_cacheDC, 450, 121, 279, 400, 0, 0, 279, 400);
				chuyin1.Draw(m_cacheDC, 800, 121, 433, 400, 0, 0, 433, 400);
				HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
				m_cacheDC.SetBkMode(TRANSPARENT);                             //透明字的背景
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390,535, _T("您就是寂静城里的风之女吗？你怎么会在这里？"), 42);
				TextOut(m_cacheDC, 390,575, _T("这里怎么变成了废墟？剑道世界究竟发生了什么？"), 45);
				Font = CreateFont(20, 8, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390, 625, _T("按E键继续..."), 12);
			}
			if (t == 2)
			{
				
				saber1.Draw(m_cacheDC, 450, 121, 279, 400, 0, 0, 279, 400);
				chuyin2.Draw(m_cacheDC, 800, 121, 433, 400, 0, 0, 433, 400);
				HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
				m_cacheDC.SetBkMode(TRANSPARENT);                            //透明字的背景
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390, 535, _T("冒险家，你终于来了，故事的开头是这样的：在毁灭纪元中，恶魔第七使徒找到了时"), 74);
				TextOut(m_cacheDC, 390, 575, _T("空洞,带领他的幽灵军队降临在这片大陆，他们摧毁了我们的防御，"), 58);
				TextOut(m_cacheDC, 390, 615, _T("剑道世界从此不再安宁,邻都卡尔特也难逃厄运"),42);
				Font = CreateFont(20, 8, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390, 665, _T("按E键继续..."), 12);
			}
			if (t == 3)
			{
				saber2.Draw(m_cacheDC, 450, 121, 266, 400, 0, 0, 266, 400);
				chuyin2.Draw(m_cacheDC, 800, 121, 433, 400, 0, 0, 433, 400);
				HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
				m_cacheDC.SetBkMode(TRANSPARENT);                             //透明字的背景
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390, 535, _T("看来这片大陆危在旦夕"), 20);
				//TextOut(m_cacheDC, 390, 575, "看来这片大陆危在旦夕", 15);
				Font = CreateFont(20, 8, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390,585, _T("按E键继续..."), 12);
			}
			if (t == 4)
			{
				saber2.Draw(m_cacheDC, 450, 121, 266, 400, 0, 0, 266, 400);
				chuyin3.Draw(m_cacheDC, 800, 121, 433, 400, 0, 0, 433, 400);
				HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
				m_cacheDC.SetBkMode(TRANSPARENT);                              //透明字的背景
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390, 535, _T("寂静城还剩下几条完好的街道和爱丽丝宫殿"), 40);
				TextOut(m_cacheDC, 390, 575, _T("勇敢的冒险家，拿起手中的剑，去打败第七使徒吧"), 43);
				TextOut(m_cacheDC, 390, 615, _T("前面有一家武器店，你可以随时强化自己的能力"), 43);
				Font = CreateFont(20, 8, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390, 665, _T("按E键继续..."), 12);
			}
			if (t == 5)
			{
				saber2.Draw(m_cacheDC, 450, 121, 266, 400, 0, 0, 266, 400);
				chuyin3.Draw(m_cacheDC, 800, 121, 433, 400, 0, 0, 433, 400);
				HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
				COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
				m_cacheDC.SetBkMode(TRANSPARENT);                              //透明字的背景
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390, 535, _T("是否接受主线任务——风之女的委托？"), 18);
				crOld = SetTextColor(m_cacheDC, RGB(255, 215,0));
				SelectObject(m_cacheDC, Font);
				TextOut(m_cacheDC, 390, 575, _T("是"), 2);
				TextOut(m_cacheDC, 390, 615, _T("否"), 2);
				if (k1 % 2 != 0)
					button.Draw(m_cacheDC, 450, 550,63, 80, 0, 0, 63, 80);
				else if(k1%2==0)
					button.Draw(m_cacheDC, 450, 590, 63, 80, 0, 0, 63, 80);
			}
			if (t == 6)
			{
				saber2.Draw(m_cacheDC, 450, 121, 266, 400, 0, 0, 266, 400);
				chuyin3.Draw(m_cacheDC, 800, 121, 433, 400, 0, 0, 433, 400);
				if (k1 % 2 != 0)
				{
					HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
					COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
					m_cacheDC.SetBkMode(TRANSPARENT);                              //透明字的背景
					SelectObject(m_cacheDC, Font);
					TextOut(m_cacheDC, 390, 535, _T("我在东边等你。"), 15);
				}
				else if (k1 % 2 == 0)
				{
					HFONT  Font = CreateFont(30, 10, 0, 0, 400, FALSE, FALSE, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
					COLORREF crOld = SetTextColor(m_cacheDC, RGB(255, 255, 255));
					m_cacheDC.SetBkMode(TRANSPARENT);                              //透明字的背景
					SelectObject(m_cacheDC, Font);
					TextOut(m_cacheDC, 390, 535, _T("真的要拒绝吗？"), 15);
					crOld = SetTextColor(m_cacheDC, RGB(255, 215, 0));
					//m_cacheDC.SetBkMode(TRANSPARENT);                              //透明字的背景
					SelectObject(m_cacheDC, Font);
					TextOut(m_cacheDC, 390, 575, _T("狠心拒绝。"), 10);
					TextOut(m_cacheDC, 390, 615, _T("再考虑一下。"), 12);
					if (k2 % 2 != 0)
						button.Draw(m_cacheDC, 500, 550, 63, 80, 0, 0, 63, 80);
					else
						button.Draw(m_cacheDC, 500, 590, 63, 80, 0, 0, 63, 80);
				}
			}
		}
	}

	cDC->BitBlt(0,0,m_client.Width(),m_client.Height(),&m_cacheDC,0,0,SRCCOPY);

	//————————————————————绘制结束—————————————————————
	
	//在绘制完图后,使窗口区有效
	ValidateRect(&m_client);
	//释放缓冲DC
	m_cacheDC.DeleteDC();
	//释放对象
	m_cacheCBitmap.DeleteObject();
	//释放窗口DC
	ReleaseDC(cDC);
		CDialogEx::OnPaint();
	}
}//by马宇 and 于溟鲲

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSwordArtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CSwordArtDlg::CanPass()
{
	for (int x = MyHero.x; x<MyHero.x + MyHero.width; x++)  //检测的宽度是人物的宽度
	{
		if (MyHero.direct == DOWN)   //方向向上时
		{
			if (m_bg.GetPixel(x, MyHero.y - 5) == RGB(0, 0, 0))
				return false;//遇到黑色像素返回false
		}
		else if (MyHero.direct == UP)  //方向向下时
		{
			//向下时，记得加上人物的宽度，因为人物的xy位置是它的左上角坐标
			if (m_bg.GetPixel(x, MyHero.y + MyHero.height + 5) == RGB(0, 0, 0))
				return false;//遇到黑色像素返回false
		}
	}

	for (int y = MyHero.y; y<MyHero.y + MyHero.height; y++)  //检测的宽度是人物的高度
	{
		if (MyHero.direct == LEFT)   //方向向左时
		{
			if (m_bg.GetPixel(MyHero.x - 5, y) == RGB(0, 0, 0))
				return false;//遇到黑色像素返回false
		}
		else if (MyHero.direct == RIGHT)  //方向向右边时
		{
			//向下时，记得加上人物的宽度，因为人物的xy位置是它的左上角坐标
			if (m_bg.GetPixel(MyHero.width + 5 + MyHero.x, y) == RGB(0, 0, 0))
				return false;//遇到黑色像素返回false
		}
	}
	return true;
}

void GetScreenX(int& xHero, int& x2Hero, int& yHero, int mapWidth, int direct, int& orignal, bool& direct2)//*copy 这个函数 七月四号 马宇
{
	//如果人物在最左边和最右边半个屏幕内时，那么人物就处在屏幕中间
	if (orignal<mapWidth - WINDOW_WIDTH / 2  && orignal>WINDOW_WIDTH / 2)
	{
		if (direct == RIGHT)
		{
			direct2 = true;
			xHero += 5;
			orignal += 5;
			count1 += 5;

		}
		else if (direct == LEFT)
		{
			direct2 = false;
			xHero -= 5;
			orignal -= 5;
			count1 -= 5;
		}
		else if (direct == UP)
		{
			yHero += 5;
		}
		else if (direct == DOWN)
		{
			yHero -= 5;
		}
		else if (direct == STAB&&direct2)
		{
			xHero += 20;
			orignal += 20;
		}
		else if (direct == STAB && !direct2)
		{
			xHero -= 20;
			orignal -= 20;
		}
		else if (direct == CUT&&direct2)
		{
			xHero += 20;
			orignal += 20;
		}
		else if (direct == CUT && !direct2)
		{
			xHero -= 20;
			orignal -= 20;
		}
		else if (direct == SHEAR&&direct2)
		{
			xHero += 20;
			orignal += 20;
		}
		else if (direct == SHEAR && !direct2)
		{
			xHero -= 20;
			orignal -= 20;
		}
		else if (direct == HACK&&direct2)
		{
			xHero += 20;
			orignal += 20;
		}
		else if (direct == HACK && !direct2)
		{
			xHero -= 20;
			orignal -= 20;
		}
		xHero = WINDOW_WIDTH / 2;
	}
	else if (xHero <= WINDOW_WIDTH)     //在最左边半个屏幕时，人物在屏幕上的位置就是自己的x坐标了xHero<=WINDOW_WIDTH/2&&
	{
		if (direct == RIGHT)
		{
			direct2 = true;
			xHero += 5;
			orignal += 5;
		}
		else if (direct == LEFT)
		{
			direct2 = false;
			xHero -= 5;
			orignal -= 5;
		}
		else if (direct == UP)
		{
			yHero += 5;
		}
		else if (direct == DOWN)
		{
			yHero -= 5;
		}
		else if (direct == STAB&&direct2)
		{
			xHero += 20;
			orignal += 20;
		}
		else if (direct == STAB && !direct2)
		{
			xHero -= 20;
			orignal -= 20;
		}
		else if (direct == CUT&&direct2)
		{
			xHero += 20;
			orignal += 20;
		}
		else if (direct == CUT && !direct2)
		{
			xHero -= 20;
			orignal -= 20;
		}
		else if (direct == SHEAR&&direct2)
		{
			xHero += 20;
			orignal += 20;
		}
		else if (direct == SHEAR && !direct2)
		{
			xHero -= 20;
			orignal -= 20;
		}
		else if (direct == HACK&&direct2)
		{
			xHero += 20;
			orignal += 20;
		}
		else if (direct == HACK && !direct2)
		{
			xHero -= 20;
			orignal -= 20;
		}
		if (!flag9)
		{
			xHero = xHero + 1600;
		}
		if(!flag10)
			xHero = xHero + 1600;
		if(!flag11)
			xHero = xHero + 1600;
	}
	else
	{
			xHero = xHero - 1600;
	}
}
void CSwordArtDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//nChar表示按下的键值
	switch(nChar)
	{
	case 'a':         //游戏中按下的键当然应该不区分大小写了
	case 'A':
		MyHero.direct=LEFT;
		if (CanPass())
			GetScreenX(MyHero.x,MyHero.x2,MyHero.y,4000,MyHero.direct,orignal,MyHero.direct2);
		break;
	case 'd':
	case 'D':
		MyHero.direct=RIGHT;
		if (CanPass())
			GetScreenX(MyHero.x,MyHero.x2,MyHero.y,4000,MyHero.direct,orignal, MyHero.direct2);
		break;
	case 's':
	case 'S':
		MyHero.direct=UP;
	    if(CanPass())
			GetScreenX(MyHero.x,MyHero.x2,MyHero.y,4000,MyHero.direct,orignal, MyHero.direct2);
	    if (t==5)
			k1++;
		if (t==6)
			k2++;
		break;
		break;
	case 'w':
	case 'W':
	    MyHero.direct=DOWN;
		if(CanPass())
			GetScreenX(MyHero.x,MyHero.x2,MyHero.y,4000,MyHero.direct,orignal, MyHero.direct2);
		if (t==5)
			k1++;
		if (t==6)
			k2++;
		break;
	case 'J':
	case 'j':
		MyHero.direct=STAB;
		if(CanPass())
		    GetScreenX(MyHero.x,MyHero.x2,MyHero.y,4000,MyHero.direct,orignal, MyHero.direct2);
		break;
	case 'E':
	case 'e':	
		{
		t++;
		if(flagbg==false)
		   t2++;
		}
		break;
	case 'K':
	case 'k':
		MyHero.direct = CUT;
		if (CanPass())
			GetScreenX(MyHero.x, MyHero.x2, MyHero.y, 4000, MyHero.direct, orignal, MyHero.direct2);
		break;
	case 'L':
	case 'l':
		MyHero.direct = SHEAR;
		if (CanPass())
			GetScreenX(MyHero.x, MyHero.x2, MyHero.y, 3000, MyHero.direct, orignal, MyHero.direct2);
		break;
	case 'U':
	case 'u':
		MyHero.direct = HACK;
		if (CanPass())
			GetScreenX(MyHero.x, MyHero.x2, MyHero.y, 3000, MyHero.direct, orignal, MyHero.direct2);
		break;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSwordArtDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//nChar表示按下的键值
	switch(nChar)
	{
	case 'a':         //游戏中按下的键当然应该不区分大小写了
	case 'A':
		MyHero.keyUp=LEFTUP;
		break;
	case 'd':
	case 'D':
		MyHero.keyUp=RIGHTUP;
		break;
	case 's':
	case 'S':
		MyHero.keyUp=UPUP;;
		break;
	case 'w':
	case 'W':
		MyHero.keyUp=DOMNUP;
		break;
	case 'J':
	case 'j':
		MyHero.keyUp=STABUP;
		break;
	case 'k':
	case 'K':
		MyHero.keyUp = CUTUP;
		break;
	case 'l':
	case 'L':
		MyHero.keyUp = SHEARUP;
		break;
	case 'U':
	case 'u':
		MyHero.keyUp = HACKUP;
		break;
	}
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CSwordArtDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 xx = point.x;
	 yy = point.y;
	CDialogEx::OnLButtonDown(nFlags, point);
}

int CSwordArtDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//创建一个105毫秒产生一次消息的定时器
	SetTimer(TIMER_PAINT,30,NULL);
	//创建人物行走动画定时器
	SetTimer(TIMER_HEROMOVE,105,NULL);
	SetTimer(TIMER_NPCMOVE,100,NULL);
	return 0;
}

void CSwordArtDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case TIMER_PAINT:OnPaint();
		break;  //若是重绘定时器，就执行OnPaint函数
	case TIMER_HEROMOVE:               //控制人物移动的定时器
		{
			MyHero.frame++;              //每次到了间隔时间就将图片换为下一帧
			if(MyHero.frame==7)          //到最后了再重头开始
				MyHero.frame=0;
		}
		break;
	case TIMER_NPCMOVE:
		{
			npc1.frame++;
			if(npc1.frame==29)          //到最后了再重头开始
				npc1.frame=0;
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

HBRUSH CSwordArtDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	/*
	if(nCtlColor ==CTLCOLOR_EDIT)
	{
	pDC->SetBkMode(TRANSPARENT);//设置为透明
	return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
	}
	*/
	return hbr;
}

//聊天窗口附在游戏窗口右边并且随着游戏窗口移动by陈海林
void CSwordArtDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnMoving(fwSide, pRect);
	int pox = pRect->left;  
    int poy = pRect->top;  
	m_dlg3->SetWindowPos(NULL,pRect->left+1592,pRect->top,250,791,SWP_SHOWWINDOW);  
	// TODO: 在此处添加消息处理程序代码
}

//重写by陈海林
void CSwordArtDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
}

void CSwordArtDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	 EndDialog(IDCANCEL);//关闭窗口
	CDialogEx::OnClose();
}
