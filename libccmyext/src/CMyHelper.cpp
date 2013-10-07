#include "CMyHelper.h"
#include "logToFile.h"

CCMyHelper::CCMyHelper(void)
{
}

CCMyHelper::~CCMyHelper(void)
{
}

void CCMyHelper::setPosition(CCNode* pnode, POSITION_TYPE type, float x, float y)
{
	CCMenu* pmenu = dynamic_cast<CCMenu*>(pnode);
	if(!pmenu)
	{
		switch(type)
		{
			case POSITION_TYPE_DEFAULT:
				pnode->setPosition(ccp(x,y));
				break;
			case POSITION_TYPE_CENTER:
				setPosC(pnode, x, y);
				break;
			case POSITION_TYPE_TOP_LEFT:
				setPosTL(pnode, x, y);
				break;
			case POSITION_TYPE_TOP_RIGHT:
				setPosTR(pnode, x, y);
				break;
			case POSITION_TYPE_BOTTOM_LEFT:
				setPosBL(pnode, x, y);
				break;
			case POSITION_TYPE_BOTTOM_RIGHT:
				setPosBR(pnode, x, y);
				break;
		}
	}
	else
	{
		switch(type)
		{		
			case POSITION_TYPE_DEFAULT:
				//pmenu->setPosition(x, y);
				//pmenu init时候已经set了position
				break;
			case POSITION_TYPE_CENTER:
				setPositionByCenter(pmenu, x, y);
				break;
			case POSITION_TYPE_TOP_LEFT:
				setPositionByTopLeft(pmenu, x, y);
				break;
			case POSITION_TYPE_TOP_RIGHT:
				setPositionByTopRight(pmenu, x, y);
				break;
			case POSITION_TYPE_BOTTOM_LEFT:
				setPositionByBottomLeft(pmenu, x, y);
				break;
			case POSITION_TYPE_BOTTOM_RIGHT:
				setPositionByBottomRight(pmenu, x, y);
				break;
		}
	}
}

void CCMyHelper::setPositionByCenter(CCMenu* pmenu, float x, float y)
{
	CCRect rt = getRect(pmenu);
	pmenu->setPosition(x-(rt.getMinX()+rt.getMaxX())/2, y-(rt.getMaxY()+rt.getMinY())/2);
}

void CCMyHelper::setPositionByTopLeft(CCMenu* pmenu, float x, float y)
{
	CCRect rt = getRect(pmenu);
	pmenu->setPosition(x-rt.getMinX(), y-rt.getMaxY());
}

void CCMyHelper::setPositionByBottomLeft(CCMenu* pmenu, float x, float y)
{
	CCRect rt = getRect(pmenu);
	pmenu->setPosition(x-rt.getMinX(), y-rt.getMinY());
}

void CCMyHelper::setPositionByTopRight(CCMenu* pmenu, float x, float y)
{
	CCRect rt = getRect(pmenu);
	pmenu->setPosition(x-rt.getMaxX(), y-rt.getMaxY());
}

void CCMyHelper::setPositionByBottomRight(CCMenu* pmenu, float x, float y)
{
	CCRect rt = getRect(pmenu);
	pmenu->setPosition(x-rt.getMaxX(), y-rt.getMinY());
}

CCRect CCMyHelper::getRect(CCMenu* pmenu)
{
	float maxX,maxY,minX,minY;
	maxX = minX = 0;
	maxY = minY = 0;

	if (pmenu->getChildrenCount() > 0)
    {
        CCObject* pObject = NULL;
		CCARRAY_FOREACH(pmenu->getChildren(), pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                CCRect r = ((CCMenuItem*)pChild)->rect();
				if(r.getMinX() < minX)
				{
					minX = r.getMinX();
				}
				
				if(r.getMaxX() > maxX)
				{
					maxX = r.getMaxX();
				}

				if(r.getMinY() < minY)
				{
					minY = r.getMinY();
				}
				
				if(r.getMaxY() > maxY)
				{
					maxY = r.getMaxY();
				}
            }
        }
    }
	return CCRectMake(minX, minY, maxX-minX, maxY-minY);
}

void CCMyHelper::logForNode(CCNode* plognode, const char* hint)
{
	CCU_LOGF("%s ref(%d) ignore(%d) anc=(%f,%f) position=(%f,%f) content(%f,%f)",
		hint, plognode->retainCount(),
		plognode->isIgnoreAnchorPointForPosition(),
		plognode->getAnchorPointInPoints().x,
		plognode->getAnchorPointInPoints().y, 
		plognode->getPosition().x, 
		plognode->getPosition().y,
		plognode->getContentSize().width,
		plognode->getContentSize().height
	);
}

CCMenu* CCMyHelper::createImgButton(const char* normalImg, CCObject* target, 
	SEL_MenuHandler selector, int tagId, const char* selectImg, const char* disableImg, float posx, float posy, POSITION_TYPE postype)
{
	CCMenu* mret = NULL;
	do{
		CCSprite* psel=NULL;
		CCSprite* pdis=NULL;
		CCSprite* pnormal = CCSprite::create(normalImg);
		if(!pnormal)
			break;
		
		if(selectImg)
			psel = CCSprite::create(selectImg);

		if(disableImg)
			pdis  = CCSprite::create(disableImg);

		mret = createSpriteButton(pnormal, psel, pdis, target, selector, tagId, posx, posy, postype);

	}while(0);

	return mret;
}

