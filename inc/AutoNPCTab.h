#pragma once
#include "tconfHelper.h"
class CAutoNPCTab : public CTconfHelper
{
public:
	const char* ID;
	const char* SHOWTYPE;
	const char* ATTRID;
	const char* ATTRPERCENT;
	const char* SKILLS;
	const char* NAME;

	CAutoNPCTab(const char* binFilePath, int colIdx=-1)
	{
		ID="ID";
		SHOWTYPE="ShowType";
		ATTRID="AttrID";
		ATTRPERCENT="AttrPercent";
		SKILLS="Skills";
		NAME="NAME";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(ID)<0) return -1;
		if(getColIdx(SHOWTYPE)<0) return -1;
		if(getColIdx(ATTRID)<0) return -1;
		if(getColIdx(ATTRPERCENT)<0) return -1;
		if(getColIdx(SKILLS)<0) return -1;
		if(getColIdx(NAME)<0) return -1;
		return 0;
	}
};

