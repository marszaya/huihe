#pragma once
#include "tconfHelper.h"
class CAutoUnitBuyTab : public CTconfHelper
{
public:
	const char* ID;
	const char* GOLD;
	const char* ITEMS;
	const char* WHERE;
	const char* LIMITS;

	CAutoUnitBuyTab(const char* binFilePath, int colIdx=-1)
	{
		ID="ID";
		GOLD="Gold";
		ITEMS="Items";
		WHERE="Where";
		LIMITS="limits";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(ID)<0) return -1;
		if(getColIdx(GOLD)<0) return -1;
		if(getColIdx(ITEMS)<0) return -1;
		if(getColIdx(WHERE)<0) return -1;
		if(getColIdx(LIMITS)<0) return -1;
		return 0;
	}
};

