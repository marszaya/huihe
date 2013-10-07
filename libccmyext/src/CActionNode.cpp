#include "CActionNode.h"
#include "CActionManager.h"

CCEActionNode::CCEActionNode(void)
{
	m_weekpManager = NULL;
	m_tmpParam = NULL;
}

CCEActionNode::~CCEActionNode(void)
{
}

CCEActionNode* CCEActionNode::create()
{
	CCEActionNode *pRet = new CCEActionNode();
	if(pRet && pRet->initCCEActionNode())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCEActionNode::initCCEActionNode()
{
	bool ret=false;
	do{
		m_weekpManager = NULL;
		m_tmpParam = NULL;
		ret = true;
	}while(0);
	
	return ret;
}

void CCEActionNode::passToManager(CCObject* p)
{
	if(m_weekpManager)
		m_weekpManager->onActionNotify(p);
}

void CCEActionNode::callAction(CCFiniteTimeAction* action)
{
	if(m_tmpParam)
	{
		this->runAction(
			CCSequence::create(action, 
				CCCallFuncO::create(this, callfuncO_selector(CCEActionNode::passToManager), m_tmpParam),
				NULL
			)
		);

		m_tmpParam = NULL;
	}
	else
	{
		this->runAction(action);
	}
}
