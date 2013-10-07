#pragma once
#include "tconfHelper.h"
class CAutoStrTab : public CTconfHelper
{
public:
	const char* ID;
	const char* V;

	CAutoStrTab(const char* binFilePath, int colIdx=-1)
	{
		ID="ID";
		V="V";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(ID)<0) return -1;
		if(getColIdx(V)<0) return -1;
		return 0;
	}
};

