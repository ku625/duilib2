#ifndef __UIDLGBUILDER_H__
#define __UIDLGBUILDER_H__

#pragma once

namespace DuiLib {

typedef CControlUI* (*LpCreateControlFuntion)();

class IDialogBuilderCallback
{
public:
    virtual CControlUI* CreateControl(LPCTSTR pstrClass) = 0;
};

class UILIB_API CDialogBuilder
{
public:
    CDialogBuilder();
    CControlUI* Create(STRINGorID xml, LPCTSTR type = NULL, IDialogBuilderCallback* pCallback = NULL,
        CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);
    CControlUI* Create(IDialogBuilderCallback* pCallback = NULL, CPaintManagerUI* pManager = NULL,
        CControlUI* pParent = NULL);

    CMarkup* GetMarkup();

    void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
    void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;
	static void AddCreateControlFuntion(LPCTSTR pstrClass, LpCreateControlFuntion fun);
private:
    CControlUI* _Parse(CMarkupNode* parent, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL);

    CMarkup m_xml;
    IDialogBuilderCallback* m_pCallback;
    LPCTSTR m_pstrtype;
	static CStdStringPtrMap m_createControlFunMap;
};

////////////////////////定义扩展控件/////////////////////////////
#define DUI_DECLARE_EXTENDED_CONTROL(pstrClass, classname)	\
public:\
	static DuiLib::CControlUI* CreateExtControl##classname(); \
private:\
	class CreateHelper##classname\
	{\
	public:\
		CreateHelper##classname(); \
	}; \
	static CreateHelper##classname createrHelper_##pstrClass;

////////////////////////实现扩展控件/////////////////////////////
#define DUI_IMPLEMENT_EXTENDED_CONTROL(pstrClass, classname)\
DuiLib::CControlUI* classname::CreateExtControl##classname()\
{\
	return new classname(); \
}\
classname::CreateHelper##classname::CreateHelper##classname()\
{\
	DuiLib::CDialogBuilder::AddCreateControlFuntion(\
		_T(#pstrClass), classname::CreateExtControl##classname); \
}\
classname::CreateHelper##classname classname::createrHelper_##pstrClass;
/////////////////////////////////////////////////////////////////////

} // namespace DuiLib

#endif // __UIDLGBUILDER_H__
