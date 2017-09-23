
// Sword  ArtDlg.h : ͷ�ļ�
//

#pragma once
#include "hero.h"
#include "afxcmn.h"
#include "afxwin.h"
//CPictureEx *pAutoGif;
#define SNOW_NUMBER 120  //ѩ�����ӵ�����  

class snow
{
public:
	int x;     //���ӵ�x����  
	int y;     //���ӵ�y����  
	int number;//���ӱ�ţ�����������  
};

class NPC
{
public:
	CImage npc;   //npcͼƬ
	int frame;    //npc�ĵ��ڼ���ͼƬ
};//by����

// CSwordArtDlg �Ի���
class CSwordArtDlg : public CDialogEx
{
	
// ����
public:
	CSwordArtDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SWORDART_DIALOG };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CRect m_client;    //����ͻ�����С

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
	snow Snow[SNOW_NUMBER];//������
	//CImage m_bgblack; //�����ɰ�ͼ
	CImage m_bg;      //����ͼƬ
	CImage m_bg1;
	CImage m_bg2;
	CImage m_bg21;		//�����ɰ�
	CImage m_bg3;
	CImage m_bg31;
	CImage m_bg4;
	CImage m_bg41;
	CImage m_bg5;
	CImage m_bg51;
	
	CImage m_side;		//ת����ť
	CImage door;
	CImage skillBox;
	CImage building;
	CImage arm;      //*װ����
	CImage arm1;	//*����װ��
	CImage arm2;
	CImage arm3;
	CImage armC;

	CImage saber1;//�Ի����
	CImage saber2;
	CImage saber3;
	CImage chuyin1;
	CImage chuyin2;
	CImage chuyin3;
	CImage niu1;
	CImage niu2;
	CImage box;
	CImage button;
	//����UI
	CImage UI1;
	CImage UI2;
	CImage UI3;
	CImage UI4;
	CImage UI5;

	int m_mapWidth;      //������ͼ�Ŀ��
	CDC m_cacheDC;   //����DC
	CBitmap m_cacheCBitmap;//����λͼ
// ����

	
// ��д

// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
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
