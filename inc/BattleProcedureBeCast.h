#pragma once
#include "CActionManager.h"

class CBattleProcedureBeCast:public CCEActionProcedure
{
public:
	CBattleProcedureBeCast(void);
	~CBattleProcedureBeCast(void);

	static CBattleProcedureBeCast* create(void);
	bool initCBattleProcedureBeCast(void);

	virtual bool nextStep(int stepToCheck);

public:
	int m_dmg;
	int m_tag;
	int m_skillId;
};
