#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "role.pb.h"
#include "BattleFightMsg.h"

using namespace std;

//������
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

	//�Ƿ�����ж�
	inline bool isAlive()
	{
		return alive;
	}

	inline void setAlive(bool v)
	{
		alive = v;
	}

	//�Ƿ��ж���
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

	int idx; //�����ѯ

	int tagId; //�����ֶ�ʹ�ã�����˲��õ�

protected:
	bool alive;
	bool acted;
	int location; //λ��	
};

//����
class CBattleTeamLogic
{
public:
	CBattleTeamLogic();
	~CBattleTeamLogic();

	//idx��λ������
	//����ֵ: NULL=ʧ��
	CBattleUnitLogic* setUnitByRole(unsigned int idx, Role* p, BattleTeam* pteam);
	CBattleUnitLogic* setUnitByConf(unsigned int idx, const char* npcID, BattleTeam* pteam);

	//�Ƿ��Ѿ����
	bool checkFail();

	//�Ѿ��ĳɷ�cd�Ļغ�����
	//int selectMinCdUnit(int& retMinCd);
	//void updateCd(int cd);

	inline CBattleUnitLogic* unitAt(unsigned int idx)
	{
		if(idx >=(unsigned int)m_unitsLen)
			return NULL;
		else
			return m_units[idx];
	}

	//��ǰ�ŵ�֮һ
	CBattleUnitLogic* randomFront();

	//�¸������ж��ĵ�λ
	CBattleUnitLogic* nextActUnit();

	//������е�λ���ж���־
	void clearAct();

protected:
	CBattleUnitLogic** m_units;
	int m_unitsLen;
};
