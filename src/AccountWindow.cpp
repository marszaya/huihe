#include "AccountWindow.h"
#include "MyData.h"
#include "MyControl.h"
#include "StdViewFactory.h"

CAccountWindow::CAccountWindow(void)
{
	m_tagGold=-1;
	m_tagMoney=-1;
	m_tagExpr=-1;
	m_tagVip=-1;
	m_tagLevel = -1;
	m_tagName = -1;
	m_expbar = NULL;
	this->initPostMsg(CMyControl::getSharedControl()->getDispatcher());
	this->addPostMsg(CMyControl::CMD_DATA_ACCOUNT_MODIFIED);
}

CAccountWindow::~CAccountWindow(void)
{
}

CAccountWindow* CAccountWindow::create()
{
	CAccountWindow *pRet = new CAccountWindow();
	if(pRet && pRet->initCAccountWindow())
    {
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CAccountWindow::initCAccountWindow()
{
	bool ret=0;
	do{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		CCSprite* phead = CCMyHelper::createZeroAnchorSprite("mainScene/head.png");
		if(!phead)
			break;
		CCMyHelper::setPosC(phead, 38, 92-38);
		this->addChild(phead,-2);

		CCSprite* backGround = CCMyHelper::createZeroAnchorSprite("mainScene/account.png");
		if(!backGround)
			break;
		this->setWindowBG(backGround);
		this->windowSizeFitBG();

		CCSprite* bGold = CCMyHelper::createZeroAnchorFrameSprite("qianbi.png");
		if(!bGold)
			break;
		CCMyHelper::setPosC(bGold, 86, 92-41);
		this->addChild(bGold);

		CCSprite* bMoney = CCMyHelper::createZeroAnchorFrameSprite("yuanbao.png");
		if(!bMoney)
			break;
		CCMyHelper::setPosC(bMoney, 86+88, 92-41);
		this->addChild(bMoney);

		m_expbar = CBarBase::create("mainScene/greenBar.png");
		if(!m_expbar)
			break;
		CCMyHelper::setPosBL(m_expbar, 73, 92-85);
		this->addChild(m_expbar);

		this->updateCAccountWindow();
		ret = true;
	}while(0);

	return ret;
}

void CAccountWindow::updateCAccountWindow()
{
	const Account& acc = CMyData::getSharedData()->user().account();

	char buff[256]={0};
	CCMyHelper::FONT_INFO tmpFont = CStdViewFactory::LABEL_FONT;
	tmpFont.size = 12;

	//gold
	sprintf(buff, "%lld", acc.gold());
	m_tagGold = this->updateLabel(m_tagGold, buff, 
		tmpFont, 
		CCMyHelper::POS_INFO(
			95, 92-47,
			CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
	);

	//money
	sprintf(buff, "%lld", acc.money());
	m_tagMoney = this->updateLabel(m_tagMoney, buff, 
		tmpFont, 
		CCMyHelper::POS_INFO(
			95+88, 92-47,
			CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
	);

	//level
	sprintf(buff, "%d", acc.expr().level());
	m_tagLevel = this->updateLabel(m_tagLevel, buff,tmpFont,
		CCMyHelper::POS_INFO(70, 92-12, CCMyHelper::POSITION_TYPE_CENTER)
	);
	
	//expr
	long long lvExpr;
	long long lvExprMax;
	if(!CMyData::getSharedData()->getLevelExpr(lvExpr, lvExprMax))
	{
		return;
	}

	float percent = ((float)lvExpr/lvExprMax)*100;
	m_expbar->setPercent(percent);
	//m_expbar->setPercent(100);

	sprintf(buff, "%lld/%lld", lvExpr, lvExprMax);
	m_tagExpr = this->updateLabel(m_tagExpr, buff, 
		tmpFont, 
		CCMyHelper::POS_INFO(
			160, 92-77,
			CCMyHelper::POSITION_TYPE_CENTER)
	);

	//name
	m_tagName = this->updateLabel(m_tagName, 
		CMyData::getSharedData()->user().id().name().c_str(), 
		tmpFont, 
		CCMyHelper::POS_INFO(
			95, 92-25,
			CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
	);

	/*
	sprintf(buff, "vip: %d / %lld", acc.vip().level(), acc.vip().expr());
	m_tagVip = this->updateLabel(m_tagVip, buff, 
		CStdViewFactory::LABEL_FONT, 
		CCMyHelper::POS_INFO(
			150, 10,
			CCMyHelper::POSITION_TYPE_CENTER)
	);*/
}

void CAccountWindow::onFrameMsg(CCObject* msg)
{
	updateCAccountWindow();
}