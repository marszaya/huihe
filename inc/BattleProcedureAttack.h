#pragma once
#include "CActionManager.h"
#include "BattleMapAttackInfo.h"
#include <vector>
using namespace std;

class CBattleProcedureAttack:public CCEActionProcedure
{
public:
	CBattleProcedureAttack(void);
	~CBattleProcedureAttack(void);

	static CBattleProcedureAttack* create(void);
	bool initCBattleProcedureAttack(void);

	virtual bool nextStep(int stepToCheck);

public:
	CBattleMapAttackInfo srcInfo;
	vector<CBattleMapAttackInfo> dstInfos;
	int skillId;
	bool m_srcDone;
	bool m_dstDone;
};
