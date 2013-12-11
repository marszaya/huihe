#pragma once

#include <stdlib.h>
#include <string.h>
#include "BattleFightTeam.h"
#include <vector>
#include "BattleFightMsg.h"
using namespace std;

enum EFFECT_CONDITION_TYPE
{
	EFFECT_CONDITION_GAME_START=0,  //例如增加基础属性等
	EFFECT_CONDITION_ROUND_START,	//本回合开始
	EFFECT_CONDITION_ROUND_END,	//本回合结束
	EFFECT_CONDITION_ACTION_START,	
	EFFECT_CONDITION_ACTION_END,
	EFFECT_CONDITION_BEFORE_ATTACK,
	EFFECT_CONDITION_ATTACK, //占位
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

//前置声明
class CBattleFightLogic;

struct EFFECT_ACTIVE_CONTEXT
{
	//属性浮动
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

		int offsetAtkPercent; //攻击百分比浮动
		int offsetAtk; //攻击数值浮动
		int offsetDefPercent; //防御百分比浮动
		int offsetDef; //防御数值浮动
		int offsetDmg; //额外伤害
	};

	//普通攻击参数缓存
	struct ATTACK
	{
		ATTACK()
		{
			skillid = -1;
			targetType = 1;
		}

		int skillid; //主动攻击技能id，=-1是无技能，显示用
		int targetType; //选取目标类型 0=all 1=单体 n=n个目标
		ATTR_OFFSET attrOffset; //属性浮动
	};

	//输出消息
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

	//控制信息
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

		bool breakFlag; //中断标识
	};

	ATTACK attack;
	MSG_HANDLE mhd;
	CONTROL control;

	CBattleUnitLogic* psrc; //激活的单位
	CBattleUnitLogic* pdst; //对象单位

	//宿主
	CBattleFightLogic* phost;
};
 
