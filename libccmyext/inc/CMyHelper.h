#pragma once
#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

#define DYNAMIC_CAST_CCASERT(SRC_VAR, DES_TYPE, DES_VAR) \
	DES_TYPE* DES_VAR=dynamic_cast<DES_TYPE*>(SRC_VAR); \
	CCAssert(DES_VAR!=NULL, "dynamic_cast fail: "#DES_TYPE)

#define DYNAMIC_CAST_CCASERT2(SRC_VAR, DES_TYPE, DES_VAR) \
	DES_VAR=dynamic_cast<DES_TYPE*>(SRC_VAR); \
	CCAssert(DES_VAR!=NULL, "dynamic_cast fail: "#DES_TYPE)


class CCMyHelper
{
public: 
	enum POSITION_TYPE{
		POSITION_TYPE_DEFAULT,
		POSITION_TYPE_CENTER,
		POSITION_TYPE_TOP_LEFT,
		POSITION_TYPE_TOP_RIGHT,
		POSITION_TYPE_BOTTOM_LEFT,
		POSITION_TYPE_BOTTOM_RIGHT
	};

	struct POS_INFO
	{
		float x;
		float y;
		POSITION_TYPE type;
		POS_INFO();

		POS_INFO(float ax, float ay, POSITION_TYPE atype);
	};

	struct FONT_INFO
	{
		ccColor3B color;
		float size;
		string name;

		FONT_INFO(const ccColor3B& acolor, float asize, const char* aname);

		FONT_INFO(const FONT_INFO& info);

		FONT_INFO();
	};

public:
	CCMyHelper(void);
	~CCMyHelper(void);

	//Í¨ÓÃ
	static void setPosition(CCNode* pnode, POSITION_TYPE type, float x, float y);

	//ÌØÊâ
	static void setPositionByCenter(CCMenu* pmenu, float x, float y);
	static void setPositionByTopLeft(CCMenu* pmenu, float x, float y);
	static void setPositionByBottomLeft(CCMenu* pmenu, float x, float y);
	static void setPositionByTopRight(CCMenu* pmenu, float x, float y);
	static void setPositionByBottomRight(CCMenu* pmenu, float x, float y);
	static CCRect getRect(CCMenu* pmenu);
	static void logForNode(CCNode* plognode, const char* hint);

	inline static void setPosC(CCNode* pnode, float x, float y)
	{
		setPosInner(pnode, x-pnode->getContentSize().width/2, y-pnode->getContentSize().height/2);
	}

	inline static void setPosTL(CCNode* pnode, float x, float y)
	{
		setPosInner(pnode, x, y-pnode->getContentSize().height);
	}

	inline static void setPosBL(CCNode* pnode, float x, float y)
	{
		setPosInner(pnode, x, y);
	}

	inline static void setPosTR(CCNode* pnode, float x, float y)
	{
		setPosInner(pnode, x-pnode->getContentSize().width, y-pnode->getContentSize().height);
	}

	inline static void setPosBR(CCNode* pnode, float x, float y)
	{
		setPosInner(pnode, x-pnode->getContentSize().width, y);
	}

	inline static void setPosScreenCenter(CCNode* pnode)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		setPosC(pnode, size.width/2, size.height/2);
	}

	static CCMenu* createImgButton(const char* normalImg, 
		CCObject* target, SEL_MenuHandler selector,
		int tagId=-1,
		const char* selecetImg=NULL, const char* disableImg=NULL, float posx=0, float posy=0, 
		POSITION_TYPE postype=POSITION_TYPE_CENTER);

	static CCMenu* createFrameButton(const char* normalFrame, 
		CCObject* target, SEL_MenuHandler selector,
		int tagId=-1,
		const char* selecetFrame=NULL, const char* disableFrame=NULL, float posx=0, float posy=0, 
		POSITION_TYPE postype=POSITION_TYPE_CENTER);

	static void loadFrames(const char* texture, const char* plist);

	static CCSprite* createZeroAnchorSprite(const char* texFileName);
	static CCSprite* createZeroAnchorSprite(CCTexture2D* tex);
	static CCSprite* createZeroAnchorFrameSprite(const char* frameName);

	static bool attachMenuToNode(CCNode* n, CCObject* target, SEL_MenuHandler selector,
		int tagId=-1, float width=0, float height=0);

	static CCMenu* createSpriteButton(CCSprite* pnormal, CCSprite* psel, CCSprite* pdis,
		CCObject* target, SEL_MenuHandler selector, int tagId=-1,
		float posx=0, float posy=0, 
		POSITION_TYPE postype=POSITION_TYPE_CENTER);

protected:
	static void setPosInner(CCNode* pnode, float x, float y);
};
