#pragma once
/*之所以写两个重绘类，
是因为我没有能力写一个具有通用行的重绘按钮方法
因为要根据背景图片的不同来实现按钮的透明
by 陈海林
*/
// CMyButton2

class CMyButton2 : public CButton
{
	DECLARE_DYNAMIC(CMyButton2)

public:
	CMyButton2();
	virtual ~CMyButton2();
public:
	void SetBkColor(COLORREF color);//设置背景色
	void SetTextColor(COLORREF color);//设置文本颜色
private:
	bool m_bOver;//松开鼠标
	bool m_bDown;//按下鼠标
	bool m_bDisable;
	bool m_bTracking;
	COLORREF m_bkColor;
	COLORREF m_textColor;
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);//设置鼠标悬停时的操作
	afx_msg void OnEnable(BOOL bEnable);
private:
	void ButtonInit();
	void DrawButton();
	void DrawButton(HDC hDestDC);
};


