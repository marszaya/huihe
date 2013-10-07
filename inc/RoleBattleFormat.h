#pragma once

#include "CWindowBase.h"
#include "CLayoutTable.h"

/*
* 编辑出战队列
*/
class CRoleBattleFormat:public CCWindowBase
{
public:
	CRoleBattleFormat(void);
	virtual ~CRoleBattleFormat(void);

	static CRoleBattleFormat* create(int currentRoleIdx);
	bool initCRoleBattleFormat(int currentRoleIdx);

	inline void setCurrentRoleIdx(int idx)
	{
		m_currentRoleIdx = idx;
	}

	inline bool hasChange()
	{
		return m_hasChange;
	}

	//回调
	void onPush(CCObject* param);
	void onPop(CCObject* param);
	bool saveFormat();

protected:
	CCWindowBase* createCellWindow(int posIdx);
	bool updateCRoleBattleFormat();

	//数据操作
	bool pushRole(int posIdx);
	bool popRole(int posIdx);

protected:
	CCLayoutTable* m_ptable;
	vector<int> m_vRoleIdx;
	int m_currentRoleIdx;
	bool m_hasChange;
};