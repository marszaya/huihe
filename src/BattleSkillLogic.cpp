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
//end

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
		addBuff(con.pdst, false, newBuff, con, 0);

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
		addBuff(con.pdst, false, newBuff, con, 0);

		ret = 0;
	}while(0);

	return ret;
}
