#pragma once
#include "tconfHelper.h"
class CAutoMapTab : public CTconfHelper
{
public:
	const char* MAPID;
	const char* BATTLES;
	const char* BACKGROUNDID;
	const char* DESC;

	CAutoMapTab(const char* binFilePath, int colIdx=-1)
	{
		MAPID="MapID";
		BATTLES="Battles";
		BACKGROUNDID="BackgroundID";
		DESC="Desc";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(MAPID)<0) return -1;
		if(getColIdx(BATTLES)<0) return -1;
		if(getColIdx(BACKGROUNDID)<0) return -1;
		if(getColIdx(DESC)<0) return -1;
		return 0;
	}
};

