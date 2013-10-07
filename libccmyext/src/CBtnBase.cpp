#include "CBtnBase.h"
#include "CNode9Grid.h"
#include "CMyHelper.h"

CCBtnBase::CCBtnBase(void)
{
}

CCBtnBase::~CCBtnBase(void)
{
}

CCBtnBase* CCBtnBase::create(CCObject *rec, SEL_MenuHandler selector, 
	 const CCBtnBase::Config* pconfig, const char* label)
{
	CCBtnBase *pRet = new CCBtnBase();
	if(pRet && pRet->initWithConfig(rec, selector, pconfig, label))
    {
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCBtnBase::initWithConfig(CCObject *rec, SEL_MenuHandler selector, 
	const CCBtnBase::Config* pconfig, const char* label)
{
	bool ret = false;
	do{
		CCLabelTTF* plabel = CCLabelTTF::create(label, pconfig->fontName.c_str(), pconfig->fontSize);
		CC_BREAK_IF(!plabel);
		plabel->setColor(pconfig->fontColor);

		float labelw = plabel->getContentSize().width;
		float labelh = plabel->getContentSize().height;

		CC_BREAK_IF(pconfig->x2 - pconfig->x1 <= 0);
		CC_BREAK_IF(pconfig->y2 - pconfig->y1 <= 0);

		float xscale = (labelw+2*pconfig->gap)/(pconfig->x2 - pconfig->x1);
		float yscale = labelh/(pconfig->y2 - pconfig->y1);
	
		CCNode9Grid* pNormal = NULL;
		CCNode9Grid* pSelect = NULL;
		CCNode9Grid* pDisable = NULL;

		if(!pconfig->normalImg.empty())
		{
			pNormal = CCNode9Grid::create(pconfig->normalImg.c_str(), 
				pconfig->x1, pconfig->x2, xscale, pconfig->y1, pconfig->y2, yscale);

			CC_BREAK_IF(!pNormal);
		}

		if(!pconfig->selectedImg.empty())
		{
			pSelect = CCNode9Grid::create(pconfig->selectedImg.c_str(), 
				pconfig->x1, pconfig->x2, xscale, pconfig->y1, pconfig->y2, yscale);

			CC_BREAK_IF(!pSelect);
		}

		if(!pconfig->disableImg.empty())
		{
			pDisable = CCNode9Grid::create(pconfig->disableImg.c_str(), 
				pconfig->x1, pconfig->x2, xscale, pconfig->y1, pconfig->y2, yscale);

			CC_BREAK_IF(!pDisable);
		}

		CC_BREAK_IF(!this->initWithNormalSprite(pNormal, pSelect, pDisable, rec, selector));
		
		const CCSize& size = this->getContentSize();
		CCMyHelper::setPosC(plabel, size.width/2, size.height/2);

		this->addChild(plabel);
		
		ret = true;
	}while(0);

	return ret;
}

CCMenu* CCBtnBase::createMenu(CCObject *rec, SEL_MenuHandler selector, 
	const Config* pconfig, const char* label,  int tagId, float posx, float posy, 
	CCMyHelper::POSITION_TYPE postype)
{
	CCMenu* mret = NULL;
	do{
		CCBtnBase* mi = CCBtnBase::create(rec, selector, pconfig, label);
		if(mi == NULL)
		{
			break;
		}

		if(tagId >= 0)
		{
			mi->setTag(tagId);
		}

		mret = CCMenu::create(mi, NULL);
		if(mret == NULL)
		{
			break;
		}

		CCMyHelper::setPosition(mret, postype, posx, posy);
	}while(0);

	return mret;
}

CCCheckBox::CCCheckBox(void)
{
	m_toggle = NULL;
	m_state = false;
	m_select = NULL;
	m_unselect = NULL;
	m_saveTarget = NULL;
	m_saveSelector = NULL;
	m_block = false;
}

CCCheckBox::~CCCheckBox(void)
{
}

CCCheckBox* CCCheckBox::create(const char* onImg, const char* offImg,
		CCObject* target, SEL_MenuHandler selector, bool imgIsFrame,
		int tagId)
{
	CCCheckBox *pRet = new CCCheckBox();
	if(pRet && pRet->initCCCheckBox(onImg, offImg, target, selector, imgIsFrame, tagId))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCCheckBox::initCCCheckBox(const char* onImg, const char* offImg,
		CCObject* target, SEL_MenuHandler selector, bool imgIsFrame ,
		int tagId)
{
	bool ret=false;
	do{
		CCSprite* on=NULL;
		CCSprite* off=NULL;
		if(imgIsFrame)
		{
			on = CCSprite::createWithSpriteFrameName(onImg);
			off = CCSprite::createWithSpriteFrameName(offImg);
		}
		else
		{
			on = CCSprite::create(onImg);
			off = CCSprite::create(offImg);
		}

		CC_BREAK_IF(!on);
		CC_BREAK_IF(!off);
		on->setAnchorPoint(ccp(0,0));
		off->setAnchorPoint(ccp(0,0));


		m_select = CCMenuItemSprite::create(on, NULL);
		CC_BREAK_IF(!m_select);

		m_unselect = CCMenuItemSprite::create(off, NULL);
		CC_BREAK_IF(!m_unselect);


		m_state = false;
		m_toggle = CCMenuItemToggle::createWithTarget(
			this, menu_selector(CCCheckBox::catchMenu), m_unselect, m_select, NULL);
		CC_BREAK_IF(!m_toggle);
		m_saveTarget = target;
		m_saveSelector = selector;

		if(tagId >= 0)
		{
			m_toggle->setTag(tagId);
		}

		CCArray* pArray = CCArray::create(m_toggle, NULL);
		ret = initWithArray(pArray);
	}while(0);

	return ret;
}

void CCCheckBox::setState(bool v)
{
	if(v != m_state && m_toggle)
	{
		m_state = v;
		m_block = true;
		m_toggle->activate();
		m_block = false;
	}
}

void CCCheckBox::catchMenu(CCObject* target)
{
	if(!m_block)
	{
		m_state = !m_state;
		if(m_saveTarget && m_saveSelector)
		{
			(m_saveTarget->*m_saveSelector)(target);
		}
	}
}

