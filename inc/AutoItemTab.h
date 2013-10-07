#pragma once
#include "tconfHelper.h"
class CAutoItemTab : public CTconfHelper
{
public:
	const char* SUBTYPE;
	const char* MAJORTYPE;
	const char* COUNTABLE;
	const char* SELLPRICE;
	const char* USAGETYPE;
	const char* USAGEPARAM;
	const char* NAME;
	const char* DESC;

	CAutoItemTab(const char* binFilePath, int colIdx=-1)
	{
		SUBTYPE="SubType";
		MAJORTYPE="MajorType";
		COUNTABLE="Countable";
		SELLPRICE="SellPrice";
		USAGETYPE="UsageType";
		USAGEPARAM="UsageParam";
		NAME="Name";
		DESC="Desc";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(SUBTYPE)<0) return -1;
		if(getColIdx(MAJORTYPE)<0) return -1;
		if(getColIdx(COUNTABLE)<0) return -1;
		if(getColIdx(SELLPRICE)<0) return -1;
		if(getColIdx(USAGETYPE)<0) return -1;
		if(getColIdx(USAGEPARAM)<0) return -1;
		if(getColIdx(NAME)<0) return -1;
		if(getColIdx(DESC)<0) return -1;
		return 0;
	}
};

