#include "CCommonDelegate.h"

CCUCommonDelegate::CCUCommonDelegate(void)
{
	m_saveTarget = NULL;
	m_saveParam = NULL;
	m_saveFunc = NULL;
}

CCUCommonDelegate::~CCUCommonDelegate(void)
{
	if(m_saveTarget)
		m_saveTarget->release();
	if(m_saveParam)
		m_saveParam->release();
}

CCUCommonDelegate* CCUCommonDelegate::create(CCObject* target, SEL_CallFuncO func, CCObject* param)
{
	CCUCommonDelegate *pRet = new CCUCommonDelegate();
	if(pRet && pRet->initCCUCommonDelegate(target,func,param))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCUCommonDelegate::initCCUCommonDelegate(CCObject* target, SEL_CallFuncO func, CCObject* param)
{
	bool ret=false;
	do{
		if(target)
		{
			if(!func)
				break;
			target->retain();
			m_saveTarget = target;
			m_saveFunc = func;
		}

		if(param)
		{
			param->retain();
			m_saveParam = param;
		}

		ret = true;
	}while(0);

	return ret;
}

void CCUCommonDelegate::callback()
{
	CParamWrap* p = new CParamWrap();
	p->m_cbType = CB_VOID;
	p->m_cbParam = NULL;
	p->m_targetParam = m_saveParam;
	notifyTarget(p);
	p->release();
}

void CCUCommonDelegate::callbackO(CCObject* param)
{
	CParamWrap* p = new CParamWrap();
	p->m_cbType = CB_OBJ;
	p->m_cbParam = param;
	p->m_targetParam = m_saveParam;
	notifyTarget(p);
	p->release();
}

void CCUCommonDelegate::callbackN(CCNode* param)
{
	CParamWrap* p = new CParamWrap();
	p->m_cbType = CB_NODE;
	p->m_cbParam = param;
	p->m_targetParam = m_saveParam;
	notifyTarget(p);
	p->release();
}

void CCUCommonDelegate::notifyTarget(CCUCommonDelegate::CParamWrap* param)
{
	if(m_saveTarget)
	{
		(m_saveTarget->*m_saveFunc)(param);
	}
}

void CCUCommonDelegate::notifyTargetWithCmd(int cmd)
{
	CParamWrap* p = new CParamWrap();
	p->m_cbType = CB_CMD;
	CCString* str = new CCString();
	str->initWithFormat("%d", cmd);
	p->m_cbParam = str;
	p->m_targetParam = m_saveParam;
	notifyTarget(p);
	p->m_cbParam->release();
	p->release();
}


CCUCommonDelegate::CParamWrap* CCUCommonDelegate::parseParam(CCObject* param)
{
	CParamWrap* ret = NULL;
	do{
		ret = dynamic_cast<CParamWrap*>(param);
	}while(0);
	return ret;
}

int CCUCommonDelegate::parseCmdFromObj(CCObject* param)
{
	int ret = -1;
	do{
		ret = parseCmdFromParam(parseParam(param));
	}while(0);
	return ret;
}

int CCUCommonDelegate::parseCmdFromParam(CCUCommonDelegate::CParamWrap* p)
{
	int ret = -1;
	do{
		if(!p || p->m_cbType != CB_CMD)
			break;
		
		CCString* str = dynamic_cast<CCString*>(p->m_cbParam);
		if(!str)
			break;

		ret = str->intValue();		
	}while(0);
	return ret;
}
