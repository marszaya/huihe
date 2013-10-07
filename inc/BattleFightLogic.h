#pragma once
#include "BattleMap.h"
//#include "CCArray.h"
#include "mathTools.h"
#include "MyData.h"
#include "tconfManager.h"
#include "BattleResult.h"
#include "BattleFightMsg.h"
#include "BattleFightTeam.h"
#include <vector>
using namespace std;

//战斗核心
class CBattleFightLogic:public CCObject
{
public:
	enum BATTLE_STATE
	{
		BATTLE_STATE_INIT, //初始状态
		BATTLE_STATE_ROUND_START, //回合开始状态
		BATTLE_STATE_ROUND_END, //回合结束状态
		BATTLE_STATE_UNIT, //单人操作状态
		BATTLE_STATE_END  //结束状态
	};

	enum GAME_STEP_RET
	{
		GAME_STEP_ERROR = -1,
		GAME_STEP_CONTINUE=0,
		CAME_STEP_END=1
	};

	struct CONTEXT //上下文
	{
		BATTLE_STATE state; //状态
		int m_round; //回合数
		bool m_homeTeamTurn; //是否主队行动 
		bool m_homeActed; //主队是否行动过了
		bool m_awayActed; //客队是否行动过了
		bool m_waitFlag; //等待标志

		inline void clear()
		{
			state = BATTLE_STATE_INIT;
			m_round = 0;
			m_homeTeamTurn = true;
			m_homeActed = m_awayActed = false;
			m_waitFlag = false;
		}

		inline CONTEXT()
		{
			clear();
		}
	};

public:
	CBattleFightLogic(void);
	~CBattleFightLogic(void);


	void initBattle();


	
	//开始战斗
	//单步执行Game过程
	//返回值: 0=成功，-1=失败
	int doGameStep();

	//自动执行到结束
	int doGameAuto();

	//game是否已经结束
	inline bool isEnd()
	{
		return m_context.state==BATTLE_STATE_END;
	}

	inline bool isWin()
	{
		return m_win;
	}

	void getReward(CBattleResultParam* retParam);

	//在没有手动操作的步骤不中断,调试的时候设置为中断
	inline void setSkipNonManualStep(bool v)
	{
		m_skipNonManualStep = v;
	}

	inline CBattleFightMsg& getMsg()
	{
		return m_msg;
	}

protected:
	//技能攻击
	//isBeforeAttack = true 表示选择攻击前触发的技能，否则攻击后 
	//ret = -1 失败 ret=0成功
	int doSkillAttack(CBattleUnitLogic* src, CBattleUnitLogic* dst, bool isBeforeAttack);
	//普通攻击
	//ret = -1 失败 ret=0成功
	int doAttack(CBattleUnitLogic* src, CBattleUnitLogic* dst);

	//执行 战斗开始前 步骤
	int onGameStart();

	//执行 战斗结束后 步骤
	int onGameEnd();

	//执行 回合开始前 步骤
	int onRoundStart();

	//执行 回合结束后 步骤
	int onRoundEnd();

	//执行一次攻击
	int doAttackStep();

	inline CBattleTeamLogic* getActiveTeam()
	{
		if(m_context.m_homeTeamTurn)
			return &m_home;
		else
			return &m_away;
	}

	inline CBattleTeamLogic* getUnActiveTeam()
	{
		if(m_context.m_homeTeamTurn)
			return &m_away;
		else
			return &m_home;
	}

	inline bool isTeamActed()
	{
		if(m_context.m_homeTeamTurn)
			return m_context.m_homeActed;
		else
			return m_context.m_awayActed;
	}

	inline void setTeamActed()
	{
		if(m_context.m_homeTeamTurn)
			m_context.m_homeActed = true;
		else
			m_context.m_awayActed = true;		
	}

	inline void switchTeam()
	{
		m_context.m_homeTeamTurn = !m_context.m_homeTeamTurn;
	}

	inline bool checkRoundOver()
	{
		bool ret= m_context.m_homeActed && m_context.m_awayActed;
		if(ret)
		{
			m_context.state = BATTLE_STATE_ROUND_END;
		}

		return ret;
	}

	inline void startAttack()
	{
		m_context.state = BATTLE_STATE_UNIT;
	}

	void startNextRound();
	void initHomeTeam();
	void initAwayTeam();

	inline bool checkEnd()
	{
		if(m_home.checkFail())
		{
			m_win = false;
			m_context.state = BATTLE_STATE_END;
			return true;
		}
		
		if(m_home.checkFail())
		{
			m_win = true;
			m_context.state = BATTLE_STATE_END;
			return true;
		}

		return false;
	}

	inline int gotoNextStep()
	{
		if(m_skipNonManualStep)
			return doGameStep();
		else
			return GAME_STEP_CONTINUE;
	}

	inline bool needWait()
	{
		if(m_context.m_waitFlag == false)
		{
			//当且仅当主队可以操作战将时等待
			if(m_context.state == BATTLE_STATE_UNIT 
				&& !m_context.m_homeActed && m_context.m_homeTeamTurn)
			{
				m_context.m_waitFlag = true;
			}
		}
		else
		{
			//再次进入取消wait
			m_context.m_waitFlag = false;
		}

		return m_context.m_waitFlag;
	}

	inline BattleAction* newAtkMsgAction(BattleAction::BattleActionType t, int s, int d, int id=-1)
	{
		BattleAction* pba = m_msg.addNewAction();
		pba->set_type(t);
		if(id>0)
			pba->set_id(id);
		pba->set_srcunitidx(CBattleFightMsg::makeMsgUnitIdx(s, m_context.m_homeTeamTurn));
		pba->add_dstunitidxes(CBattleFightMsg::makeMsgUnitIdx(d, !m_context.m_homeTeamTurn));
		return pba;
	}

protected:
	CBattleTeamLogic m_home; //主队
	CBattleTeamLogic m_away; //客队
	bool m_win;
	const TconfRow* m_saveBattleConf; //战斗单局配置
	CONTEXT m_context; //上下文
	CBattleFightMsg m_msg; //信息输出
	bool m_skipNonManualStep;
};
