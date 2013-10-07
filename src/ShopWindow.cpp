#include "ShopWindow.h"
#include "ItemUnit.h"
#include "tconfManager.h"
#include "StdViewFactory.h"
#include "STRTABLE.h"
#include "MyControl.h"
#include "StrTool.h"
#include "AttrLabel.h"
#include "MyData.h"

CShopWindow::CShopWindow(void)
{
	this->initPostMsg(CMyControl::getSharedControl()->getDispatcher());
	this->addPostMsg(CMyControl::CMD_DATA_ACCOUNT_MODIFIED);
}

CShopWindow::~CShopWindow(void)
{
}

CShopWindow* CShopWindow::create()
{
	CShopWindow *pRet = new CShopWindow();
	if(pRet && pRet->initCShopWindow())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CShopWindow::initCShopWindow()
{
	bool ret=false;
	do{
		if(!initCCEItemContainer(DEFUALT_ROW, DEFUALT_COL, SHOP_TAB_ALL))
			break;

		CCNode* psel=NULL;
		CCNode* punsel=NULL;
		CStdViewFactory::createTabNode(CONST_STR_BTN_TAB_ALL, psel, punsel);
		this->getTabMenu()->addTab(SHOP_TAB_ALL, psel,punsel);

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

		CCNode* bg = CStdViewFactory::createPopUpBg(tableWinW+40, tableWinH+110);
		this->setWindowBG(bg);
		this->windowSizeFitBG();
		CCMenu* closeBtn = CStdViewFactory::createCloseBtn(this, menu_selector(CShopWindow::onClose));
		if(!closeBtn)
			break;
		this->setCloseBtn(closeBtn);


		//positions
		CCMyHelper::setPosC(this->getPageNav(), 
			int(this->getWindowWidth()/2), 25);

		int theX = int(this->getWindowWidth()-this->getTableWindow()->getWindowWidth())/2;
		int theY = 40 + this->getTableWindow()->getWindowHeight();
		CCMyHelper::setPosBL(this->getTabMenu(), theX, theY);
		CCMyHelper::setPosTL(this->getTableWindow(), theX, theY);

		ret = true;
	}while(0);

	return ret;
}

bool CShopWindow::refreshData(int tab)
{
	m_curData.clear();
	bool ret = false;
	do{
		CAutoShopTab* ptable = TCONF_GET(CAutoShopTab);
		if(!ptable)
			break;

		const TconfTable& table = ptable->getTable();
		for(int i=0; i<table.rows_size(); ++i)
		{
			bool ok=false;
			if(tab==SHOP_TAB_ALL)
			{
				ok=true;
			}

			if(ok)
			{
				const TconfRow* row = &(table.rows(i));
				m_curData.push_back(atoi(ptable->getRowValue(row, ptable->SHOPID)));
			}
		}
		
		resetPageInfo(m_curData.size());
		ret = true;
	}while(0);
	return ret;
}

CCWindowBase* CShopWindow::createItemWindow(int idx)
{
	int cellWidth = CItemUnit::DEFAULT_WIDTH;
	int cellHeight = CItemUnit::DEFAULT_HEIGHT+DEFAULT_BUTTON_HEIGHT+DEFAULT_PRICE_HEIGTH;

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
		if(idx>=(int)m_curData.size())
		{
			ret = pwindow;
			break;
		}

		int shopID = this->m_curData[idx];
		CAutoShopTab* ptable = TCONF_GET(CAutoShopTab);
		if(!ptable)
			break;

		const TconfRow* row = ptable->getRowByKey(CStrTool::strDecimal(shopID).c_str());
		if(!row)
			break;

		const char* v = ptable->getRowValue(row, ptable->ITEMTYPE);
		if(v==NULL)
			break;
		int subtype = atoi(v);

		v = ptable->getRowValue(row, ptable->ITEMNUM);
		if(v==NULL)
			break;
		int itemNum = atoi(v);

		v = ptable->getRowValue(row, ptable->PAYTYPE);
		if(v==NULL)
			break;
		int payType = atoi(v);

		v = ptable->getRowValue(row, ptable->PRICEREAL);
		if(v==NULL)
			break;
		int payPrice = atoi(v);

		//不显示个数为1的
		if(itemNum == 1)
			itemNum = -1;
		CItemUnit* punit = CItemUnit::create(subtype, itemNum);
		if(!punit)
			break;

		CCMyHelper::setPosC(punit, cellWidth/2, 
			DEFAULT_PRICE_HEIGTH+DEFAULT_BUTTON_HEIGHT+CItemUnit::DEFAULT_HEIGHT/2 );
		pwindow->addChild(punit);

		//售价
		const Account& acc = CMyData::getSharedData()->user().account();
		CCNode* priceLabel=NULL;
		bool canPay = false;
		if(payType == Item::PAY_GOLD)
		{
			priceLabel = CAttrLabel::createGoldLabel(payPrice);
			canPay = acc.gold() >= payPrice;
		}
		else 
		{
			priceLabel = CAttrLabel::createMoneyLabel(payPrice);
			canPay = acc.money() >= payPrice;
		}

		if(!priceLabel)
			break;
		CCMyHelper::setPosC(priceLabel, cellWidth/2,
			DEFAULT_PRICE_HEIGTH/2+DEFAULT_BUTTON_HEIGHT);
		pwindow->addChild(priceLabel);

		CCMenu* pbtn = CStdViewFactory::createBtn(this, 
			menu_selector(CShopWindow::onPayItem), 
			CONST_STR_BTN_PAY, idx, cellWidth/2, DEFAULT_BUTTON_HEIGHT/2);
		if(!pbtn)
		{
			break;
		}
		pwindow->addChild(pbtn);
		
		if(!canPay)
		{
			CCMenuItem* node = dynamic_cast<CCMenuItem*>(pbtn->getChildByTag(idx));
			if(node)
			{
				node->setEnabled(false);
			}
		}

		ret = pwindow;
	}while(0);

	return ret;
}


void CShopWindow::onClose(CCObject* target)
{
	this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
}

void CShopWindow::onPayItem(CCObject* target)
{
	DYNAMIC_CAST_CCASERT(target, CCNode, pnode);
	int tag = pnode->getTag();
	if(tag < 0 || tag >= (int)m_curData.size())
	{
		return;
	}

	int shopID = this->m_curData[tag];
	CMyData::getSharedData()->payItem(shopID,1);
}

void CShopWindow::onFrameMsg(CCObject* msg)
{
	int cmd = this->getCmdFromPostMsg(msg);
	if(cmd == CMyControl::CMD_WINDOW_SELF_LOOP)
	{
		CMyControl::getSharedControl()->invokeCmd(CMyControl::CMD_MAINSCENE_POPUPCLOSE, this);
	}
	else
	{
		updateCCEItemContainer();
	}
}