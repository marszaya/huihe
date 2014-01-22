#pragma once

#include "CWindowBase.h"
#include "CLayoutTable.h"
#include "CPageNav.h"
#include "CTabMenu.h"

class CCEItemContainer:public CCWindowBase
{
public:
	enum POSITION_INFO{
		CELL_GAP=10
	};
public:
	CCEItemContainer(void);
	virtual ~CCEItemContainer(void);

	static CCEItemContainer* create(int row, int col, int defaultTabIdx=0);
	bool initCCEItemContainer(int row, int col, int defaultTabIdx=0);

	inline CCETabMenu* getTabMenu()
	{
		return m_ptab;
	}

	inline CCEPageNav* getPageNav()
	{
		return m_pageNav;
	}

	inline CCWindowBase* getTableWindow()
	{
		return m_tableWindow;
	}

	inline void setCellGap(int v)
	{
		m_cellGap = v;
	}

	inline bool updateCCEItemContainer()
	{
		m_ptab->selectTab(m_tabIdx, false);
		return changeTab(m_tabIdx);
	}

	void onTabSelected(CCObject* p);
	void onPageChanged(CCObject* p);

	bool changeTab(int tab);
	bool showPage(int page);

	//please call resetPageInfo inside
	virtual bool refreshData(int tab);

	virtual CCWindowBase* createItemWindow(int idx);

protected:
	inline void resetPageInfo(int itemTotal)
	{
		m_totalPage = itemTotal/(m_row*m_col);
		if(m_totalPage % (m_row*m_col) !=0)
			++m_totalPage;
		if(m_totalPage == 0)
			m_totalPage = 1;
		m_curPage = 0;
	}

protected:
	CCETabMenu* m_ptab;
	CCEPageNav* m_pageNav;
	CCWindowBase* m_tableWindow;
	CCLayoutTable* m_table;
	int m_totalPage;
	int m_row;
	int m_col;
	int m_curPage;
	int m_cellGap;
	int m_tabIdx;
};
