#include "RoleUnit.h"
#include "StdViewFactory.h"
#include "StrTool.h"
#include "AttrLabel.h"

CRoleUnit::CRoleUnit(void)
{
	m_conf=NULL;
	m_pic = NULL;
}

CRoleUnit::~CRoleUnit(void)
{
}

CRoleUnit* CRoleUnit::create(const Role* prole)
{
	CRoleUnit *pRet = new CRoleUnit();
	if(pRet && pRet->initCRoleUnit(prole))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CRoleUnit::initCRoleUnit(const Role* prole)
{
	bool ret=0;
	do{
		CCNode* bg = CStdViewFactory::createSmallBg(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		if(!bg)
			break;
		this->setWindowBG(bg);
		this->windowSizeFitBG();

		if(prole)
		{
			updateCRoleUnit(prole);
		}

		ret = true;
	}while(0);

	return ret;
}

CCSprite* CRoleUnit::createPic(int picid)
{
	CCSprite* ret = NULL;
	do{
		char buff[32] = {0};
		sprintf(buff, "role/rhead%d.jpg", picid);
		CCSprite* sp = CCMyHelper::createZeroAnchorSprite(buff);
		CC_BREAK_IF(!sp);

		ret = sp;
	}while(0);

	return ret;
}

void CRoleUnit::updateCRoleUnit(const Role* prole)
{
	int hstart = 5;
	m_roleID = prole->id().id();

	if(m_pic)
	{
		this->removeChild(m_pic, true);
	}

	m_pic = createPic(prole->showtype());
	if(!m_pic)
		return;

	CCMyHelper::setPosC(m_pic, DEFAULT_HEIGHT/2, DEFAULT_HEIGHT/2);
	this->addChild(m_pic);

	//name
	CAttrLabel* namelabel = CAttrLabel::createShortNameLabel(prole->id().name().c_str());
	if(!namelabel)
		return;
	CCMyHelper::setPosBL(namelabel, DEFAULT_WIDTH/2+10,  int(DEFAULT_HEIGHT/3*2)+hstart);
	this->addChild(namelabel);

	//level
	CAttrLabel* lvlabel = CAttrLabel::createShortLevelLabel(prole->expr().level());
	if(!lvlabel)
		return;
	CCMyHelper::setPosBL(lvlabel, DEFAULT_WIDTH/2+10,  int(DEFAULT_HEIGHT/3)+hstart);
	this->addChild(lvlabel);

	m_conf=NULL;
}



