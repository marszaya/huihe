#pragma once

#include "CWindowBase.h"
#include "CItemContainer.h"

/*
* ¹ÍÓ¶Õ½½«
*/
class CRoleHire:public CCEItemContainer
{
public:
	const static int TABLE_ROW = 3;
	const static int TABLE_COL = 2;
public:
	CRoleHire(void);
	virtual ~CRoleHire(void);

	static CRoleHire* create(void);
	bool initCRoleHire(void);

	virtual bool refreshData(int tab);
	virtual CCWindowBase* createItemWindow(int idx);
	void onClose(CCObject* target);
	void onHire(CCObject* target);
	void onRefreshHire(CCObject* target);

	void onDialogueClose(CCObject* param);
protected:
	virtual void onFrameMsg(CCObject* msg);

protected:
	CCWindowBase* m_dialog;
};
