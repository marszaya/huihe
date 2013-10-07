#include "PveMap.h"
#include "tconfManager.h"
#include "StrTool.h"
#include "MyData.h"
#include "MyControl.h"
#include "BattleScene.h"
#include "StdViewFactory.h"
#include "MainScene.h"
#include <vector>
#include <string>
using namespace std;

CPveMap::CPveMap(void)
{
	m_mapId = -1;
}

CPveMap::~CPveMap(void)
{
}

CPveMap* CPveMap::create(int mapId)
{
	CPveMap *pRet = new CPveMap();
	if(pRet && pRet->initCPveMap(mapId))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CPveMap::initCPveMap(int mapId)
{
	bool ret=false;
	do{
		m_sceneFlag = 0;
		m_mapId = mapId;

		CAutoMapTab* mapConf = TCONF_GET(CAutoMapTab);
		if(!mapConf)
			break;

		const char* back = mapConf->getValue(CStrTool::strDecimal(mapId).c_str(), 
			mapConf->BACKGROUNDID);
		if(back == NULL)
			break;

		char textrue[64] = {0};
		sprintf(textrue, "battle/battlemap%d.jpg", atoi(back));
		this->fullWindowSize();
		this->setWindowBG(CCMyHelper::createZeroAnchorSprite(textrue), true);

		this->setCloseBtn(CStdViewFactory::createCloseBtn(this, menu_selector(CPveMap::onClose)));

		const char* battles = mapConf->getValue(CStrTool::strDecimal(mapId).c_str(),
			mapConf->BATTLES);
		if(battles == NULL)
			break;

		vector<string> vout;
		CStrTool::split(battles, ",", vout);
		for(unsigned int i=0; i<vout.size(); ++i)
		{
			int battleid = atoi(vout[i].c_str());
			CCMenu* pmenu = CCMyHelper::createFrameButton("judian.png", this,
				menu_selector(CPveMap::onBattleSelected), battleid, NULL, NULL, 100+100*i, 200);
			if(!pmenu)
				break;

			this->addChild(pmenu);
		}

		ret = true;
	}while(0);

	return ret;
}

void CPveMap::onBattleSelected(CCObject* obj)
{
	do{
		CCNode* pnode = dynamic_cast<CCNode*>(obj);
		if(!pnode)
			break;

		int battleId = pnode->getTag();

		CMyData::getSharedData()->setCurrentBattle(battleId);
		m_sceneFlag = 1;
		this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
	}while(0);
}

void CPveMap::onFrameMsg(CCObject* msg)
{
	do{

		this->removeAllChildrenWithCleanup(true);
		CCScene *pScene = NULL;
		if(m_sceneFlag == 1)
		{
			CCLog("from CBattleMapScene.pveMap to CBattleScene");
			pScene = CCESceneWindow::createScene(new CBattleScene, "");
		}
		else if(m_sceneFlag == 2)
		{
			CCLog("from CBattleMapScene.pveMap to CMainScene");
			pScene = CCESceneWindow::createScene(new CMainScene);
		}
		else
		{
			break;
		}

		if(pScene)
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}while(0);
}

void CPveMap::onClose(CCObject* obj)
{
	m_sceneFlag = 2;
	this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
}
