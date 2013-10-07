#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "role.pb.h"
#include "BattleFightMsg.h"

using namespace std;

//单个将
class CBattleUnitLogic
{
public:
	static const int MAX_SPEED=1000000;

public:
	CBattleUnitLogic();
	virtual ~CBattleUnitLogic();

	inline void setParam(int ahp, int aatk, int adef, int aspd, int aenergy, int ashow)
	{
		hp = ahp;
		atk = aatk;
		def = adef;
		spd = aspd;
		hpmax = hp;
		energy = aenergy;
		showtype = ashow;
		alive = true;
		acted = false;
		resetCd();
	}

	inline void addSkill(int skillid)
	{
		skills.push_back(skillid);
	}

	//是否可以行动
	inline bool isAlive()
	{
		return alive;
	}

	inline void setAlive(bool v)
	{
		alive = v;
	}

	//是否行动过
	inline bool isActed()
	{
		return acted;
	}

	inline void setActed(bool v)
	{
		acted = v;
	}

	inline void resetCd()
	{
		cd = MAX_SPEED/spd;
		if(cd == 0)
			cd=1;
	}

	inline void setLocation(int v)
	{
		location = v;
	}

	inline int getLocation()
	{
		return location;
	}

public:
	int showtype;
	int hp;
	int hpmax;
	int atk;
	int def;
	int spd;
	int cd;
	int energy;
	vector<int> skills;

	int idx; //方便查询

	int tagId; //仅表现端使用，计算端不用的

protected:
	bool alive;
	bool acted;
	int location; //位置	
};

//队伍
class CBattleTeamLogic
{
public:
	CBattleTeamLogic();
	~CBattleTeamLogic();

	//idx是位置索引
	//返回值: NULL=失败
	CBattleUnitLogic* setUnitByRole(unsigned int idx, Role* p, BattleTeam* pteam);
	CBattleUnitLogic* setUnitByConf(unsigned int idx, const char* npcID, BattleTeam* pteam);

	//是否已经输掉
	bool checkFail();

	//已经改成非cd的回合制了
	//int selectMinCdUnit(int& retMinCd);
	//void updateCd(int cd);

	inline CBattleUnitLogic* unitAt(unsigned int idx)
	{
		if(idx >=(unsigned int)m_unitsLen)
			return NULL;
		else
			return m_units[idx];
	}

	//最前排的之一
	CBattleUnitLogic* randomFront();

	//下个可以行动的单位
	CBattleUnitLogic* nextActUnit();

	//清除所有单位的行动标志
	void clearAct();

protected:
	CBattleUnitLogic** m_units;
	int m_unitsLen;
};
