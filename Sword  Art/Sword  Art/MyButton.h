#pragma once
//��ť�ػ�by�º���

// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();
public:
	void SetBkColor(COLORREF color);//���ñ���ɫ
	void SetTextColor(COLORREF color);//�����ı���ɫ
private:
	bool m_bOver;//�ɿ����
	bool m_bDown;//�������
	bool m_bDisable;
	bool m_bTracking;
	COLORREF m_bkColor;
	COLORREF m_textColor;
protected:
	DECLARE_MESSAGE_MAP()
	/*�ڴ��ڵ�CWnd::Create()/CreateEx()���÷���ǰ,Ҫ����PreCreateWindow(),
	��Create()/CreateEx()�еķ���������Ԥ��������.֮�����OnCreate����ʵ�ʵĴ��ڴ���,
	���غ�,Create()/CreateEx()Ҳ����,���ڴ�������.
	*/
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();//��ܵ��������Ա�����������ڴ��ڱ����໯֮ǰ����������Ҫ�����໯�������������������ؼ��Ķ�̬���໯�����Ǹ��߼������غ���
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);//���������ͣʱ�Ĳ���
	afx_msg void OnEnable(BOOL bEnable);
private:
	void ButtonInit();
	void DrawButton();
	void DrawButton(HDC hDestDC);
};


