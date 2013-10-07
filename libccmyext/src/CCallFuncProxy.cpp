#include "CCallFuncProxy.h"

CCECallFuncProxy::CCECallFuncProxy(void)
{
	m_saveCmd = -1;
}

CCECallFuncProxy::CCECallFuncProxy(int cmd, CCEMsgDispatcher* p)
{
	initCCECallFuncProxy(cmd, p);
}

CCECallFuncProxy::~CCECallFuncProxy(void)
{
	if(m_saveDispatcher)
		m_saveDispatcher->release();
}

CCECallFuncProxy* CCECallFuncProxy::create(int cmd, CCEMsgDispatcher* p)
{
	CCECallFuncProxy *pRet = new CCECallFuncProxy();
	if(pRet && pRet->initCCECallFuncProxy(cmd, p))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCECallFuncProxy::initCCECallFuncProxy(int cmd, CCEMsgDispatcher* p)
{
	bool ret=false;
	do{
		m_saveCmd = cmd;
		m_saveDispatcher = p;

		if(m_saveDispatcher == NULL)
		{
			m_saveDispatcher = CCEMsgDispatcher::getSharedInstance();
		}
		
		if(!m_saveDispatcher)
			break;

		m_saveDispatcher->retain();
		ret = true;
	}while(0);

	return ret;
}

void CCECallFuncProxy::callback()
{
	if(m_saveDispatcher)
	{
		m_saveDispatcher->invokeCmd(this->m_saveCmd);
	}
}

void CCECallFuncProxy::callbackO(CCObject* p)
{
	if(m_saveDispatcher)
	{
		m_saveDispatcher->invokeCmd(this->m_saveCmd, p);
	}
}

void CCECallFuncProxy::callbackN(CCNode* pn)
{
	if(m_saveDispatcher)
	{
		m_saveDispatcher->invokeCmd(this->m_saveCmd, pn);
	}
}
