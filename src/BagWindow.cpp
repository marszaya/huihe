#include "BagWindow.h"
#include "StdViewFactory.h"
#include "MyControl.h"
#include "ItemUnit.h"
CBagWindow::CBagWindow(void)
{
	m_innerWin = NULL;
}

CBagWindow::~CBagWindow(void)
{
}

CBagWindow* CBagWindow::create(int row, int col)
{
	CBagWindow *pRet = new CBagWindow();
	if(pRet && pRet->initCBagWindow(row, col))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBagWindow::initCBagWindow(int row, int col)
{
	bool ret=0;
	do{
		CCNode* pbg = CStdViewFactory::createPopUpBg();
		if(!pbg)
			break;

		this->setWindowBG(pbg);
		this->windowSizeFitBG();

		CCMenu* closeBtn = CStdViewFactory::createCloseBtn(this, menu_selector(CBagWindow::onClose));
		CC_BREAK_IF(!closeBtn);
		this->setCloseBtn(closeBtn);

		m_innerWin = CBagWindowBase::create();
		if(!m_innerWin)
			break;

		m_innerWin->addTab(m_innerWin->ITEM_TAB_ALL);
		m_innerWin->addTab(m_innerWin->ITEM_TAB_USABLE);
		m_innerWin->addTab(m_innerWin->ITEM_TAB_EQUIP);

		m_innerWin->setDefaultTab(m_innerWin->ITEM_TAB_ALL);
		m_innerWin->setEnableSell(true);
		m_innerWin->setEnableUse(true);

		if(!m_innerWin->initCBagWindowBase(row, col))
			break;

		CCMyHelper::setPosC(m_innerWin, this->m_width/2, this->m_height/2 - 30);
		this->addChild(m_innerWin);

		ret = true;
	}while(0);

	return ret;
}

void CBagWindow::onClose(CCObject* target)
{
	this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
}

void CBagWindow::onFrameMsg(CCObject* msg)
{
	int cmd = this->getCmdFromPostMsg(msg);
	if(cmd == CMyControl::CMD_WINDOW_SELF_LOOP)
	{
		CMyControl::getSharedControl()->invokeCmd(CMyControl::CMD_MAINSCENE_POPUPCLOSE, this);
	}
}

