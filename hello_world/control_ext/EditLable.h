#ifndef __UI_EDIT_LABEL_H_
#define __UI_EDIT_LABEL_H_


namespace DuiLib {
	

class EditLabelUI :public CHorizontalLayoutUI, public IMessageFilterUI
{
	DUI_DECLARE_EXTENDED_CONTROL(EditLabel, EditLabelUI)
public:
	EditLabelUI(void);
	~EditLabelUI(void);

	virtual LPCTSTR	GetClass() const override;
	virtual LPVOID GetInterface(LPCTSTR pstrName) override;
	
	void SetText(LPCTSTR text);//覆盖了这个函数
	CDuiString GetText();
	LPCTSTR GetNormalImage();
	void SetNormalImage(LPCTSTR pStrImage);
	LPCTSTR GetHotImage();
	void SetHotImage(LPCTSTR pStrImage);
	LPCTSTR GetPushedImage();
	void SetPushedImage(LPCTSTR pStrImage);

protected:
	virtual void DoInit() override;
	virtual void DoEvent(TEventUI& event) override;
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	//signal
	//finishedit 失去焦点完成编辑
private:
	bool OnRichEditKillFocus(DuiLib::TNotifyUI* pMsg);

	CRichEditUI* m_richEdit;
	CDuiString m_sNormalImage;
	CDuiString m_sHotImage;
	CDuiString m_sPushedImage;
};

}// 
#endif