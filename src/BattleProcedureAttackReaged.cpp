#include "BattleProcedureAttackRaged.h"
#include "BattleMap.h"
#include "MyControl.h"



CBattleProcedureAttackRaged::CBattleProcedureAttackRaged(void)
{
	m_srcDone = false;
	m_dstDone = false;
}

CBattleProcedureAttackRaged::~CBattleProcedureAttackRaged(void)
{
}

CBattleProcedureAttackRaged* CBattleProcedureAttackRaged::create()
{
	CBattleProcedureAttackRaged *pRet = new CBattleProcedureAttackRaged();
	if(pRet && pRet->initCBattleProcedureAttackRaged())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleProcedureAttackRaged::initCBattleProcedureAttackRaged()
{
	bool ret=false;
	do{
		m_srcDone = false;
		m_dstDone = false;
		ret = true;
	}while(0);

	return ret;
}

bool CBattleProcedureAttackRaged::nextStep(int stepToCheck)
{
	if(!this->m_weekpManager)
	{
		return false;
	}

	CBattleWindowMap* pMap = dynamic_cast<CBattleWindowMap*>(m_weekpManager);
	if(!pMap)
	{
		return false;
	}

	if(stepToCheck == 0)
	{
		//开始步骤，攻击
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 1);
		
		CBattleFightUnit* punit = pMap->getFightUnit(this->m_srcTag);
		if(punit)
		{
			punit->paramForNextCall(param);
			punit->actionDoAttack(this->m_skillId);
		}
		
		param->release();
	}
	else if(stepToCheck == 1)
	{
		//发出子弹
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 2);
		CBattleFightUnit* punit = pMap->getFightUnit(this->m_srcTag);
		if(punit)
		{
			punit->getFightUnit()->stay();
			float dt=0.1;//初始值保险
			pMap->showBullets(m_bulletConf.c_str(), m_srcPos, m_dstPos, &dt);
			punit->paramForNextCall(param);
			punit->actionDelay(dt);
		}
		param->release();
	}
	else if(stepToCheck == 2)
	{
		CCEActionParam* param2 = new CCEActionParam(m_procedureTag , 11);
		CBattleFightUnit* punit2 = pMap->getFightUnit(this->m_dstTag);
		if(punit2)
		{
			punit2->paramForNextCall(param2);
			punit2->actionShowDmg(this->m_dmg);
		}
		param2->release();

		m_srcDone = true;
		if(m_srcDone && m_dstDone)
		{
			return false;
		}
	}
	else if(stepToCheck == 11)
	{
		m_dstDone = true;
		if(m_srcDone && m_dstDone)
		{
			return false;
		}
	}

	return true;
}

