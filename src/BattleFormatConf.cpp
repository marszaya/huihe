#include "BattleFormatConf.h"
#include "item.pb.h"

CBattleFormatConf* CBattleFormatConf::m_instance = NULL;

CBattleFormatConf* CBattleFormatConf::getSharedInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CBattleFormatConf;
	}

	return m_instance;
}

CBattleFormatConf::CBattleFormatConf()
{
	m_xMax = 2;
	m_yMax = 3;
}

CBattleFormatConf::~CBattleFormatConf()
{
}

//以下实现均写死数字
bool CBattleFormatConf::getEffectByIdx(unsigned int idx, int& effectId, int& effectValue)
{
	bool ret = false;
	do{
		/*
		if(idx == 0 || idx == 3 || idx == 6)
		{
			effectId = Item::EFFECT_SPD;
			effectValue = 50;
		}
		else if(idx == 1 || idx == 4 || idx == 7)
		{
			effectId = Item::EFFECT_SPD;
			effectValue = 20;
		}
		else if(idx == 2  || idx == 5 || idx == 8)
		{
			effectId = Item::EFFECT_ARMOR;
			effectValue = 50;
		}
		else
		{*/
			effectId = Item::EFFECT_NONE;
			effectValue = 0;
			break;
		/*}*/

		ret = true;
	}while(0);
	return ret;
}

void CBattleFormatConf::getIdxesByX(int x, vector<int>& retIdxes)
{
	retIdxes.clear();
	if(m_xMax <= 0 || m_yMax <=0)
		return;
	retIdxes.reserve(m_yMax);
	for(int i=0; i<this->getTotal(); ++i)
	{
		if(i%this->m_xMax == x)
		{
			retIdxes.push_back(i);
		}
	}
}

void CBattleFormatConf::getIdxesByY(int y, vector<int>& retIdxes)
{
	retIdxes.clear();
	retIdxes.reserve(m_yMax);
	if(y == 0)
	{
		retIdxes.push_back(0);
		retIdxes.push_back(1);
		retIdxes.push_back(2);
	}
	else if(y==1)
	{
		retIdxes.push_back(3);
		retIdxes.push_back(4);
		retIdxes.push_back(5);
	}
	else if(y==2)
	{
		retIdxes.push_back(6);
		retIdxes.push_back(7);
		retIdxes.push_back(8);
	}
}
