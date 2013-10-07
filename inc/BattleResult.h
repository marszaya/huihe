#pragma once
#include "CWindowBase.h"
#include "item.pb.h"
#include "CLayoutTable.h"

class CBattleResultParam: public CCObject
{
public:
	int m_win;
	int m_expup;
	int m_goldup;
	ItemSet m_items;
};

class CBattleResult:public CCWindowBase
{
public:
	CBattleResult(void);
	virtual ~CBattleResult(void);

	static CBattleResult* create();
	bool initCBattleResult();
	void showResult(CBattleResultParam& param);

	void onClose(CCObject* ob);

protected:
	int m_tagResult;
	int m_tagLabelExpr;
	int m_tagLabelGold;
	CCLayoutTable* m_pitemTable;
};