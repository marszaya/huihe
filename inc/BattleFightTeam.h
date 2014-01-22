#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include "role.pb.h"
#include "BattleFightMsg.h"

using namespace std;

//������
class CBattleUnitLogic
{
public:
	static const int MAX_SPEED=1000000;
	static const int MAX_BUFF_PARAM=10;
	static int ID_COUNTER;

	struct BUFF
	{
		int id; //��һ�o����id
		int fromIdx; //ʹ��msg��ת������idx	
		int fromSkillSeq; //���ǂ�����seq���ɵ�
		int fromSkillID; //���ǂ�����Id���ɵ�
		int remainCnt; //ʣ�������-1=����
		int usedCnt; //ʹ�ù�����
		int effectCnt; //�ۼ�Ч��
		int effectType; //Ч������
		int param[MAX_BUFF_PARAM]; //�ɱ����

		inline BUFF()
		{
			fromIdx = -1;
			id = 0;
			fromSkillID = 0;
			fromSkillSeq = 0;
			remainCnt = -1;
			usedCnt = 0;
			effectType = 0;
			effectCnt = 0;
			memset(param,0, sizeof(param));
		}

		inline void updateCnt(int cnt=1)
		{
			if(remainCnt >= cnt)
			{
				remainCnt -= cnt;
				if(remainCnt < 0)
					remainCnt = 0;
			}

			usedCnt += cnt;
		}

		inline bool isEnd()
		{
			return remainCnt==0;
		}

		inline void assignID()
		{
			this->id = (++ID_COUNTER);
		}
	};

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

	inline void dealDmg(int dmg)
	{
		if(hp > dmg)
			hp -= dmg;
		else
		{
			hp = 0;
			alive = false;
		}
	}

public:
	typedef list<BUFF> TYPE_BUFF_LIST;

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
	TYPE_BUFF_LIST buffs;

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
	int randomTarget(int targetType, vector<CBattleUnitLogic*>& output);

	//�¸������ж��ĵ�λ
	CBattleUnitLogic* nextActUnit();

	//������е�λ���ж���־
	void clearAct();

	bool hasUnacted();

public:
	CBattleUnitLogic** m_units;
	int m_unitsLen;
};
