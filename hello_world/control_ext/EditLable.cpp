#include "stdafx.h"
#include "EditLable.h"

namespace DuiLib{

///////////////////////////////////////////////////////////////////////////////
DUI_IMPLEMENT_EXTENDED_CONTROL(EditLabel, EditLabelUI)
EditLabelUI::EditLabelUI(void)
{
	m_dragWindow = NOT_DRAG_WINDOW;
	m_richEdit = new CRichEditUI();
	if(m_richEdit)
	{
		m_richEdit->SetMultiline(false);
		m_richEdit->SetWantTab(false);
		m_richEdit->SetEnabled(false);
		m_richEdit->SetMouseEnabled(false);
		m_richEdit->OnNotify += MakeDelegate(
			this, &EditLabelUI::OnRichEditKillFocus, _T("killfocus"));
	}
	
	Add(m_richEdit);
}


EditLabelUI::~EditLabelUI(void)
{	
	if(m_pManager)
		m_pManager->RemoveMessageFilter(this);
}


LPCTSTR EditLabelUI::GetClass() const
{
	return _T("EditLabelUI");
}

LPVOID EditLabelUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("EditLabel")) == 0 ) return static_cast<EditLabelUI*>(this);
	return CControlUI::GetInterface(pstrName);
}

void EditLabelUI::DoInit()
{
	if(m_pManager)
		m_pManager->AddMessageFilter(this);
}

void EditLabelUI::DoEvent(TEventUI& event)
{
	if(event.Type == UIEVENT_MOUSEENTER)
	{
		if(!m_richEdit->IsFocused())
			SetBkImage(m_sHotImage.GetData());
	}
	else if(event.Type == UIEVENT_MOUSELEAVE)
	{
		if(!m_richEdit->IsFocused())
			SetBkImage(m_sNormalImage.GetData());
	}
	else if(event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK)
	{
		SetBkImage(m_sPushedImage.GetData());
		m_richEdit->SetMouseEnabled(true);
		m_richEdit->SetEnabled(true);
		m_richEdit->SetFocus();
	}

	CHorizontalLayoutUI::DoEvent(event);
}

void EditLabelUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if(_tcscmp(pstrName, _T("normalimage")) == 0) SetNormalImage(pstrValue);
	else if(_tcscmp(pstrName, _T("hotimage")) == 0) SetHotImage(pstrValue);
	else if(_tcscmp(pstrName, _T("pushedimage")) == 0) SetPushedImage(pstrValue);
	else if(_tcscmp(pstrName, _T("text")) == 0) SetText(pstrValue);
	else if(_tcscmp(pstrName, _T("font")) == 0) m_richEdit->SetFont(_ttoi(pstrValue));
	else if(_tcscmp(pstrName, _T("textcolor")) == 0) {
		if(*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		m_richEdit->SetTextColor(clrColor);
	}
	else CHorizontalLayoutUI::SetAttribute(pstrName,pstrValue);
}

void EditLabelUI::SetText(LPCTSTR text)
{
	if(m_richEdit)
		m_richEdit->SetText(text);
}

CDuiString EditLabelUI::GetText()
{
	if(m_richEdit)
		return m_richEdit->GetText();

	return CDuiString();
}

LPCTSTR EditLabelUI::GetNormalImage()
{
	return m_sNormalImage;
}

void EditLabelUI::SetNormalImage(LPCTSTR pStrImage)
{
	m_sNormalImage = pStrImage;
	Invalidate();
}

LPCTSTR EditLabelUI::GetHotImage()
{
	return m_sHotImage;
}

void EditLabelUI::SetHotImage(LPCTSTR pStrImage)
{
	m_sHotImage = pStrImage;
}

LPCTSTR EditLabelUI::GetPushedImage()
{
	return m_sPushedImage;
}

void EditLabelUI::SetPushedImage(LPCTSTR pStrImage)
{
	m_sPushedImage = pStrImage;
}

bool EditLabelUI::OnRichEditKillFocus(DuiLib::TNotifyUI* pMsg)
{
	m_richEdit->SetEnabled(false);
	m_richEdit->SetMouseEnabled(false);
	SetBkImage(m_sNormalImage.GetData());
	if(m_pManager != NULL) 
		m_pManager->SendNotify((CControlUI*)this, _T("finishedit"));

	return true;
}

LRESULT EditLabelUI::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if(WM_NCLBUTTONDOWN == uMsg)
	{
		if(m_richEdit->IsFocused())
			SetFocus();
	}

	return 0;
}




}
