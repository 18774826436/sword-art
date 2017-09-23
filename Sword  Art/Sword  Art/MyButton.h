#pragma once
//按钮重绘by陈海林

// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();
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
	/*在窗口的CWnd::Create()/CreateEx()调用返回前,要调用PreCreateWindow(),
	对Create()/CreateEx()中的风格参数进行预处理设置.之后调用OnCreate进行实际的窗口创建,
	返回后,Create()/CreateEx()也返回,窗口创建结束.
	*/
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();//框架调用这个成员函数以允许在窗口被子类化之前进行其它必要的子类化。重载这个函数以允许控件的动态子类化。这是个高级可重载函数
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


