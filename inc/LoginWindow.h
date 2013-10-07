#pragma once

#include "CWindowBase.h"
class CLoginWindow:public CCWindowBase
{
public:
	CLoginWindow(void);
	virtual ~CLoginWindow(void);

	static CLoginWindow* create();
	bool initCLoginWindow();

	void onBtn(CCObject* target);
};
