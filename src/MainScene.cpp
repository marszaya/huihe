#include "MainScene.h"

#include "FightUnit.h"
#include "AccountWindow.h"
#include "CWindowBase.h"
#include "BagWindow.h"
#include "LoginWindow.h"
#include "BattleWindow.h"
#include "RoleWindow.h"
#include "MyControl.h"
#include "CBtnBase.h"
#include "StdViewFactory.h"
#include "ShopWindow.h"
#include "RoleHire.h"
#include "RoleBattleList.h"
#include "StrTool.h"
#include "MyData.h"
#include "BattleMapScene.h"

bool CMainScene::showMainWindow()
{
	bool ret = false;
	do{

		m_nextSceneFlag = 0;

		//debug下
		CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();

		//确保已经load了
		CCMyHelper::loadFrames("icons/icons.png", "icons/icons.plist");
		CCMyHelper::loadFrames("icons/mainMenu.png", "icons/mainMenu.plist");

 		CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCSprite* pSprite = CCMyHelper::createZeroAnchorSprite("MainScene/background.jpg");
		CC_BREAK_IF(! pSprite);

		// Add the sprite to CMainScene layer as a child layer.
		this->addChild(pSprite, 0);

		//buttons
		setBtn(BTN_TAG_BTN_ROLE_HIRE, "juxian.png", 
			NULL, ccp(510,80));
		setBtn(BTN_TAG_BTN_SHOP, "shangcheng.png",
			NULL, ccp(590,80));
		setBtn(BTN_TAG_BTN_ROLE, "wujiang.png", 
			NULL, ccp(670,80));
		setBtn(BTN_TAG_BTN_BAG, "beibao.png", 
			NULL, ccp(750,80));
		setBtn(BTN_TAG_BTN_BATTLE, "xiulian.png", 
			NULL, ccp(830,80));
		setBtn(BTN_TAG_BTN_ROLE_BATTLE_LIST, "zhenxing.png",
			NULL, ccp(430,80));

		CAccountWindow* paw = CAccountWindow::create();
		CC_BREAK_IF(! paw);
		CCMyHelper::setPosTL(paw, 0, size.height);
		this->addChild(paw, 0, CHILD_LAYER_ACCOUNT);

		//POPUP window close callback
		CMyControl::getSharedControl()->registCmdHandle(CMyControl::CMD_MAINSCENE_POPUPCLOSE, this, 
			callfuncO_selector(CMainScene::onPopupClose));
		ret = true;
	}while(0);
	return ret;
		//test code
		/* 	
		CFightUnit* punit = CFightUnit::create(1);
		punit->stay();
		punit->setPosition(ccp(100,100));
		this->addChild(punit);

		CCLayoutTable* ptable = CCLayoutTable::create(120, 150);
		CC_BREAK_IF(! ptable);
		pSprite  = CCSprite::create("mainScene/head1.jpg");
		CC_BREAK_IF(! pSprite);
		ptable->addItem(pSprite, 0, 0);
		pSprite  = CCSprite::create("mainScene/head2.jpg");
		CC_BREAK_IF(! pSprite);
		ptable->addItem(pSprite, 1, 1);
		ptable->setPosition(ccp(100,100));
		this->addChild(ptable, 10);
	
		//test  CCSpriteFillTex
		CCSpriteFillTex* psft = CCSpriteFillTex::create("mainScene/head1.jpg", 90, 90, 4,3,0);
		CC_BREAK_IF(! psft);
		psft->setPosition(ccp(100,100));
		this->addChild(psft);

		//test sprite scale
		pSprite  = CCSprite::create("mainScene/btn1.png");
		CC_BREAK_IF(! pSprite);

		pSprite->setPosition(ccp(size.width/2, size.height/2));

		pSprite->setScale(2.0);
		 this->addChild(pSprite);

		//test label atlas
		CCLabelAtlas* pdmglabel = CCLabelAtlas::create("1", "number.png", 16, 23, '.');
		//CCLabelTTF* pdmglabel = CCLabelTTF::create("1", "Arial", 24);
		pdmglabel->setPosition(ccp(size.width/2, size.height/2));
		//pdmglabel->setOpacity(255);
		//pdmglabel->setColor(ccc3(255,0,0));
		this->addChild(pdmglabel);*/
}

void CMainScene::onPopupClose(CCObject* msg)
{
	CCNode* childToClose = dynamic_cast<CCNode*>(msg);
	if(childToClose)
	{
		this->removeChildOnNextFrame(childToClose);
	}
	enableBtns();
}

