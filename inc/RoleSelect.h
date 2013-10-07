#pragma once

#include "CWindowBase.h"
#include "RoleUnit.h"
#include "MyData.h"
#include "CCommonDelegate.h"
#include <vector>
using namespace std;

/*
* 战将选择框
*/
class CRoleSelect:public CCWindowBase
{
public:
	CRoleSelect(void);
	virtual ~CRoleSelect(void);

	static CRoleSelect* create(int unitNum, CCUCommonDelegate* pd);
	bool initCRoleSelect(int unitNum, CCUCommonDelegate* pd);
	void onRoleDown(CCObject* pnode);

	void onRoleUp(CCObject* pnode);

	void onSelectRole(CCObject* pnode);

	inline int getCurRoleIdx()
	{
		return m_sortedIndex[m_curLocalIdx];
	}

	//不会触发通知
	void setCurRoleIdx(int idx);
	virtual void onFrameMsg(CCObject* msg);

protected:
	bool updateRoleSelect(int startLocalIdx);
	CCWindowBase* createRoleView(Role* prole);
	int roleIdxToLocalIdx(int roleIdx);

	virtual void initUnitSize();

protected:
	vector<int> m_saveTags;
	vector<int> m_sortedIndex;
	int m_curLocalIdx;
	int m_roleViewStartLocalIdx;
	int m_unitNum;
	int m_defaultUnitWidth;
	int m_defaultUnitHight;
	int m_defaultUnitGap;
};


