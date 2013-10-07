#pragma once

#include "BagWindowBase.h"

class CBagWindow:public CCWindowBase
{
public:
	CBagWindow(void);
	virtual ~CBagWindow(void);

	static CBagWindow* create(int row, int col); 
	bool initCBagWindow(int row, int col);

	void onClose(CCObject* target);

protected:
	virtual void onFrameMsg(CCObject* msg);

public:
	CBagWindowBase* m_innerWin;
};
