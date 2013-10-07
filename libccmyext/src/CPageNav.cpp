#include "CPageNav.h"
#include "StrTool.h"

CCEPageNav::CCEPageNav(void)
{
	m_pageLabelTag=-1;
	m_pre=NULL;
	m_next=NULL;
}

CCEPageNav::~CCEPageNav(void)
{
}

CCEPageNav* CCEPageNav::create(CCUCommonDelegate* pd)
{
	CCEPageNav *pRet = new CCEPageNav();
	if(pRet && pRet->initCCEPageNav(pd))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCEPageNav::initCCEPageNav(CCUCommonDelegate* pd)
{
	bool ret=false;
	do{
		this->setDelegate(pd);
		ret = true;
	}while(0);

	return ret;
}

void CCEPageNav::onPreBtn(CCObject* target)
{
	if(m_saveDelegate)
		m_saveDelegate->notifyTargetWithCmd(GO_PRE);
}

void CCEPageNav::onNextBtn(CCObject* target)
{
	if(m_saveDelegate)
		m_saveDelegate->notifyTargetWithCmd(GO_NEXT);
}



void CCEPageNav::setPreBtn(CCSprite* normal, CCSprite* selected, CCSprite* disable)
{
	do{
		m_pre = CCMyHelper::createSpriteButton(normal, selected, disable,
			this, menu_selector(CCEPageNav::onPreBtn),-1,
			int(getWindowWidth()/2)-DEFAULT_GAP, int(getWindowHeight()/2)
			);
		if(!m_pre)
			break;

		this->addChild(m_pre);
	}while(0);
}

void CCEPageNav::setNextBtn(CCSprite* normal, CCSprite* selected, CCSprite* disable)
{
	do{
		m_next = CCMyHelper::createSpriteButton(normal, selected, disable,
			this, menu_selector(CCEPageNav::onNextBtn),-1,
			int(getWindowWidth()/2)+DEFAULT_GAP, int(getWindowHeight()/2)
			);
		if(!m_next)
			break;

		this->addChild(m_next);
	}while(0);
}

void CCEPageNav::setLabel(CCMyHelper::FONT_INFO pageFont, int pageNum)
{
	do{
		m_font = pageFont;
		updatePageNum(pageNum);
	}while(0);
}

void CCEPageNav::alignByGap(int gap)
{
	do{
		if(m_pre)
		{
			CCMyHelper::setPosC(m_pre, 
				int(getWindowWidth()/2)-DEFAULT_GAP, int(getWindowHeight()/2));
		}

		if(m_next)
		{
			CCMyHelper::setPosC(m_next, 
				int(getWindowWidth()/2)+DEFAULT_GAP, int(getWindowHeight()/2));
		}
	}while(0);
}

void CCEPageNav::updatePageNum(int num)
{
	do{
		m_pageLabelTag = updateLabel(m_pageLabelTag, CStrTool::strDecimal(num).c_str(), 
			m_font, 
			CCMyHelper::POS_INFO(
			int(getWindowWidth()/2), int(getWindowHeight()/2),
				CCMyHelper::POSITION_TYPE_CENTER)
		);	
	}while(0);
}