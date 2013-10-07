#pragma once
#include "tconfHelper.h"
class CAutoExprTab : public CTconfHelper
{
public:
	const char* LEVEL;
	const char* LEVELEXPR;
	const char* BASEEXPR;

	CAutoExprTab(const char* binFilePath, int colIdx=-1)
	{
		LEVEL="Level";
		LEVELEXPR="LevelExpr";
		BASEEXPR="BaseExpr";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(LEVEL)<0) return -1;
		if(getColIdx(LEVELEXPR)<0) return -1;
		if(getColIdx(BASEEXPR)<0) return -1;
		return 0;
	}
};

