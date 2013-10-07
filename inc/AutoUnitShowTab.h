#pragma once
#include "tconfHelper.h"
class CAutoUnitShowTab : public CTconfHelper
{
public:
	const char* SHOWTYPE;
	const char* RANGED;
	const char* BULLET;

	CAutoUnitShowTab(const char* binFilePath, int colIdx=-1)
	{
		SHOWTYPE="ShowType";
		RANGED="Ranged";
		BULLET="Bullet";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(SHOWTYPE)<0) return -1;
		if(getColIdx(RANGED)<0) return -1;
		if(getColIdx(BULLET)<0) return -1;
		return 0;
	}
};

