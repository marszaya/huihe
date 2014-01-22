#pragma once

#include "cocos2d.h"
USING_NS_CC;
class CCEMsgWithCmd:public CCObject
{
public:
	CCEMsgWithCmd(int cmd, CCObject* msg);
	virtual ~CCEMsgWithCmd(void);

public:
	int m_cmd;
	CCObject* m_msg;
};
