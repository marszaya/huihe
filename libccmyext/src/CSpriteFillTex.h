#pragma once
#include "cocos2d.h"

USING_NS_CC;

//平铺Textrue
class CCSpriteFillTex:
	public CCAtlasNode
{
public:
	CCSpriteFillTex(void);
	virtual ~CCSpriteFillTex(void);

	//把texture平铺到contentSize上,row*col

	//tileFile是由tileWidth x  tileHeight 构成的等分图
	//tileIdx是指定使用tileFile的第几块来拼图
	static CCSpriteFillTex* create(const char *tile, unsigned int tileWidth, unsigned int tileHeight,
		float row, float col, unsigned tileIdx=0);
	
	//固定使用整个图作为图元
	static CCSpriteFillTex* create(const char * tex, float row, float col);

	//更加灵活，指定图元的rect
	static CCSpriteFillTex* create(const char * tex, float row, float col, 
		const CCRect& texRect);	

	inline void setFillParam(float row, float col, unsigned tileIdx)
	{
		CCRect rect;
		fillRectByTile(&rect, tileIdx);
		setFillParamInner(row, col, rect);
	}

	void setFillParam(float row, float col, const CCRect& rect)
	{
		CCRect newrect;
		fillRect(&newrect, rect);
		setFillParamInner(row, col, newrect);
	}

	inline void setFillParam(float row, float col)
	{
		CCRect rect;
		fillFullRect(&rect);
		setFillParamInner(row, col, rect);
	}

protected:
	void setFillParamInner(float row, float col, const CCRect& pixelRect);
	void fillRectByTile(CCRect* rect, int tileIdx);
	void fillFullRect(CCRect* rect);
	void fillRect(CCRect* rect, const CCRect& crect);

protected:
	float m_row;
	float m_col;
};
