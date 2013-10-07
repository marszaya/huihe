#pragma once
#include "CSpriteFrameAnime.h"
#include <string>
using namespace std;

class CFightEffect: public CCNode
{
public:
	CFightEffect(void);
	virtual ~CFightEffect(void);

	static CFightEffect* create(int effectid, int subID = -1);
	bool initByEffectID(int effectid, int subID = -1);

	void play(int spd=1);

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

public:
	int m_id;
	int m_subId;
	CCSpriteFrameAnime* m_anime;
};

class CFightEffectImg:public CCSprite
{
public:
	CFightEffectImg(void);
	virtual ~CFightEffectImg(void);

	static CFightEffectImg* create(int effectID, int subID);
	bool initCFightEffectImg(int effectID, int subID);

	static string getFrameName(int effectID, int subID);
};
