#pragma once

#include "BattleLogicEffect.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

//��������
//����������
class CBattleSkillLogicDmgUp: public CBattleLogicEffectSkill
{
public:
	virtual int getType(){return 1;}

	virtual EFFECT_CONDITION_TYPE getCondition() {return EFFECT_CONDITION_BEFORE_ATTACK;}

	virtual int active(EFFECT_ACTIVE_CONTEXT& con);

	virtual int getPriority() {return EFFECT_PRIORTIY_SKILL_DMGUP;}

	virtual CBattleLogicEffect* clone()
	{
		return new CBattleSkillLogicDmgUp;
	}
};



//��������
class CBattleSkillLogicDmg: public CBattleLogicEffectSkill
{
public:
	virtual int getType(){return 2;}

	virtual EFFECT_CONDITION_TYPE getCondition() {return EFFECT_CONDITION_BEFORE_ATTACK;}

	virtual int active(EFFECT_ACTIVE_CONTEXT& con);

	virtual int getPriority() {return EFFECT_PRIORTIY_SKILL_DMG;}

	virtual CBattleLogicEffect* clone()
	{
		return new CBattleSkillLogicDmg;
	}
};

//��Ѫdebuff
class CBattleSkillLogicDebuffHpDown: public CBattleLogicEffectSkill
{
public:
	virtual int getType(){return 3;}

	virtual EFFECT_CONDITION_TYPE getCondition() {return EFFECT_CONDITION_AFTER_ATTACK;}

	virtual int active(EFFECT_ACTIVE_CONTEXT& con);

	virtual int getPriority() {return EFFECT_PRIORITY_SKILL_DEBUFF_HPDOWN;}

	virtual CBattleLogicEffect* clone()
	{
		return new CBattleSkillLogicDebuffHpDown;
	}
};

//�Ʒ�debuff
class CBattleSkillLogicDebuffDefDown: public CBattleLogicEffectSkill
{
public:
	virtual int getType(){return 4;}

	virtual EFFECT_CONDITION_TYPE getCondition() {return EFFECT_CONDITION_AFTER_ATTACK;}

	virtual int active(EFFECT_ACTIVE_CONTEXT& con);

	virtual int getPriority() {return EFFECT_PRIORITY_SKILL_DEBUFF_DEFDOWN;}

	virtual CBattleLogicEffect* clone()
	{
		return new CBattleSkillLogicDebuffDefDown;
	}
};