#pragma once
#include "CWindowBase.h"
#include <vector>
using namespace std;

/*
* Õ½½«Éý¼¶
*/
class CRoleUpgrade:public CCWindowBase
{
public:
	CRoleUpgrade(void);
	virtual ~CRoleUpgrade(void);

	static CRoleUpgrade* create(void);
	bool initCRoleUpgrade(void);

	void onClose(CCObject* target);
	void onBtnRefresh(CCObject* target);

	inline void setCurRoleIdx(int idx)
	{
		m_curRoleIdx = idx;
	}

protected:
	bool createCheckBox(bool isopen, const CCPoint & initPos);
	bool getCheckBoxValue(int idx);

protected:
	int m_curRoleIdx;
	vector<int> m_saveTags;
};