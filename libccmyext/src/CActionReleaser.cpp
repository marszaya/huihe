#include "CActionReleaser.h"

CCEActionReleaser::CCEActionReleaser(void)
{
}

CCEActionReleaser::~CCEActionReleaser(void)
{
}

CCEActionReleaser* CCEActionReleaser::create(
	CCNode* childNode, CCWindowBase* parentNode, CCFiniteTimeAction* action)
{
	CCEActionReleaser *pRet = new CCEActionReleaser();
	if(pRet && pRet->initCCEActionReleaser(childNode,parentNode,action))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCEActionReleaser::initCCEActionReleaser(
	CCNode* childNode, CCWindowBase* parentNode, CCFiniteTimeAction* action)
{
	bool ret=false;
	do{
		if(!parentNode->getChildren()->containsObject(childNode))
		{
			break;
		}

		m_childNode = childNode;
		m_parentNode = parentNode;

		m_childNode->runAction(
			CCSequence::create(action, 
				CCCallFunc::create(this, callfunc_selector(CCEActionReleaser::callbackActionDone)),
				NULL
			)
		);

		ret = true;
	}while(0);

	return ret;
}

void CCEActionReleaser::callbackActionDone(void)
{
	m_parentNode->removeChildOnNextFrame(m_childNode);
}
