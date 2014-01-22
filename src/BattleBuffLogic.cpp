#include "BattleBuffLogic.h"
#include "StrTool.h"
#include "mathTools.h"

//----------------------------
//记得要在这里注册新的buff类型
//----------------------------

BATTLE_EFFECT_REGIST_BUFF(CBattleBuffLogicHpDown);
BATTLE_EFFECT_REGIST_BUFF(CBattleBuffLogicDefDown);
BATTLE_EFFECT_REGIST_BUFF(CBattleBuffLogicAttackUp);  
BATTLE_EFFECT_REGIST_BUFF(CBattleBuffLogicAttackDown);

//end
int CBattleBuffLogicHpDown::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!checkSrcAlive(con))
	{
		return 0;
	}

	con.psrc->dealDmg(pbuff->param[0]);

	BattleAction* pba = con.mhd.pmsg->addBeCastAction(pbuff->fromSkillID, con.psrc->idx, con.mhd.isHomeTurn);
	pba->add_params(CStrTool::strDecimal(pbuff->id));
	pba->add_params(CStrTool::strDecimal(pbuff->param[0]));
	pba->add_params(CStrTool::strDecimal(con.psrc->hp));

	trySrcDieMsg(con);

	return 0;
}

int CBattleBuffLogicDefDown::active(EFFECT_ACTIVE_CONTEXT& con)
{
	//dst是自己
	if(!checkDstAlive(con))
	{
		return 0;
	}

	EFFECT_ACTIVE_CONTEXT::ATTR_OFFSET& attrOffset = con.attack.attrOffset;
	attrOffset.offsetDef -= pbuff->param[0];
	
	return 0;
}

int CBattleBuffLogicAttackUp::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!checkSrcAlive(con))
	{
		return 0;
	}

	EFFECT_ACTIVE_CONTEXT::ATTR_OFFSET& attrOffset = con.attack.attrOffset;
	attrOffset.offsetAtk += pbuff->param[0];
	return 0;
}

int CBattleBuffLogicAttackDown::active(EFFECT_ACTIVE_CONTEXT& con)
{
	if(!checkSrcAlive(con))
	{
		return 0;
	}

	EFFECT_ACTIVE_CONTEXT::ATTR_OFFSET& attrOffset = con.attack.attrOffset;
	attrOffset.offsetAtk -= pbuff->param[0];
	return 0;
}