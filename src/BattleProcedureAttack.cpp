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

	if(stepToCheck == 0)
	{
		//��ʼ���裬�ƶ���Ŀ��
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 1);
		
		CBattleFightUnit* punit = pMap->getFightUnit(this->m_srcTag);
		if(punit)
		{
			punit->paramForNextCall(param);
			punit->actionMoveToPos(this->m_dstPos);
		}
		
		param->release();
	}
	else if(stepToCheck == 1)
	{
		//����
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 2);
		CBattleFightUnit* punit = pMap->getFightUnit(this->m_srcTag);
		if(punit)
		{
			punit->paramForNextCall(param);
			punit->actionDoAttack(this->m_skillId);
		}
		param->release();
	}
	else if(stepToCheck == 2)
	{
		//���س�ʼλ��
		CCEActionParam* param = new CCEActionParam(m_procedureTag , 3);
		CBattleFightUnit* punit = pMap->getFightUnit(this->m_srcTag);
		if(punit)
		{
			punit->getFightUnit()->changeFlip();
			punit->paramForNextCall(param);
			punit->actionMoveToPos(this->m_srcPos);
		}
		param->release();
		//�Է�����˺�
		CCEActionParam* param2 = new CCEActionParam(m_procedureTag , 11);
		CBattleFightUnit* punit2 = pMap->getFightUnit(this->m_dstTag);
		if(punit2)
		{
			punit2->paramForNextCall(param2);
			punit2->actionShowDmg(this->m_dmg);
		}
		param2->release();
	}
	else if(stepToCheck == 3)
	{
		//����������
		CBattleFightUnit* punit = pMap->getFightUnit(this->m_srcTag);
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
	else if(stepToCheck == 11)
	{
		//�ܻ������
		CBattleFightUnit* punit = pMap->getFightUnit(this->m_dstTag);
		if(punit)
		{
			if(punit->isDead())
			{
				//���˾�ɾ��
				pMap->removeFightUnit(this->m_dstTag);
			}
		}

		m_dstDone = true;
		if(m_srcDone && m_dstDone)
		{
			return false;
		}
	}

	return true;
}

