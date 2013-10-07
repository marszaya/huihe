#include "LoginWindow.h"
#include "CCoverLayer.h"
#include "CNode9Grid.h"
#include "StdViewFactory.h"
#include "CTextFieldWindow.h"
#include "MyControl.h"
#include "MyData.h"
#include "STRTABLE.h"
#include "CMyHelper.h"

CLoginWindow::CLoginWindow(void)
{
}

CLoginWindow::~CLoginWindow(void)
{
}

CLoginWindow* CLoginWindow::create()
{
	CLoginWindow *pRet = new CLoginWindow();
	if(pRet && pRet->initCLoginWindow())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CLoginWindow::initCLoginWindow()
{
	bool ret=0;
	do{
 		CCSize size = CCDirector::sharedDirector()->getWinSize();
		//CCSprite* pSprite = CCSprite::create("mainScene/background.jpg");
		//CC_BREAK_IF(! pSprite);

		//pSprite->setPosition(ccp(size.width/2, size.height/2));
		//this->addChild(pSprite);

		//CCCoverLayer* pcover = CCCoverLayer::create();
		//pcover->cover(this);

		CCNode9GridFillTex* pnode = CCNode9GridFillTex::createWithTargetSize("mainScene/loginBack.png",
			40, 40, 300, 300);
		CC_BREAK_IF(! pnode);

		CCMyHelper::setPosC(pnode, size.width/2, size.height/2);
		//this->addChild(pnode, pcover->getCurZ()+1);
		this->addChild(pnode);

		const CCSize& nodeSize = pnode->getContentSize();
		CCMenu* ploginBtn = CStdViewFactory::createBtn(this, menu_selector(CLoginWindow::onBtn), CONST_STR_BTN_LOGIN, 
			-1, nodeSize.width/2, nodeSize.height/2 - 30);
		CC_BREAK_IF(! ploginBtn);
		pnode->addChild(ploginBtn);

		CCSprite* pinputback = CCMyHelper::createZeroAnchorSprite("mainScene/labelBg.png");
		CC_BREAK_IF(!pinputback);
		CCMyHelper::setPosC(pinputback, nodeSize.width/2, nodeSize.height/2 + 30);
		pnode->addChild(pinputback);

		CCTextFieldWindow* pinput = CCTextFieldWindow::create(100, 22, 
			CStdViewFactory::LABEL_FONT, 10);
		CC_BREAK_IF(!pinput);
		CCMyHelper::loadFrames("icons/icons.png", "icons/icons.plist");
		pinput->setHintSprite(CCSprite::createWithSpriteFrameName("inputHint.png"));
		pinput->bindString(&(CMyData::curUser));
		pinput->setString("asdf");
		pinput->enableInput();

		CCMyHelper::setPosC(pinput, nodeSize.width/2, nodeSize.height/2 + 30);
		pnode->addChild(pinput);

		ret = true;
	}while(0);

	return ret;
}

void CLoginWindow::onBtn(CCObject* target)
{
	CMyControl::getSharedControl()->invokeCmd(CMyControl::CMD_LOGIN);
}
