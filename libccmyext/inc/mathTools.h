#pragma once
#include <stdlib.h>

class CMZMathTools
{
protected:
	unsigned int m_rseed;
public:
	CMZMathTools(void);
	~CMZMathTools(void);

public:
	inline int rand(int min, int max)
	{
		return min + randInner()%(max - min + 1);
	}

	inline float randf(float min, float max)
	{
		return min+(max-min)*((float)randInner()/RAND_MAX);
	}

	inline int randAround(int base, unsigned int percent)
	{
		return rand((long long)base*(100-percent)/100, (long long)base*(100+percent)/100);
	}

protected:
	inline int randInner()
	{
		return ((m_rseed=m_rseed*214013L+25310112)>>16)&0x7fff; 
	}


};

extern CMZMathTools gGameTools;
