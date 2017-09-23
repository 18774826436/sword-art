
// Sword  ArtDlg.h : 头文件
//

#pragma once
#include "hero.h"
#include "afxcmn.h"
#include "afxwin.h"
//CPictureEx *pAutoGif;
#define SNOW_NUMBER 120  //雪花例子的数量  

class snow
{
public:
	int x;     //粒子的x坐标  
	int y;     //粒子的y坐标  
	int number;//粒子编号，共七种粒子  
};

class NPC
{
public:
	CImage npc;   //npc图片
	int frame;    //npc的到第几张图片
};//by马宇

// CSwordArtDlg 对话框
class CSwordArtDlg : public CDialogEx
{
	
// 构造
public:
	CSwordArtDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SWORDART_DIALOG };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CRect m_client;    //保存客户区大小

	CImage m_snowMap[7];  

	NPC npc1;
	NPC npc2;
	NPC npc3;
	NPC npc4;
	NPC npc5;
	NPC npc7;
	NPC npc8;
	NPC npcb;
	hero MyHero;
	snow Snow[SNOW_NUMBER];//声明类
	//CImage m_bgblack; //背景蒙版图
	CImage m_bg;      //背景图片
	CImage m_bg1;
	CImage m_bg2;
	CImage m_bg21;		//背景蒙版
	CImage m_bg3;
	CImage m_bg31;
	CImage m_bg4;
	CImage m_bg41;
	CImage m_bg5;
	CImage m_bg51;
	
	CImage m_side;		//转场按钮
	CImage door;
	CImage skillBox;
	CImage building;
	CImage arm;      //*装备栏
	CImage arm1;	//*各种装备
	CImage arm2;
	CImage arm3;
	CImage armC;

	CImage saber1;//对话相关
	CImage saber2;
	CImage saber3;
	CImage chuyin1;
	CImage chuyin2;
	CImage chuyin3;
	CImage niu1;
	CImage niu2;
	CImage box;
	CImage button;
	//各种UI
	CImage UI1;
	CImage UI2;
	CImage UI3;
	CImage UI4;
	CImage UI5;

	int m_mapWidth;      //背景地图的宽度
	CDC m_cacheDC;   //缓冲DC
	CBitmap m_cacheCBitmap;//缓冲位图
// 操作

	
// 重写

// 实现
protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	bool CanPass();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);

	virtual void OnOK();
	virtual void OnCancel();
};
