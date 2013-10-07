#pragma once

#include "BagWindowBase.h"

class CBagWindowEquip:public CCWindowBase
{
public:
	CBagWindowEquip(void);
	virtual ~CBagWindowEquip(void);

	static CBagWindowEquip* create(int row, int col); 
	bool initCBagWindowEquip(int row, int col);
public:
	CBagWindowBase* m_innerWin;
};
