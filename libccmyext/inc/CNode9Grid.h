#pragma once
#include "cocos2d.h"
#include "CSpriteFillTex.h"
#include <string>

USING_NS_CC;
using namespace std;

class CCNode9Grid: public CCNodeRGBA
{
public:
	CCNode9Grid(void);
	virtual ~CCNode9Grid(void);

	static CCNode9Grid* create(const char* texFile, float x1, float x2, float xscale,
		float y1, float y2, float yscale);

	bool initWithGrid(const char* texFile, float x1, float x2, float xscale,
		float y1, float y2, float yscale);

	static CCNode9Grid* createWithTargetSize(const char* texFile,
		float cornerX, float cornerY, float targetX, float targetY);

	bool initWithTarget(const char* texFile,
		float cornerX, float cornerY, float targetX, float targetY);

	void do9Scale(float xscale, float yscale);

protected:
	CCSprite* createChildSprite(const CCRect& texRect, const CCPoint& posBottomLeft, float xscale=0, float yscale=0);

	virtual bool createChildren(float xscale, float yscale, float x1, float x2, float wd0, float wd1, float wd2,
		float y1, float y2, float ht0, float ht1, float ht2);

protected:
	float m_x1;
	float m_x2;
	float m_xscale;
	float m_y1;
	float m_y2;
	float m_yscale;
	CCTexture2D* m_texFile;
	string m_texFileName;
};

class CCNode9GridFillTex: public CCNode9Grid
{
public:
	CCNode9GridFillTex(void);
	virtual ~CCNode9GridFillTex(void);

	static CCNode9GridFillTex* create(const char* texFile, float x1, float x2, float xscale,
		float y1, float y2, float yscale);

	static CCNode9GridFillTex* createWithTargetSize(const char* texFile,
		float cornerX, float cornerY, float targetX, float targetY);

protected:
	CCSpriteFillTex* createChildSpriteFT(const CCRect& texRect, float col, float row, const CCPoint& posBottomLeft);
	
	virtual bool createChildren(float xscale, float yscale, float x1, float x2, float wd0, float wd1, float wd2,
		float y1, float y2, float ht0, float ht1, float ht2);

};

