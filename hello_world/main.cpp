// hello_world.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "resource.h"

#include "hello_world_window.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	HRESULT Hr = ::CoInitialize(NULL); 
	CPaintManagerUI::SetInstance(hInstance);
	CTestWndWindow* pFrame = new CTestWndWindow();
	if(pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("hello_world"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();
	::CoUninitialize();
	
	return 0;
}