#pragma once
#include "tconfHelper.h"
class CAutoUnitTab : public CTconfHelper
{
public:
	const char* ID;
	const char* SHOWTYPE;
	const char* BASEHP;
	const char* LEVELUPHP;
	const char* BASEDEF;
	const char* LEVELUPDEF;
	const char* BASEATK;
	const char* LEVELUPATK;
	const char* BASEENERGY;
	const char* SKILLS;
	const char* NAME;

	CAutoUnitTab(const char* binFilePath, int colIdx=-1)
	{
		ID="ID";
		SHOWTYPE="ShowType";
		BASEHP="BaseHp";
		LEVELUPHP="LevelUpHp";
		BASEDEF="BaseDef";
		LEVELUPDEF="LevelUpDef";
		BASEATK="BaseAtk";
		LEVELUPATK="LevelUpAtk";
		BASEENERGY="BaseEnergy";
		SKILLS="Skills";
		NAME="NAME";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(ID)<0) return -1;
		if(getColIdx(SHOWTYPE)<0) return -1;
		if(getColIdx(BASEHP)<0) return -1;
		if(getColIdx(LEVELUPHP)<0) return -1;
		if(getColIdx(BASEDEF)<0) return -1;
		if(getColIdx(LEVELUPDEF)<0) return -1;
		if(getColIdx(BASEATK)<0) return -1;
		if(getColIdx(LEVELUPATK)<0) return -1;
		if(getColIdx(BASEENERGY)<0) return -1;
		if(getColIdx(SKILLS)<0) return -1;
		if(getColIdx(NAME)<0) return -1;
		return 0;
	}
};

