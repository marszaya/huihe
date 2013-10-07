#pragma once
#include "tconfHelper.h"
class CAutoItemPackTab : public CTconfHelper
{
public:
	const char* PACKID;
	const char* PACKTYPE;
	const char* ITEM0;
	const char* ITEM1;
	const char* ITEM2;
	const char* ITEM3;
	const char* ITEM4;
	const char* ITEM5;
	const char* ITEM6;
	const char* ITEM7;
	const char* ITEM8;
	const char* ITEM9;

	CAutoItemPackTab(const char* binFilePath, int colIdx=-1)
	{
		PACKID="PackID";
		PACKTYPE="PackType";
		ITEM0="Item0";
		ITEM1="Item1";
		ITEM2="Item2";
		ITEM3="Item3";
		ITEM4="Item4";
		ITEM5="Item5";
		ITEM6="Item6";
		ITEM7="Item7";
		ITEM8="Item8";
		ITEM9="Item9";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(PACKID)<0) return -1;
		if(getColIdx(PACKTYPE)<0) return -1;
		if(getColIdx(ITEM0)<0) return -1;
		if(getColIdx(ITEM1)<0) return -1;
		if(getColIdx(ITEM2)<0) return -1;
		if(getColIdx(ITEM3)<0) return -1;
		if(getColIdx(ITEM4)<0) return -1;
		if(getColIdx(ITEM5)<0) return -1;
		if(getColIdx(ITEM6)<0) return -1;
		if(getColIdx(ITEM7)<0) return -1;
		if(getColIdx(ITEM8)<0) return -1;
		if(getColIdx(ITEM9)<0) return -1;
		return 0;
	}
};

