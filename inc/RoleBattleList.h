#pragma once

#include "CWindowBase.h"
#include "CLayoutTable.h"
#include "RoleSelect.h"
#include "RoleDetail.h"
#include "RoleBattleFormat.h"

/*
* ²¼Õó´°¿Ú
*/
class CRoleBattleList:public CCWindowBase
{
public:
	enum CONST_VALUES{
		ROLE_VIEW_NUM = 5
	};

public:
	CRoleBattleList(void);
	virtual ~CRoleBattleList(void);

	static CRoleBattleList* create(void);
	bool initCRoleBattleList(void);
	
	void onClose(CCObject* target);
	virtual void onFrameMsg(CCObject* msg);
	void onRoleSelected(CCObject* param);
	void onSave(CCObject* target);
    void onDialogueClose(CCObject* param);
	void onDialogueSave(CCObject* param);

protected:
	bool updateRoleSelect();
	bool updateRoleDetail();
	bool createRoleFormat();

protected:
	CRoleSelect* m_roleSel;
	CRoleBattleFormat* m_roleFormat;
	CRoleDetail* m_roleDetail;
	int m_curRoleIdx;
	CCWindowBase* m_dialog;
};
