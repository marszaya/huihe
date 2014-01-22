#include "BattleProcedureAttack.h"
#include "BattleMap.h"
#include "MyControl.h"

CBattleProcedureAttack::CBattleProcedureAttack(void)
{
	m_srcDone = false;
	m_dstDone = false;
}

CBattleProcedureAttack::~CBattleProcedureAttack(void)
{
}

CBattleProcedureAttack* CBattleProcedureAttack::create()
{
	CBattleProcedureAttack *pRet = new CBattleProcedureAttack();
	if(pRet && pRet->initCBattleProcedureAttack())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleProcedureAttack::initCBattleProcedureAttack()
{
	bool ret=false;
	do{
		m_srcDone = false;
		m_dstDone = false;
		ret = true;
	}while(0);

	return ret;
}

bool CBattleProcedureAttack::nextStep(int stepToCheck)
{
	if(!this->m_weekpManager)
	{
		return false;;
	}

	CBattleWindowMap* pMap = dynamic_cast<CBattleWindowMap*>(m_weekpManager);
	if(!pMap)
	{
		return false;;
	}

	//for short
	int srcTag = this->srcInfo.tagId;
	CCPoint srcPos(this->srcInfo.x, this->srcInfo.y);
	CCPoint dstPos(dstInfos[0].x, dstInfos[0].y); //只移動到第一個目標

	if(stepToCheck == 0)
	{
		//开始步骤，移动到目标
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 1);
		
		CBattleFightUnit* punit = pMap->getFightUnit(srcTag);
		if(punit)
		{
			punit->paramForNextCall(param);
			punit->actionMoveToPos(dstPos);
		}
		
		param->release();
	}
	else if(stepToCheck == 1)
	{
		//攻击
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 2);
		CBattleFightUnit* punit = pMap->getFightUnit(srcTag);
		if(punit)
		{
			punit->paramForNextCall(param);
			punit->actionDoAttack(this->skillId);
		}
		param->release();
	}
	else if(stepToCheck == 2)
	{
		//返回初始位置
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 3);
		CBattleFightUnit* punit = pMap->getFightUnit(srcTag);
		if(punit)
		{
			punit->getFightUnit()->changeFlip();
			punit->paramForNextCall(param);
			punit->actionMoveToPos(srcPos);
		}
		param->release();

		//对方造成伤害
		for(unsigned int di=0; di<this->dstInfos.size(); ++di)
		{
			CCEActionParam* param2 = new CCEActionParam(m_procedureTag , 10+di);
			CBattleFightUnit* punit2 = pMap->getFightUnit(this->dstInfos[di].tagId);
			if(punit2)
			{
				punit2->paramForNextCall(param2);
				punit2->actionShowDmg(this->dstInfos[di].dmg);
			}
			param2->release();
		}
	}
	else if(stepToCheck == 3)
	{
		//待机，结束
		CBattleFightUnit* punit = pMap->getFightUnit(srcTag);
		if(punit)
		{
			punit->getFightUnit()->changeFlip();
			punit->getFightUnit()->stay();
		}

		m_srcDone = true;
		if(m_srcDone && m_dstDone) 
		{
			return false;
		}
	}
	else if(stepToCheck >= 10) //目標只要一個結束就可以
	{
		m_dstDone = true;
		if(m_srcDone && m_dstDone)
		{
			return false;
		}
	}

	return true;
}

