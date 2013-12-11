#pragma once

#include "BattleLogicEffect.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

class CBattleBuffLogicHpDown:public CBattleLogicEffectBuff
{
public:
	virtual int getType(){return 3;}

	virtual EFFECT_CONDITION_TYPE getCondition() {return EFFECT_CONDITION_ACTION_START;}

	virtual int getPriority() {return EFFECT_PRIORITY_BUFF_HPDOWN;}

	virtual int active(EFFECT_ACTIVE_CONTEXT& con);

	virtual CBattleLogicEffect* clone()
	{
		return new CBattleBuffLogicHpDown;
	}
};

class CBattleBuffLogicDefDown:public CBattleLogicEffectBuff
{
public:
	virtual int getType(){return 3;}

	virtual EFFECT_CONDITION_TYPE getCondition() {return EFFECT_CONDITION_BEFORE_BEATTACK;}

	virtual int getPriority() {return EFFECT_PRIORITY_BUFF_DEFDOWN;}

	virtual int active(EFFECT_ACTIVE_CONTEXT& con);

	virtual CBattleLogicEffect* clone()
	{
		return new CBattleBuffLogicDefDown;
	}
};
