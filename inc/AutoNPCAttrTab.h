#pragma once
#include "tconfHelper.h"
class CAutoNPCAttrTab : public CTconfHelper
{
public:
	const char* ID;
	const char* HP;
	const char* ATK;
	const char* DEF;
	const char* SPD;
	const char* ENERGY;

	CAutoNPCAttrTab(const char* binFilePath, int colIdx=-1)
	{
		ID="ID";
		HP="HP";
		ATK="ATK";
		DEF="DEF";
		SPD="SPD";
		ENERGY="ENERGY";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(ID)<0) return -1;
		if(getColIdx(HP)<0) return -1;
		if(getColIdx(ATK)<0) return -1;
		if(getColIdx(DEF)<0) return -1;
		if(getColIdx(SPD)<0) return -1;
		if(getColIdx(ENERGY)<0) return -1;
		return 0;
	}
};

