#pragma once

#include "cocos2d.h"
#include "CMsgDispatcher.h"
USING_NS_CC;
class CCECallFuncProxy:public CCObject
{
public:
	CCECallFuncProxy(void);
	CCECallFuncProxy(int cmd, CCEMsgDispatcher* p=NULL);
	virtual ~CCECallFuncProxy(void);

	static CCECallFuncProxy* create(int cmd, CCEMsgDispatcher* p=NULL);
	bool initCCECallFuncProxy(int cmd, CCEMsgDispatcher* p=NULL);

	void callback();

	void callbackO(CCObject* p);

	void callbackN(CCNode* pn);

protected:
	int m_saveCmd;
	CCEMsgDispatcher* m_saveDispatcher;
};