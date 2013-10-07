#include "BattleFightTeam.h"
#include "mathTools.h"
#include "DataUtil.h"
#include "StrTool.h"
#include "BattleFormatConf.h"
#include "tconfManager.h"
#include "STRTABLE.h"

CBattleUnitLogic::CBattleUnitLogic()
{
}

CBattleUnitLogic::~CBattleUnitLogic()
{
}

CBattleTeamLogic::CBattleTeamLogic()
{
	m_unitsLen = CBattleFormatConf::getSharedInstance()->getTotal();
	m_units = new CBattleUnitLogic* [m_unitsLen];
	for(int i=0; i<m_unitsLen; ++i)
	{
		m_units[i] = NULL;
	}
}

CBattleTeamLogic::~CBattleTeamLogic()
{
	if(m_units)
	{
		for(int i=0; i<m_unitsLen; ++i)
		{
			if(m_units[i] != NULL)
			{
				delete m_units[i];
				m_units[i] = NULL;
			}
		}
		delete[] m_units;
		m_units = NULL;
	}
}


CBattleUnitLogic* CBattleTeamLogic::setUnitByRole(unsigned int idx, Role* p, BattleTeam* pteam)
{
	CBattleUnitLogic* ret =NULL;
	do{
		if(idx >= m_unitsLen)
			break;

		//不允许重复设置
		if(m_units[idx]!=NULL)
			break;

		CBattleUnitLogic* punit = new CBattleUnitLogic();
		if(!punit)
			break;

		punit->setParam(p->battr().hp(), p->battr().ad(), p->battr().arm(), p->battr().as(),
			p->battr().energy(), p->showtype());
		//目前location=idx，方便
		punit->setLocation(idx);
		punit->idx = idx;
		if(p->has_skill())
		{
			for(int i=0; i<p->skill().ids_size(); ++i)
			{
				punit->addSkill(p->skill().ids(i));
			}
		}

		m_units[idx] = punit;

		//发送消息
		if(pteam)
		{
			BattleUnit* pmsgunit = pteam->add_units();
			pmsgunit->set_idx(punit->idx);
			pmsgunit->set_posidx(punit->getLocation());
			pmsgunit->mutable_roleinfo()->CopyFrom(*p);
		}

		ret = punit;
	}while(0);
	return ret;
}

CBattleUnitLogic* CBattleTeamLogic::setUnitByConf(unsigned int idx,const char* npcID, BattleTeam* pteam)
{
	CBattleUnitLogic* ret = NULL;
	do{
		if(idx >= m_unitsLen)
			break;

		//不允许重复设置
		if(m_units[idx]!=NULL)
			break;

		CAutoNPCTab* confNpcTable = TCONF_GET(CAutoNPCTab);
		if(!confNpcTable)
			break;

		CAutoNPCAttrTab* confNpcAttrTable = TCONF_GET(CAutoNPCAttrTab);
		if(!confNpcAttrTable)
			break;

		const TconfRow* pnpcRow = confNpcTable->getRowByKey(npcID);
		if(!pnpcRow)
			break;

		const TconfRow* pnpcAttrRow = confNpcAttrTable->getRowByKey(
			confNpcTable->getRowValue(pnpcRow, confNpcTable->ATTRID));
		if(!pnpcAttrRow)
			break;

		CBattleUnitLogic* punit = new CBattleUnitLogic();
		if(!punit)
			break;

		punit->	setParam(
			atoi(confNpcAttrTable->getRowValue(pnpcAttrRow, confNpcAttrTable->HP)),
			atoi(confNpcAttrTable->getRowValue(pnpcAttrRow, confNpcAttrTable->ATK)),
			atoi(confNpcAttrTable->getRowValue(pnpcAttrRow, confNpcAttrTable->DEF)),
			atoi(confNpcAttrTable->getRowValue(pnpcAttrRow, confNpcAttrTable->SPD)),
			atoi(confNpcAttrTable->getRowValue(pnpcAttrRow, confNpcAttrTable->ENERGY)),
			atoi(confNpcTable->getRowValue(pnpcRow, confNpcTable->SHOWTYPE))
		);

		//目前location=idx，方便
		punit->setLocation(idx);
		punit->idx = idx;

		const char* skillstr = confNpcTable->getRowValue(pnpcRow, confNpcTable->SKILLS);
		if(skillstr == NULL)
			break;

		vector<string> vskillout;
		CStrTool::split(skillstr, ",", vskillout);
		for(unsigned int i=0; i<vskillout.size(); ++i)
		{
			if(atoi(vskillout[i].c_str()) > 0)
				punit->addSkill(atoi(vskillout[i].c_str()));
		}

		m_units[idx] = punit;

		//发送消息
		if(pteam)
		{
			BattleUnit* pmsgunit = pteam->add_units();
			pmsgunit->set_idx(punit->idx);
			pmsgunit->set_posidx(punit->getLocation());
			//make role
			Role theRole;
			BattleAttr* pba = theRole.mutable_battr();
			Identity* pid = theRole.mutable_id();
			BattleSkill* pskill = theRole.mutable_skill();
			theRole.set_showtype(punit->showtype);
			pba->set_hp(punit->hp);
			pba->set_ad(punit->atk);
			pba->set_arm(punit->def);
			pba->set_as(punit->spd);
			pba->set_energy(punit->energy);
			pid->set_id(npcID);
			pid->set_name(CStrTableHelper::getStrById(
					confNpcTable->getRowValue(pnpcRow, confNpcTable->NAME)
				));
		
			pmsgunit->mutable_roleinfo()->CopyFrom(theRole);
		}

		ret = punit;
	}while(0);
	return ret;
}

