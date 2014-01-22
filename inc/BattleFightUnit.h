#pragma once
//#include "CWindowBase.h"
#include "tconfManager.h"
#include "CActionManager.h"
#include "FightUnit.h"
#include "CBarBase.h"
#include <string>
#include "CSlideWindow.h"
#include "StrTool.h"
using namespace std;

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
		updateHp();
		updateEnergy();
	}

	inline CFightUnit* getFightUnit()
	{
		return m_fightUnit;
	}

	//actionXXX functions should call CActionNode::callAction
	void actionMoveToPos(CCPoint pos);
	void actionDoAttack(int skillId);
	void actionShowDmg(int dmg, int skillId=-1);
	void actionDelay(float dt);
	void actionEffect(int effectid);

	void addBuffIcon(int id, int iconid, int effectCnt);
	void delBuffIcon(int id);
	
	void updateHp();
	void updateEnergy();

	void callbackHideDmgLabel();
	void callbackRemoveEffect(CCObject* p);

protected:
	void addDmgNumber(int dmg, float duration);
	void addEffect(int effectid, float& durationOut);
	void addSkillName(int skillid, float duration);

protected:
	CFightUnit* m_fightUnit;
	CCObject* m_actionParam;
	CBarBase* m_hpbar;
	CBarBase* m_energyBar;
	int m_hpbarLableTag;
	int m_energyLableTag;
	CBattleUnitLogic* m_pdata;
	CCESlideWindow* m_pslide;

public:
	int m_x;
	int m_y;
	bool m_flip;
	int m_dmgTag;
	int m_spd;
};