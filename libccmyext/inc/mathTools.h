#pragma once
#include <stdlib.h>
#include <vector>
using namespace std;

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

	void randSelect(unsigned int inputArraySize, vector<int>& outputIdxes, unsigned int max)
	{
		if(max > inputArraySize)
			max = inputArraySize;

		vector<int> inputIdxes;
		inputIdxes.reserve(inputArraySize);
		outputIdxes.clear();
		outputIdxes.reserve(max);

		for(unsigned int a=0; a<inputArraySize; ++a)
		{
			inputIdxes.push_back(a);
		}

		for(unsigned int i=0; i<max; ++i)
		{
			int endPos = inputArraySize-i-1;
			int selectPos = rand(0, endPos);
			int selectIdx = inputIdxes[selectPos];
			inputIdxes[selectPos] = inputIdxes[endPos];

			outputIdxes.push_back(selectIdx);
		}
	}

protected:
	inline int randInner()
	{
		return ((m_rseed=m_rseed*214013L+25310112)>>16)&0x7fff; 
	}


};

extern CMZMathTools gGameTools;
