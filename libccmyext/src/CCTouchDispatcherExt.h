
#pragma once
#include "cocos2d.h"

USING_NS_CC;

//用在弹出对话框，不允许其他touch分发的情况
//useExtHandles使用一个临时handle数组替换掉原来的target数组
//1 useExtHandles(true) 
//2 create dialog with ok or cancel button
//3 ok or cancel button recieves event
//4 useExtHandles(false) 

class CCTouchDispatcherExt:public CCTouchDispatcher
{
public:
	CCTouchDispatcherExt(void);
	virtual ~CCTouchDispatcherExt(void);

public:
	void useExtHandles(bool v);

protected:
	CCArray* m_saveTargetHandles;
	bool m_useExtHandles;
};
