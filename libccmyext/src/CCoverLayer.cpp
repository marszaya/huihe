#include "CCoverLayer.h"

CCCoverLayer::CCCoverLayer(void)
{
	m_curZ = -1;
	m_curTag = -1;
}

CCCoverLayer::~CCCoverLayer(void)
{
}

CCCoverLayer* CCCoverLayer::create()
{
	CCCoverLayer *pRet = new CCCoverLayer();
	if(pRet && pRet->initWithColor(ccc4(0,0,0,128)))
    {
        pRet->autorelease();
    }

	return pRet;
}

void CCCoverLayer::cover(CCNode* parent, int tag)
{
	CCObject* pObject = NULL;
	int maxz = -1;
	int maxtag = -1;
	CCARRAY_FOREACH(parent->getChildren(), pObject)
    {
        CCNode* pChild = dynamic_cast<CCNode*>(pObject);
		if(maxz < pChild->getZOrder())
		{
			maxz = pChild->getZOrder();
		}

		if(maxtag < pChild->getTag())
		{
			maxtag = pChild->getTag();
		}

		if(tag>=0 && tag == pChild->getTag())
		{
			tag = -1;
		}
	}

	m_curZ = maxz+1;
	if(tag < 0)
		m_curTag = maxtag+1;
	else
		m_curTag = tag;

	parent->addChild(this, m_curZ, m_curTag);
}

