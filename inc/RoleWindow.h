#pragma once
#include "CWindowBase.h"
#include "MyData.h"
#include <vector>
#include "CCommonDelegate.h"
#include "RoleSelect.h"
#include "RoleDetail.h"
#include "RoleEquip.h"
#include "BagWindowEquip.h"
using namespace std;

/*
* 战将信息窗口
*/
class CRoleWindow:public CCWindowBase
{
public:
	enum CONST_VALUES{
		ROLE_VIEW_NUM = 5
	};

public:
	CRoleWindow(void);
	virtual ~CRoleWindow(void);

	static CRoleWindow* create();
	bool initCRoleWindow();

	void onClose(CCObject* target);

	void onRoleSelected(CCObject* param);

	void onFire(CCObject* param);

protected:
	CCWindowBase* createRoleInfoWindow();
	bool updateRoleInfoWindow(int curRoleIdx);
	virtual void onFrameMsg(CCObject* msg);
	bool updateRoleSelect();

protected:
	CRoleSelect* m_roleSel;
	CCWindowBase* m_roleInfo;

	int m_curRoleIdx;

	vector<int> m_roleViewTags;
	vector<int> m_roleInfoTags;

	//info
	CRoleDetail* m_roleDetail;
	CRoleEquip* m_roleEquip;
	CBagWindowEquip* m_roleBagEquip;
	CCMenu* m_fireBtn;
};
