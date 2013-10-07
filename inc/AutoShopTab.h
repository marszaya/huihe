#pragma once
#include "tconfHelper.h"
class CAutoShopTab : public CTconfHelper
{
public:
	const char* SHOPID;
	const char* PAYTYPE;
	const char* PRICESHOW;
	const char* PRICEREAL;
	const char* ITEMTYPE;
	const char* ITEMNUM;
	const char* LIMIT;

	CAutoShopTab(const char* binFilePath, int colIdx=-1)
	{
		SHOPID="ShopID";
		PAYTYPE="PayType";
		PRICESHOW="PriceShow";
		PRICEREAL="PriceReal";
		ITEMTYPE="ItemType";
		ITEMNUM="ItemNum";
		LIMIT="Limit";
		init(binFilePath, colIdx);
	}

	virtual int selfCheck()
	{
		if(getColIdx(SHOPID)<0) return -1;
		if(getColIdx(PAYTYPE)<0) return -1;
		if(getColIdx(PRICESHOW)<0) return -1;
		if(getColIdx(PRICEREAL)<0) return -1;
		if(getColIdx(ITEMTYPE)<0) return -1;
		if(getColIdx(ITEMNUM)<0) return -1;
		if(getColIdx(LIMIT)<0) return -1;
		return 0;
	}
};

