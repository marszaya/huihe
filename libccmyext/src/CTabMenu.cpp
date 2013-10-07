#include "CTabMenu.h"

CCETabMenuItem::CCETabMenuItem(void)
{
	m_isItemSelected = false;
}

CCETabMenuItem::~CCETabMenuItem(void)
{
}

CCETabMenuItem* CCETabMenuItem::create(CCNode* selSp, CCNode* unselSp,
	CCObject *target, SEL_MenuHandler selector)
{
	CCETabMenuItem *pRet = new CCETabMenuItem();
	if(pRet && pRet->initCCETabMenuItem(selSp,unselSp,target,selector))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCETabMenuItem::initCCETabMenuItem(CCNode* selSp, CCNode* unselSp,
	CCObject *target, SEL_MenuHandler selector)
{
	bool ret=false;
	do{
		m_selSprite = selSp;
		m_unselSprite = unselSp;
		this->addChild(selSp);
		this->addChild(unselSp);
		setItemSelected(false);
		ret = CCMenuItem::initWithTarget(target, selector);
	}while(0);

	return ret;
}

void CCETabMenuItem::activate()
{
	//²»ÖØ¸´¼¤»î
	if(m_isItemSelected)
		return;

	CCMenuItem::activate();
}

void CCETabMenuItem::setItemSelected(bool v)
{
	m_isItemSelected = v;
	if(m_isItemSelected)
	{
		m_selSprite->setVisible(true);
		m_unselSprite->setVisible(false);
		this->setContentSize(m_selSprite->getContentSize());
	}
	else
	{
		m_selSprite->setVisible(false);
		m_unselSprite->setVisible(true);
		this->setContentSize(m_unselSprite->getContentSize());
	}
}


CCETabMenu::CCETabMenu(void)
{
	m_menu = NULL;
	m_space = 0;
	m_selectedTag = -1;
	m_lastX = 0;
}

CCETabMenu::~CCETabMenu(void)
{
}

CCETabMenu* CCETabMenu::create(CCUCommonDelegate* pd)
{
	CCETabMenu *pRet = new CCETabMenu();
	if(pRet && pRet->initCCETabMenu(pd))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCETabMenu::initCCETabMenu(CCUCommonDelegate* pd)
{
	bool ret=false;
	do{
		m_menu = CCMenu::create();
		if(!m_menu)
			break;
		m_space = 0;
		m_lastX = 0;
		this->addChild(m_menu);
		this->setDelegate(pd);
		ret = true;
	}while(0);

	return ret;
}

bool CCETabMenu::addTab(int tag,CCNode* selSp, CCNode* unSelSp)
{
	bool ret = false;
	do{
		if(this->getChildByTag(tag))
			break;

		CCETabMenuItem* pnewItem = CCETabMenuItem::create(selSp, unSelSp,
			this, menu_selector(CCETabMenu::callbackTabSelected));
		if(!pnewItem)
			break;

		CCMyHelper::setPosBL(pnewItem, m_lastX, 0);
		m_lastX += pnewItem->getContentSize().width + m_space;

		m_menu->addChild(pnewItem, 1, tag);
		CCMyHelper::setPositionByBottomLeft(m_menu, 0, 0);
		ret= true;
	}while(0);
	return ret;
}

void CCETabMenu::callbackTabSelected(CCNode* pnode)
{
	CCETabMenuItem* pmenu = dynamic_cast<CCETabMenuItem*>(pnode);
	if(pmenu)
	{
		this->selectTab(pmenu->getTag(), true);
	}
}

void CCETabMenu::selectTab(int tag, bool invokeCallBack)
{
	m_selectedTag = tag;

    CCObject* pObject = NULL;
	CCArray* pChildren = m_menu->getChildren();
    CCARRAY_FOREACH(pChildren, pObject)
	{
		CCETabMenuItem* pmenu = dynamic_cast<CCETabMenuItem*>(pObject);
		if(pmenu)
		{
			if(pmenu->getTag() == tag)
			{
				pmenu->setItemSelected(true);
			}
			else
			{
				pmenu->setItemSelected(false);
			}
		}
	}

	if(m_saveDelegate && invokeCallBack)
		m_saveDelegate->notifyTargetWithCmd(ITEM_SELECTED);
}

void CCETabMenu::resetPosition()
{
	CCObject* pObject = NULL;
	CCArray* pChildren = m_menu->getChildren();
	m_lastX = 0;
    CCARRAY_FOREACH(pChildren, pObject)
	{
		CCETabMenuItem* pmenu = dynamic_cast<CCETabMenuItem*>(pObject);
		CCMyHelper::setPosBL(pmenu, m_lastX, 0);
		m_lastX += pmenu->getContentSize().width + m_space;
	}
}
