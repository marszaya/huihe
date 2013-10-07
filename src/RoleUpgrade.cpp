#include "RoleUpgrade.h"
#include "StdViewFactory.h"
#include "STRTABLE.h"
#include "mathTools.h"
#include "RoleUnit.h"
#include "StrTool.h"
#include "MyData.h"

CRoleUpgrade::CRoleUpgrade(void)
{
	m_curRoleIdx = 0;
}

CRoleUpgrade::~CRoleUpgrade(void)
{
}

CRoleUpgrade* CRoleUpgrade::create()
{
	CRoleUpgrade *pRet = new CRoleUpgrade();
	if(pRet && pRet->initCRoleUpgrade())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CRoleUpgrade::initCRoleUpgrade()
{
	bool ret=false;
	do{
		if(!createCheckBox(false, ccp(200, 340)))
			break;
		if(!createCheckBox(false, ccp(200, 280)))
			break;
		if(!createCheckBox(false, ccp(200, 220)))
			break;

		CCMenu* refreshBtn = CStdViewFactory::createBtn(this, menu_selector(CRoleUpgrade::onBtnRefresh),
			CONST_STR_BTN_REFRESH, -1, 200, 20);
		CC_BREAK_IF(!refreshBtn);
		this->addChild(refreshBtn);

		CCMenu* closeBtn = CStdViewFactory::createCloseBtn(this, menu_selector(CRoleUpgrade::onClose));
		CC_BREAK_IF(!closeBtn);
		this->setCloseBtn(closeBtn);

		ret = true;
	}while(0);

	return ret;
}



bool CRoleUpgrade::createCheckBox(bool isopen, const CCPoint & initPos)
{
	bool ret = false;
	do{
		int tag = createCustomTag();
		CCCheckBox* pcheckbox = CStdViewFactory::createCheckBox("checkSel.png", "checkUnSel.png", isopen, tag);
		CC_BREAK_IF(!pcheckbox);
		CCMyHelper::setPositionByCenter(pcheckbox, initPos.x, initPos.y);
		this->addChild(pcheckbox, 0, tag);
		m_saveTags.push_back(tag);
		ret = true;
	}while(0);

	return ret;
}

bool CRoleUpgrade::getCheckBoxValue(int idx)
{
	CCCheckBox* pcheckbox;
	CCNode* pnode;
	//自己当心不要越界
	pnode = getChildByTag(m_saveTags[idx]);
	if(pnode)
	{
		DYNAMIC_CAST_CCASERT2(pnode, CCCheckBox, pcheckbox);
		return pcheckbox->getState();
	}

	return false;
}

void CRoleUpgrade::onBtnRefresh(CCObject* target)
{
	do{
		CMyData* pdata = CMyData::getSharedData();
		Role* pcurrole = pdata->getRoleByIdx(m_curRoleIdx);
		CC_BREAK_IF(!pcurrole);

		bool isHpProtected = getCheckBoxValue(0);
		bool isDefProtected = getCheckBoxValue(1);
		bool isAtkProtected = getCheckBoxValue(2);

		int dhp=0;
		int darm=0;
		int dad=0;

		if(!isHpProtected)
		{
			dhp = gGameTools.rand(-100,100);
			pdata->modifyRoleAttr(pcurrole, Item::EFFECT_HP, dhp);
		}

		if(!isDefProtected)
		{
			darm = gGameTools.rand(-100,100);
			pdata->modifyRoleAttr(pcurrole, Item::EFFECT_ARMOR, darm);
		}

		if(!isAtkProtected)
		{
			dad = gGameTools.rand(-100,100);
			pdata->modifyRoleAttr(pcurrole, Item::EFFECT_AD, dad);
		}

	}	while(0);
}

void CRoleUpgrade::onClose(CCObject* target)
{
	this->removeFromParentAndCleanup(true);
}