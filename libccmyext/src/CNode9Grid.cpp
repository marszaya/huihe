#include "CNode9Grid.h"
#include "CMyHelper.h"

CCNode9Grid::CCNode9Grid(void)
{
	m_x1=0;
	m_x2=0;
	m_xscale=0;
	m_y1=0;
	m_y2=0;
	m_yscale=0;
}

CCNode9Grid::~CCNode9Grid(void)
{
}

bool CCNode9Grid::initWithGrid(const char* texFile, float x1, float x2, float xscale,
	float y1, float y2, float yscale)
{
	bool ret = false;
	do{
		m_texFileName = texFile;
		this->m_x1 = x1;
		this->m_x2 = x2;
		this->m_y1 = y1;
		this->m_y2 = y2;
		this->m_texFile = CCTextureCache::sharedTextureCache()->addImage(texFile);
		CC_BREAK_IF(!this->m_texFile);
		do9Scale(xscale, yscale);
		ret = true;
	}while(0);
	return ret;
}

void CCNode9Grid::do9Scale(float xscale, float yscale)
{
	//先清掉
	this->removeAllChildrenWithCleanup(true);
	do{
		CCTexture2D *texture = this->m_texFile;

		//texture坐标
		float twide = texture->getContentSize().width;
		float thigh = texture->getContentSize().height;

		float wd0 = m_x1;
		float wd1 = m_x2 - m_x1;
		float wd2 = twide - m_x2;

		float ht0 = m_y1;
		float ht1 = m_y2 - m_y1;
		float ht2 = thigh - m_y2;

		//绘图坐标
		float x1 = m_x1;
		float x2 = x1 + xscale*wd1;

		float y1 = ht2;
		float y2 = y1 + yscale*ht1;

		CC_BREAK_IF(!createChildren(xscale, yscale, x1,x2,wd0,wd1,wd2, y1,y2,ht0,ht1,ht2));
		this->setContentSize(CCSizeMake(x2+wd2, y2+ht2));

	}while(0);
}

bool CCNode9Grid::createChildren(float xscale, float yscale, float x1, float x2, float wd0, float wd1, float wd2,
		float y1, float y2, float ht0, float ht1, float ht2)
{
	bool ret = false;
	do{
		CCRect texRect;
		CCPoint posBL;

		//坐标上还有纠结下，是否会自动转，先当作会

		//四个角用sprite填充
		CCSprite* pret = NULL;

		//textrue坐标系与绘图坐标系y轴相反的
		//左上
		texRect.setRect(0,0, wd0, ht0);
		posBL.setPoint(0, y2);
		pret = createChildSprite(texRect, posBL);
		CC_BREAK_IF(!pret);
		this->addChild(pret);
		
		//左下
		texRect.setRect(0, m_y2, wd0, ht2);
		posBL.setPoint(0, 0);
		pret = createChildSprite(texRect, posBL);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//右上
		texRect.setRect(m_x2, 0, wd2,  ht0);
		posBL.setPoint(x2, y2);
		pret = createChildSprite(texRect, posBL);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//右下
		texRect.setRect(m_x2, m_y2, wd2, ht2);
		posBL.setPoint(x2, 0);
		pret = createChildSprite(texRect, posBL);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//四个边和中间用spritefulltex填充
		//左边
		texRect.setRect(0, m_y1, wd0, ht1);
		posBL.setPoint(0, y1);
		pret = createChildSprite(texRect, posBL, 0, yscale);
		CC_BREAK_IF(!pret);
		this->addChild(pret);
		
		//上边
		texRect.setRect(m_x1, 0, wd1, ht0);
		posBL.setPoint(x1, y2);
		pret = createChildSprite(texRect, posBL, xscale);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//下边
		texRect.setRect(m_x1,m_y2, wd1, ht2);
		posBL.setPoint(x1, 0);
		pret = createChildSprite(texRect, posBL, xscale);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//右边
		texRect.setRect(m_x2, m_y1, wd2, ht1);
		posBL.setPoint(x2, y1);
		pret = createChildSprite(texRect, posBL, 0, yscale);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//中间
		texRect.setRect(m_x1, m_y1, wd1, ht1);
		posBL.setPoint(x1, y1);
		pret = createChildSprite(texRect, posBL, xscale, yscale);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		ret = true;
	}while(0);
	return ret;
}


