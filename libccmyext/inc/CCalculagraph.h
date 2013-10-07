#pragma once

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class CCUCalculagraph:public CCObject
{
public:
	CCUCalculagraph(void);
	virtual ~CCUCalculagraph(void);

	static CCUCalculagraph* create();
	bool initCCUCalculagraph();

public:
	void reset();

	void getDt(cc_timeval* dtOut);

	string getDtStr();

	static string dtToStr(const cc_timeval* dt);

protected:
	cc_timeval m_beginTime;
};
