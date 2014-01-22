#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CCEActionParam:public CCObject
{
public:
	CCEActionParam(int procedureID, int stepID);
	virtual ~CCEActionParam(void);

public:
	int m_procedureID;
	int m_stepID;
};
