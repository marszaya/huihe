#pragma once

#include "CWindowBase.h"
#include <string>

using namespace std;

class CBattleSkillName:public CCWindowBase
{
public:
	CBattleSkillName(void);
	virtual ~CBattleSkillName(void);

	static CBattleSkillName* create(int skillId);
	bool initCBattleSkillName(int skillId);

	bool addToWindow(CCWindowBase* parentWin, float dt);

protected:
	int m_skillId;
	string m_skillName;
};
