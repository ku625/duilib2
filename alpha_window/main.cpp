// hello_world.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "resource.h"

#include "alpha_window.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	
	CPaintManagerUI::SetInstance(hInstance);
	AlphaWindow* pFrame = new AlphaWindow();
	if(pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("hello_world"), WS_POPUP|WS_VISIBLE|WS_DLGFRAME|WS_MINIMIZEBOX, UI_WNDSTYLE_EX_FRAME, 0, 0, 800, 572);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();
	
	
	return 0;
}