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
	enum{ ID_MOVE_TIMER = 15};	//�����ƶ��Ķ�ʱ��ID
		
	bool m_bIsLButtonDowning;	//�Ƿ������
	int	m_nLButtonDownCX;		//����ڰ�ť�е�λ��CX
	int m_nLButtonDownCY;		//����ڰ�ť�е�λ��CY

	RECT m_rcTargetRect;		//Ŀ��λ��
	RECT m_rcCurrentRect;		//��ǰλ��
	RECT m_rcOldRect;			//�ƶ�ǰ��λ��
	int m_nStepLen;				//�ƶ�����
	bool m_bIsMoving;			//�Ƿ������ƶ�
	bool m_isDragged;			//�Ƿ��Ǳ��϶���Item
	int m_nEndPos;				//���϶�Item����Pos;
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