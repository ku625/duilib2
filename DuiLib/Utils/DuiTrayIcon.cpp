#include "StdAfx.h"

namespace DuiLib
{
	DuiTrayIcon::DuiTrayIcon(void)
	{
		memset(&m_trayData, 0, sizeof(m_trayData));
		m_bEnabled		= false;
		m_bVisible		= false;
		m_bTwinkling	= false;
		m_bTrackMouse	= false;
		m_hWnd			= NULL;
		m_uMessage		= WM_SYSTEM_TRAY_MESSAGE;

		m_trayIconTimer.SetCallback(this, &DuiTrayIcon::OnTrayIconTimer);
		m_trayIconTimer.SetInterval(400);

		m_mouseTimer.SetCallback(this, &DuiTrayIcon::OnMousePointTimer);
		m_mouseTimer.SetInterval(200);
	}


	DuiTrayIcon::~DuiTrayIcon(void)
	{
		DeleteTrayIcon();
	}

	void DuiTrayIcon::CreateTrayIcon( HWND _RecvHwnd,UINT _IconIDResource,
									 LPCTSTR _ToolTipText, UINT _Message, 
									 CPaintManagerUI* pManager)
	{
		if(_Message == NULL)
			_Message = WM_SYSTEM_TRAY_MESSAGE;

		if(!_RecvHwnd || _IconIDResource <= 0 || _Message < 0)
			return;

		m_hIcon = LoadIcon(CPaintManagerUI::GetInstance(),MAKEINTRESOURCE(_IconIDResource));

		m_trayData.cbSize = sizeof(NOTIFYICONDATA);
		m_trayData.hWnd	 = _RecvHwnd;
		m_trayData.uID	 = _IconIDResource;
		m_trayData.hIcon = m_hIcon;
		m_trayData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		m_trayData.uCallbackMessage = _Message;
		if(_ToolTipText)
			wcscpy(m_trayData.szTip,_ToolTipText);

		Shell_NotifyIcon(NIM_ADD,&m_trayData);
		m_bEnabled = true;

		m_mouseTimer.StartTimer();

	//	if(pManager)
	//		pManager->GetEventSource() += MakeDelegate(this,&DuiTrayIcon::OnCommon,WM_SYSTEM_TRAY_MESSAGE);
	}
	
	void DuiTrayIcon::DeleteTrayIcon()
	{
		StopTwinkling();
		m_mouseTimer.StopTimer();
		SetHideIcon();
		
		Shell_NotifyIcon(NIM_DELETE,&m_trayData);
		m_bEnabled		= false;
		m_bVisible		= false;
		m_bTwinkling	= false;
		m_hWnd			= NULL;
		m_uMessage		= WM_SYSTEM_TRAY_MESSAGE;
	}

	bool DuiTrayIcon::SetTooltipText( LPCTSTR _ToolTipText )
	{
		if(_ToolTipText)
			wcscpy(m_trayData.szTip,_ToolTipText);

		if (!m_bEnabled) return FALSE;
		m_trayData.uFlags = NIF_TIP;
		return Shell_NotifyIcon(NIM_MODIFY, &m_trayData) == TRUE;
	}

	bool DuiTrayIcon::SetTooltipText( UINT _IDResource )
	{
		wchar_t mbuf[64];
		LoadString(CPaintManagerUI::GetInstance(),_IDResource,mbuf,64);

		return SetTooltipText(mbuf);
	}

	CDuiString DuiTrayIcon::GetTooltipText() const
	{
		return m_trayData.szTip;
	}

	bool DuiTrayIcon::SetIcon( HICON _Hicon )
	{
		if(_Hicon)
			m_hIcon = _Hicon;

		m_trayData.uFlags = NIF_ICON;
		m_trayData.hIcon = _Hicon;
		
		if (!m_bEnabled) return FALSE;
		return Shell_NotifyIcon(NIM_MODIFY, &m_trayData) == TRUE;

		return false;
	}

	bool DuiTrayIcon::SetIcon( LPCTSTR _IconFile )
	{
		HICON hIcon = LoadIcon(CPaintManagerUI::GetInstance(),_IconFile);
		return SetIcon(hIcon);
	}

	bool DuiTrayIcon::SetIcon( UINT _IDResource )
	{
		HICON hIcon = LoadIcon(CPaintManagerUI::GetInstance(),MAKEINTRESOURCE(_IDResource));
		return SetIcon(hIcon);
	}

	HICON DuiTrayIcon::GetIcon() const
	{
		HICON hIcon = NULL;
		hIcon = m_trayData.hIcon;
		return hIcon;
	}

	void DuiTrayIcon::SetHideIcon()
	{
		if (IsVisible()) {
			SetIcon((HICON)NULL);
			m_bVisible = TRUE;
		}
	}

	void DuiTrayIcon::SetShowIcon()
	{
		if (!IsVisible()) {
			SetIcon(m_hIcon);
			m_bVisible = FALSE;
		}
	}

	void DuiTrayIcon::RemoveIcon()
	{
		m_trayData.uFlags = 0;
		Shell_NotifyIcon(NIM_DELETE, &m_trayData);
		m_bEnabled = FALSE;
	}

	bool DuiTrayIcon::StartTwinkling()
	{
		if(m_bTwinkling || !m_bEnabled)
			return false;

		m_trayIconTimer.StartTimer();
		m_bTwinkling = true;
		return true;
	}

	void DuiTrayIcon::StopTwinkling()
	{
		m_trayIconTimer.StopTimer();
		m_bTwinkling = false;
		SetShowIcon();
	}
	
	bool DuiTrayIcon::OnCommon( TEventUI* pTEventUI,LPARAM lParam,WPARAM wParam )
	{
		if(m_trayData.uID == pTEventUI->wParam && pTEventUI->lParam == WM_MOUSEMOVE)
		{
			GetCursorPos(&m_ptMouse);
			if(!m_bTrackMouse)
			{
				m_bTrackMouse = true;
			//	PostMessage(m_hWnd,WM_MOUSEINTRAYICON,NULL,NULL);
			}
		}
		return true;
	}

	void DuiTrayIcon::OnTrayIconTimer()
	{
		IsVisible()?SetHideIcon():SetShowIcon();
	}

	void DuiTrayIcon::OnMousePointTimer()
	{
		if(m_bTrackMouse)
		{
			POINT ptMouse;
			GetCursorPos(&ptMouse);
			if(ptMouse.x != m_ptMouse.x || ptMouse.y != m_ptMouse.y)
			{
				m_bTrackMouse = false;
				//PostMessage(hWnd,WM_MOUSEOUTTRAYICON,NULL,NULL);
			}
		}
	}
}
