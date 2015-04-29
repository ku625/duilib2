#ifndef __OPTION_EX_H_
#define __OPTION_EX_H_


namespace DuiLib{

	class COptionExUI :public COptionUI
	{
		DUI_DECLARE_EXTENDED_CONTROL(OptionEx, COptionExUI)
	public:
		COptionExUI();
		virtual void COptionExUI::DoEvent(TEventUI& event);
	};

}

#endif