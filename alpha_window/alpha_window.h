#pragma once

using namespace DuiLib;

class AlphaWindow :
	public WindowImplBase
{
public:
	AlphaWindow(void);
	~AlphaWindow(void);
	
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void)const;
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();

private:
	bool OnLoginBtnClicked(TNotifyUI* pMsg);
	bool OnFlashBkShowActivex(TNotifyUI* pMsg);
	
};
