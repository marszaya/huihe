#pragma once

#include "BattleLogicDef.h"
#include "BattleFightTeam.h"
#include "StrTool.h"
#include "mathTools.h"
#include <map>

using namespace std;

//���ܣ�buff�Ļ���
class CBattleLogicEffect
{
public:
	CBattleLogicEffect();
	virtual ~CBattleLogicEffect();

	virtual EFFECT_CONDITION_TYPE getCondition() = 0;

	virtual int getType() = 0;

	//С������
	virtual int getPriority() = 0;

	virtual CBattleLogicEffect* clone() = 0;

	inline bool checkChangce()
	{
		int rand = gGameTools.rand(0,100);
		return rand < m_chance;
	}

	virtual int active(EFFECT_ACTIVE_CONTEXT& context) = 0;

protected:
	//���ߺ���
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

//��ͨ����Ч��
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
	CBattleLogicEffectSkill();
	virtual ~CBattleLogicEffectSkill();

	struct BATTLE_SKILL_CONFIG
	{
		int skillid;
		int skilltype;
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
	void addBuff(CBattleUnitLogic* unit, bool unitIsSrc, CBattleUnitLogic::BUFF& buff,
		EFFECT_ACTIVE_CONTEXT& con, int overlap);

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
		//���type����һ��
		if(getType() != p->effectType)
			return false;

		pbuff = p;
		m_chance = 100;
		return true;
	}

protected:
	const CBattleUnitLogic::BUFF* pbuff;
};

//create effect����
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

//effect�����ȼ�ִ��
class CBattleLogicEffectManager
{
public:
	CBattleLogicEffectManager();
	~CBattleLogicEffectManager();

	typedef map<int, CBattleLogicEffect*> PRIORTY_MAP;

	//p������new������
	bool addEffect(CBattleLogicEffect* p);

	void executeEffects(EFFECT_ACTIVE_CONTEXT& context);

protected:
	PRIORTY_MAP m_map;
};

//ע��helper��
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