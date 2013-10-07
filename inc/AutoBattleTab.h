#pragma once
#include "tconfHelper.h"
class CAutoBattleTab : public CTconfHelper
{
public:
	const char* BATTLEID;
	const char* UNITS;
	const char* ITEM;
	const char* EXPR;
	const char* GOLD;
	const char* MAPID;
	const char* BACKGROUNDID;
	const char* DESC;

	CAutoBattleTab(const char* binFilePath, int colIdx=-1)
	{
		BATTLEID="BattleID";
		UNITS="Units";
		ITEM="Item";
		EXPR="Expr";
		GOLD="Gold";
		MAPID="MapID";
		BACKGROUNDID="BackGroundID";
		DESC="Desc";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(BATTLEID)<0) return -1;
		if(getColIdx(UNITS)<0) return -1;
		if(getColIdx(ITEM)<0) return -1;
		if(getColIdx(EXPR)<0) return -1;
		if(getColIdx(GOLD)<0) return -1;
		if(getColIdx(MAPID)<0) return -1;
		if(getColIdx(BACKGROUNDID)<0) return -1;
		if(getColIdx(DESC)<0) return -1;
		return 0;
	}
};

