#include "StdAfx.h"
#include "OptionEx.h"


namespace DuiLib{

	DUI_IMPLEMENT_EXTENDED_CONTROL(OptionEx, COptionExUI)
	COptionExUI::COptionExUI()
	{

	}

	void COptionExUI::DoEvent(TEventUI& event)
	{
		this->GetParent()->DoEvent(event);
		__super::DoEvent(event);
	}

}