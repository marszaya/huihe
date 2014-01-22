#pragma once

#include "BattleFightTeam.h"

class CBattleMapAttackInfo
{
public:
	int tagId;
	float x;
	float y;
	int dmg;

	inline void set(int t, float ax, float ay, int d)
	{
		tagId = t;
		x = ax;
		y = ay;
		dmg = d;
	}
};