CCMenu* CCMyHelper::createFrameButton(const char* normalFrame, 
		CCObject* target, SEL_MenuHandler selector,
		int tagId,
		const char* selecetFrame, const char* disableFrame, float posx, float posy, 
		POSITION_TYPE postype)
{
	CCMenu* mret = NULL;
	do{
		CCSprite* pnormal = CCSprite::createWithSpriteFrameName(normalFrame);
		if(!pnormal)
		{
			//调用者自己先加载frame
			break;
		}
		
		CCSprite* psel = NULL;
		if(selecetFrame)
			psel = CCSprite::createWithSpriteFrameName(selecetFrame);

		CCSprite* pdis = NULL;
		if(disableFrame)
			pdis = CCSprite::createWithSpriteFrameName(disableFrame);

		mret = createSpriteButton(pnormal, psel, pdis, target, selector, tagId, posx, posy, postype);
	}while(0);

	return mret;
}


CCMenu* CCMyHelper::createSpriteButton(CCSprite* pnormal, CCSprite* psel, CCSprite* pdis,
	CCObject* target, SEL_MenuHandler selector, int tagId,
	float posx, float posy, POSITION_TYPE postype)
{
	CCMenu* mret = NULL;
	do{
		if(!pnormal)
		{
			break;
		}

		pnormal->setAnchorPoint(ccp(0,0));
		if(psel)
			psel->setAnchorPoint(ccp(0,0));
		if(pdis)
			pdis->setAnchorPoint(ccp(0,0));
	
		CCMenuItemSprite* mi = CCMenuItemSprite::create(
			pnormal,psel,pdis, target, selector);
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

		setPosition(mret, postype, posx, posy);
	}while(0);

	return mret;
}

void CCMyHelper::loadFrames(const char* texture, const char* plist)
{
	CCTexture2D *textureObj = CCTextureCache::sharedTextureCache()->textureForKey(texture);
	if(!textureObj)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, texture);
	}
}

CCMyHelper::POS_INFO::POS_INFO()
{
	x = 0;
	y = 0;
	type = POSITION_TYPE_DEFAULT;
}

CCMyHelper::POS_INFO::POS_INFO(float ax, float ay, POSITION_TYPE atype)
{
	x = ax;
	y = ay;
	type = atype;
}

CCMyHelper::FONT_INFO::FONT_INFO(const ccColor3B& acolor, float asize, const char* aname)
{
	color = acolor;
	size = asize;
	name = aname;
}

CCMyHelper::FONT_INFO::FONT_INFO(const FONT_INFO& info)
{
	color = info.color;
	size = info.size;
	name = info.name;
}

CCMyHelper::FONT_INFO::FONT_INFO()
{
	color=ccWHITE;
	size = 14;
	name = "Arial";
}

CCSprite* CCMyHelper::createZeroAnchorSprite(const char* texFileName)
{
	CCSprite* ret = NULL;
	do{
		ret = CCSprite::create(texFileName);
		if(!ret)
			break;
		ret->setAnchorPoint(ccp(0,0));
	}while(0);

	return ret;
}

CCSprite* CCMyHelper::createZeroAnchorSprite(CCTexture2D* tex)
{
	CCSprite* ret = NULL;
	do{
		ret = CCSprite::createWithTexture(tex);
		if(!ret)
			break;
		ret->setAnchorPoint(ccp(0,0));
	}while(0);

	return ret;
}

CCSprite* CCMyHelper::createZeroAnchorFrameSprite(const char* frameName)
{
	CCSprite* ret = NULL;
	do{
		ret = CCSprite::createWithSpriteFrameName(frameName);
		if(!ret)
			break;
		ret->setAnchorPoint(ccp(0,0));
	}while(0);

	return ret;
}

void CCMyHelper::setPosInner(CCNode* pnode, float x, float y)
{
	if(pnode->isIgnoreAnchorPointForPosition())
	{
		//pos at origh
		pnode->setPosition(ccp(x, y));
	}
	else
	{
		const CCPoint& anc = pnode->getAnchorPointInPoints();
		//pos at anchor
		pnode->setPosition(ccp(x+anc.x, y+anc.y));
	}
}

bool CCMyHelper::attachMenuToNode(CCNode* n, CCObject* target, SEL_MenuHandler selector,
	int tagId, float width, float height)
{
	bool ret = false;
	do{
		CCMenuItem* pitem = CCMenuItem::create(target, selector);
		if(!pitem)
			break;
		if(width > 0 && height>0)
			pitem->setContentSize(CCSizeMake(width, height));
		else
			pitem->setContentSize(n->getContentSize());
		
		pitem->setTag(tagId);

		CCMenu* pmenu = CCMenu::create(pitem,NULL);
		if(!pmenu)
			break;
		
		setPositionByBottomLeft(pmenu, 0,0);
		n->addChild(pmenu,0,tagId);
		ret = true;
	}
	while(0);
	return ret;
}
