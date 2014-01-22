#include "BattleProcedureAttackRaged.h"
#include "BattleMap.h"
#include "MyControl.h"

CBattleProcedureAttackRaged::CBattleProcedureAttackRaged(void)
{
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

	//for short
	int srcTag = this->srcInfo.tagId;
	CCPoint srcPos(this->srcInfo.x, this->srcInfo.y);

	if(stepToCheck == 0)
	{
		//开始步骤，攻击
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 1);
		
		CBattleFightUnit* punit = pMap->getFightUnit(srcTag);
		if(punit)
		{
			punit->paramForNextCall(param);
			punit->actionDoAttack(this->skillId);
		}
		
		param->release();
	}
	else if(stepToCheck == 1)
	{
		//发出子弹,多個目標
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 2);
		CBattleFightUnit* punit = pMap->getFightUnit(srcTag);
		if(punit)
		{
			punit->getFightUnit()->stay();
			float dt=0.1;//初始值保险
			for(unsigned int di=0; di<this->dstInfos.size(); ++di)
			{
				CCPoint dstPos(dstInfos[di].x, dstInfos[di].y);
				pMap->showBullets(this->bulletConf.c_str(), srcPos, dstPos, &dt);
			}
			
			punit->paramForNextCall(param);
			punit->actionDelay(dt);
		}
		param->release();
	}
	else if(stepToCheck == 2)
	{
		//受到攻擊方
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
	else if(stepToCheck >= 10)
	{
		return false;
	}

	return true;
}

