#include "CTextFieldWindow.h"
#include <string.h>

CCTextFieldTTFPos::CCTextFieldTTFPos()
{
	m_psave = NULL;
	m_maxLen = 0;
	m_cbobj = NULL;
}

CCTextFieldTTFPos::~CCTextFieldTTFPos()
{
	setCallBack(NULL,NULL);
}

void CCTextFieldTTFPos::setCallBack(CCObject* target, SEL_CallFuncO func)
{
	if(target)
		target->retain();
	if(m_cbobj)
		m_cbobj->release();
	m_cbobj = target;
	m_callback = func;
}

CCTextFieldTTFPos* CCTextFieldTTFPos::textFieldWithPlaceHolder(const char *placeholder, 
		const char *fontName, float fontSize)
{
    CCTextFieldTTFPos *pRet = new CCTextFieldTTFPos();
    if(pRet && pRet->initWithString("", fontName, fontSize))
    {
        pRet->autorelease();
		pRet->bindString(NULL);
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }

		pRet->bindPos(ccp(0,0), CCMyHelper::POSITION_TYPE_BOTTOM_LEFT);
		pRet->setMaxLen(100);
		pRet->setCallBack(NULL, NULL);
		pRet->setAnchorPoint(ccp(0,0));
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CCTextFieldTTFPos::setString(const char *text)
{
	if(strlen(text) > m_maxLen)
	{
		return;
	}
	CCTextFieldTTF::setString(text);
	CCMyHelper::setPosition(this, m_postype, m_pos.x, m_pos.y);
	if(m_psave)
	{
		*m_psave = text;
	}

	if(m_cbobj && m_callback)
	{
		CCString* cs = new CCString(text);
		(m_cbobj->*m_callback)(cs);
		cs->release();
	}
}

void CCTextFieldTTFPos::bindPos(const CCPoint& pos, CCMyHelper::POSITION_TYPE postype)
{
	m_pos = pos;
	m_postype = postype;
}

CCTextFieldWindow::CCTextFieldWindow(void)
{
	m_pfield = NULL;
	m_hint =NULL;
}

CCTextFieldWindow::~CCTextFieldWindow(void)
{
}

CCTextFieldWindow* CCTextFieldWindow::create(float width, float height, 
		const CCMyHelper::FONT_INFO& font, int maxLen)
{
	CCTextFieldWindow *pRet = new CCTextFieldWindow();
	if(pRet && pRet->initWithFontConfig(width,height, font, maxLen))
    {
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCTextFieldWindow::initWithFontConfig(float width, float height, 
	const CCMyHelper::FONT_INFO& font, int maxLen)
{
	bool ret = false;
	m_pfield = NULL;
	setWindowSize(width, height);
	do{
		CCTextFieldTTFPos* ptf = CCTextFieldTTFPos::textFieldWithPlaceHolder(
			NULL, font.name.c_str(), font.size);
		CC_BREAK_IF(!ptf);
		ptf->setColor(font.color);
		ptf->setMaxLen(maxLen);
		ptf->setCallBack(this, callfuncO_selector(CCTextFieldWindow::textCallBack));
		this->addChild(ptf,1);
		m_pfield = ptf;
		m_hint =NULL;
		ret = true;
	}while(0);

	return ret;
}

void CCTextFieldWindow::setHintSprite(CCSprite* sp)
{
	m_hint = sp;
	CCBlink* pblink = CCBlink::create(3.0, 2);
	sp->runAction(CCRepeatForever::create(pblink));
	this->addChild(sp);
	updateHintPos();
}

void CCTextFieldWindow::updateHintPos()
{
	if(m_hint && m_pfield)
	{
		float xx = m_pfield->getContentSize().width;
		string fc = m_pfield->getString();
		if(fc.length() == 0) 
			xx = 0;
		CCMyHelper::setPosBL(m_hint,xx ,0);
	}
}

void CCTextFieldWindow::textCallBack(CCObject* obj)
{
	updateHintPos();
}
