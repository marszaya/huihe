#pragma once
#include "tconfHelper.h"
class CAutoSkillTab : public CTconfHelper
{
public:
	const char* ID;
	const char* SEQ;
	const char* LEVEL;
	const char* TYPE;
	const char* COST;
	const char* CHANCE;
	const char* PARAMS;
	const char* NAME;

	CAutoSkillTab(const char* binFilePath, int colIdx=-1)
	{
		ID="ID";
		SEQ="SEQ";
		LEVEL="LEVEL";
		TYPE="Type";
		COST="Cost";
		CHANCE="Chance";
		PARAMS="Params";
		NAME="NAME";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(ID)<0) return -1;
		if(getColIdx(SEQ)<0) return -1;
		if(getColIdx(LEVEL)<0) return -1;
		if(getColIdx(TYPE)<0) return -1;
		if(getColIdx(COST)<0) return -1;
		if(getColIdx(CHANCE)<0) return -1;
		if(getColIdx(PARAMS)<0) return -1;
		if(getColIdx(NAME)<0) return -1;
		return 0;
	}
};