bool CBattleTeamLogic::checkFail()
{
	for(int i=0; i<m_unitsLen; ++i)
	{
		if(m_units[i] != NULL && m_units[i]->isAlive())
		{
			return false;
		}
	}

	return true;
}


//已经改成非cd的回合制了
/*
int CBattleTeamLogic::selectMinCdUnit(int& retMinCd)
{
	int mincd = -1;
	int retIdx = -1;
	for(int i=0; i<m_unitsLen; ++i)
	{
		CBattleUnitLogic* now = m_units[i];
		if(now && now->isActive() && (mincd < 0 || now->cd < mincd))
		{
			mincd = now->cd;
			retIdx = i;
		}
	}

	retMinCd = mincd;
	return retIdx;
}

void CBattleTeamLogic::updateCd(int cd)
{
	do
	{
		for(int i=0; i<m_unitsLen; ++i)
		{
			CBattleUnitLogic* now = m_units[i];
			if(now && now->isActive())
			{
				if(now->cd > cd)
					now->cd -= cd;
				else
					now->cd = 0;
			}
		}
	}while(0);
}
*/


CBattleUnitLogic* CBattleTeamLogic::randomFront()
{
	CBattleUnitLogic* ret = NULL;
	do{
		CBattleUnitLogic* cur = NULL;
		vector<CBattleUnitLogic*> curSet;
		curSet.reserve(CBattleFormatConf::getSharedInstance()->getYMax());
		int xMax = CBattleFormatConf::getSharedInstance()->getXMax();
		for(int i=xMax-1; i>=0; --i)
		{
			curSet.clear();
			vector<int> idxes;
			CBattleFormatConf::getSharedInstance()->getIdxesByX(i, idxes);
			for(unsigned int j=0; j<idxes.size(); ++j)
			{
				cur = m_units[idxes[j]];
				if(cur && cur->isAlive())
				{
					curSet.push_back(cur);
				}
			}

			if(curSet.size() > 0)
			{
				ret = curSet[gGameTools.rand(0,curSet.size()-1)];
				break;
			}
		}
	}while(0);
	return ret;
}


CBattleUnitLogic* CBattleTeamLogic::nextActUnit()
{
	CBattleUnitLogic* ret = NULL;
	for(int i=0; i<this->m_unitsLen; ++i)
	{
		if(this->m_units[i]->isAlive() && !this->m_units[i]->isActed())
		{
			this->m_units[i]->setActed(true);
			ret = this->m_units[i];
			break;
		}
	}

	return ret;
}

void CBattleTeamLogic::clearAct()
{
	for(int i=0; i<this->m_unitsLen; ++i)
	{
		this->m_units[i]->setActed(false);
	}
}

