#include "CSpriteFillTex.h"

CCSpriteFillTex::CCSpriteFillTex(void)
{
	m_row = 0;
	m_col = 0;
}

CCSpriteFillTex::~CCSpriteFillTex(void)
{
}

CCSpriteFillTex* CCSpriteFillTex::create(const char *tile, unsigned int tileWidth, 
	unsigned int tileHeight, float row, float col, unsigned tileIdx)
{
	CCSpriteFillTex *pRet = new CCSpriteFillTex();
    if(pRet && pRet->initWithTileFile(tile, tileWidth, tileHeight, ceilf(row)*ceil(col)))
    {
        pRet->autorelease();
		pRet->setFillParam(row, col,tileIdx);
		return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCSpriteFillTex* CCSpriteFillTex::create(const char * tex, float row, float col)
{
	CCSpriteFillTex *pRet = new CCSpriteFillTex();
	//100是随便填写的
	if(pRet && pRet->initWithTileFile(tex, 100, 100, ceilf(row)*ceilf(col)))
	{
		pRet->autorelease();
		pRet->setFillParam(row, col);
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

CCSpriteFillTex* CCSpriteFillTex::create(const char * tex, float row, float col, 
	const CCRect& texRect)
{
	CCSpriteFillTex *pRet = new CCSpriteFillTex();
	//100是随便填写的
	if(pRet && pRet->initWithTileFile(tex, 100, 100, ceilf(row)*ceilf(col)))
	{
		pRet->autorelease();
		pRet->setFillParam(row, col, texRect);
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

void CCSpriteFillTex::fillRect(CCRect* rect , const CCRect& crect)
{
		CCTexture2D *texture = m_pTextureAtlas->getTexture();
		float textureWide = (float) texture->getPixelsWide();
		float textureHigh = (float) texture->getPixelsHigh();
		m_uItemWidth = crect.size.width;
		m_uItemHeight = crect.size.height;	
		rect->origin.x = crect.origin.x * CC_CONTENT_SCALE_FACTOR() / textureWide;
		rect->origin.y = crect.origin.y * CC_CONTENT_SCALE_FACTOR() / textureHigh;
		rect->size.width = crect.size.width * CC_CONTENT_SCALE_FACTOR() / textureWide;
		rect->size.height = crect.size.height * CC_CONTENT_SCALE_FACTOR() / textureHigh;
}


void CCSpriteFillTex::fillRectByTile(CCRect* rect, int tileIdx)
{
    CCTexture2D *texture = m_pTextureAtlas->getTexture();
    float textureWide = (float) texture->getPixelsWide();
    float textureHigh = (float) texture->getPixelsHigh();
    float itemWidthInPixels = m_uItemWidth * CC_CONTENT_SCALE_FACTOR();
    float itemHeightInPixels = m_uItemHeight * CC_CONTENT_SCALE_FACTOR();
	float xidx = (float) (tileIdx % m_uItemsPerRow);
	float yidx = (float) (tileIdx / m_uItemsPerRow);

	rect->setRect(xidx * itemWidthInPixels / textureWide, 
		yidx * itemHeightInPixels / textureHigh, 
		itemWidthInPixels / textureWide, itemHeightInPixels / textureHigh);
}

void CCSpriteFillTex::fillFullRect(CCRect* rect)
{
    CCTexture2D *texture = m_pTextureAtlas->getTexture();
	rect->setRect(0,0, 1.0, 1.0);
	m_uItemWidth = texture->getContentSize().width;
	m_uItemHeight = texture->getContentSize().height;
}

void CCSpriteFillTex::setFillParamInner(float row, float col, const CCRect& texRect)
{
	int nrow = ceilf(row);
	int ncol = ceilf(col);
	float drow = row+1 - ceilf(row);
	float dcol = col+1 - ceilf(col);
	unsigned int len = nrow*ncol;
    if (len > m_pTextureAtlas->getTotalQuads())
    {
        m_pTextureAtlas->resizeCapacity(len);
    }

	m_row = row;
	m_col = col;

	ccV3F_C4B_T2F_Quad quad;

	float left = texRect.getMinX();
	float right = texRect.getMaxX();
	float top = texRect.getMinY();
	float bottom = texRect.getMaxY();

    for(int i = 0; i < nrow; i++) {
		for(int j=0; j<ncol; j++)
		{
	        quad.tl.texCoords.u = left;
			quad.tl.texCoords.v = top;
			quad.tr.texCoords.u = right;
			quad.tr.texCoords.v = top;
			quad.bl.texCoords.u = left;
			quad.bl.texCoords.v = bottom;
			quad.br.texCoords.u = right;
			quad.br.texCoords.v = bottom;

			quad.bl.vertices.x = (float) (j * m_uItemWidth);
			quad.bl.vertices.y = (float) (i * m_uItemHeight);
			quad.bl.vertices.z = 0.0f;
			quad.br.vertices.x = (float)(j * m_uItemWidth + m_uItemWidth);
			quad.br.vertices.y = (float) (i * m_uItemHeight);
			quad.br.vertices.z = 0.0f;
			quad.tl.vertices.x = (float)(j * m_uItemWidth);
			quad.tl.vertices.y = (float)(i * m_uItemHeight + m_uItemHeight);
			quad.tl.vertices.z = 0.0f;
			quad.tr.vertices.x = (float)(j * m_uItemWidth + m_uItemWidth);
			quad.tr.vertices.y = (float)(i * m_uItemHeight + m_uItemHeight);
			quad.tr.vertices.z = 0.0f;

			//非整数的row和col，边缘截断修正
			if(j == ncol - 1 && dcol < 1)
			{
				quad.tr.texCoords.u = left + (right-left)*dcol;
				quad.br.texCoords.u = left + (right-left)*dcol;
				quad.tr.vertices.x = ((float)j+dcol) * m_uItemWidth;
				quad.br.vertices.x = ((float)j+dcol)* m_uItemWidth;
			}

			if(i== nrow-1 && drow < 1)
			{
				quad.tl.texCoords.v = bottom-(bottom-top)*drow;
				quad.tr.texCoords.v = bottom-(bottom-top)*drow;
				quad.tl.vertices.y = ((float)i+drow) * m_uItemHeight;
				quad.tr.vertices.y = ((float)i+drow) * m_uItemHeight;
			}

			ccColor3B theC3B = getColor();
			ccColor4B c = { theC3B.r, theC3B.g, theC3B.b, getOpacity() };
			quad.tl.colors = c;
			quad.tr.colors = c;
			quad.bl.colors = c;
			quad.br.colors = c;
			m_pTextureAtlas->updateQuad(&quad, i*ncol+j);
		}
    }

	CCSize s = CCSizeMake(col*m_uItemWidth, row*m_uItemHeight);
    this->setContentSize(s);
}