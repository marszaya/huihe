#include "BattleSkillLogic.h"
#include "tconfManager.h"
#include "StrTool.h"
#include "mathTools.h"

//----------------------------
//记得要在这里注册新的skill类型
//----------------------------

BATTLE_EFFECT_REGIST_SKILL(CBattleSkillLogicDmgUp);
BATTLE_EFFECT_REGIST_SKILL(CBattleSkillLogicDmg);
BATTLE_EFFECT_REGIST_SKILL(CBattleSkillLogicDebuffHpDown);
BATTLE_EFFECT_REGIST_SKILL(CBattleSkillLogicDebuffDefDown);
BATTLE_EFFECT_REGIST_SKILL(CBattleSkillLogicBuffAttackUp);
BATTLE_EFFECT_REGIST_SKILL(CBattleSkillLogicMutilAttack);
BATTLE_EFFECT_REGIST_SKILL(CBattleSkillLogicBuffAttackDown);

//enf
int CBattleSkillLogicDmgUp::active(EFFECT_ACTIVE_CONTEXT& con)
{
	int ret = -1;
	do{
		if(m_config.vparams.size() < 1)
			return -1;
		con.attack.attrOffset.offsetAtkPercent += atoi(m_config.vparams[0].c_str());
		ret = 0;
	}while(0);

	return ret;
}

int CBattleSkillLogicDmg::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!checkSrcAlive(con))
		return 0;

	//需要消耗能量
	if(!useEnergy(con.psrc))
	{
		return 0;
	}

	int ret = -1;
	do{
		if(m_config.vparams.size() < 2)
			break;

		con.attack.attrOffset.offsetAtk += con.psrc->atk * (atoi(m_config.vparams[0].c_str())-100)/100;
		con.attack.attrOffset.offsetAtk += atoi(m_config.vparams[1].c_str());
		con.attack.skillid = m_config.skillid;
		ret = 0;
	}while(0);

	return ret;
}

int CBattleSkillLogicDebuffHpDown::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!checkDstAlive(con))
		return 0;
	int ret = -1;

	do{
		CBattleUnitLogic::BUFF newBuff;	
		srcCastBuff(con, newBuff);

		vector<CBattleLogicEffectSkill::BUFF_MATCH_CONDITION> conditions; 
		vector<CBattleLogicEffectSkill::BUFF_MATCH_OPTION> options;
		conditions.push_back(CBattleLogicEffectSkill::BUFF_MATCH_SEQ);
		conditions.push_back(CBattleLogicEffectSkill::BUFF_MATCH_FROMIDX);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_RESET_REMAIN);
		addBuff(con.pdst, false, newBuff, con, conditions, options, 1);

		//新buff不在当下触发，不追加effect

		ret = 0;
	}while(0);

	return ret;
}


int CBattleSkillLogicDebuffDefDown::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!checkDstAlive(con))
		return 0;

	int ret = -1;

	do{
		CBattleUnitLogic::BUFF newBuff;
		srcCastBuff(con, newBuff);

		vector<CBattleLogicEffectSkill::BUFF_MATCH_CONDITION> conditions; 
		vector<CBattleLogicEffectSkill::BUFF_MATCH_OPTION> options;
		conditions.push_back(CBattleLogicEffectSkill::BUFF_MATCH_SEQ);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_REPLACE);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_FILTER_SKILLID_BIGER_OR_EQUAL);
		addBuff(con.pdst, false, newBuff, con, conditions, options, 1);

		ret = 0;
	}while(0);

	return ret;
}

int CBattleSkillLogicBuffAttackUp::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!this->checkSrcAlive(con))
		return 0;
	int ret = -1;

	do{
		CBattleUnitLogic::BUFF newBuff;
		srcCastBuff(con, newBuff);

		vector<CBattleLogicEffectSkill::BUFF_MATCH_CONDITION> conditions; 
		vector<CBattleLogicEffectSkill::BUFF_MATCH_OPTION> options;
		conditions.push_back(CBattleLogicEffectSkill::BUFF_MATCH_SEQ);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_RESET_REMAIN);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_INCREASE_EFFECTCNT);
		addBuff(con.psrc, true, newBuff, con, conditions, options, 1);
		ret = 0;
	}while(0);

	return ret;
}

int CBattleSkillLogicMutilAttack::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!this->checkSrcAlive(con))
		return 0;
	
	if(!useEnergy(con.psrc))
	{
		return 0;
	}

	int ret = -1;
	do{
		//群體傷害
		con.attack.targetType = 0;
		con.attack.attrOffset.offsetAtk += con.psrc->atk * (atoi(m_config.vparams[0].c_str())-100)/100;
		con.attack.attrOffset.offsetAtk += atoi(m_config.vparams[1].c_str());
		ret = 0;
	}while(0);

	return ret;
}

int CBattleSkillLogicBuffAttackDown::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!checkDstAlive(con))
		return 0;

	int ret = -1;

	do{
		CBattleUnitLogic::BUFF newBuff;
		srcCastBuff(con, newBuff);

		vector<CBattleLogicEffectSkill::BUFF_MATCH_CONDITION> conditions; 
		vector<CBattleLogicEffectSkill::BUFF_MATCH_OPTION> options;
		conditions.push_back(CBattleLogicEffectSkill::BUFF_MATCH_SEQ);
		conditions.push_back(CBattleLogicEffectSkill::BUFF_MATCH_FROMIDX);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_REPLACE);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_FILTER_SKILLID_BIGER_OR_EQUAL);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_RESET_REMAIN);
		options.push_back(CBattleLogicEffectSkill::BUFF_MATCH_INCREASE_EFFECTCNT);

		addBuff(con.pdst, false, newBuff, con, conditions, options, newBuff.param[0]);

		ret = 0;
	}while(0);

	return ret;
}
