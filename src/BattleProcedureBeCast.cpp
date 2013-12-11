#include "BattleProcedureBeCast.h"
#include "BattleMap.h"
#include "MyControl.h"

CBattleProcedureBeCast::CBattleProcedureBeCast(void)
{
}

CBattleProcedureBeCast::~CBattleProcedureBeCast(void)
{
}

CBattleProcedureBeCast* CBattleProcedureBeCast::create()
{
	CBattleProcedureBeCast *pRet = new CBattleProcedureBeCast();
	if(pRet && pRet->initCBattleProcedureBeCast())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleProcedureBeCast::initCBattleProcedureBeCast()
{
	bool ret=false;
	do{
		ret = true;
	}while(0);

	return ret;
}

bool CBattleProcedureBeCast::nextStep(int stepToCheck)
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

	if(stepToCheck == 0)
	{
		//开始步骤，移动到目标
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 1);
		
		CBattleFightUnit* punit = pMap->getFightUnit(this->m_tag);
		if(punit)
		{
			punit->paramForNextCall(param);
			punit->actionShowDmg(m_dmg, m_skillId);
		}
		
		param->release();
	}
	else if(stepToCheck == 1)
	{
		//完成
		return false;
	}

	return true;
}

