#pragma once
//#include "CWindowBase.h"
#include "CActionManager.h"
#include "FightUnit.h"
#include "CBarBase.h"

class CBattleUnitLogic;

class CBattleFightUnit: public CCEActionNode
{
public:
	CBattleFightUnit(void);
	virtual ~CBattleFightUnit(void);

	static CBattleFightUnit* create(int unitid);
	bool initCBattleFightUnit(int unitid);

	void initExt(int x, int y, bool flip, CBattleUnitLogic* pdata, int speed)
	{
		m_x = x;
		m_y = y;
		m_flip = flip;
		if(m_fightUnit)
		{
			m_fightUnit->setFlip(m_flip);
			m_fightUnit->stay(speed);
		}
		m_pdata = pdata;
	}

	inline CFightUnit* getFightUnit()
	{
		return m_fightUnit;
	}

	bool isDead();

	//actionXXX functions should call CActionNode::callAction
	void actionMoveToPos(CCPoint pos);
	void actionDoAttack(int skillId);
	void actionShowDmg(int dmg);
	void actionDelay(float dt);
	
	void updateHp();

	void callbackHideDmgLabel();
	void callbackRemoveEffect(CCObject* p);

protected:
	void addDmgNumber(int dmg, float duration);
	void addEffect(int effectid, float& durationOut);

protected:
	CFightUnit* m_fightUnit;
	CCObject* m_actionParam;
	CBarBase* m_hpbar;
	int m_hpbarLableTag;
	CBattleUnitLogic* m_pdata;

public:
	int m_x;
	int m_y;
	bool m_flip;
	int m_dmgTag;
	int m_spd;
};