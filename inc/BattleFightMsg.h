#pragma once

#include "battlemsg.pb.h"

//��Ϣ��
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

	//msg�е�idx��Ϣ�Ǵ�������Ϣ��
	static int makeMsgUnitIdx(int localIdx, bool isHome);
	static int makeLocalUnitIdx(int msgIdx, bool& isHome);

protected:
	int m_roundIdxInDetail;
	int m_actionIdxInRound;

public:
	BattleRecord msg; //proto buf��Ϣ
};