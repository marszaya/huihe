#pragma once
#include "CSpriteFrameAnime.h"

class CFightUnit: public CCNode
{
public:
	CFightUnit(void);
	virtual ~CFightUnit(void);

	static const float ANIME_FRAME_DURATION;

	static CFightUnit* create(int unitid);
	bool initByUintID(int unitid);

	void stay(int spd=1);
	void attack(int spd=1);
	void move(int spd=1);

	inline void setFlip(bool v)
	{
		if(m_anime)
		{
			m_anime->setFlip(v);
		}
	}

	inline void changeFlip()
	{
		if(m_anime)
		{
			m_anime->setFlip(!m_anime->getFlip());
		}		
	}

	inline bool getFlip()
	{
		return m_anime && m_anime->getFlip();
	}

	inline CCSpriteFrameAnime* getAnime()
	{
		return m_anime;
	}

	inline int getUnitID()
	{
		return m_id;
	}

public:
	int m_id;
	CCSpriteFrameAnime* m_anime;
};
