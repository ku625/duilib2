#include "stdafx.h"
#include "alpha_window.h"


AlphaWindow::AlphaWindow(void)
{
}

AlphaWindow::~AlphaWindow(void)
{
}

void AlphaWindow::InitWindow()
{
	CButtonUI* loginBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("loginServerBtn")));
	if(loginBtn)
	{
		loginBtn->OnNotify += MakeDelegate(
			this, &AlphaWindow::OnLoginBtnClicked, _T("click"));
	}

	DuiLib::CActiveXUI* flashUI = reinterpret_cast<DuiLib::CActiveXUI*>(m_pm.FindControl(L"flashBk"));
	if(flashUI)
	{
		flashUI->OnNotify += MakeDelegate(
			this, &AlphaWindow::OnFlashBkShowActivex, _T("showactivex"));
	}
}

CDuiString AlphaWindow::GetSkinFolder()
{
	return _T("skin/alpha_window");
}
CDuiString AlphaWindow::GetSkinFile()
{
	return _T("layout/login_window.xml");

}
LPCTSTR AlphaWindow::GetWindowClassName(void)const
{
	return _T("hello_world");
}

void AlphaWindow::Notify(TNotifyUI& msg)
{
	if(msg.sType == L"click")
	{
		if(msg.pSender->GetName() == _T("closebtn"))
		{
			PostQuitMessage(0L);
		}
	}
	

}

bool AlphaWindow::OnLoginBtnClicked(TNotifyUI* pMsg)
{
	::MessageBox(m_hWnd, L"点击了登录按钮", L"提示", 0);
	return true;
}

bool AlphaWindow::OnFlashBkShowActivex(TNotifyUI* pMsg)
{
	IShockwaveFlash* pFlash = NULL;
	DuiLib::CActiveXUI* pActiveX = static_cast<DuiLib::CActiveXUI*>(pMsg->pSender);
	pActiveX->GetControl(__uuidof(IShockwaveFlash), (void**)&pFlash);
	if(!pFlash)
		pActiveX->SetVisible(false);

	pFlash->put_WMode(_bstr_t(_T("Transparent")));
	pFlash->put_Movie(_bstr_t(CPaintManagerUI::GetInstancePath()
		+ _T("\\skin\\alpha_window\\swf\\noon.swf")));
	pFlash->DisableLocalSecurity();
	pFlash->put_AllowScriptAccess(L"always");
	return true;
}




