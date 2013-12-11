#pragma once
//#include "CWindowBase.h"
#include "CActionManager.h"
#include "BattleFightUnit.h"
#include "CLayoutTable.h"
#include "StdViewFactory.h"
#include "BattleFightMsg.h"
#include "BattleFightTeam.h"

class CBattleSpeed;

class CBattleWindowMap:public CCEActionManager
{
	//����action���̣�����Ϊ��Ԫ
	friend class CBattleProcedureAttack;
	friend class CBattleProcedureAttackRaged;

public:
	CBattleWindowMap(void);
	virtual ~CBattleWindowMap(void);

	static CBattleWindowMap* create(int row, int col, float cellw, float cellh);
	bool initCBattleWindowMap(int row, int col, float cellw, float cellh);

	//��msg�ж�ȡ������Ϣ
	int initTeamFromMsg(CBattleFightMsg& msg);

	//��msg�в��Ŷ���
	//return true, �в���
	//return false û��msg�ɹ�����
	bool playFromMsg(CBattleFightMsg& msg);

	inline void debugString(const char* c)
	{
		m_debugLabelTag = this->updateLabel(m_debugLabelTag, c, 
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(0,0,CCMyHelper::POSITION_TYPE_BOTTOM_LEFT));
	}

	inline void bindSpd(CBattleSpeed* spd)
	{
		m_spd = spd;
	}


	CBattleFightUnit* getFightUnit(int tagId);

	inline int getColMax()
	{
		return m_colMax;
	}

	inline bool isPlaying()
	{
		return m_isPlaying;
	}

protected:
	int getSpd();
	void doAttack(int srcTagId, int dstTagId, int dmg, int skillId=-1);
	void showBullets(const char* bulletConf, 
		 const CCPoint& srcPos,const CCPoint& dstPos,float* dtOut=NULL);

	void showDmg(int tagId, int dmg, int skillid=-1);

	//add new unit to map
	//return unit tagId;
	int addFightUnit(int unitId, int x, int y, bool flip, CBattleUnitLogic* pdata);
	
	//remove unit from map by tagId
	bool removeFightUnit(int tagId);

	int initTeamFromMsgTeam(BattleTeam* pmsgteam, CBattleTeamLogic& localTeam, bool isAway);

	CBattleUnitLogic* getUnitLogicByMsgIdx(int msgIdx);

	virtual void onProcedureEnd(int tag);

protected:
	CCLayoutTable* m_ptable;
	int m_rowMax;
	int m_colMax;
	int m_debugLabelTag;
	float m_cellW;
	float m_cellH;
	CBattleSpeed* m_spd;
	bool m_isPlaying;

	//data��msg�е�����
	CBattleTeamLogic m_hometeam;
	CBattleTeamLogic m_awayteam;
};
