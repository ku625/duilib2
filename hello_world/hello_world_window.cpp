#include "stdafx.h"
#include "hello_world_window.h"

int CTestWndWindow::index=0;
CTestWndWindow::CTestWndWindow(void)
{
}

CTestWndWindow::~CTestWndWindow(void)
{
}

void CTestWndWindow::InitWindow()
{
	m_pTagLayout = static_cast<CTagLayoutUI*>(m_pm.FindControl(_T("TabContainer")));
	m_webBrowser = static_cast<CWebBrowserUI*>(m_pm.FindControl(_T("webBrowser")));
	m_webBrowser->DoCreateControl();
	m_webBrowser->Navigate2(L"www.baidu.com");
}

CDuiString CTestWndWindow::GetSkinFolder()
{
	return _T("skin/hello_word");
}
CDuiString CTestWndWindow::GetSkinFile()
{
	return _T("skin.xml");

}
LPCTSTR CTestWndWindow::GetWindowClassName(void)const
{
	return _T("hello_world");
}

void CTestWndWindow::Notify(TNotifyUI& msg)
{
	CDuiString strCtrlName = msg.pSender->GetName();
	if(msg.sType == _T("click"))
	{
		if(strCtrlName == _T("NewItemBtn"))
		{
			int j = index++;
			CDuiString strTxt;
			strTxt.Format(L"±êÇ©%d", j);
			static CDuiString strAttrOptionEx = _T("float=\"false\" group=\"group1\" maxwidth=\"174\" normalimage=\"file=\'TabBtnBk.png\' corner=\'15,15,15,15\' source=\'0,0,87,30\'\" hotimage=\"file=\'TabBtnBk.png\' corner=\'15,15,15,15\' source=\'87,0,174,30\'\" selectedimage=\"file=\'TabBtnBk.png\' corner=\'15,15,15,15\' source=\'174,0,261,30\'\" ");
			COptionExUI* pNewOption = new COptionExUI;
			pNewOption->ApplyAttributeList(strAttrOptionEx);
			pNewOption->SetText(strTxt);


			CTagMoveUI* pNewTagMove = new CTagMoveUI;
			pNewTagMove->ApplyAttributeList(_T("maxwidth=\"174\" "));
			pNewTagMove->Add(pNewOption);
			m_pTagLayout->AddAt(pNewTagMove, m_pTagLayout->GetCount());
			pNewOption->Activate();
		}

		if(strCtrlName == _T("closebtn"))
		{
			PostQuitMessage(0L);
		}
	}

}




