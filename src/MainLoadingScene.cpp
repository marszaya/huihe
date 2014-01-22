#include "MainLoadingScene.h"
#include "LoginWindow.h"
#include "MainScene.h"
#include "MyControl.h"
#include "CTextureHolder.h"
#include "StrTool.h"
#include "StdViewFactory.h"

bool CMainLoadingScene::showMainWindow()
{
	bool ret = false;
	do{
		this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
		ret = true;
	}while(0);
	return ret;
}

void CMainLoadingScene::onFrameMsg(CCObject* msg)
{
	this->removeAllChildrenWithCleanup(true);
	CCLog("from CMainLoadingScene to CMainScene");
	CCScene *pScene = CCESceneWindow::createScene(new CMainScene);
	if(pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void CMainLoadingScene::updateLable()
{
	int total = m_preloader->getFileTotal();
	int current = m_preloader->getLoadedFiles();
	int totalb = m_preloader->getCachedTotalBytes();
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
		string("Bytes: ").append(CStrTool::strDecimal(currentb)).append("/").append(CStrTool::strDecimal(totalb)).c_str(),
		CStdViewFactory::LABEL_FONT, 
		CCMyHelper::POS_INFO(
			50,50,
			CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
	);
}

bool CMainLoadingScene::beforePreloadWindow()
{
	bool ret = false;
	do{
		m_tagLableFile = -1;
		m_tagLableBytes = -1;
		m_processView = CCWindowBase::create();
		CC_BREAK_IF(!m_processView);
		m_processView->fullWindowSize();
		m_processView->setWindowBG(CCMyHelper::createZeroAnchorSprite("loaderBack.jpg"));
		this->addChild(m_processView);
		updateLable();

		this->m_preloadFileNumPerFrame = 5;
		ret = true;
	}while(0);
	return ret;
}

bool CMainLoadingScene::onPreloadProcess()
{
	bool ret = false;
	do{
		string curName = m_preloader->getCurFileName();
		//main loading的资源不释放
		CCUTextureHolder::getSharedInstance()->retainTexture(curName.c_str());
		CCUTextureHolder::getSharedInstance()->retainFrames(m_preloader->currentFrames());
		updateLable();
		ret = true;
	}while(0);
	return ret;
}