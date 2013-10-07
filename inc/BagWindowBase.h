#pragma once

#include "CItemContainer.h"
#include <vector>
#include "MyData.h"

using namespace std;

class CBagWindowBase:public CCEItemContainer
{
public:
	enum TAB_TAGS{
		ITEM_TAB_ALL = 1,
		ITEM_TAB_USABLE = 2,
		ITEM_TAB_EQUIP=3
	};
public:
	int DEFAULT_PAGE_AREA_HEIGHT;
	int DEFAULT_BUTTON_HEIGHT;
	int DEFAULT_TAB_HEIGHT;
public:
	CBagWindowBase(void);
	virtual ~CBagWindowBase(void);

	static CBagWindowBase* create();

	//call before initCBagWindowBase
	void addTab(int tabId);

	bool initCBagWindowBase(int row, int col);

	//please call resetPageInfo inside
	virtual bool refreshData(int tab);

	virtual CCWindowBase* createItemWindow(int idx);

	virtual void onFrameMsg(CCObject* msg);

	void onEquipItem(CCObject* target);
	void onUseItem(CCObject* target);
	void onSaleItem(CCObject* target);
	inline void setDefaultTab(int tab)
	{
		m_defaultTab = tab;
	}

	inline void setEnableEquip(bool v)
	{
		m_enableEquip = v;
	}

	inline void setEnableSell(bool v)
	{
		m_enableSell = v;
	}

	inline void setEnableUse(bool v)
	{
		m_enableUse = v;
	}

protected:
	void cleanTabData();

protected:
	vector<Item*> m_tabData;
	vector<int> m_tabs;
	int m_defaultTab;
	bool m_enableEquip;
	bool m_enableSell;
	bool m_enableUse;
};
