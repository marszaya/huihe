#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class CCSpriteFrameAnime:public CCNode
{
public:
	class AnimeNameRule
	{
	public:
		virtual const char* getFrameName(const char* animeName, int idx);

	protected:
		string buff;
	};

	enum Tags{
		TAG_ANIME
	};

public:
	CCSpriteFrameAnime(void);
	virtual ~CCSpriteFrameAnime(void);

	static CCSpriteFrameAnime* create(const char* texture, const char* plist, float frameDuration=0, 
		int frameCapacity=32, AnimeNameRule* prule=NULL);

	bool initFrameAnime(const char* texture, const char* plist, 
		float frameDuration, int frameCapacity, AnimeNameRule* prule);

	//frame name is calculated by AnimeNameRule
	bool playAnimeByName(const char* animeName, 
		CCObject* pSelectorTarget=NULL, 
		SEL_CallFuncO selector=NULL, CCObject* param=NULL);

	//frame name is calculated by AnimeNameRule
	bool repeatAnimeByName(const char* animeName);

	//frame name is calculated by AnimeNameRule
	bool showFirstFrameByName(const char* frameName);

	//frame name uses frameName directly
	bool showFrameByName(const char* frameName);

	inline int getCurFrameTotal()
	{
		return m_currentAnimeFrameTotal;
	}

	inline float getCurDuration()
	{
		if(m_tmpAnime)
			return m_tmpAnime->getDuration();
		else
			return 0;
	}

	inline void setFlip(bool v)
	{
		m_fliped = v;
	}

	inline bool getFlip( )
	{
		return m_fliped;
	}

	inline float getFrameDuration()
	{
		return m_frameDuration;
	}

	inline void setFrameDuration(float fd)
	{
		m_frameDuration = fd;
	}

protected:
	bool createAnimeByName(const char* animeName);

protected:
	static AnimeNameRule defaultRule;

protected:
	float m_frameDuration;
	int m_frameCapacity;
	int m_currentAnimeFrameTotal;
	CCSprite* m_tmpSp;
	CCAnimate* m_tmpAnime;
	AnimeNameRule*  m_prule;
	bool m_fliped;
};
