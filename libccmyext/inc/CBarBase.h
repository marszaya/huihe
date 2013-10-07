#pragma once
#include "CWindowBase.h"

class CBarBase:public CCWindowBase
{
public:
	enum BAR_TYPE{
		LEFT_TO_RIGHT,
		RIGHT_TO_LEFT
	};
public:
	CBarBase(void);
	virtual ~CBarBase(void);

	static CBarBase* create(const char* barImg, BAR_TYPE type=LEFT_TO_RIGHT);
	bool initCBarBase(const char* barImg, BAR_TYPE type=LEFT_TO_RIGHT);

	void setPercent(float p);

	//Ä¬ÈÏ¸ñÊ½
	void setTypeLeftToRight();

	void setTypeRightToLeft();

protected:
	CCProgressTimer* m_ppt;
};
