#include "StdAfx.h"
#include "UITimer.h"

#pragma comment(lib,"winmm.lib")

namespace DuiLib{

CDuiTimerBase::CDuiTimerBase()
: m_uTimerID(0)
, m_uInterval(0)
, m_runing(false)
{
}

CDuiTimerBase::~CDuiTimerBase()
{
	InnerKillTimer();
}

void CDuiTimerBase::SetInterval(int ms)
{
	if(ms < 10)
		ms = 10;

	m_uInterval = ms;
}

void CDuiTimerBase::StartTimer()
{
	if(m_runing)
		return;

	m_runing = InnerSetTimer();
}

void CDuiTimerBase::StopTimer()
{
	if(!m_runing)
		return;

	InnerKillTimer();
	m_runing = false;
}

bool CDuiTimerBase::IsRuning()
{
	return m_runing;
}

void CDuiTimerBase::OnTimer()
{
	//调用基类的OnTimer
}
	
bool CDuiTimerBase::InnerSetTimer()
{
	if(m_uTimerID > 0)
		InnerKillTimer();

	m_uTimerID = timeSetEvent(m_uInterval, 1, CDuiTimerBase::TimerProc, (DWORD_PTR)this, TIME_PERIODIC);

	if(m_uTimerID > 0)
		return true;

	return false;
}


void CDuiTimerBase::InnerKillTimer()
{
	if(m_uTimerID > 0)
	{
		timeKillEvent(m_uTimerID);
		m_uTimerID = 0;
	}	
}

void CALLBACK CDuiTimerBase::TimerProc(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser,
										DWORD_PTR dw1, DWORD_PTR dw2)
{
	CDuiTimerBase* pTimerUI = (CDuiTimerBase*)dwUser;
	if(pTimerUI)
		pTimerUI->OnTimer();
}

}