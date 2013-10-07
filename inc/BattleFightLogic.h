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

//ս������
class CBattleFightLogic:public CCObject
{
public:
	enum BATTLE_STATE
	{
		BATTLE_STATE_INIT, //��ʼ״̬
		BATTLE_STATE_ROUND_START, //�غϿ�ʼ״̬
		BATTLE_STATE_ROUND_END, //�غϽ���״̬
		BATTLE_STATE_UNIT, //���˲���״̬
		BATTLE_STATE_END  //����״̬
	};

	enum GAME_STEP_RET
	{
		GAME_STEP_ERROR = -1,
		GAME_STEP_CONTINUE=0,
		CAME_STEP_END=1
	};

	struct CONTEXT //������
	{
		BATTLE_STATE state; //״̬
		int m_round; //�غ���
		bool m_homeTeamTurn; //�Ƿ������ж� 
		bool m_homeActed; //�����Ƿ��ж�����
		bool m_awayActed; //�Ͷ��Ƿ��ж�����
		bool m_waitFlag; //�ȴ���־

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


	
	//��ʼս��
	//����ִ��Game����
	//����ֵ: 0=�ɹ���-1=ʧ��
	int doGameStep();

	//�Զ�ִ�е�����
	int doGameAuto();

	//game�Ƿ��Ѿ�����
	inline bool isEnd()
	{
		return m_context.state==BATTLE_STATE_END;
	}

	inline bool isWin()
	{
		return m_win;
	}

	void getReward(CBattleResultParam* retParam);

	//��û���ֶ������Ĳ��費�ж�,���Ե�ʱ������Ϊ�ж�
	inline void setSkipNonManualStep(bool v)
	{
		m_skipNonManualStep = v;
	}

	inline CBattleFightMsg& getMsg()
	{
		return m_msg;
	}

protected:
	//���ܹ���
	//isBeforeAttack = true ��ʾѡ�񹥻�ǰ�����ļ��ܣ����򹥻��� 
	//ret = -1 ʧ�� ret=0�ɹ�
	int doSkillAttack(CBattleUnitLogic* src, CBattleUnitLogic* dst, bool isBeforeAttack);
	//��ͨ����
	//ret = -1 ʧ�� ret=0�ɹ�
	int doAttack(CBattleUnitLogic* src, CBattleUnitLogic* dst);

	//ִ�� ս����ʼǰ ����
	int onGameStart();

	//ִ�� ս�������� ����
	int onGameEnd();

	//ִ�� �غϿ�ʼǰ ����
	int onRoundStart();

	//ִ�� �غϽ����� ����
	int onRoundEnd();

	//ִ��һ�ι���
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
			//���ҽ������ӿ��Բ���ս��ʱ�ȴ�
			if(m_context.state == BATTLE_STATE_UNIT 
				&& !m_context.m_homeActed && m_context.m_homeTeamTurn)
			{
				m_context.m_waitFlag = true;
			}
		}
		else
		{
			//�ٴν���ȡ��wait
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
	CBattleTeamLogic m_home; //����
	CBattleTeamLogic m_away; //�Ͷ�
	bool m_win;
	const TconfRow* m_saveBattleConf; //ս����������
	CONTEXT m_context; //������
	CBattleFightMsg m_msg; //��Ϣ���
	bool m_skipNonManualStep;
};
