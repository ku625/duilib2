#ifndef __UITIMER_H_
#define __UITIMER_H_

#pragma once

namespace DuiLib{

class UILIB_API CDuiTimerBase
{
public:
	CDuiTimerBase();
	~CDuiTimerBase();

	void SetInterval(int ms);
	void StartTimer();
	void StopTimer();
	bool IsRuning();
protected:
	virtual void OnTimer();
	bool InnerSetTimer();
	void InnerKillTimer();

private:
	static void CALLBACK TimerProc(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, 
								   DWORD_PTR dw1, DWORD_PTR dw2);

	UINT m_uTimerID;
	UINT m_uInterval;
	bool m_runing;
};


template<typename T>
class UILIB_TEMPLATE CDuiTimer : public CDuiTimerBase
{
	typedef void (T::* OnTimerFn)();
public:
	CDuiTimer()
	: m_obj(NULL)
	, m_callback(NULL)
	{
	}

	~CDuiTimer()
	{
	}

	void SetCallback(T* obj, OnTimerFn callback)
	{
		m_obj = obj;
		m_callback = callback;
	}
protected:
	virtual void OnTimer()
	{
		if(m_obj && m_callback)
		{
			(m_obj->*m_callback)();
		}
	}

private:
	T* m_obj;
	OnTimerFn m_callback;
};

}
#endif // __UITIMER_H_
