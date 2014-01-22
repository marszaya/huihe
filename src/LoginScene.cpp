#include "LoginScene.h"
#include "LoginWindow.h"
#include "MainLoadingScene.h"
#include "MyControl.h"
#include "MyData.h"

bool CLoginScene::showMainWindow()
{
	bool ret = false;
	do{
		CLoginWindow* plogin = CLoginWindow::create();
		CC_BREAK_IF(!plogin);
		this->addChild(plogin);

		CMyControl::getSharedControl()->registCmdHandle(CMyControl::CMD_LOGIN, this, 
			callfuncO_selector(CLoginScene::onLoginClose));

		ret = true;
	}while(0);
	return ret;
}

void CLoginScene::onLoginClose(CCObject* msg)
{
	CMyData::getSharedData(); //load data now
	CMyControl::getSharedControl()->unregistCmdHandle(CMyControl::CMD_LOGIN, this);
	this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
}

void CLoginScene::onFrameMsg(CCObject* msg)
{
	this->removeAllChildrenWithCleanup(true);
	CCLog("from CLoginScene to CMainLoadingScene");
	CCScene *pScene = CCESceneWindow::createScene(new CMainLoadingScene, "preload.plist");
	if(pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

