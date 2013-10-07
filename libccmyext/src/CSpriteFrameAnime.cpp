#include "CSpriteFrameAnime.h"
#include "StrTool.h"

CCSpriteFrameAnime::AnimeNameRule CCSpriteFrameAnime::defaultRule;

CCSpriteFrameAnime::CCSpriteFrameAnime(void)
{
	m_frameDuration = float(CCDirector::sharedDirector()->getAnimationInterval());
	m_currentAnimeFrameTotal = 0;
	m_frameCapacity = 0;
	m_fliped = false;
}

CCSpriteFrameAnime::~CCSpriteFrameAnime(void)
{
}

const char* CCSpriteFrameAnime::AnimeNameRule::getFrameName(
	const char* animeName, int idx)
{
	buff = animeName;
	buff.append(" (");
	buff.append(CStrTool::strDecimal(idx+1));
	buff.append(").png");
	return buff.c_str();
}

CCSpriteFrameAnime* CCSpriteFrameAnime::create(const char* texture, 
	const char* plist, float frameDuration, int frameCapacity, AnimeNameRule* prule)
{
	CCSpriteFrameAnime *pRet = new CCSpriteFrameAnime();
	if(pRet && pRet->initFrameAnime(texture, plist, frameDuration, frameCapacity, prule))
    {
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCSpriteFrameAnime::initFrameAnime(const char* texture, const char* plist, 
	float frameDuration, int frameCapacity, AnimeNameRule* prule)
{
	bool ret = false;
	do{
		//虽然图片和帧会缓存，但是plist每次都会重新解析，所以这里优化下
		//假设图片和帧缓存是同步的，图片在缓存中就不再load帧
		CCTexture2D *textureObj = CCTextureCache::sharedTextureCache()->textureForKey(texture);
		if(!textureObj)
		{
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, texture);
		}

		if(frameDuration>0)
		{
			m_frameDuration = frameDuration;
		}
		m_frameCapacity = frameCapacity;
		if(prule)
		{
			m_prule = prule;
		}
		else
		{
			m_prule = &defaultRule;
		}
		ret = true;
	}while(0);

	return ret;
}

bool CCSpriteFrameAnime::playAnimeByName(const char* animeName, 
	CCObject* pSelectorTarget, SEL_CallFuncO selector, CCObject* param)
{
	if(!createAnimeByName(animeName))
	{
		return false;
	}

	if(pSelectorTarget && selector)
	{
		m_tmpSp->runAction(CCSequence::create(m_tmpAnime
			,CCCallFuncO::create(pSelectorTarget, selector, param)
			,NULL));
	}
	else
	{
		m_tmpSp->runAction(m_tmpAnime);
	}

	return true;
}

bool CCSpriteFrameAnime::repeatAnimeByName(const char* animeName)
{
	if(!createAnimeByName(animeName))
	{
		return false;
	}

	m_tmpSp->runAction(CCRepeatForever::create(m_tmpAnime));

	return true;
}

bool CCSpriteFrameAnime::createAnimeByName(const char* animeName)
{
	bool ret = false;
	do{
		//清理掉旧的动画
		CCNode* nodeAnime = this->getChildByTag(TAG_ANIME);
		if(nodeAnime)
		{
			this->removeChild(nodeAnime, true);
		}

		CCArray* walkAnimFrames = CCArray::createWithCapacity(m_frameCapacity); 
		m_currentAnimeFrameTotal = 0;

		CCSpriteFrame* pfirst=NULL;
		for(int i = 0; i <= m_frameCapacity; i++) 
		{ 
			const char* fn = m_prule->getFrameName(animeName,i);
			CCSpriteFrame* p = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fn);
			if(p == NULL)
			{
				break;
			}

			if(i==0)
			{
				pfirst = p;
			}
			
			++m_currentAnimeFrameTotal;
			walkAnimFrames->addObject(p);
		} 

		if(m_currentAnimeFrameTotal == 0)
		{
			CCMessageBox((string("no anime: ")).append(animeName).c_str(), "Debug");
				break;
		}

	    CCAnimation * animation = CCAnimation::createWithSpriteFrames(walkAnimFrames, m_frameDuration); 
		CC_BREAK_IF(!animation);

		CCSprite* sp = CCSprite::createWithSpriteFrame(pfirst); 
		CC_BREAK_IF(!sp);
		if(m_fliped)
		{
			sp->setFlipX(true);
		}

		this->addChild(sp, 0, TAG_ANIME);
		m_tmpSp = sp;
		m_tmpAnime =CCAnimate::create(animation);

		ret = true;
	}while(0);

	return ret;
}

bool CCSpriteFrameAnime::showFirstFrameByName(const char* frameName)
{
	return showFrameByName(m_prule->getFrameName(frameName,0));
}


bool CCSpriteFrameAnime::showFrameByName(const char* frameName)
{
	bool ret = false;
	do{
		//清理掉旧的动画
		CCNode* nodeAnime = this->getChildByTag(TAG_ANIME);
		if(nodeAnime)
		{
			this->removeChild(nodeAnime, true);
		}

		m_currentAnimeFrameTotal = 1;
		CCSpriteFrame* p = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
		if(p == NULL)
		{
			break;
		}

		CCSprite* sp = CCSprite::createWithSpriteFrame(p); 
		CC_BREAK_IF(!sp);
		if(m_fliped)
		{
			sp->setFlipX(true);
		}

		this->addChild(sp, 0, TAG_ANIME);
		m_tmpSp = sp;
		m_tmpAnime = NULL;

		ret = true;
	}while(0);

	return ret;
}