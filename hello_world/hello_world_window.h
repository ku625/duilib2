#pragma once
#include "control_ext/OptionEx.h"
#include "control_ext/TagControl.h"

using namespace DuiLib;

class CTestWndWindow :
	public WindowImplBase
{
public:
	CTestWndWindow(void);
	~CTestWndWindow(void);
	
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void)const;
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();

public:
	CTagLayoutUI* m_pTagLayout;
	CWebBrowserUI* m_webBrowser;
	static int index;
};
