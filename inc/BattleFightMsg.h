#pragma once

#include "battlemsg.pb.h"

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

	//msg中的idx信息是带队伍信息的
	static int makeMsgUnitIdx(int localIdx, bool isHome);
	static int makeLocalUnitIdx(int msgIdx, bool& isHome);

protected:
	int m_roundIdxInDetail;
	int m_actionIdxInRound;

public:
	BattleRecord msg; //proto buf消息
};