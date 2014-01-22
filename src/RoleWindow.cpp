#include "RoleWindow.h"
#include "StdViewFactory.h"
#include "MyData.h"
#include "MyControl.h"
#include "STRTABLE.h"
#include "RoleUnit.h"
#include "StrTool.h"
#include "CMsgWithCmd.h"

CRoleWindow::CRoleWindow(void)
{
	m_roleSel = NULL;
	m_roleInfo = NULL;

	m_curRoleIdx = 0;

	//info
	m_roleDetail = NULL;
	m_roleEquip = NULL;
	m_roleBagEquip = NULL;
	m_fireBtn = NULL;

	//
	this->initPostMsg(CMyControl::getSharedControl()->getDispatcher());
	this->addPostMsg(CMyControl::CMD_ITEM_EQUIP);
	this->addPostMsg(CMyControl::CMD_DATA_ROLE_FIRED);
}

CRoleWindow::~CRoleWindow(void)
{
}

CRoleWindow* CRoleWindow::create()
{
	CRoleWindow *pRet = new CRoleWindow();
	if(pRet && pRet->initCRoleWindow())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CRoleWindow::initCRoleWindow()
{
	bool ret=false;
	do{
		CCNode* pbg = CStdViewFactory::createPopUpBg(900,600);

		if(!pbg)
		{
			break;
		}

		this->setWindowBG(pbg);
		this->windowSizeFitBG();

		CCMenu* closeBtn = CStdViewFactory::createCloseBtn(this, menu_selector(CRoleWindow::onClose));
		CC_BREAK_IF(!closeBtn);
		this->setCloseBtn(closeBtn);

		m_roleInfo = this->createRoleInfoWindow();
		if(!m_roleInfo)
			break;

		updateRoleInfoWindow(0);
		updateRoleSelect();
		ret = true;
	}while(0);

	return ret;
}

bool CRoleWindow::updateRoleSelect()
{
	bool ret = false;
	do{
		if(m_roleSel)
		{
			this->removeChild(m_roleSel, true);
		}

		m_roleSel = CRoleSelect::create( ROLE_VIEW_NUM,
			CCUCommonDelegate::create(this, callfuncO_selector(CRoleWindow::onRoleSelected))
		);

		if(!m_roleSel)
			break;
		CCMyHelper::setPosBL(m_roleSel,15,15);
		this->addChild(m_roleSel);

		ret = true;
	}while(0);

	return ret;
}

void CRoleWindow::onClose(CCObject* target)
{
	CMyControl::getSharedControl()->invokeCmd(CMyControl::CMD_MAINSCENE_POPUPCLOSE, this);
}

CCWindowBase* CRoleWindow::createRoleInfoWindow()
{
	CCWindowBase* ret = NULL;
	do{
		CCWindowBase* tmpVal = CCWindowBase::create();
		if(!tmpVal)
			break;
		int blX = 230;
		int blY = 15;
		CCNode* bg = CStdViewFactory::createSmallBg(m_width-blX-16,m_height-blY-40);
		if(!bg)
			break;
		tmpVal->setWindowBG(bg);
		tmpVal->windowSizeFitBG();

		//角色装备
		m_roleBagEquip = CBagWindowEquip::create(3,2);
		if(!m_roleBagEquip)
			break;
		CCMyHelper::setPosBL(m_roleBagEquip, 50, 0);
		tmpVal->addChild(m_roleBagEquip);

		m_roleDetail = NULL;
		CCMyHelper::setPosBL(tmpVal,230,15);
		this->addChild(tmpVal);
		ret = tmpVal;
	}while(0);
	return ret;
}

bool CRoleWindow::updateRoleInfoWindow(int curIdx)
{
	bool ret = false;
	do{
		if(m_roleDetail)
			m_roleInfo->removeChild(m_roleDetail, true);

		m_roleDetail = CRoleDetail::create(curIdx);
		if(!m_roleDetail)
			break;

		CCMyHelper::setPosTL(m_roleDetail, 20, 
			m_roleInfo->getWindowHeight() - 10);
		m_roleInfo->addChild(m_roleDetail);

		if(m_roleEquip)
			m_roleInfo->removeChild(m_roleEquip, true);
		m_roleEquip = CRoleEquip::create(curIdx);
		if(!m_roleEquip)
			break;

		CCMyHelper::setPosTL(m_roleEquip, 
			m_roleDetail->getWindowWidth()+40, 
			m_roleInfo->getWindowHeight() - 10);
			
		m_roleInfo->addChild(m_roleEquip);

		//解雇按钮
		if(m_fireBtn)
			m_roleInfo->removeChild(m_fireBtn, true);

		if(curIdx != 0)
		{
			m_fireBtn = CStdViewFactory::createBtn(this, menu_selector(CRoleWindow::onFire),
				CONST_STR_BTN_FIRE, -1, m_roleInfo->getWindowWidth()-140,50);
			if(!m_fireBtn)
				break;
			m_roleInfo->addChild(m_fireBtn);
		}

		ret = true;
	}while(0);
	return ret;
}


void CRoleWindow::onRoleSelected(CCObject* pobj)
{
	do{
		CCUCommonDelegate::CParamWrap* param = dynamic_cast<CCUCommonDelegate::CParamWrap*>(pobj);
		if(!param)
			break;

		CCNode* pnode = dynamic_cast<CCNode*>(param->m_cbParam);
		if(!pnode)
			break;

		m_curRoleIdx = m_roleSel->getCurRoleIdx();
		//CCMessageBox(CStrTool::strDecimal(m_curRoleIdx).c_str(), "Debug");
		updateRoleInfoWindow(m_curRoleIdx);
	}while(0);
}

void CRoleWindow::onFrameMsg(CCObject* msg)
{
	int cmd = this->getCmdFromPostMsg(msg);
	if(cmd == CMyControl::CMD_ITEM_EQUIP)
	{
		Role* prole = CMyData::getSharedData()->getRoleByIdx(m_curRoleIdx);
		if(!prole)
			return;

		CCString* itemidxstr = dynamic_cast<CCString*>(this->getParamFromPostMsg(msg));

		CMyData::getSharedData()->equip(prole, itemidxstr->intValue());
	}
	else if(cmd ==  CMyControl::CMD_DATA_ROLE_FIRED)
	{
		m_curRoleIdx = 0;
		updateRoleSelect();
		updateRoleInfoWindow(m_curRoleIdx);
	}
}

void CRoleWindow::onFire(CCObject* param)
{
	CMyData::getSharedData()->fireRole(m_curRoleIdx);
}
