#include "CItemContainer.h"

CCEItemContainer::CCEItemContainer(void)
{
	m_ptab=NULL;
	m_pageNav=NULL;
	m_tableWindow=NULL;
	m_table=NULL;
	m_totalPage=1;
	m_row = 0;
	m_col = 0;
	m_curPage=0;
	m_cellGap = CELL_GAP;
	m_tabIdx = -1;
}

CCEItemContainer::~CCEItemContainer(void)
{
}

CCEItemContainer* CCEItemContainer::create(int row, int col, int defaultTabIdx)
{
	CCEItemContainer *pRet = new CCEItemContainer();
	if(pRet && pRet->initCCEItemContainer(row, col, defaultTabIdx))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCEItemContainer::initCCEItemContainer(int row, int col, int defaultTabIdx)
{
	bool ret=false;
	do{
		m_row = row;
		m_col = col;
		m_tabIdx = defaultTabIdx;

		m_ptab = CCETabMenu::create(CCUCommonDelegate::create(this, 
			callfuncO_selector(CCEItemContainer::onTabSelected)));
		if(!m_ptab)
			break;

		m_pageNav = CCEPageNav::create(CCUCommonDelegate::create(this, 
			callfuncO_selector(CCEItemContainer::onPageChanged)));
		if(!m_pageNav)
			break;

		m_tableWindow = CCWindowBase::create();
		if(!m_tableWindow)
			break;

		this->addChild(m_ptab);
		this->addChild(m_pageNav);
		this->addChild(m_tableWindow);

		ret = true;
	}while(0);

	return ret;
}

void CCEItemContainer::onTabSelected(CCObject* p)
{
	do
	{
		int cmd = CCUCommonDelegate::parseCmdFromObj(p);
		if(cmd != CCETabMenu::ITEM_SELECTED)
			break;
		changeTab(m_ptab->getSelectedTab());
	}while(0);
}

void CCEItemContainer::onPageChanged(CCObject* p)
{
	do
	{
		int page = m_curPage;
		int cmd = CCUCommonDelegate::parseCmdFromObj(p);
		if(cmd == CCEPageNav::GO_PRE)
			--page;
		else if(cmd == CCEPageNav::GO_NEXT)
			++page;
		else
			break;

		showPage(page);
	}while(0);
}

bool CCEItemContainer::changeTab(int tab)
{
	bool ret = false;
	do{
		if(!refreshData(tab))
			break;
		
		this->m_tabIdx = tab;
		showPage(0);
		ret = true;
	}while(0);
	return ret;
}

bool CCEItemContainer::showPage(int page)
{
	bool ret =false;
	do{
		int pageItemCount = m_row*m_col;
		if(page <0 || page >= this->m_totalPage)
			m_curPage = 0;
		else
			m_curPage = page;

		if(m_table)
			m_tableWindow->removeChild(m_table, true);
		m_table = NULL;

		for(int i=0; i<pageItemCount; ++i)
		{
			CCWindowBase* child = createItemWindow(m_curPage*pageItemCount+i);
			if(!child)
				break;
			if(!m_table)
			{
				int cellWidth = child->getWindowWidth()+m_cellGap;
				int cellHeight = child->getWindowHeight()+m_cellGap;
				m_table = CCLayoutTable::create(cellWidth, cellHeight,
					m_row, m_col);
				if(!m_table)
					break;
				m_tableWindow->setWindowSize(m_table->getContentSize().width, 
					m_table->getContentSize().height);
				m_tableWindow->addChild(m_table);
			}
			m_table->addItem(child, i/m_col, i%m_col);
		}

		m_pageNav->updatePageNum(m_curPage+1);
		ret = true;
	}while(0);

	return ret;
}

bool CCEItemContainer::refreshData(int tag)
{
	return true;
}

CCWindowBase* CCEItemContainer::createItemWindow(int idx)
{
	CCWindowBase* ret = NULL;
	do{
		CCWindowBase* tmpVal = CCWindowBase::create(100,50);
		tmpVal->setColorBG();
		ret = tmpVal;
	}while(0);
	return ret;
}

