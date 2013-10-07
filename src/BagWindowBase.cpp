#include "BagWindowBase.h"
#include "ItemUnit.h"
#include "MyData.h"
#include "StdViewFactory.h"
#include "StrTool.h"
#include "MyControl.h"
#include "STRTABLE.h"
#include "CNode9Grid.h"
#include <algorithm>
#include "DataUtil.h"
#include "CCommonDelegate.h"

bool itemSortByIdBig(Item* a, Item* b)
{
	return atoi(a->id().id().c_str()) > atoi(b->id().id().c_str());
}

CBagWindowBase::CBagWindowBase(void)
{
	DEFAULT_PAGE_AREA_HEIGHT = 40;
	DEFAULT_BUTTON_HEIGHT=30;
	DEFAULT_TAB_HEIGHT = 20;
	m_defaultTab = 0;
	m_enableEquip = false;
	m_enableSell = false;
	m_enableUse = false;

	this->initPostMsg(CMyControl::getSharedControl()->getDispatcher());
	this->addPostMsg(CMyControl::CMD_DATA_BAG_MODIFIED);
}

CBagWindowBase::~CBagWindowBase(void)
{
	cleanTabData();
}

CBagWindowBase* CBagWindowBase::create()
{
	CBagWindowBase *pRet = new CBagWindowBase();
	if(pRet)
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBagWindowBase::initCBagWindowBase(int row, int col)
{
	bool ret=0;
	do{

		if(!initCCEItemContainer(row, col, m_defaultTab))
			break;

		for(unsigned int i=0; i<m_tabs.size(); ++i)
		{
			CCNode* psel=NULL;
			CCNode* punsel=NULL;
			if(m_tabs[i] == ITEM_TAB_ALL)
			{
				CStdViewFactory::createTabNode(CONST_STR_BTN_TAB_ALL, psel, punsel);
			}
			else if(m_tabs[i] == ITEM_TAB_USABLE)
			{
				CStdViewFactory::createTabNode(CONST_STR_BTN_TAB_USABLE, psel, punsel);
			}
			else if(m_tabs[i] == ITEM_TAB_EQUIP)
			{
				CStdViewFactory::createTabNode(CONST_STR_BTN_TAB_EQUIP, psel, punsel);
			}
			else
				continue;
			
			this->getTabMenu()->addTab(m_tabs[i], psel,punsel);
		}


		CStdViewFactory::configPageNav(this->getPageNav());

		//show
		if(!this->updateCCEItemContainer())
			break;

		//bg
		int tableWinW=this->getTableWindow()->getWindowWidth();
		int tableWinH=this->getTableWindow()->getWindowHeight();

		CCNode* tableBg = CStdViewFactory::create9ScaleBg("mainScene/tabContent.png",
			tableWinW, tableWinH, 30, 30);
		this->getTableWindow()->setWindowBG(tableBg);

		//positions
		this->setWindowSize(tableWinW, tableWinH+DEFAULT_PAGE_AREA_HEIGHT+DEFAULT_TAB_HEIGHT);

		CCMyHelper::setPosC(this->getPageNav(), 
			int(this->getWindowWidth()/2), DEFAULT_PAGE_AREA_HEIGHT/2);

		int theX = 0;
		int theY = DEFAULT_PAGE_AREA_HEIGHT + tableWinH;
		CCMyHelper::setPosBL(this->getTabMenu(), theX, theY);
		CCMyHelper::setPosTL(this->getTableWindow(), theX, theY);

		ret = true;
	}while(0);

	return ret;
}

CCWindowBase* CBagWindowBase::createItemWindow(int idx)
{
	int cellWidth = CItemUnit::DEFAULT_WIDTH;
	int cellHeight = CItemUnit::DEFAULT_HEIGHT+DEFAULT_BUTTON_HEIGHT;

	CCWindowBase* ret = NULL;
	do{
		CCWindowBase* pwindow = CCWindowBase::create(cellWidth, cellHeight);
		if(!pwindow)
			break;

		CCNode* pbg = CStdViewFactory::createSmallBg(cellWidth, cellHeight);
		if(!pbg)
			break;

		pwindow->setWindowBG(pbg);

		//显示一个背景就可以了
		if((unsigned int)idx>=m_tabData.size())
		{
			ret = pwindow;
			break;
		}

		const Item& theItem = *(m_tabData[idx]);
		int param = theItem.num();
		if(CDataUtil::getMajorType(theItem.subtype())==Item::MAJOR_TYPE_EQUIP)
		{
			param = theItem.has_expr()? theItem.expr().level():0;
		}

		CItemUnit* punit = CItemUnit::create(theItem.subtype(), param);
		if(!punit)
			break;

		CCMyHelper::setPosC(punit, cellWidth/2, DEFAULT_BUTTON_HEIGHT+CItemUnit::DEFAULT_HEIGHT/2 );
		pwindow->addChild(punit);
		
		int majorType = CDataUtil::getMajorType(theItem.subtype());
		if(majorType == Item::MAJOR_TYPE_USABLE && m_enableUse)
		{
			CCMenu* pbtn = CStdViewFactory::createBtn(this, 
				menu_selector(CBagWindowBase::onUseItem), 
				CONST_STR_BTN_USE, idx, 113, DEFAULT_BUTTON_HEIGHT/2+3);
			if(!pbtn)
			{
				break;
			}
			pwindow->addChild(pbtn);
		}
		else if(majorType == Item::MAJOR_TYPE_EQUIP && m_enableEquip)
		{
			CCMenu* pbtn = CStdViewFactory::createBtn(this, 
				menu_selector(CBagWindowBase::onEquipItem), 
				CONST_STR_BTN_EQUIP, idx, 113, DEFAULT_BUTTON_HEIGHT/2+3);
			if(!pbtn)
			{
				break;
			}
			pwindow->addChild(pbtn);
		}

		if(m_enableSell)
		{
			CCMenu* psalebtn = CStdViewFactory::createBtn(this, menu_selector(CBagWindowBase::onSaleItem), 
				CONST_STR_BTN_SALE, idx, 47, DEFAULT_BUTTON_HEIGHT/2+3);
			if(!psalebtn)
			{
				break;
			}
			pwindow->addChild(psalebtn);
		}

		ret = pwindow;
	}while(0);

	return ret;
}

bool CBagWindowBase::refreshData(int tab)
{
	bool ret = false;
	do{
		cleanTabData();
		const ItemSet& is = CMyData::getSharedData()->user().item();
		//以后增加过滤
		for(int i=0; i<is.items_size(); ++i)
		{
			bool ok = false;
			if(tab == ITEM_TAB_ALL)
			{
				ok = true;
			}
			else if(tab == ITEM_TAB_USABLE)
			{
				ok = (CDataUtil::getMajorType(is.items(i).subtype()) == Item::MAJOR_TYPE_USABLE);
			}
			else if(tab == ITEM_TAB_EQUIP)
			{
				ok = (CDataUtil::getMajorType(is.items(i).subtype()) == Item::MAJOR_TYPE_EQUIP);
			}

			if(ok)
			{
				Item* copyItem = new Item();
				copyItem->CopyFrom(is.items(i));
				m_tabData.push_back(copyItem);
			}
		}

		//sort by id big
		std::sort(m_tabData.begin(), m_tabData.end(), itemSortByIdBig);
		resetPageInfo(m_tabData.size());
		ret = true;
	}while(0);
	return ret;
}


void CBagWindowBase::onFrameMsg(CCObject* msg)
{
	this->updateCCEItemContainer();
}

void CBagWindowBase::onEquipItem(CCObject* target)
{
	DYNAMIC_CAST_CCASERT(target, CCNode, pnode);
	int tag = pnode->getTag();
	if(tag < 0 || tag >= (int)m_tabData.size())
	{
		return;
	}
	//抛出给监听者处理
	int itemidx = CMyData::getSharedData()->getItemIdxById(m_tabData[tag]->id().id());
	CMyControl::getSharedControl()->invokeCmd(CMyControl::CMD_ITEM_EQUIP, 
		CCString::createWithFormat("%d", itemidx));
}


void CBagWindowBase::onUseItem(CCObject* target)
{
	DYNAMIC_CAST_CCASERT(target, CCNode, pnode);
	int tag = pnode->getTag();
	if(tag < 0 || tag >= (int)m_tabData.size())
	{
		return;
	}
	int itemidx = CMyData::getSharedData()->getItemIdxById(m_tabData[tag]->id().id());
	CMyData::getSharedData()->useItem(itemidx, 1);
	//CCMessageBox(CStrTool::strDecimal(tag).c_str(), "Debug");
}

void CBagWindowBase::onSaleItem(CCObject* target)
{
	DYNAMIC_CAST_CCASERT(target, CCNode, pnode);
	int tag = pnode->getTag();
	if(tag < 0 || tag >= (int)m_tabData.size())
	{
		return;
	}
	int itemidx = CMyData::getSharedData()->getItemIdxById(m_tabData[tag]->id().id());
	CMyData::getSharedData()->saleItem(itemidx, 1);
	//CCMessageBox(CStrTool::strDecimal(tag).c_str(), "Debug");
}

void CBagWindowBase::addTab(int tabId)
{
	m_tabs.push_back(tabId);
}

void CBagWindowBase::cleanTabData()
{
	for(unsigned int i=0; i<m_tabData.size(); ++i)
	{
		delete m_tabData[i];
	}

	m_tabData.clear();
}

