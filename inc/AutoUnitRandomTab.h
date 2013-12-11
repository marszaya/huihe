#pragma once
#include "tconfHelper.h"
class CAutoUnitRandomTab : public CTconfHelper
{
public:
	const char* ID;
	const char* GOLD;
	const char* ITEMS;
	const char* RANDOMSET;
	const char* WEIGHT;

	CAutoUnitRandomTab(const char* binFilePath, int colIdx=-1)
	{
		ID="ID";
		GOLD="Gold";
		ITEMS="Items";
		RANDOMSET="RandomSet";
		WEIGHT="Weight";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(ID)<0) return -1;
		if(getColIdx(GOLD)<0) return -1;
		if(getColIdx(ITEMS)<0) return -1;
		if(getColIdx(RANDOMSET)<0) return -1;
		if(getColIdx(WEIGHT)<0) return -1;
		return 0;
	}
};

