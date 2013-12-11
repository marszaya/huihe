#include "CActionManager.h"

CCEActionManager::CCEActionManager(void)
{
	m_maxProcedureTag = 0;
}

CCEActionManager::~CCEActionManager(void)
{
	removeAllProcedures();
}

CCEActionManager* CCEActionManager::create()
{
	CCEActionManager *pRet = new CCEActionManager();
	if(pRet && pRet->initCCEActionManager())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCEActionManager::initCCEActionManager()
{
	bool ret=false;
	do{
		ret = true;
	}while(0);

	return ret;
}

void CCEActionManager::onActionNotify(CCObject* obj)
{
	CCEActionParam* param = dynamic_cast<CCEActionParam*>(obj); 
	CCEActionProcedure* p = getProcedure(param->m_procedureID);
	if(p)
	{
		if(!p->nextStep(param->m_stepID))
		{
			onProcedureEnd(p->m_procedureTag);
			removeProcedure(p->m_procedureTag);
		}
	}
}

int CCEActionManager::startProcedure(CCEActionProcedure* p)
{
	p->retain();
	int retTag = ++m_maxProcedureTag;
	m_procedures.insert(make_pair(retTag, p));
	p->m_procedureTag = retTag;
	p->bindManager(this);
	if(!p->nextStep(0))
	{
		onProcedureEnd(p->m_procedureTag);
		removeProcedure(p->m_procedureTag);
	}
	return 0;
}

CCEActionProcedure* CCEActionManager::getProcedure(int tag)
{
	map<int, CCEActionProcedure*>::iterator it = m_procedures.find(tag);
	if(it == m_procedures.end())
	{
		return NULL;
	}

	return it->second;
}

void CCEActionManager::removeProcedure(int tag)
{
	map<int, CCEActionProcedure*>::iterator it = m_procedures.find(tag);
	if(it != m_procedures.end())
	{
		it->second->bindManager(NULL);
		it->second->release();
		m_procedures.erase(it);
	}
}

void CCEActionManager::removeAllProcedures()
{
	map<int, CCEActionProcedure*>::iterator it;
	for(it = m_procedures.begin(); it!=m_procedures.end(); ++it)
	{
		it->second->bindManager(NULL);
		it->second->release();
	}

	m_procedures.clear();
}

void CCEActionManager::onProcedureEnd(int tag)
{
}