#pragma once
#include "cocos2d.h"

USING_NS_CC;

//ƽ��Textrue
class CCSpriteFillTex:
	public CCAtlasNode
{
public:
	CCSpriteFillTex(void);
	virtual ~CCSpriteFillTex(void);

	//��textureƽ�̵�contentSize��,row*col

	//tileFile����tileWidth x  tileHeight ���ɵĵȷ�ͼ
	//tileIdx��ָ��ʹ��tileFile�ĵڼ�����ƴͼ
	static CCSpriteFillTex* create(const char *tile, unsigned int tileWidth, unsigned int tileHeight,
		float row, float col, unsigned tileIdx=0);
	
	//�̶�ʹ������ͼ��ΪͼԪ
	static CCSpriteFillTex* create(const char * tex, float row, float col);

	//������ָ��ͼԪ��rect
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
