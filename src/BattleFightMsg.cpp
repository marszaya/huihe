#include "BattleFightMsg.h"

CBattleFightMsg::CBattleFightMsg()
{
	m_roundIdxInDetail = 0;
	m_actionIdxInRound = 0;
	msg.set_version(1);
	msg.set_type("base");
}

BattleRound* CBattleFightMsg::addNewRound()
{
	return msg.mutable_detail()->add_rounds();
}

BattleAction* CBattleFightMsg::addNewAction()
{
	BattleDetail* detail = msg.mutable_detail();
	if(detail->rounds_size() == 0)
	{
		return NULL;
	}

	return detail->mutable_rounds(detail->rounds_size()-1)->add_actions();
}

BattleRound* CBattleFightMsg::readRound()
{
	BattleDetail* detail = msg.mutable_detail();
	if(m_roundIdxInDetail < 0 || m_roundIdxInDetail >= detail->rounds_size())
	{
		return NULL;
	}

	m_actionIdxInRound = 0;
	return detail->mutable_rounds(m_roundIdxInDetail++);
}

BattleAction* CBattleFightMsg::readAction()
{
	BattleDetail* detail = msg.mutable_detail();
	//call readRound before this call
	int curround = m_roundIdxInDetail-1;
	if(curround < 0 || curround >= detail->rounds_size())
	{
		return NULL;
	}

	BattleRound* pround = detail->mutable_rounds(curround);
	if(m_actionIdxInRound >= pround->actions_size())
	{
		return NULL;
	}

	return pround->mutable_actions(m_actionIdxInRound++);
}

int CBattleFightMsg::makeMsgUnitIdx(int localIdx, bool isHome)
{
	if(isHome)
	{
		return BattleUnitIdxDef::UINT_IDX_HOME_BEGIN + localIdx;
	}
	else
	{
		return BattleUnitIdxDef::UNIT_IDX_AWAY_BEGIN + localIdx;
	}
}

int CBattleFightMsg::makeLocalUnitIdx(int msgIdx, bool& isHome)
{
	int idx = msgIdx;
	if(msgIdx >= BattleUnitIdxDef::UNIT_IDX_AWAY_BEGIN)
	{
		isHome = false;
		idx -= BattleUnitIdxDef::UNIT_IDX_AWAY_BEGIN;
	}
	else
	{
		isHome = true;
		idx -= BattleUnitIdxDef::UINT_IDX_HOME_BEGIN;
	}

	return idx;
}