#ifndef __UIDELEGATE_H__
#define __UIDELEGATE_H__

#pragma once

namespace DuiLib {

typedef struct tagTNotifyUI TNotifyUI;

class UILIB_API CDelegateBase	 
{
public:
    CDelegateBase(void* pObject, void* pFn);
    CDelegateBase(const CDelegateBase& rhs);
    virtual ~CDelegateBase();
    bool Equals(const CDelegateBase& rhs) const;
    bool operator() (void* param);
	bool operator() (TNotifyUI* pTNotifyUI);
    virtual CDelegateBase* Copy() const = 0; // add const for gcc

protected:
    void* GetFn();
    void* GetObject();
    virtual bool Invoke(void* param) = 0;
	virtual bool Invoke(TNotifyUI* pTNotifyUI) = 0;

private:
    void* m_pObject;
    void* m_pFn;
};

class CDelegateStatic: public CDelegateBase
{
    typedef bool (*Fn)(void*);
public:
    CDelegateStatic(Fn pFn) : CDelegateBase(NULL, pFn) { } 
    CDelegateStatic(const CDelegateStatic& rhs) : CDelegateBase(rhs) { } 
    virtual CDelegateBase* Copy() const { return new CDelegateStatic(*this); }

protected:
    virtual bool Invoke(void* param)
    {
        Fn pFn = (Fn)GetFn();
        return (*pFn)(param); 
    }

	virtual bool Invoke(TNotifyUI* pTNotifyUI)
	{
		return Invoke(pTNotifyUI);
	}
};

template <class O, class T>
class CDelegate : public CDelegateBase
{
    typedef bool (T::* Fn)(void*);
	typedef bool (T::*NotifyUIFn)(TNotifyUI* pTNotifyUI);
public:
    CDelegate(O* pObj, Fn pFn) 
	: CDelegateBase(pObj, &pFn)
	, m_pFn(pFn) 
	, m_pNotifyFn(NULL)
	{ 
	}

	CDelegate(O* pObj, NotifyUIFn pNotifyFn, LPCTSTR sNotifyType)
	: CDelegateBase(pObj, NULL)
	, m_pFn(NULL)
	, m_pNotifyFn(pNotifyFn)
	, m_sNotifyType(sNotifyType)
	{
	}

	CDelegate(const CDelegate& rhs) 
	: CDelegateBase(rhs) 
	{
		m_pFn = rhs.m_pFn; 
		m_pNotifyFn = rhs.m_pNotifyFn; 
		m_sNotifyType = rhs.m_sNotifyType;
	}
    virtual CDelegateBase* Copy() const { return new CDelegate(*this); }

protected:
	virtual bool Invoke(void* param)
	{
		O* pObject = (O*)GetObject();
		if(pObject && m_pFn)
			return (pObject->*m_pFn)(param);
		else if(pObject && m_pNotifyFn)
			return Invoke((TNotifyUI*)param);

		return true;
	}

	virtual bool Invoke(TNotifyUI* pTNotifyUI)
	{
		O* pObject = (O*)GetObject();
		if(pObject && m_pNotifyFn && (m_sNotifyType.IsEmpty() || pTNotifyUI->sType == m_sNotifyType))
			return (pObject->*m_pNotifyFn)(pTNotifyUI);
		else if(pObject && m_pFn)
			return (pObject->*m_pFn)(pTNotifyUI);

		return true;
	}

private:
    Fn m_pFn;
	NotifyUIFn m_pNotifyFn;
	CDuiString m_sNotifyType;
};

template <class O, class T>
CDelegate<O, T> MakeDelegate(O* pObject, bool (T::* pFn)(void*))
{
    return CDelegate<O, T>(pObject, pFn);
}

template <class O, class T>
CDelegate<O, T> MakeDelegate(O* pObject, bool (T::* pNotifyUIFn)(TNotifyUI*), LPCTSTR sNotifyType = NULL)
{
	return CDelegate<O, T>(pObject, pNotifyUIFn, (LPCTSTR)sNotifyType);
}

inline CDelegateStatic MakeDelegate(bool (*pFn)(void*))
{
    return CDelegateStatic(pFn); 
}

class UILIB_API CEventSource
{
    typedef bool (*FnType)(void*);
public:
    ~CEventSource();
    operator bool();
    void operator+= (const CDelegateBase& d); // add const for gcc
    void operator+= (FnType pFn);
    void operator-= (const CDelegateBase& d);
    void operator-= (FnType pFn);
    bool operator() (void* param);
	bool operator() (TNotifyUI* pTNotifyUI);

protected:
    CStdPtrArray m_aDelegates;
};

} // namespace DuiLib

#endif // __UIDELEGATE_H__