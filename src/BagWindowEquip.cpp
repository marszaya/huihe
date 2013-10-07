#include "BagWindowEquip.h"
#include "StdViewFactory.h"
#include "MyControl.h"
#include "ItemUnit.h"
CBagWindowEquip::CBagWindowEquip(void)
{
}

CBagWindowEquip::~CBagWindowEquip(void)
{
}

CBagWindowEquip* CBagWindowEquip::create(int row, int col)
{
	CBagWindowEquip *pRet = new CBagWindowEquip();
	if(pRet && pRet->initCBagWindowEquip(row, col))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBagWindowEquip::initCBagWindowEquip(int row, int col)
{
	bool ret=0;
	do{

		m_innerWin = CBagWindowBase::create();
		if(!m_innerWin)
			break;

		m_innerWin->setEnableEquip(true);
		m_innerWin->setDefaultTab(m_innerWin->ITEM_TAB_EQUIP);
		if(!m_innerWin->initCBagWindowBase(row, col))
			break;

		this->setWindowSize(m_innerWin->getWindowWidth(), 
			m_innerWin->getWindowHeight());
		CCMyHelper::setPosBL(m_innerWin, 0, 0);
		this->addChild(m_innerWin);

		ret = true;
	}while(0);

	return ret;
}

