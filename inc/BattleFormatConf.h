#pragma once

#include <vector>

using namespace std;
 

/*
* 战斗相关的帮助类
*/
class CBattleFormatConf
{
public:
	CBattleFormatConf();
	~CBattleFormatConf();

	static CBattleFormatConf* getSharedInstance();

	inline int getXMax()
	{
		return m_xMax;
	}

	inline int getYMax()
	{
		return m_yMax;
	}

	inline int getTotal()
	{
		return m_xMax*m_yMax;
	}

	inline int getIdxByXY(unsigned int x, unsigned int y)
	{
		return x + y * m_xMax;
	}

	inline int getYByIdx(unsigned int idx)
	{
		return idx / m_xMax;
	}

	inline int getXByIdx(unsigned int idx)
	{
		return idx % m_xMax;
	}

	bool getEffectByIdx(unsigned int idx, int& effectId, int& effectValue);

	void getIdxesByX(int x, vector<int>& retIdxes); 
	void getIdxesByY(int y, vector<int>& retIdxes); 

protected:
	static CBattleFormatConf* m_instance;

	int m_xMax;
	int m_yMax;
};