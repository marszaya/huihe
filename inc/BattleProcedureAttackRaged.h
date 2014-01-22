#pragma once
#include "BattleProcedureAttack.h"
#include <string>
using namespace std;

class CBattleProcedureAttackRaged:public CBattleProcedureAttack
{
public:
	CBattleProcedureAttackRaged(void);
	~CBattleProcedureAttackRaged(void);

	static CBattleProcedureAttackRaged* create(void);
	bool initCBattleProcedureAttackRaged(void);

	virtual bool nextStep(int stepToCheck);

public:
	string bulletConf;
};
