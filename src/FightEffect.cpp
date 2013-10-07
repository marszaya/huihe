#include "FightEffect.h"
#include "CMyHelper.h"

CFightEffect::CFightEffect(void)
{
	m_anime = NULL;
	m_id = -1;
	m_subId = -1;
}

CFightEffect::~CFightEffect(void)
{
}

CFightEffect* CFightEffect::create(int effectid, int subID)
{
	CFightEffect *pRet = new CFightEffect();
	if(pRet && pRet->initByEffectID(effectid, subID))
    {
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CFightEffect::initByEffectID(int effectid, int subID)
{
	bool ret = false;
	do{
		char texture[64] = {0};
		sprintf(texture, "effect/t%d.png", effectid);
		char plist[64] = {0};
		sprintf(plist, "effect/t%d.plist", effectid);

		CCSpriteFrameAnime* panime = CCSpriteFrameAnime::create(
			texture, plist, 1.0/7);
		CC_BREAK_IF(! panime);

		this->addChild(panime);
		
		m_id = effectid;
		m_subId = subID;
		m_anime = panime;
		ret = true;
	}while(0);
	return ret;
}


void CFightEffect::play(int spd)
{
	if(m_anime)
	{
		char buff[32] = {0};
		if(m_subId >= 0)
			sprintf(buff, "t%d.%d", m_id,m_subId);
		else
			sprintf(buff, "t%d", m_id);
		if(spd != 1)
			m_anime->setFrameDuration(m_anime->getFrameDuration()/spd);
		m_anime->repeatAnimeByName(buff);
	}
}

CFightEffectImg::CFightEffectImg(void)
{
}

CFightEffectImg::~CFightEffectImg(void)
{
}

CFightEffectImg* CFightEffectImg::create(int effectID, int subID)
{
	CFightEffectImg *pRet = new CFightEffectImg();
	if(pRet && pRet->initCFightEffectImg(effectID,subID))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CFightEffectImg::initCFightEffectImg(int effectID, int subID)
{
	bool ret=false;
	do{
		ret = this->initWithSpriteFrameName(getFrameName(effectID, subID).c_str());
	}while(0);

	return ret;
}

string CFightEffectImg::getFrameName(int effectID, int subID)
{
	char texture[64] = {0};
	sprintf(texture, "effect/t%d.png", effectID);
	char plist[64] = {0};
	sprintf(plist, "effect/t%d.plist", effectID);
	char buff[32] = {0};
	sprintf(buff, "t%d.%d (1).png", effectID,subID);
	CCMyHelper::loadFrames(texture, plist);
	return buff;
}

