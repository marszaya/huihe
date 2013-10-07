#pragma once
#include "tconfHelper.h"
class CAutoSkillTab : public CTconfHelper
{
public:
	const char* ID;
	const char* TYPE;
	const char* PARAMS;
	const char* NAME;

	CAutoSkillTab(const char* binFilePath, int colIdx=-1)
	{
		ID="ID";
		TYPE="Type";
		PARAMS="Params";
		NAME="NAME";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(ID)<0) return -1;
		if(getColIdx(TYPE)<0) return -1;
		if(getColIdx(PARAMS)<0) return -1;
		if(getColIdx(NAME)<0) return -1;
		return 0;
	}
};