void CMainScene::onBtn(CCObject* target)
{
	DYNAMIC_CAST_CCASERT(target, CCNode, pnode);
	int tag = pnode->getTag();
 	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(tag == BTN_TAG_BTN_ROLE) //武将页
	{
		if(getChildByTag(CHILD_POPUP_ROLE) == NULL)
		{
			disableBtns();
			CRoleWindow* prole = CRoleWindow::create();
			this->addChild(prole, 1, CHILD_POPUP_ROLE);
			CCMyHelper::setPosC(prole, size.width/2, size.height/2);
		}
	}
	else if(tag == BTN_TAG_BTN_BAG) //背包页
	{
		if(getChildByTag(CHILD_POPUP_BAG) == NULL)
		{
			disableBtns();
			CBagWindow* pbag = CBagWindow::create(3,3);
			this->addChild(pbag, 1, CHILD_POPUP_BAG);
			CCMyHelper::setPosC(pbag, size.width/2, size.height/2);
		}
	}
	else if(tag == BTN_TAG_BTN_BATTLE) //战斗页
	{
		if(getChildByTag(CHILD_POPUP_BATTLE) == NULL)
		{
			//需要切换scene
			m_nextSceneFlag = 1;
			this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
		}
	}
	else if(tag == BTN_TAG_BTN_SHOP)
	{
		if(getChildByTag(CHILD_POPUP_SHOP) == NULL)
		{
			disableBtns();
			CShopWindow* pshop = CShopWindow::create();
			this->addChild(pshop, 1, CHILD_POPUP_SHOP);
			CCMyHelper::setPosC(pshop, size.width/2, size.height/2);
		}
	}
	else if(tag == BTN_TAG_BTN_ROLE_HIRE)
	{
		if(getChildByTag(CHILD_POPUP_ROLE_HIRE) == NULL)
		{
			disableBtns();
			CRoleHire* proleh = CRoleHire::create();
			this->addChild(proleh, 1, CHILD_POPUP_ROLE_HIRE);
			CCMyHelper::setPosC(proleh, size.width/2, size.height/2);
		}
	}
	else if(tag == BTN_TAG_BTN_ROLE_BATTLE_LIST)
	{
		if(getChildByTag(CHILD_POPUP_ROLE_BATTLE_LIST) == NULL)
		{
			disableBtns();
			CRoleBattleList* proleb = CRoleBattleList::create();
			this->addChild(proleb, 1, CHILD_POPUP_ROLE_BATTLE_LIST);
			CCMyHelper::setPosC(proleb, size.width/2, size.height/2);
		}
	}

	else
	{
		CCMessageBox("unkown btn clicked", "Debug");
	}
}

bool CMainScene::setBtn(int tag, const char* img, const char* img2, const CCPoint & initPos, CCMyHelper::POSITION_TYPE postype)
{
	bool ret = false;
	do{
		CCSprite* psbg = CCMyHelper::createZeroAnchorFrameSprite("beijing.png");
		if(psbg)
		{
			CCMyHelper::setPosC(psbg, initPos.x, initPos.y);
			addChild(psbg);
		}

		CCMenu* pmenu;
		pmenu = CCMyHelper::createFrameButton(
			img,
			this, 
			menu_selector(CMainScene::onBtn),
			tag,
			img2,
			NULL,
			initPos.x,
			initPos.y,
			postype
		);

		CC_BREAK_IF(!pmenu);	
		addChild(pmenu, 1, tag);

		m_allBtns.push_back(tag);
		ret = true;
	}while(0);

	return ret;
}

void CMainScene::disableBtn(int tag)
{
	do{
		CCNode* node = this->getChildByTag(tag);
		CC_BREAK_IF(!node);
		DYNAMIC_CAST_CCASERT(node, CCMenu, pbtn);
		pbtn->setEnabled(false);
	}while(0);
}

void CMainScene::enableBtn(int tag)
{
	do{
		CCNode* node = this->getChildByTag(tag);
		CC_BREAK_IF(!node);
		DYNAMIC_CAST_CCASERT(node, CCMenu, pbtn);
		pbtn->setEnabled(true);
	}while(0);
}

void CMainScene::onFrameMsg(CCObject* msg)
{
	if(m_nextSceneFlag == 1)
	{
		//初始地图
		if(CMyData::getSharedData()->getCurrentMap() == 0)
		{
			CMyData::getSharedData()->setCurrentMap(1);
		}

		this->removeAllChildrenWithCleanup(true);
		CCLog("from CMainScene to CBattleMapScene");
		CCScene *pScene = CCESceneWindow::createScene(new CBattleMapScene);
		if(pScene)
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}
}