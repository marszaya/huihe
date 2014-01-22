#pragma once

#include "battlemsg.pb.h"
#include "StrTool.h"

//消息类
class CBattleFightMsg
{
public:
	CBattleFightMsg();

	inline int getCurRound()
	{
		return m_roundIdxInDetail;
	}

	BattleRound* addNewRound();
	BattleAction* addNewAction();

	BattleRound* readRound();
	BattleAction* readAction();

	//特殊的msg创建
	inline BattleAction* addAtkMsgAction(int srcIdx, int skillId, int energyLeft, bool srcIsHome)
	{
		BattleAction* pba = addNewAction();
		pba->set_type(BattleAction::ACTION_DMG);
		pba->set_id(skillId);
		pba->set_srcunitidx(makeMsgUnitIdx(srcIdx, srcIsHome));
		pba->add_params(CStrTool::strDecimal(energyLeft));
		return pba;
	}

	inline void addAtkMsgDst(BattleAction* pba, int dstIdx, int dmg, int hp, bool srcIsHome)
	{
		BattleAction* psub = pba->add_subactions();
		psub->add_dstunitidxes(makeMsgUnitIdx(dstIdx, !srcIsHome));
		psub->add_params(CStrTool::strDecimal(dmg));
		psub->add_params(CStrTool::strDecimal(hp));
	}

	inline void addDieAction(int unitidx, bool isHome)
	{
		BattleAction* pba = addNewAction();
		pba->set_type(BattleAction::ACTION_DIE);
		pba->set_srcunitidx(makeMsgUnitIdx(unitidx, isHome));
	}

	inline BattleAction* addBuffBeginAction(int buffid, int unitidx, bool isHome, int fromIdx, 
		int fromSkillId, int effectCnt, int maxEffectCnt)
	{
		BattleAction* pba = addNewAction();
		pba->set_type(BattleAction::ACTION_BUFF_BEGIN);
		pba->set_srcunitidx(fromIdx);
		pba->add_dstunitidxes(makeMsgUnitIdx(unitidx, isHome));
		pba->set_id(buffid);
		pba->add_params(CStrTool::strDecimal(fromSkillId));
		pba->add_params(CStrTool::strDecimal(effectCnt));
		pba->add_params(CStrTool::strDecimal(maxEffectCnt));
		return pba;
	}

	inline BattleAction* addBuffEndAction(int buffid, int unitidx, bool isHome, int fromIdx)
	{
		BattleAction* pba = addNewAction();
		pba->set_type(BattleAction::ACTION_BUFF_END);
		pba->set_srcunitidx(fromIdx);
		pba->add_dstunitidxes(makeMsgUnitIdx(unitidx, isHome));
		pba->set_id(buffid);

		return pba;
	}

	inline BattleAction* addBeCastAction(int castid, int unitidx, bool isHome)
	{
		BattleAction* pba = addNewAction();
		pba->set_type(BattleAction::ACTION_BECAST);
		pba->set_srcunitidx(makeMsgUnitIdx(unitidx, isHome));
		pba->set_id(castid);
		return pba;
	}

	//msg中的idx信息是带队伍信息的
	static int makeMsgUnitIdx(int localIdx, bool isHome);
	static int makeLocalUnitIdx(int msgIdx, bool& isHome);

protected:
	int m_roundIdxInDetail;
	int m_actionIdxInRound;

public:
	BattleRecord msg; //proto buf消息
};