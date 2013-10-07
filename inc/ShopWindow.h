#pragma once

#include "CItemContainer.h"
#include <vector>
using namespace std;

class CShopWindow:public CCEItemContainer
{
public:
	enum TAB_TAGS{
		SHOP_TAB_ALL
	};

	static const int DEFUALT_ROW=3;
	static const int DEFUALT_COL=4;
	static const int DEFAULT_BUTTON_HEIGHT=32;
	static const int DEFAULT_PRICE_HEIGTH=22;

public:
	CShopWindow(void);
	virtual ~CShopWindow(void);

	static CShopWindow* create();
	bool initCShopWindow(void);

	//please call resetPageInfo inside
	virtual bool refreshData(int tab);

	virtual CCWindowBase* createItemWindow(int idx);

	void onClose(CCObject* target);

	virtual void onFrameMsg(CCObject* msg);

	void onPayItem(CCObject* target);
public:
	vector<int> m_curData;
};
