#include "CBarBase.h"

CBarBase::CBarBase(void)
{
	m_ppt = NULL;
}

CBarBase::~CBarBase(void)
{
}

CBarBase* CBarBase::create(const char* barImg, BAR_TYPE type)
{
	CBarBase *pRet = new CBarBase();
	if(pRet && pRet->initCBarBase(barImg,type))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBarBase::initCBarBase(const char* barImg, BAR_TYPE type)
{
	bool ret=false;
	do{
		CCSprite* psp = CCSprite::create(barImg);
		CC_BREAK_IF(!psp);
		m_ppt = CCProgressTimer::create(psp);
		CC_BREAK_IF(!m_ppt);
		m_ppt->setType(kCCProgressTimerTypeBar);
		m_ppt->ignoreAnchorPointForPosition(true);
		CCMyHelper::setPosBL(m_ppt,0,0);
		this->addChild(m_ppt);
		this->setContentSize(psp->getContentSize());
		if(type==LEFT_TO_RIGHT)
			setTypeLeftToRight();
		else
			setTypeRightToLeft();
		ret = true;
	}while(0);

	return ret;
}

void CBarBase::setPercent(float p)
{
	if(m_ppt)
	{
		m_ppt->setPercentage(p);
	}
}

void CBarBase::setTypeLeftToRight()
{
	if(!m_ppt)
		return;
	//y不变
	m_ppt->setMidpoint(ccp(0,0.5));
	m_ppt->setBarChangeRate(ccp(1.0,0));
}

void CBarBase::setTypeRightToLeft()
{
	if(!m_ppt)
		return;
	//y不变
	m_ppt->setMidpoint(ccp(1,0.5));
	m_ppt->setBarChangeRate(ccp(1.0,0));
}