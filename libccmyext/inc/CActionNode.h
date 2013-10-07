#pragma once

#include "CWindowBase.h"
#include "CActionParam.h"

class CCEActionManager;
class CCEActionNode:public CCWindowBase
{
public:
	CCEActionNode(void);
	virtual ~CCEActionNode(void);

	static CCEActionNode* create(void);
	bool initCCEActionNode(void);

	inline void bindManager(CCEActionManager* p)
	{
		m_weekpManager = p;
	}

	inline void paramForNextCall(CCEActionParam* p)
	{
		m_tmpParam = p;
	}

	//cc functionO callback
	void passToManager(CCObject* p);

protected:
	void callAction(CCFiniteTimeAction* action);

protected:
	CCEActionManager* m_weekpManager;
	CCEActionParam* m_tmpParam;
};
