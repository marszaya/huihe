#include "BattleWindow.h"
#include "StdViewFactory.h"
#include "BattleResult.h"
#include "StrTool.h"
#include "logToFile.h"
#include "CCalculagraph.h"
#include <sstream>
#include "BattleResult.h"
#include "BattleMapScene.h"
#include "BattleFormatConf.h"

CBattleSpeed::CBattleSpeed(void)
{
	m_speed = 1;
	m_speedMin = 1;
	m_speedMax = 3;
}

CBattleSpeed::~CBattleSpeed(void)
{
}

CBattleSpeed* CBattleSpeed::create()
{
	CBattleSpeed *pRet = new CBattleSpeed();
	if(pRet && pRet->initCBattleSpeed())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleSpeed::initCBattleSpeed()
{
	bool ret=false;
	do{
		m_speed = 2;

		this->setWindowSize(SWIDTH, SHEIGHT);
		this->setColorBG(ccBLACK, 128);

		CCMenu* tmp = CCMyHelper::createFrameButton(
			"add.png", this, menu_selector(CBattleSpeed::onPlus), 1,
			NULL, NULL,  20, SHEIGHT/2);
		if(!tmp)
			break;

		this->addChild(tmp);

		tmp = CCMyHelper::createFrameButton(
			"sub.png", this, menu_selector(CBattleSpeed::onMinus), 1,
			NULL, NULL,  SWIDTH-20, SHEIGHT/2);
		if(!tmp)
			break;
		this->addChild(tmp);

		m_tag = this->updateLabel(m_tag, CStrTool::strDecimal(m_speed).c_str(), 
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(SWIDTH/2, SHEIGHT/2,CCMyHelper::POSITION_TYPE_CENTER)
		);

		ret = true;
	}while(0);

	return ret;
}

	void CBattleSpeed::onMinus(CCObject* obj)
	{
		--m_speed;
		if(m_speed < m_speedMin)
		{
			m_speed = m_speedMin;
		}

		m_tag = this->updateLabel(m_tag, CStrTool::strDecimal(m_speed).c_str(), 
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(SWIDTH/2, SHEIGHT/2,CCMyHelper::POSITION_TYPE_CENTER)
		);

	}

	void CBattleSpeed::onPlus(CCObject* obj)
	{
		++m_speed;
		if(m_speed > m_speedMax)
		{
			m_speed = m_speedMax;
		}
		m_tag = this->updateLabel(m_tag, CStrTool::strDecimal(m_speed).c_str(), 
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(SWIDTH/2, SHEIGHT/2,CCMyHelper::POSITION_TYPE_CENTER)
		);

	}

CBattleWindow::CBattleWindow(void)
{
	m_map = NULL;
	m_nextFlag = 0;
	m_pbtnNext = NULL;
	m_pbtnAuto = NULL;
	m_autoFlag = 0;
	m_spd = NULL;
}

CBattleWindow::~CBattleWindow(void)
{
	CMyControl::getSharedControl()->unregistCmdHandle(CMyControl::CMD_BATTLE_RESULT_CLOSE, this);
}

CBattleWindow* CBattleWindow::create(int backgroundId)
{
	CBattleWindow *pRet = new CBattleWindow();
	if(pRet && pRet->initCBattleWindow(backgroundId))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleWindow::initCBattleWindow(int backgroundId)
{
	CCUCalculagraph* pcal = CCUCalculagraph::create();
	ostringstream debugCache;
	bool ret=false;
	do{
		this->fullWindowSize();
		char sbackName[64] = {0};
		sprintf(sbackName, "battle/battleback%d.jpg", backgroundId);
		CCSprite* pbg = CCMyHelper::createZeroAnchorSprite(sbackName);
		CC_BREAK_IF(!pbg);
		this->setWindowBG(pbg);
		debugCache << "BG=" << pcal->getDtStr() << "|";

		m_map = CBattleWindowMap::create(CBattleFormatConf::getSharedInstance()->getYMax(),
			CBattleFormatConf::getSharedInstance()->getXMax()*2+2, 90, 150);
		CC_BREAK_IF(!m_map);
		CCMyHelper::setPosC(m_map, this->m_width/2, this->m_height/2);
		this->addChild(m_map);
		debugCache << "MAP=" << pcal->getDtStr() << "|";

		m_logic.initBattle();
		debugCache << "LOGIC=" << pcal->getDtStr() << "|";

		CC_BREAK_IF(m_map->initTeamFromMsg(m_logic.getMsg())!=0);

		this->setCloseBtn(CStdViewFactory::createCloseBtn(this, menu_selector(CBattleWindow::onClose)));

		m_pbtnNext = CCMyHelper::createImgButton(
			"battle/nextNor.png", this, menu_selector(CBattleWindow::onNext), 1,
			NULL, "battle/nextDis.png",  50, 500);
		CC_BREAK_IF(!m_pbtnNext);
		this->addChild(m_pbtnNext);

		m_pbtnAuto = CCMyHelper::createImgButton(
			"battle/auto.png", this, menu_selector(CBattleWindow::onAuto), 1,
			NULL, NULL,  50, 450);
		CC_BREAK_IF(!m_pbtnAuto);
		this->addChild(m_pbtnAuto);

		m_spd = CBattleSpeed::create();
		CC_BREAK_IF(!m_spd);
		CCMyHelper::setPosBL(m_spd, 15, 530);
		this->addChild(m_spd);

		m_map->bindSpd(m_spd);

		CMyControl::getSharedControl()->registCmdHandle(
			CMyControl::CMD_BATTLE_RESULT_CLOSE,
			this, callfuncO_selector(CBattleWindow::onClose));		

		debugCache << "DONE=" << pcal->getDtStr();

		this->m_map->debugString(debugCache.str().c_str());

		//注册update
		this->scheduleUpdate();

		ret = true;
	}while(0);

	return ret;
}

void CBattleWindow::onClose(CCObject* obj)
{
	this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
}

void CBattleWindow::onNext(CCObject* obj)
{
	if(m_nextFlag == 0)
	{
		//m_map->debugString("doNextRound");
		m_nextFlag = 1;
		this->disableNext();
		m_logic.doGameStep();
	}
}

void CBattleWindow::onAuto(CCObject* obj)
{
	if(m_autoFlag==0)
	{
		//start auto
		m_autoFlag = 1;
		onNext(NULL);
	}
	else
	{
		//stop auto
		m_autoFlag = 0;
		this->checkNextEnable();
	}
}

void CBattleWindow::disableAllMenu()
{
	if(m_pbtnNext)
	{
		m_pbtnAuto->setEnabled(false);
	}

	if(m_pbtnAuto)
	{
		m_pbtnAuto->setEnabled(false);
	}
}

void CBattleWindow::checkNextEnable()
{
	if(m_nextFlag==0 && m_autoFlag == 0 && m_pbtnNext)
	{
		DYNAMIC_CAST_CCASERT(m_pbtnNext->getChildByTag(1), CCMenuItem, p);
		p->setEnabled(true);
	}
}

void CBattleWindow::disableNext()
{
	if(m_pbtnNext)
	{
		DYNAMIC_CAST_CCASERT(m_pbtnNext->getChildByTag(1), CCMenuItem, p);
		p->setEnabled(false);
	}
}

void CBattleWindow::showResult()
{
	CBattleResult* presult = CBattleResult::create();
	if(!presult)
		return;

	CBattleResultParam param;
	m_logic.getReward(&param);

	presult->showResult(param);
	CCMyHelper::setPosScreenCenter(presult);
	this->addChild(presult);
}


void CBattleWindow::onFrameMsg(CCObject* msg)
{
	int cmd = this->getCmdFromPostMsg(msg);
	if(cmd == CMyControl::CMD_WINDOW_SELF_LOOP)
	{
		//加载mapscene
		this->removeAllChildrenWithCleanup(true);
		CCLog("from CBattleScene.battleWindow to CBattleMapScene");
		CCScene *pScene = CCESceneWindow::createScene(new CBattleMapScene);
		if(pScene)
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}
}

void CBattleWindow::update(float dt)
{
	if(!m_map->isPlaying())
	{
		//可以继续播放了
		CBattleFightMsg& msg = this->m_logic.getMsg();
		if(!m_map->playFromMsg(msg))
		{
			//没什么可以播放的了
			if(this->m_logic.isEnd()) //已经结束
			{
				this->disableAllMenu();
				this->showResult();
				return;
			}

			m_nextFlag = 0;
			checkNextEnable();

			if(m_autoFlag != 0)//自动点击
			{			
				onNext(NULL);
			}
		}
	}
}

