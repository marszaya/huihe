#pragma once

#include <stdlib.h>
#include <string.h>
#include "BattleFightTeam.h"
#include <vector>
#include "BattleFightMsg.h"
using namespace std;

enum EFFECT_CONDITION_TYPE
{
	EFFECT_CONDITION_GAME_START=0,  //�������ӻ������Ե�
	EFFECT_CONDITION_ROUND_START,	//���غϿ�ʼ
	EFFECT_CONDITION_ROUND_END,	//���غϽ���
	EFFECT_CONDITION_ACTION_START,	
	EFFECT_CONDITION_ACTION_END,
	EFFECT_CONDITION_BEFORE_ATTACK,
	EFFECT_CONDITION_ATTACK, //ռλ
	EFFECT_CONDITION_AFTER_ATTACK,
	EFFECT_CONDITION_BEFORE_BEATTACK,
	EFFECT_CONDITION_AFTER_BEATTACK
};

enum EFFECT_PRIORITY_TYPE
{
	EFFECT_PRIORITY_DEFAULT_DMG,
	EFFECT_PRIORITY_SKILL_DEBUFF_HPDOWN,
	EFFECT_PRIORITY_SKILL_DEBUFF_DEFDOWN,
	EFFECT_PRIORTIY_SKILL_DMGUP,
	EFFECT_PRIORTIY_SKILL_DMG,
	EFFECT_PRIORITY_BUFF_HPDOWN,
	EFFECT_PRIORITY_BUFF_DEFDOWN,
};

//ǰ������
class CBattleFightLogic;

struct EFFECT_ACTIVE_CONTEXT
{
	//���Ը���
	struct ATTR_OFFSET
	{
		ATTR_OFFSET()
		{
			offsetAtkPercent = 0;
			offsetAtk = 0;
			offsetDefPercent = 0;
			offsetDef = 0;
			offsetDmg = 0;
		}

		int offsetAtkPercent; //�����ٷֱȸ���
		int offsetAtk; //������ֵ����
		int offsetDefPercent; //�����ٷֱȸ���
		int offsetDef; //������ֵ����
		int offsetDmg; //�����˺�
	};

	//��ͨ������������
	struct ATTACK
	{
		ATTACK()
		{
			skillid = -1;
			targetType = 1;
		}

		int skillid; //������������id��=-1���޼��ܣ���ʾ��
		int targetType; //ѡȡĿ������ 0=all 1=���� n=n��Ŀ��
		ATTR_OFFSET attrOffset; //���Ը���
	};

	//�����Ϣ
	struct MSG_HANDLE
	{
		inline void init(CBattleFightMsg* apmsg, bool aIsHomeTurn)
		{
			pmsg = apmsg;
			isHomeTurn = aIsHomeTurn;
		}

		CBattleFightMsg* pmsg;
		bool isHomeTurn;
	};

	//������Ϣ
	struct CONTROL
	{
		inline CONTROL()
		{
			clear();
		}

		inline void clear()
		{
			breakFlag = false;
		}

		bool breakFlag; //�жϱ�ʶ
	};

	ATTACK attack;
	MSG_HANDLE mhd;
	CONTROL control;

	CBattleUnitLogic* psrc; //����ĵ�λ
	CBattleUnitLogic* pdst; //����λ

	//����
	CBattleFightLogic* phost;
};
 
