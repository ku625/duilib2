#ifndef __TAG_CONTROL_H_
#define __TAG_CONTROL_H_

namespace DuiLib{

class CTagMoveUI : public CHorizontalLayoutUI
{
	DUI_DECLARE_EXTENDED_CONTROL(TagMove, CTagMoveUI)
public:	
	CTagMoveUI();
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	virtual void DoEvent(TEventUI& event);

	void UpdateOldRect(){m_rcOldRect = m_rcItem;}
	void SetOldRect(RECT rect){m_rcOldRect = rect;}
	RECT GetOldRect(){return m_rcOldRect; }
	void SetTargetRect(RECT rect);
	RECT GetTargetRect();
		
protected:
	enum{ ID_MOVE_TIMER = 15};	//用于移动的定时器ID
		
	bool m_bIsLButtonDowning;	//是否按下左键
	int	m_nLButtonDownCX;		//鼠标在按钮中的位置CX
	int m_nLButtonDownCY;		//鼠标在按钮中的位置CY

	RECT m_rcTargetRect;		//目标位置
	RECT m_rcCurrentRect;		//当前位置
	RECT m_rcOldRect;			//移动前的位置
	int m_nStepLen;				//移动步长
	bool m_bIsMoving;			//是否正在移动
	bool m_isDragged;			//是否是被拖动的Item
	int m_nEndPos;				//被拖动Item最后的Pos;
};

class CTagLayoutUI : public CHorizontalLayoutUI
{
DUI_DECLARE_EXTENDED_CONTROL(TagLayout, CTagLayoutUI)
public:	
	CTagLayoutUI();
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	bool SetItemIndexNoRedraw(CControlUI* pControl, int index);
	bool IntItemsOldRect(CControlUI* pControl);
	void SetEmptyPlaceRect(RECT rect){ m_rtEmptyPlace = rect;}
	RECT GetEmptyPlaceRect() { return m_rtEmptyPlace;}

protected:
	RECT m_rtEmptyPlace;

};
	
}

#endif