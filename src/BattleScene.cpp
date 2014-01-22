#include "BattleScene.h"
#include "MyControl.h"
#include "StrTool.h"
#include "StdViewFactory.h"
#include "BattleWindow.h"
#include "MyData.h"
#include "tconfManager.h"
#include <vector>
#include <string>
using namespace std;

bool CBattleScene::showMainWindow()
{
	bool ret = false;
	do{
		this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
		ret = true;
	}while(0);
	return ret;
}

void CBattleScene::onFrameMsg(CCObject* msg)
{
	do
	{
		CBattleWindow* pbwin = CBattleWindow::create(m_savebackgroundId);
		if(!pbwin)
			break;

		this->removeAllChildrenWithCleanup(true);
		this->addChild(pbwin);
	}while(0);
	//显示战斗场景
}

void CBattleScene::updateLable()
{
	int total = m_preloader->getFileTotal();
	int current = m_preloader->getLoadedFiles();
	int currentb = m_preloader->getLoadedTotalBytes();
	string curName = m_preloader->getCurFileName();
	m_tagLableFile = m_processView->updateLabel(m_tagLableFile, 
		string("load file ").append(curName).append(":").append(CStrTool::strDecimal(current)).append("/").append(CStrTool::strDecimal(total)).c_str(),
		CStdViewFactory::LABEL_FONT, 
		CCMyHelper::POS_INFO(
			50, 100,
			CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
	);

	m_tagLableBytes = m_processView->updateLabel(m_tagLableBytes, 
		string("Bytes: ").append(CStrTool::strDecimal(currentb)).c_str(),
		CStdViewFactory::LABEL_FONT, 
		CCMyHelper::POS_INFO(
			50,50,
			CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
	);

	m_processBar->setPercent((float(current)/total)*100);
}

bool CBattleScene::beforePreloadWindow()
{
	bool ret = false;
	do{
		if(!fillPreloader())
			break;

		m_tagLableFile = -1;
		m_tagLableBytes = -1;
		m_processView = CCWindowBase::create();
		CC_BREAK_IF(!m_processView);
		m_processBar = CBarBase::create("mainScene/greenBar.png");
		CC_BREAK_IF(!m_processBar);

		m_processBar->setPercent(0);
		m_processView->fullWindowSize();
		//m_processView->setWindowBG(CCMyHelper::createZeroAnchorSprite("loaderBack.jpg"));

		CCMyHelper::setPosC(m_processBar, m_processView->getWindowWidth()/2, 
			m_processView->getWindowHeight()/2);
		m_processView->addChild(m_processBar);
	
		this->addChild(m_processView);
		updateLable();

		this->m_preloadFileNumPerFrame = 5;

		ret = true;
	}while(0);
	return ret;
}

bool CBattleScene::onPreloadProcess()
{
	bool ret = false;
	do{
		updateLable();
		ret = true;
	}while(0);
	return ret;
}

bool CBattleScene::fillPreloader()
{
	bool ret = false;
	do{
		//预加载pve角色
		int battleId = CMyData::getSharedData()->getCurrentBattle();
		
		CAutoBattleTab* conf = TCONF_GET(CAutoBattleTab);
		if(!conf)
			break;

		const TconfRow* prow = conf->getRowByKey(CStrTool::strDecimal(battleId).c_str());
		if(prow==NULL)
			break;

		const char* units = conf->getRowValue(prow, conf->UNITS);
		if(units==NULL)
			break;

		vector<string> vout;
		CStrTool::split(units, ",", vout);

		bool npcError = false;
		for(unsigned int vi=0; vi<vout.size(); ++vi)
		{
			int unitid = atoi(vout[vi].c_str());
			if(unitid <= 0)
				continue;
			if(!fillPreloadUnit(unitid))
			{
				npcError = true;
				break;
			}
		}

		if(npcError)
			break;

		//预加载自己的
		bool selfError = false;
		RoleSet* prs = CMyData::getSharedData()->allRoles();
		for(int i=0; i<prs->battlelist_size(); ++i)
		{
			if(prs->battlelist(i).has_id())
			{
				string id = prs->battlelist(i).id();
				Role* p = CMyData::getSharedData()->getRoleById(id.c_str());
				if(!p)
					continue;

				if(!fillPreloadUnit(p->showtype()))
				{
					selfError = true;
					break;
				}
			}
		}

		if(selfError)
			break;

		//battle common
		m_savebackgroundId = atoi(conf->getRowValue(prow, conf->BACKGROUNDID));
		if(!fillPreloadBattle(m_savebackgroundId))
			break;

		//所有buff图标
		m_preloader->addPreLoadFrames("icons/buff.png");

		ret = true;
	}while(0);
	return ret;
}

bool CBattleScene::fillPreloadUnit(int unitid)
{
	bool ret = false;
	do{
		char texture[64] = {0};
		//形象
		sprintf(texture, "unit/u%d.png", unitid);
		m_preloader->addPreLoadFrames(texture);

		//技能特效..以后添加
		ret = true;
	}while(0);
	return ret;
}

bool CBattleScene::fillPreloadBattle(int backgroundId)
{
	bool ret = false;
	do{
		char texture[64] = {0};
		//背景
		sprintf(texture, "battle/battleback%d.jpg", backgroundId);
		m_preloader->addPreLoadPic(texture);

		//通用特效
		if(!fillPreloadEffect(1))
			break;
		if(!fillPreloadEffect(2))
			break;
		if(!fillPreloadEffect(3))
			break;

		ret = true;
	}while(0);
	return ret;
}

bool CBattleScene::fillPreloadEffect(int effectid)
{
	bool ret = false;
	do{
		char texture[64] = {0};
		//形象
		sprintf(texture, "effect/t%d.png", effectid);
		m_preloader->addPreLoadFrames(texture);

		ret = true;
	}while(0);
	return ret;
}
