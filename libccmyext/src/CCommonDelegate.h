#pragma once

#include "cocos2d.h"
USING_NS_CC;
class CCUCommonDelegate:public CCObject
{
public:
	enum CALLBACK_TYPE{
		CB_VOID,
		CB_OBJ,
		CB_NODE,
		CB_CMD
	};

	class CParamWrap: public CCObject
	{
	public:
		CALLBACK_TYPE m_cbType;
		CCObject* m_targetParam;
		CCObject* m_cbParam;
	};

public:
	CCUCommonDelegate(void);
	virtual ~CCUCommonDelegate(void);

	static CCUCommonDelegate* create(CCObject* target=NULL, SEL_CallFuncO func=NULL, CCObject* param=NULL);
	bool initCCUCommonDelegate(CCObject* target=NULL, SEL_CallFuncO func=NULL, CCObject* param=NULL);

	void callback();

	void callbackO(CCObject* p);

	void callbackN(CCNode* pn);

	//×Ô¶¨Òåcmd
	void notifyTargetWithCmd(int cmd);

	virtual void notifyTarget(CParamWrap* param);

	//tool function
	static CParamWrap* parseParam(CCObject* param);
	static int parseCmdFromObj(CCObject* param);
	static int parseCmdFromParam(CParamWrap* param);

public:
	CCObject* m_saveTarget;
	CCObject* m_saveParam;
	SEL_CallFuncO m_saveFunc;
};
