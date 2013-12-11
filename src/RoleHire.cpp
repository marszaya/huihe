#include "RoleHire.h"
#include "StdViewFactory.h"
#include "RoleUnit.h"
#include "MyData.h"
#include "AttrLabel.h"
#include "STRTABLE.h"
#include "MyControl.h"
#include "DEFINED_VALUES.h"
#include "StrTool.h"

CRoleHire::CRoleHire(void)
{
	this->initPostMsg(CMyControl::getSharedControl()->getDispatcher());
	this->addPostMsg(CMyControl::CMD_DATA_ROLE_HIRED);
	this->addPostMsg(CMyControl::CMD_DATA_ROLE_HIRED_NO_MONEY);
	this->addPostMsg(CMyControl::CMD_DATA_UNIT_OWN_MAX);
}

CRoleHire::~CRoleHire(void)
{
}

CRoleHire* CRoleHire::create()
{
	CRoleHire *pRet = new CRoleHire();
	if(pRet && pRet->initCRoleHire())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CRoleHire::initCRoleHire()
{
	m_dialog = NULL;
	bool ret=false;
	do{
		int windowWidth = 700;
		int windowHeight = 600;

		CMyData::getSharedData()->refreshRoleHire(TABLE_ROW*TABLE_COL,true, true);

		CCNode* pbg = CStdViewFactory::createPopUpBg(windowWidth,windowHeight);

		if(!pbg)
		{
			break;
		}

		this->setWindowBG(pbg);
		this->windowSizeFitBG();

		CCMenu* closeBtn = CStdViewFactory::createCloseBtn(this, menu_selector(CRoleHire::onClose));
		CC_BREAK_IF(!closeBtn);
		this->setCloseBtn(closeBtn);

		if(!initCCEItemContainer(TABLE_ROW, TABLE_COL, 0))
			break;

		if(!updateCCEItemContainer())
			break;

		int tableWinW=this->getTableWindow()->getWindowWidth();
		int tableWinH=this->getTableWindow()->getWindowHeight();

		CCNode* tableBg = CStdViewFactory::create9ScaleBg("mainScene/tabContent.png",
			tableWinW, tableWinH, 30, 30);
		this->getTableWindow()->setWindowBG(tableBg);
		CCMyHelper::setPosC(this->getTableWindow(), windowWidth/2, windowHeight-tableWinH/2-60);
		
		vector<string> theargs;
		theargs.push_back(CStrTool::strDecimal(DEFINED_VALUE_HIRE_REFRESH_COST));
		this->updateLabel(-1, 
			CStrTool::escapeStr(CONST_STR_LABEL_REFESHHIRE, &theargs).c_str(), 
			CStdViewFactory::LABEL_FONT,
				CCMyHelper::POS_INFO(
					windowWidth/2-100, 40, CCMyHelper::POSITION_TYPE_CENTER
				)
			);

		CCMenu* refbtn = CStdViewFactory::createBtn(this, 
			menu_selector(CRoleHire::onRefreshHire), CONST_STR_BTN_REFRESH,-1, 
			windowWidth/2+100, 40);
		if(!refbtn)
			break;

		this->addChild(refbtn);

		ret = true;
	}while(0);

	return ret;
}

void CRoleHire::onClose(CCObject* target)
{
	this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
}

bool CRoleHire::refreshData(int tab)
{
	bool ret = false;
	do{
		ret = true;
	}while(0);
	return ret;
}

CCWindowBase* CRoleHire::createItemWindow(int idx)
{
	CCWindowBase* ret = NULL;
	do{
		int cellWidth=310;
		int cellHeight=100;
		int btnHeight= 30;
		CCNode* pbg = CStdViewFactory::createSmallBg(cellWidth, cellHeight+btnHeight);
		if(!pbg)
			break;
		CCWindowBase* pwin = CCWindowBase::create();
		if(!pwin)
			break;
		pwin->setWindowBG(pbg);
		pwin->windowSizeFitBG();

		RoleSet* rs = CMyData::getSharedData()->allRoles();
		if(idx < 0 || idx >= rs->shoproles_size())
		{
			ret = pwin;
			break;
		}

		Role* prole = rs->mutable_shoproles(idx);
		CCSprite* pic = CRoleUnit::createPic(prole->showtype());
		if(!pic)
			break;

		CCMyHelper::setPosC(pic, cellHeight/2, cellHeight/2);
		pwin->addChild(pic);

		int LABEL_WDITH = 100;
		int LABEL_HEIGHT = 20;
		int GAP = 4;
		int labelStartX = cellHeight;
		int labelDeltaX = LABEL_WDITH+GAP;
		int labelDeltaY = LABEL_HEIGHT+GAP;
		int labelStartY = (cellHeight - labelDeltaY*3-GAP*2)/2+btnHeight;

		CCMyHelper::FONT_INFO fontInfo = CStdViewFactory::LABEL_FONT;
		char strBuff[64] = {0};
		
		//name
		CAttrLabel* namelabel = CAttrLabel::createNameLabel(prole->id().name().c_str());
		if(!namelabel)
			break;
		CCMyHelper::setPosBL(namelabel, labelStartX, labelStartY+labelDeltaY*2);
		pwin->addChild(namelabel);

		//level
		CAttrLabel* lvlabel = CAttrLabel::createLevelLabel(prole->expr().level());
		if(!lvlabel)
			break;
		CCMyHelper::setPosBL(lvlabel, labelStartX+labelDeltaX, labelStartY+labelDeltaY*2);
		pwin->addChild(lvlabel);

		//hp
		CAttrLabel* hplabel = CAttrLabel::createHpLabel(prole->battr().hp());
		if(!hplabel)
			break;
		CCMyHelper::setPosBL(hplabel, labelStartX, labelStartY+labelDeltaY);
		pwin->addChild(hplabel);

		//def
		CAttrLabel* deflabel = CAttrLabel::createDefLabel(prole->battr().arm());
		if(!deflabel)
			break;
		CCMyHelper::setPosBL(deflabel, labelStartX+labelDeltaX, labelStartY+labelDeltaY);
		pwin->addChild(deflabel);

		//atk
		CAttrLabel* atklabel = CAttrLabel::createAtkLabel(prole->battr().ad());
		if(!atklabel)
			break;
		CCMyHelper::setPosBL(atklabel, labelStartX, labelStartY);
		pwin->addChild(atklabel);

		//speed
		CAttrLabel* speedlabel = CAttrLabel::createSpdLabel(prole->battr().as());
		if(!speedlabel)
			break;
		CCMyHelper::setPosBL(speedlabel, labelStartX+labelDeltaX, labelStartY);
		pwin->addChild(speedlabel);

		
		if(prole->hireflag() != 0)
		{
			//未招募过，显示招募按钮和价格
			CAutoUnitRandomTab* pconfur = TCONF_GET(CAutoUnitRandomTab);
			if(pconfur == NULL)
				break;

			int goldNeed = atoi(pconfur->getValue(CStrTool::strDecimal(prole->hireflag()).c_str(),pconfur->GOLD)); 

			CAttrLabel* plabel = CAttrLabel::createGoldLabel(goldNeed);
			if(plabel == NULL)
				break;

			CCMyHelper::setPosC(plabel, cellWidth/2, btnHeight/2);
			pwin->addChild(plabel);

			CCMenu* btn = CStdViewFactory::createBtn(this, menu_selector(CRoleHire::onHire), 
				CONST_STR_BTN_HIRE, idx, cellWidth-30, btnHeight/2);

			pwin->addChild(btn);
		}
		else
		{
			//显示已经招募
			pwin->updateLabel(-1, CONST_STR_BTN_HIRED, CStdViewFactory::LABEL_FONT,
				CCMyHelper::POS_INFO(
					cellWidth/2, btnHeight/2, CCMyHelper::POSITION_TYPE_CENTER
				)
			);
		}

		ret = pwin;
	}while(0);
	return ret;

}

void CRoleHire::onHire(CCObject* target)
{
	DYNAMIC_CAST_CCASERT(target, CCNode, pnode);
	int tag = pnode->getTag();
	CMyData::getSharedData()->hireRole(tag);
}

void CRoleHire::onRefreshHire(CCObject* target)
{
	CMyData::getSharedData()->refreshRoleHire(TABLE_ROW*TABLE_COL);
}

void CRoleHire::onFrameMsg(CCObject* msg)
{
	int cmd = this->getCmdFromPostMsg(msg);
	if(cmd == CMyControl::CMD_WINDOW_SELF_LOOP)
	{
		CMyControl::getSharedControl()->invokeCmd(CMyControl::CMD_MAINSCENE_POPUPCLOSE, this);
	}
	else if(cmd == CMyControl::CMD_DATA_ROLE_HIRED)
	{
		updateCCEItemContainer();
	}
	else if(cmd == CMyControl::CMD_DATA_ROLE_HIRED_NO_MONEY)
	{
		if(m_dialog)
		{
			this->removeChild(m_dialog);
			m_dialog = NULL;
		}
		m_dialog = CStdViewFactory::createDialog("not enough money",
			CCUCommonDelegate::create(this, callfuncO_selector(CRoleHire::onDialogueClose)),
			CStdViewFactory::DIALOG_TYPE_ALERT
		);

		CCMyHelper::setPosC(m_dialog, this->getWindowWidth()/2, this->getWindowHeight()/2);
		this->addChild(m_dialog);
	}
	else if(cmd == CMyControl::CMD_DATA_UNIT_OWN_MAX)
	{
		if(m_dialog)
		{
			this->removeChild(m_dialog);
			m_dialog = NULL;
		}

		m_dialog = CStdViewFactory::createDialog("can't hire any more",
			CCUCommonDelegate::create(this, callfuncO_selector(CRoleHire::onDialogueClose)),
			CStdViewFactory::DIALOG_TYPE_ALERT
		);

		CCMyHelper::setPosC(m_dialog, this->getWindowWidth()/2, this->getWindowHeight()/2);
		this->addChild(m_dialog);
	}
}

void CRoleHire::onDialogueClose(CCObject* p)
{
	this->removeChildOnNextFrame(m_dialog);
	m_dialog = NULL;
}