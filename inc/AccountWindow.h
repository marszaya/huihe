#pragma once

#include "CWindowBase.h"
#include "CBarBase.h"

class CAccountWindow: public CCWindowBase
{
public:
	CAccountWindow(void);
	virtual ~CAccountWindow(void);

	static CAccountWindow* create();
	bool initCAccountWindow();
	void updateCAccountWindow();

protected:
	virtual void onFrameMsg(CCObject* msg);

protected:
	int m_tagGold;
	int m_tagMoney;
	int m_tagExpr;
	int m_tagLevel;
	int m_tagVip;
	int m_tagName;
	CBarBase* m_expbar;
};

