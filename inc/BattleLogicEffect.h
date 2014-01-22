#pragma once

#include "BattleLogicDef.h"
#include "BattleFightTeam.h"
#include "StrTool.h"
#include "mathTools.h"
#include <map>
#include <vector>

using namespace std;

//技能，buff的基类
class CBattleLogicEffect
{
public:
	CBattleLogicEffect();
	virtual ~CBattleLogicEffect();

	virtual EFFECT_CONDITION_TYPE getCondition() = 0;

	virtual int getType() = 0;

	//小的优先
	virtual int getPriority() = 0;

	virtual CBattleLogicEffect* clone() = 0;

	inline bool checkChangce()
	{
		int rand = gGameTools.rand(0,100);
		return rand < m_chance;
	}

	virtual int active(EFFECT_ACTIVE_CONTEXT& context) = 0;

protected:
	//工具函数
	inline bool checkSrcAlive(EFFECT_ACTIVE_CONTEXT& context)
	{
		if(!context.psrc->isAlive())
		{
			context.control.breakFlag = true;
			return false;
		}
		return true;
	}

	inline bool checkDstAlive(EFFECT_ACTIVE_CONTEXT& context)
	{
		if(!context.pdst->isAlive())
		{
			context.control.breakFlag = true;
			return false;
		}
		return true;
	}

	inline void trySrcDieMsg(EFFECT_ACTIVE_CONTEXT& con)
	{
		if(!con.psrc->isAlive())
		{
			con.mhd.pmsg->addDieAction(con.psrc->idx, con.mhd.isHomeTurn);
			con.control.breakFlag = true;
		}
	}

	inline void tryDstDieMsg(EFFECT_ACTIVE_CONTEXT& con)
	{
		if(!con.pdst->isAlive())
		{
			con.mhd.pmsg->addDieAction(con.pdst->idx, !con.mhd.isHomeTurn);
			con.control.breakFlag = true;
		}
	}

public:
	int m_chance;
};

//普通攻击效果
class CBattleLogicEffectDefaultAttack: public CBattleLogicEffect
{
public:
	virtual int getType(){return 0;}

	virtual EFFECT_CONDITION_TYPE getCondition() {return EFFECT_CONDITION_ATTACK;}

	virtual int getPriority() {return EFFECT_PRIORITY_DEFAULT_DMG;}

	virtual int active(EFFECT_ACTIVE_CONTEXT& con);

	virtual CBattleLogicEffect* clone()
	{
		return new CBattleLogicEffectDefaultAttack;
	}

	int caculateDmg(EFFECT_ACTIVE_CONTEXT& con);
};

class CBattleLogicEffectSkill: public CBattleLogicEffect
{
public:

	enum BUFF_MATCH_CONDITION
	{
		BUFF_MATCH_EFFECT, //按效果type字段匹配
		BUFF_MATCH_SEQ, //按SEQ字段匹配
		BUFF_MATCH_SKILLID, //按技能id匹配 
		BUFF_MATCH_FROMIDX //按照釋放buff的對象idx匹配
	};

	enum BUFF_MATCH_OPTION
	{
		BUFF_MATCH_FILTER_SKILLID_BIGER, //只有skillid大的生效
		BUFF_MATCH_FILTER_SKILLID_BIGER_OR_EQUAL, //skillid>=
		BUFF_MATCH_DISCARD, //丟棄
		BUFF_MATCH_REPLACE, //替換
		BUFF_MATCH_RESET_REMAIN, //重置剩餘次數
		BUFF_MATCH_INCREASE_EFFECTCNT //增加生效次數
	};

	CBattleLogicEffectSkill();
	virtual ~CBattleLogicEffectSkill();

	struct BATTLE_SKILL_CONFIG
	{
		int skillid;
		int skilltype;
		int skillseq;
		int cost;
		vector<string> vparams;
	};

	bool bindSkill(int id);

	static int getTypeById(int id);

	inline bool useEnergy(CBattleUnitLogic* ptarget)
	{
		if(m_config.cost > ptarget->energy)
			return false;

		ptarget->energy -= m_config.cost;
		return true;
	}

protected:
	void addBuff(CBattleUnitLogic* unit, bool unitIsSrc, CBattleUnitLogic::BUFF& buff, EFFECT_ACTIVE_CONTEXT& con,  
		vector<BUFF_MATCH_CONDITION>& conditions, vector<BUFF_MATCH_OPTION>& options, int effectCntMax=1);

	void srcCastBuff(EFFECT_ACTIVE_CONTEXT& con, CBattleUnitLogic::BUFF& newBuff);

protected:
	BATTLE_SKILL_CONFIG m_config;
};

class CBattleLogicEffectBuff: public CBattleLogicEffect
{
public:
	CBattleLogicEffectBuff();
	virtual ~CBattleLogicEffectBuff();

	inline bool bindBuff(CBattleUnitLogic::BUFF* p)
	{
		//检查type必须一致
		if(getType() != p->effectType)
			return false;

		pbuff = p;
		m_chance = 100;
		return true;
	}

protected:
	const CBattleUnitLogic::BUFF* pbuff;
};

//create effect的类
class CBattleLogicEffectFactory
{
public:
	typedef map<int, CBattleLogicEffect*> REGIST_MAP;
public:
	CBattleLogicEffect* createEffectBySkill(int id);
	CBattleLogicEffect* createEffectByBuff(CBattleUnitLogic::BUFF* p);

	void registEffect(CBattleLogicEffect* peffectProto, int which);

	static CBattleLogicEffectFactory* getInstance();

protected:
	static CBattleLogicEffectFactory* m_pinstance;

protected:
	REGIST_MAP m_skills;
	REGIST_MAP m_buffs;
};

//effect按优先级执行
class CBattleLogicEffectManager
{
public:
	CBattleLogicEffectManager();
	~CBattleLogicEffectManager();

	typedef vector<CBattleLogicEffect*> PRIORTY_MAP_ITEM;
	typedef map<int, PRIORTY_MAP_ITEM*> PRIORTY_MAP;

	//p必须是new出来的
	bool addEffect(CBattleLogicEffect* p);

	void executeEffects(EFFECT_ACTIVE_CONTEXT& context);

protected:
	PRIORTY_MAP m_map;
};

//注册helper类
class CBattleLogicEffectRegister
{
public:
	inline CBattleLogicEffectRegister(CBattleLogicEffect* proto, int which)
	{
		CBattleLogicEffectFactory::getInstance()->registEffect(proto, which);
	}
};

#define BATTLE_EFFECT_REGIST_SKILL(className) CBattleLogicEffectRegister gBEReg##className(new className, 0)
#define BATTLE_EFFECT_REGIST_BUFF(className) CBattleLogicEffectRegister gBEReg##className(new className, 1)