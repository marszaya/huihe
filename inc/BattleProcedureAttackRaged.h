#pragma once
#include "CActionManager.h"
#include <string>
using namespace std;

class CBattleProcedureAttackRaged:public CCEActionProcedure
{
public:
	CBattleProcedureAttackRaged(void);
	~CBattleProcedureAttackRaged(void);

	static CBattleProcedureAttackRaged* create(void);
	bool initCBattleProcedureAttackRaged(void);

	virtual bool nextStep(int stepToCheck);

public:
	int m_dmg;
	int m_srcTag;
	int m_dstTag;
	string m_bulletConf;	
	int m_skillId;
	bool m_srcDone;
	bool m_dstDone;
	CCPoint m_dstPos;
	CCPoint m_srcPos;
};
