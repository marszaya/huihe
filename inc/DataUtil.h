#pragma once
#include "MyData.h"
#include "tconfManager.h"

class CDataUtil
{
public:
	static bool getItemFromConfStr(const char* confStr, ItemSet* pitemOutput);
	//config functions
	static int getEquipAttrIdx(int subtype);
	static int getEquipAttrValue(int subtype, int level);
	static int getEffectType(int subtype);
	static int getEffectValue(int subtype);
	static int getSellPrice(int subtype);
	static int getMajorType(int subtype);
};