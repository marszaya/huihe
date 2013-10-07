#include "CCalculagraph.h"
#include <stdio.h>
#include <string.h>

CCUCalculagraph::CCUCalculagraph(void)
{
}

CCUCalculagraph::~CCUCalculagraph(void)
{
}

CCUCalculagraph* CCUCalculagraph::create()
{
	CCUCalculagraph *pRet = new CCUCalculagraph();
	if(pRet && pRet->initCCUCalculagraph())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCUCalculagraph::initCCUCalculagraph()
{
	bool ret=false;
	do{
		reset();
		ret = true;
	}while(0);

	return ret;
}


void CCUCalculagraph::reset()
{
	CCTime::gettimeofdayCocos2d(&m_beginTime, NULL);
}

void CCUCalculagraph::getDt(cc_timeval* dtOut)
{
	cc_timeval tnow;
	CCTime::gettimeofdayCocos2d(&tnow, NULL);
	if(tnow.tv_usec > m_beginTime.tv_usec)
	{
		dtOut->tv_usec = tnow.tv_usec - m_beginTime.tv_usec;
		dtOut->tv_sec = tnow.tv_sec - m_beginTime.tv_sec;
	}
	else
	{
		dtOut->tv_usec = 1000000 + tnow.tv_usec - m_beginTime.tv_usec;
		dtOut->tv_sec = tnow.tv_sec - m_beginTime.tv_sec - 1;
	}
}

string CCUCalculagraph::dtToStr(const cc_timeval* dt)
{
	char buff[64]={0};
	sprintf(buff, "%d.%06d", dt->tv_sec, dt->tv_usec);
	return buff;
}

string CCUCalculagraph::getDtStr()
{
	cc_timeval dt;
	getDt(&dt);
	return dtToStr(&dt);
}