CCNode9Grid* CCNode9Grid::create(const char* texFile, float x1, float x2, float xscale,
	float y1, float y2, float yscale)
{
	CCNode9Grid *pRet = new CCNode9Grid();
	if(pRet && pRet->initWithGrid(texFile, x1, x2, xscale, y1, y2, yscale))
    {
        pRet->autorelease();
 		return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCNode9Grid* CCNode9Grid::createWithTargetSize(const char* texFile,
	float cornerX, float cornerY, float targetX, float targetY)
{
	CCNode9Grid *pRet = new CCNode9Grid();
	if(pRet && pRet->initWithTarget(texFile, cornerX, cornerY, targetX, targetY))
    {
        pRet->autorelease();
 		return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCNode9Grid::initWithTarget(const char* texFile,
	float cornerX, float cornerY, float targetX, float targetY)
{
	bool ret = false;
	do{
		m_texFileName = texFile;
		this->m_texFile = CCTextureCache::sharedTextureCache()->addImage(texFile);
		CC_BREAK_IF(!this->m_texFile);

		float twide = m_texFile->getContentSize().width;
		float thigh = m_texFile->getContentSize().height;

		CC_BREAK_IF(twide <= cornerX*2);
		CC_BREAK_IF(thigh <= cornerY*2);

		this->m_x1 = cornerX;
		this->m_x2 = twide-cornerX;
		this->m_y1 = cornerY;
		this->m_y2 = thigh - cornerY;


		float xscale = (targetX-2*cornerX)/(twide-2*cornerX);
		float yscale = (targetY-2*cornerY)/(thigh-2*cornerY);

		do9Scale(xscale, yscale);
		ret = true;
	}while(0);
	return ret;
}


CCSprite* CCNode9Grid::createChildSprite(const CCRect& texRect, const CCPoint& posBottomLeft,
		float xscale, float yscale)
{
	CCSprite* pret = NULL;
	do{
		CCSpriteFrame* pframe = CCSpriteFrame::createWithTexture(m_texFile, texRect);
		CC_BREAK_IF(!pframe);
		CCSprite* psprite = CCSprite::createWithSpriteFrame(pframe);
		CC_BREAK_IF(!psprite);

		psprite->setAnchorPoint(ccp(0,0));

		if(xscale > 0)
		{
			psprite->setScaleX(xscale);
		}

		if(yscale > 0)
		{
			psprite->setScaleY(yscale);
		}

		CCMyHelper::setPosBL(psprite, posBottomLeft.x, posBottomLeft.y);

		pret = psprite;
	}while(0);

	return pret;
}


CCNode9GridFillTex::CCNode9GridFillTex(void)
{
}

CCNode9GridFillTex::~CCNode9GridFillTex(void)
{
}

CCNode9GridFillTex* CCNode9GridFillTex::create(const char* texFile, float x1, float x2, float xscale,
	float y1, float y2, float yscale)
{
	CCNode9GridFillTex *pRet = new CCNode9GridFillTex();
	if(pRet && pRet->initWithGrid(texFile, x1, x2, xscale, y1, y2, yscale))
    {
		pRet->do9Scale(xscale, yscale);
        pRet->autorelease();
 		return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCNode9GridFillTex::createChildren(float xscale, float yscale, float x1, float x2, float wd0, float wd1, float wd2,
		float y1, float y2, float ht0, float ht1, float ht2)
{
	bool ret = false;
	do{
		CCRect texRect;
		CCPoint posBL;

		//坐标上还有纠结下，是否会自动转，先当作会

		//四个角用sprite填充
		CCSprite* pret = NULL;
		CCSpriteFillTex* pt = NULL;

		//textrue坐标系与绘图坐标系y轴相反的
		//左上
		texRect.setRect(0,0, wd0, ht0);
		posBL.setPoint(0, y2);
		pret = createChildSprite(texRect, posBL);
		CC_BREAK_IF(!pret);
		this->addChild(pret);
		
		//左下
		texRect.setRect(0, m_y2, wd0, ht2);
		posBL.setPoint(0, 0);
		pret = createChildSprite(texRect, posBL);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//右上
		texRect.setRect(m_x2, 0, wd2,  ht0);
		posBL.setPoint(x2, y2);
		pret = createChildSprite(texRect, posBL);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//右下
		texRect.setRect(m_x2, m_y2, wd2, ht2);
		posBL.setPoint(x2, 0);
		pret = createChildSprite(texRect, posBL);
		CC_BREAK_IF(!pret);
		this->addChild(pret);

		//四个边和中间用spritefulltex填充
		//左边
		texRect.setRect(0, m_y1, wd0, ht1);
		posBL.setPoint(0, y1);
		pt = createChildSpriteFT(texRect, 1, yscale, posBL);
		CC_BREAK_IF(!pt);
		this->addChild(pt);
		
		//上边
		texRect.setRect(m_x1, 0, wd1, ht0);
		posBL.setPoint(x1, y2);
		pt = createChildSpriteFT(texRect, xscale, 1, posBL);
		CC_BREAK_IF(!pt);
		this->addChild(pt);

		//下边
		texRect.setRect(m_x1,m_y2, wd1, ht2);
		posBL.setPoint(x1, 0);
		pt = createChildSpriteFT(texRect, xscale, 1, posBL);
		CC_BREAK_IF(!pt);
		this->addChild(pt);

		//右边
		texRect.setRect(m_x2, m_y1, wd2, ht1);
		posBL.setPoint(x2, y1);
		pt = createChildSpriteFT(texRect, 1, yscale, posBL);
		CC_BREAK_IF(!pt);
		this->addChild(pt);

		//中间
		texRect.setRect(m_x1, m_y1, wd1, ht1);
		posBL.setPoint(x1, y1);
		pt = createChildSpriteFT(texRect, xscale, yscale, posBL);
		CC_BREAK_IF(!pt);
		this->addChild(pt);

		ret = true;
	}while(0);
	return ret;
}

CCSpriteFillTex* CCNode9GridFillTex::createChildSpriteFT(const CCRect& texRect, 
	float col, float row, const CCPoint& posBottomLeft)
{
	CCSpriteFillTex* pret = NULL;
	do
	{
		CCSpriteFillTex* psft = CCSpriteFillTex::create(m_texFileName.c_str(), row, col, texRect);
		CC_BREAK_IF(!psft);
		CCMyHelper::setPosBL(psft, posBottomLeft.x, posBottomLeft.y);
		pret = psft;
	}while(0);

	return pret;
}



CCNode9GridFillTex* CCNode9GridFillTex::createWithTargetSize(const char* texFile,
		float cornerX, float cornerY, float targetX, float targetY)
{
	CCNode9GridFillTex *pRet = new CCNode9GridFillTex();
	if(pRet && pRet->initWithTarget(texFile, cornerX, cornerY, targetX, targetY))
    {
        pRet->autorelease();
 		return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
