#include "CActionEffectAfterImage.h"

CCEActionEffectAfterImage::CCEActionEffectAfterImage(void)
{
	m_enableCreate = false;
	m_enableDel = false;
	m_dtAdd = 0;
	m_pbatchnode = NULL;
	m_createdNum = 0;
}

CCEActionEffectAfterImage::~CCEActionEffectAfterImage(void)
{
	this->unschedule(schedule_selector(CCEActionEffectAfterImage::afterImgSchedule));
}

CCEActionEffectAfterImage* CCEActionEffectAfterImage::create(
	const CCEActionEffectAfterImage::CAfterImageConfig& conf)
{
	CCEActionEffectAfterImage *pRet = new CCEActionEffectAfterImage();
	if(pRet && pRet->initCCEActionEffectAfterImage(conf ))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCEActionEffectAfterImage::initCCEActionEffectAfterImage(
	const CCEActionEffectAfterImage::CAfterImageConfig& conf)
{
	bool ret=false;
	do{
		m_conf = conf;
		m_enableCreate = false;
		m_enableDel = false;
		m_dtAdd = 0;
		m_createdNum = 0;

		m_pbatchnode = NULL;

		m_childAnchorPoint = ccp(0,0);

		ret = true;
	}while(0);

	return ret;
}

bool CCEActionEffectAfterImage::beginAfterImage()
{
	bool ret =false;
	do{
		if(m_enableCreate || m_enableDel)
			break;
		cleanAfterImg();
		m_enableCreate = true;
		this->schedule(schedule_selector(CCEActionEffectAfterImage::afterImgSchedule));
		ret = true;
	}while(0);

	return ret;
}

bool CCEActionEffectAfterImage::stopAfterImage()
{
	bool ret =false;
	do{
		if(m_enableCreate || m_enableDel)
			break;

		m_enableDel = true;
		this->schedule(schedule_selector(CCEActionEffectAfterImage::afterImgSchedule));
		ret = true;
	}while(0);

	return ret;
}


void CCEActionEffectAfterImage::afterImgSchedule(float dt)
{
	m_dtAdd += dt;
	if(m_dtAdd < m_conf.m_createDt)
	{
		//时间不足
		return;
	}

	//时间足够
	//帧的整数倍
	m_dtAdd = 0;

	int keepSchedule = false;
	do{
		if(m_enableCreate) //创建中
		{
			if(m_createdNum >= m_conf.m_num)
			{
				//创建完了
				m_enableCreate = false;
				break;
			}

			CCSprite* psp = createNewSprite();
			if(!psp)
			{
				//出错了
				m_enableCreate = false;
				break;
			}
		}
		else if(m_enableDel)
		{
			//删除
			if(m_createdNum <= 0)
			{
				m_enableDel = false;
				break;
			}
			m_pbatchnode->removeChildByTag(m_createdNum, true);
			--m_createdNum;
		}
		else
		{
			break;
		}

		keepSchedule = true;
	}while(0);

	if(!keepSchedule)
	{
		this->unschedule(schedule_selector(CCEActionEffectAfterImage::afterImgSchedule));
	}
}

void CCEActionEffectAfterImage::cleanAfterImg()
{
	//tag=1 是m_pbaseSprite
	for(unsigned int i=1; i<=m_createdNum; ++i)
	{
		this->removeChildByTag((int)i, true);
	}

	m_enableCreate = false;
	m_enableDel = false;
	m_createdNum = 0;
}

CCSprite* CCEActionEffectAfterImage::createNewSprite()
{
	CCSprite* ret=NULL;
	if(m_conf.m_srcType == 0)
	{
		ret = CCSprite::create(m_conf.m_srcName.c_str());
	}
	else
	{
		ret = CCSprite::createWithSpriteFrameName(m_conf.m_srcName.c_str());
	}

	if(ret == NULL)
		return NULL;

	ret->setAnchorPoint(this->m_childAnchorPoint);

	if(!lazyCreateBatchNode(ret))
		return NULL;

	++m_createdNum;

	//修改大小
	if(m_conf.m_lastScale != 1.0 || m_conf.m_firstScale != 1.0)
	{
		ret->setScale( m_conf.m_firstScale
			+ (m_conf.m_lastScale-m_conf.m_firstScale)/(m_conf.m_num-1)*(m_createdNum-1));
	}

	//修改透明度 
	if(m_conf.m_lastOpacity  != 255 || m_conf.m_firstOpacity != 255)
	{
		GLubyte op = m_conf.m_firstOpacity +
			(m_conf.m_lastOpacity - m_conf.m_firstOpacity)/(m_conf.m_num-1)*(m_createdNum-1);
		ret->setOpacity(op);
	}

	for(unsigned int i=0; i<m_actionArray.count(); ++i)
	{
		CCAction * pact = dynamic_cast<CCAction *>(m_actionArray.objectAtIndex(i));
		if(!pact)
			return NULL;
		CCAction* pnewact = dynamic_cast<CCAction *>(pact->copyWithZone(NULL));
		if(!pnewact)
			return NULL;
		ret->runAction(pnewact);
		pnewact->release();
	}

	m_pbatchnode->addChild(ret, 0, m_createdNum);

	return ret;
}

void CCEActionEffectAfterImage::addActionToImage(CCAction *paction)
{
	CCAction* pnewact = dynamic_cast<CCAction *>(paction->copyWithZone(NULL));
	if(!pnewact)
		return;
	m_actionArray.addObject(pnewact);
	pnewact->release();
}


bool CCEActionEffectAfterImage::lazyCreateBatchNode(CCSprite* sp)
{
	if(m_pbatchnode!=NULL)
		return true;

	m_pbatchnode = CCSpriteBatchNode::createWithTexture(
		sp->getTexture(), m_conf.m_num);

	if(!m_pbatchnode)
		return false;

	this->addChild(m_pbatchnode);

	return true;
}
