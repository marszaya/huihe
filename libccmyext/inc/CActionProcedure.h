#pragma once

#include "cocos2d.h"
USING_NS_CC;

class CCEActionManager;
class CCEActionProcedure:public CCObject
{
public:
	CCEActionProcedure(void);
	virtual ~CCEActionProcedure(void);
	
	inline void bindManager(CCEActionManager* p)
	{
		m_weekpManager = p;
	}

	//return true = has next step
	//return false = end
	virtual bool nextStep(int stepToCheck) = 0;

	int m_procedureTag;

protected:
	CCEActionManager* m_weekpManager;
};
