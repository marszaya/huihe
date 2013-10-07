#pragma once

#include "CWindowBase.h"
#include <vector>

using namespace std;

/*
* 单个战将的装备
*/
class CRoleEquip:public CCWindowBase
{
public:
	CRoleEquip(void);
	virtual ~CRoleEquip(void);

	static CRoleEquip* create(int roleIdx);
	bool initCRoleEquip(int roleIdx);

	void onUnEquip(CCObject* p);

	virtual void onFrameMsg(CCObject* msg);

protected:
	CCWindowBase* createEquipByType(int tag);
	bool updateCRoleEquip();
	void clearEquipViews();

protected:
	int m_roleIdx;
	vector<int> m_saveTags;
};
