#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CCCoverLayer: public CCLayerColor
{
public:
	CCCoverLayer(void);
	virtual ~CCCoverLayer(void);

	static CCCoverLayer* create();

	//if tag == -1 will use parent's max children tag + 1
	void cover(CCNode* parent, int tag = -1);

	inline int getCurZ()
	{
		return m_curZ;
	}

	inline int getCurTag()
	{
		return m_curTag;
	}

protected:
	int m_curZ;
	int m_curTag;
};
