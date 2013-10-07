#pragma once
#include "CActionManager.h"

class CBattleProcedureAttack:public CCEActionProcedure
{
public:
	CBattleProcedureAttack(void);
	~CBattleProcedureAttack(void);

	static CBattleProcedureAttack* create(void);
	bool initCBattleProcedureAttack(void);

	virtual bool nextStep(int stepToCheck);

public:
	int m_dmg;
	int m_srcTag;
	int m_dstTag;
	int m_skillId;
	CCPoint m_srcPos;
	CCPoint m_dstPos;
	bool m_srcDone;
	bool m_dstDone;
};
