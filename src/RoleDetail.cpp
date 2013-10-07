#include "RoleDetail.h"
#include "MyData.h"
#include "StdViewFactory.h"
#include "RoleUnit.h"
#include "AttrLabel.h"
#include "MyControl.h"

CRoleDetail::CRoleDetail(void)
{
	m_roleIdx = 0;
	m_labelWin = NULL;
	m_pic = NULL;
	this->initPostMsg(CMyControl::getSharedControl()->getDispatcher());
	this->addPostMsg(CMyControl::CMD_DATA_ROLE_ATTR_MODIFIED);
}

CRoleDetail::~CRoleDetail(void)
{	
}

CRoleDetail* CRoleDetail::create(int roleIdx)
{
	CRoleDetail *pRet = new CRoleDetail();
	if(pRet && pRet->initCRoleDetail(roleIdx))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CRoleDetail::initCRoleDetail(int roleIdx)
{
	bool ret=false;
	do{
		m_roleIdx = roleIdx;
		Role* prole = CMyData::getSharedData()->getRoleByIdx(roleIdx);
		if(!prole)
			break;

		m_pic = CRoleUnit::createPic(prole->showtype());
		if(!m_pic)
			break;

		int windowHeight = m_pic->getContentSize().height+GAP*2;
		int windowWidth = m_pic->getContentSize().width+GAP*5+LABEL_WDITH*3;

		CCNode* bg = CStdViewFactory::createSmallBg(windowWidth,windowHeight);
		if(!bg)
			break;
		this->setWindowBG(bg);
		this->windowSizeFitBG();

		CCMyHelper::setPosBL(m_pic, GAP, GAP);
		this->addChild(m_pic);

		ret = updateRoleDetail();
	}while(0);

	return ret;
}

bool CRoleDetail::updateRoleDetail()
{
	bool ret = false;
	do{
		if(!m_pic)
			break;

		Role* prole = CMyData::getSharedData()->getRoleByIdx(m_roleIdx);
		if(!prole)
			break;


		if(m_labelWin != NULL)
			this->removeChild(m_labelWin, true);

		m_labelWin = CCWindowBase::create();
		if(!m_labelWin)
			break;
		CCMyHelper::setPosBL(m_labelWin, m_pic->getContentSize().width+GAP*2, 0);
		this->addChild(m_labelWin);

		int labelStartX = 0;
		int labelDeltaX = LABEL_WDITH+GAP;
		int labelDeltaY = LABEL_HEIGHT+GAP;
		int labelStartY = (this->getWindowHeight() - labelDeltaY*3-GAP*2)/2;

		CCMyHelper::FONT_INFO fontInfo = CStdViewFactory::LABEL_FONT;
		char strBuff[64] = {0};
		
		//name
		CAttrLabel* namelabel = CAttrLabel::createNameLabel(prole->id().name().c_str());
		if(!namelabel)
			break;
		CCMyHelper::setPosBL(namelabel, labelStartX, labelStartY+labelDeltaY*2);
		m_labelWin->addChild(namelabel);

		//level
		CAttrLabel* lvlabel = CAttrLabel::createLevelLabel(prole->expr().level());
		if(!lvlabel)
			break;
		CCMyHelper::setPosBL(lvlabel, labelStartX+labelDeltaX, labelStartY+labelDeltaY*2);
		m_labelWin->addChild(lvlabel);

		//expr
		CAttrLabel* exprlabel = CAttrLabel::createExpLabel(prole->expr().expr());
		if(!exprlabel)
			break;
		CCMyHelper::setPosBL(exprlabel, labelStartX+labelDeltaX*2, labelStartY+labelDeltaY*2);
		m_labelWin->addChild(exprlabel);

		//hp
		CAttrLabel* hplabel = CAttrLabel::createHpLabel(prole->battr().hp());
		if(!hplabel)
			break;
		CCMyHelper::setPosBL(hplabel, labelStartX, labelStartY+labelDeltaY);
		m_labelWin->addChild(hplabel);

		//def
		CAttrLabel* deflabel = CAttrLabel::createDefLabel(prole->battr().arm());
		if(!deflabel)
			break;
		CCMyHelper::setPosBL(deflabel, labelStartX+labelDeltaX, labelStartY+labelDeltaY);
		m_labelWin->addChild(deflabel);

		//atk
		CAttrLabel* atklabel = CAttrLabel::createAtkLabel(prole->battr().ad());
		if(!atklabel)
			break;
		CCMyHelper::setPosBL(atklabel, labelStartX, labelStartY);
		m_labelWin->addChild(atklabel);

		//speed
		CAttrLabel* speedlabel = CAttrLabel::createSpdLabel(prole->battr().as());
		if(!speedlabel)
			break;
		CCMyHelper::setPosBL(speedlabel, labelStartX+labelDeltaX, labelStartY);
		m_labelWin->addChild(speedlabel);

		ret = true;
	}while(0);
	return ret;
}

void CRoleDetail::onFrameMsg(CCObject* msg)
{
	if(m_roleIdx >= CMyData::getSharedData()->allRoles()->roles_size())
	{
		m_roleIdx = 0;
	}
	updateRoleDetail();
}
