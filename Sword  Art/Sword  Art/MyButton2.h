#pragma once
/*֮����д�����ػ��࣬
����Ϊ��û������дһ������ͨ���е��ػ水ť����
��ΪҪ���ݱ���ͼƬ�Ĳ�ͬ��ʵ�ְ�ť��͸��
by �º���
*/
// CMyButton2

class CMyButton2 : public CButton
{
	DECLARE_DYNAMIC(CMyButton2)

public:
	CMyButton2();
	virtual ~CMyButton2();
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
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
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


