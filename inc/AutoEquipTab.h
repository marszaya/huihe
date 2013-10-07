#pragma once
#include "tconfHelper.h"
class CAutoEquipTab : public CTconfHelper
{
public:
	const char* SUBTYPE;
	const char* POSITON;
	const char* ATTRIDX;
	const char* ATTRVALUE;
	const char* ATTRLEVELUPVALUE;

	CAutoEquipTab(const char* binFilePath, int colIdx=-1)
	{
		SUBTYPE="SubType";
		POSITON="Positon";
		ATTRIDX="AttrIdx";
		ATTRVALUE="AttrValue";
		ATTRLEVELUPVALUE="AttrLevelupValue";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(SUBTYPE)<0) return -1;
		if(getColIdx(POSITON)<0) return -1;
		if(getColIdx(ATTRIDX)<0) return -1;
		if(getColIdx(ATTRVALUE)<0) return -1;
		if(getColIdx(ATTRLEVELUPVALUE)<0) return -1;
		return 0;
	}
};

