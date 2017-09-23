// MyButton2.cpp : 实现文件
//

#include "stdafx.h"
#include "Sword  Art.h"
#include "MyButton2.h"
#include "signup.h"

// CMyButton2

IMPLEMENT_DYNAMIC(CMyButton2, CButton)

CMyButton2::CMyButton2()
{

}

CMyButton2::~CMyButton2()
{
}


BEGIN_MESSAGE_MAP(CMyButton2, CButton)
		ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_ENABLE()
END_MESSAGE_MAP()


void CMyButton2::SetBkColor(COLORREF color)
{
	m_bkColor=color;
}
void CMyButton2::SetTextColor(COLORREF color)
{
	m_textColor=color;
}

BOOL CMyButton2::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bRet=CButton::PreCreateWindow(cs);
	ButtonInit();
	return bRet;
}

void CMyButton2::PreSubclassWindow()
{
	CButton::PreSubclassWindow();
	ButtonInit();
}
void CMyButton2::ButtonInit()
{
	m_bTracking=false;
	m_bOver=m_bDown=m_bDisable=false;
	m_bDisable=IsWindowEnabled()?FALSE:TRUE;
	ModifyStyle(NULL,BS_OWNERDRAW);
}

void CMyButton2::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	DrawButton(lpDrawItemStruct->hDC);
}

void CMyButton2::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		m_bOver = TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 50;
		m_bTracking = (bool)_TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}

void CMyButton2::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown=TRUE;

	CButton::OnLButtonDown(nFlags, point);
}

void CMyButton2::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDown=FALSE;
	CButton::OnLButtonUp(nFlags, point);
}
LRESULT CMyButton2::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	m_bDown=FALSE;
	//InvalidateRect是一个函数，该函数向指定的窗体更新区域添加一个矩形，然后窗口客户区域的这一部分将被重新绘制。
	InvalidateRect(NULL, FALSE);
	return 0;
}

LRESULT CMyButton2::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bOver = TRUE;
	InvalidateRect(NULL);
	return 0;
}
void CMyButton2::DrawButton()
{
	HDC hDC=::GetDC(m_hWnd);
	DrawButton(hDC);
	::ReleaseDC(m_hWnd,hDC);
}
void CMyButton2::DrawButton(HDC hDestDC)
{
	CRect rc;
	GetClientRect(rc);
	int nWindth=rc.Width();
	int nHeight=rc.Height();
	HDC hDC=CreateCompatibleDC(hDestDC);//创建兼容DC,采用双缓冲画出
	HDC hMaskDC=CreateCompatibleDC(hDestDC);
	HBITMAP hBitmap=CreateCompatibleBitmap(hDestDC,nWindth,nHeight);
	HBITMAP hMaskBitmap=CreateCompatibleBitmap(hDestDC,nWindth,nHeight);
	HBITMAP hOldBitmap=(HBITMAP)SelectObject(hDC,hBitmap);
	HBITMAP hOldMaskBitmap=(HBITMAP)SelectObject(hMaskDC,hMaskBitmap);
	SetBkMode(hDC,TRANSPARENT);

	//把父窗口的背景图复制到按钮的DC上,实现视觉透明----------------
	signup* pParent=(signup*)GetParent();
	CPoint pt(0,0);
	MapWindowPoints(pParent,&pt,1);
	pParent->m_bkImage2.BitBlt(hDC,rc,pt,SRCCOPY);


	//-------------------------------------------------------------
	int nAlpha=100;//0--255
	int nOffset=0;

	HBRUSH hbr=CreateSolidBrush(m_bkColor);
	FillRect(hMaskDC,&rc,hbr);
	DeleteObject(hbr);

	if(m_bDisable){
		nAlpha=100;
	}else if(m_bDown){
		nAlpha=180;
		nOffset=1;
	}else if(m_bOver){
		nAlpha=150;
	}else{
		nAlpha=100;
	}
	BLENDFUNCTION blend;
	memset( &blend, 0, sizeof( blend) );
	blend.BlendOp= AC_SRC_OVER;
	blend.SourceConstantAlpha= nAlpha; // 透明度 最大255

	HRGN hRgn=CreateRoundRectRgn(0,0,nWindth,nHeight,3,3);
	SelectClipRgn (hDC,hRgn);
	AlphaBlend (hDC,0,0,nWindth,nHeight,hMaskDC, 0,0,nWindth,nHeight,blend);

	CString strText;
	GetWindowText(strText);
	if(strText!=_T("")){
		rc.InflateRect(-2,-2);
		rc.OffsetRect(nOffset,nOffset);
		HFONT hFont=(HFONT)SendMessage(WM_GETFONT);
		if(!hFont)hFont=(HFONT)GetStockObject(DEFAULT_GUI_FONT);
		HFONT hOldFont=(HFONT)SelectObject(hDC,hFont);
		::SetTextColor(hDC,m_textColor);
		::DrawText(hDC,strText,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_WORD_ELLIPSIS);
		::SelectObject(hDC,hOldFont);
	}
	SelectClipRgn (hDC,NULL);
	DeleteObject(hRgn);
	//复制到控件的DC上------------------------
	BitBlt(hDestDC,0,0,nWindth,nHeight,hDC,0,0,SRCCOPY);
	//删除资源,释放内存-----------------------
	SelectObject(hDC,hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hDC);
	SelectObject(hMaskDC,hOldMaskBitmap);
	DeleteObject(hMaskBitmap);
	DeleteDC(hMaskDC);

}
void CMyButton2::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);
	m_bDisable=IsWindowEnabled()?FALSE:TRUE;
	DrawButton();
}



// CMyButton2 消息处理程序


