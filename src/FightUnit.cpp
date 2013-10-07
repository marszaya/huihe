#include "FightUnit.h"

const float CFightUnit::ANIME_FRAME_DURATION = 0.1;

CFightUnit::CFightUnit(void)
{
	m_anime = NULL;
	m_id = -1;
}

CFightUnit::~CFightUnit(void)
{
}

CFightUnit* CFightUnit::create(int unitid)
{
	CFightUnit *pRet = new CFightUnit();
	if(pRet && pRet->initByUintID(unitid))
    {
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CFightUnit::initByUintID(int unitid)
{
	bool ret = false;
	do{
		char texture[64] = {0};
		sprintf(texture, "unit/u%d.png", unitid);
		char plist[64] = {0};
		sprintf(plist, "unit/u%d.plist", unitid);

		CCSpriteFrameAnime* panime = CCSpriteFrameAnime::create(
			texture, plist, ANIME_FRAME_DURATION);
		CC_BREAK_IF(! panime);

		this->addChild(panime);
		
		m_id = unitid;
		m_anime = panime;
		ret = true;
	}while(0);
	return ret;
}


void CFightUnit::stay(int spd)
{
	if(m_anime)
	{
		char buff[32] = {0};
		sprintf(buff, "u%d.stay", m_id);
		if(spd != 1)
			m_anime->setFrameDuration(ANIME_FRAME_DURATION/spd);
		m_anime->repeatAnimeByName(buff);
	}
}

void CFightUnit::attack(int spd)
{
	if(m_anime)
	{
		char buff[32] = {0};
		sprintf(buff, "u%d.attack", m_id);
		if(spd != 1)
			m_anime->setFrameDuration(ANIME_FRAME_DURATION/spd);
		m_anime->playAnimeByName(buff);
	}
}

void CFightUnit::move(int spd)
{
	if(m_anime)
	{
		char buff[32] = {0};
		sprintf(buff, "u%d.move", m_id);
		if(spd != 1)
			m_anime->setFrameDuration(ANIME_FRAME_DURATION/spd);
		m_anime->repeatAnimeByName(buff);
	}
}
