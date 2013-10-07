#pragma once

#include "CWindowBase.h"

class CCEActionReleaser:public CCObject
{
public:
	CCEActionReleaser(void);
	virtual ~CCEActionReleaser(void);

	static CCEActionReleaser* create(CCNode* childNode, CCWindowBase* parentNode, CCFiniteTimeAction* action);
	bool initCCEActionReleaser(CCNode* childNode, CCWindowBase* parentNode, CCFiniteTimeAction* action);

	void callbackActionDone(void);
protected:
	CCNode* m_childNode;
	CCWindowBase* m_parentNode;
};
