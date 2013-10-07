#pragma once

#include "CWindowBase.h"

/*
* 此类窗口create时将切换touch delegate队列，使之前的可触摸区域都失效，析构时恢复
* 必须为短生命周期的窗口，比如alert窗口
*/
class CSwitchTouchWindow:public CCWindowBase
{
public:
	CSwitchTouchWindow(void);
	virtual ~CSwitchTouchWindow(void);

	static CSwitchTouchWindow* create(void);
	bool initCSwitchTouchWindow(void);
};

