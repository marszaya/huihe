#include "RoleEquip.h"
#include "ItemUnit.h"
#include "StdViewFactory.h"
#include "MyData.h"
#include "STRTABLE.h"
#include "MyControl.h"

CRoleEquip::CRoleEquip(void)
{
	m_roleIdx = -1;
	this->initPostMsg(CMyControl::getSharedControl()->getDispatcher());
	this->addPostMsg(CMyControl::CMD_DATA_ROLE_EQUIP_MODIFIED);
}

CRoleEquip::~CRoleEquip(void)
{
}

CRoleEquip* CRoleEquip::create(int roleIdx)
{
	CRoleEquip *pRet = new CRoleEquip();
	if(pRet && pRet->initCRoleEquip(roleIdx))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CRoleEquip::initCRoleEquip(int roleIdx)
{
	bool ret=false;
	do{
		m_roleIdx =roleIdx;
		ret = updateCRoleEquip();
	}while(0);

	return ret;
}

CCWindowBase* CRoleEquip::createEquipByType(int tag)
{
	CCWindowBase* ret=NULL;
	do{
		Role* prole = CMyData::getSharedData()->getRoleByIdx(m_roleIdx);
		if(!prole)
			break;

		Item* pitem = CMyData::getSharedData()->getEquip(prole, tag);
		if(!pitem)
			break;

		int btnHeight=30;
		CCWindowBase* theWin = CCWindowBase::create();
		CCNode* bg = CStdViewFactory::createSmallBg(CItemUnit::DEFAULT_WIDTH, 
			CItemUnit::DEFAULT_HEIGHT+btnHeight);
		if(!bg)
			break;
		theWin->setWindowBG(bg);
		theWin->windowSizeFitBG();

		if(pitem && pitem->has_id())
		{
			int centerX = int(theWin->getWindowWidth()/2);
			int level = 0;
			if(pitem->has_expr())
				level = pitem->expr().level();
			CItemUnit* punit = CItemUnit::create(pitem->subtype(), level);
			if(!punit)
				break;
			CCMyHelper::setPosC(punit, centerX, int(btnHeight+theWin->getWindowHeight())/2);
			theWin->addChild(punit);
			
			CCMenu* pbtn = CStdViewFactory::createBtn(this, menu_selector(CRoleEquip::onUnEquip), 
				CONST_STR_BTN_UNEQUIP, tag,
				centerX, btnHeight/2);
			theWin->addChild(pbtn);
		}

		ret = theWin;
	}while(0);

	return ret;
}

void CRoleEquip::onUnEquip(CCObject* target)
{
	DYNAMIC_CAST_CCASERT(target, CCNode, pnode);
	int tag = pnode->getTag();
	if(tag < 0 || tag >= Equip::END)
	{
		return;
	}

	Role* prole = CMyData::getSharedData()->getRoleByIdx(m_roleIdx);
	if(!prole)
		return;
	CMyData::getSharedData()->unequip(prole, tag);
}


void CRoleEquip::onFrameMsg(CCObject* msg)
{
	updateCRoleEquip();
}

bool CRoleEquip::updateCRoleEquip()
{
	bool ret=false;
	do{
		clearEquipViews();
		int i=0;
		int offsetY = 5;
		int offsetX = 5;
		int cwX = 0;
		for(i=0; i<Equip::END; ++i)
		{
			CCWindowBase* cw = createEquipByType(i);
			if(!cw)
				break;
			CCMyHelper::setPosBL(cw, offsetX, offsetY);
			offsetY+=cw->getWindowHeight()+5;
			cwX = cw->getWindowWidth();
			int ctag = this->createCustomTag();
			m_saveTags.push_back(ctag);
			this->addChild(cw, 0, ctag);
		}
		if(i!= Equip::END)
			break;
		this->setWindowSize(cwX+2*offsetX,offsetY);
		ret = true;
	}while(0);

	return ret;
}

void CRoleEquip::clearEquipViews()
{
	CCNode * pnode = NULL;
	for(unsigned int i=0; i<m_saveTags.size(); ++i)
	{
		if((pnode = this->getChildByTag(m_saveTags[i]))!=NULL)
		{
			this->removeChild(pnode, true);
		}
	}
	m_saveTags.clear();
}
