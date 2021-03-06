#include "BattleLogicEffect.h"
#include "tconfManager.h"
#include "BattleFightLogic.h"

CBattleLogicEffectFactory* CBattleLogicEffectFactory::m_pinstance=NULL;

CBattleLogicEffect::CBattleLogicEffect()
{
}

CBattleLogicEffect::~CBattleLogicEffect()
{
}


int CBattleLogicEffectDefaultAttack::active(EFFECT_ACTIVE_CONTEXT& con)
{
	int ret=-1;
	do{
		EFFECT_CONDITION_TYPE fixedSteps[] = {
			EFFECT_CONDITION_BEFORE_BEATTACK,
			EFFECT_CONDITION_ATTACK, //占位，作为计算伤害的入口
			EFFECT_CONDITION_AFTER_BEATTACK,
			EFFECT_CONDITION_AFTER_ATTACK
		};

		//攻击
		EFFECT_ACTIVE_CONTEXT::ATTACK& atk = con.attack;
		CBattleTeamLogic* pDstTeam = con.phost->getUnActiveTeam();

		vector<CBattleUnitLogic*> output;
		if(pDstTeam->randomTarget(atk.targetType,output)!=0)
			break;

		if(output.size() > 0 && con.attack.skillid < 0)
		{
			//固定增加
			con.psrc->energy += 100;
		}

		BattleAction* patkmsg = con.mhd.pmsg->addAtkMsgAction(con.psrc->idx, con.attack.skillid, 
				con.psrc->energy,con.mhd.isHomeTurn);
	
		bool end=false;
		for(unsigned int i=0; i<output.size() && !end; ++i)
		{
			con.pdst = output[i];
			atk.attrOffset.offsetDefPercent = 0;
			atk.attrOffset.offsetDef = 0;
			for(unsigned int j=0; j < sizeof(fixedSteps)/sizeof(fixedSteps[0]); ++j)
			{
				con.control.clear();
				fixedSteps[j];
				EFFECT_CONDITION_TYPE type = fixedSteps[j];
				
				if(type == EFFECT_CONDITION_ATTACK)
				{
					//计算伤害
					int dmg= caculateDmg(con);
					con.mhd.pmsg->addAtkMsgDst(patkmsg, con.pdst->idx, dmg, con.pdst->hp,con.mhd.isHomeTurn);
					tryDstDieMsg(con);
				}
				else
				{
					CBattleLogicEffectManager manager;

					if(type == EFFECT_CONDITION_AFTER_ATTACK)
					{
						con.phost->createEffectFromUnit(con.psrc, type, manager);
					}
					else
					{
						con.phost->createEffectFromUnit(con.pdst, type, manager);
					}
				
					manager.executeEffects(con);
				}

				if(!con.psrc->isAlive() || !con.psrc->isAlive())
				{
					end = true;
					break;
				}

				if(con.control.breakFlag)
					break;			
			}
		}

		ret = 0;
	}while(0);

	return ret;
}

int CBattleLogicEffectDefaultAttack::caculateDmg(EFFECT_ACTIVE_CONTEXT& con)
{
	//攻击
	int aper = con.attack.attrOffset.offsetAtkPercent+100;
	if(aper < 0)
		aper = 0;

	//先加绝对数值
	int dmg = con.psrc->atk + con.attack.attrOffset.offsetAtk;
	if(dmg < 0)
		dmg = 0;
	else
	{
		dmg = dmg*aper/100;
	}

	//先算免伤百分比
	int dper = 100 - con.attack.attrOffset.offsetDefPercent;
	if(dper < 0)
		dper = 0;
	else if(dper >= 100)
		dper = 100; //不算溢出伤害

	dmg = dmg*dper/100;

	if(con.pdst->def >= 0)
		 dmg = dmg - con.pdst->def;
	
	if(dmg <= 0)
		dmg = 1; //至少伤1

	con.pdst->dealDmg(dmg);

	return dmg;
}

CBattleLogicEffectBuff::CBattleLogicEffectBuff()
{
}

CBattleLogicEffectBuff::~CBattleLogicEffectBuff()
{
}

CBattleLogicEffectSkill::CBattleLogicEffectSkill()
{
}

CBattleLogicEffectSkill::~CBattleLogicEffectSkill()
{
}

int CBattleLogicEffectSkill::getTypeById(int id)
{
	int ret = -1;
	do{
		CAutoSkillTab* skillconfTab = TCONF_GET(CAutoSkillTab);
		if(!skillconfTab)
			break;

		const char* strtype = skillconfTab->getValue(CStrTool::strDecimal(id).c_str(), skillconfTab->TYPE);
		if(strtype == NULL)
			break;

		ret = atoi(strtype);
	}while(0);

	return ret;
}

bool CBattleLogicEffectSkill::bindSkill(int id)
{
	bool ret= false;
	do{
		CAutoSkillTab* skillconfTab = TCONF_GET(CAutoSkillTab);
		if(!skillconfTab)
			break;

		m_config.skillid = id;

		const TconfRow* prow = skillconfTab->getRowByKey(CStrTool::strDecimal(m_config.skillid).c_str());
		if(!prow)
			break;

		const char* strtype = skillconfTab->getRowValue(prow, skillconfTab->TYPE);
		if(strtype == NULL)
			break;

		const char* strparams = skillconfTab->getRowValue(prow, skillconfTab->PARAMS);
		if(strtype == NULL)
			break;

		const char* strseq = skillconfTab->getRowValue(prow, skillconfTab->SEQ);
		if(strseq == NULL)
			break;

		m_config.skilltype = atoi(strtype);
		m_config.skillseq = atoi(strseq);
		m_config.cost = atoi(skillconfTab->getRowValue(prow, skillconfTab->COST));
		m_chance = atoi(skillconfTab->getRowValue(prow, skillconfTab->CHANCE));
		m_config.vparams.clear();
		CStrTool::split(strparams, ",", m_config.vparams);

		ret = true;
	}while(0);

	return ret;
}

void CBattleLogicEffectSkill::addBuff(CBattleUnitLogic* unit, bool unitIsSrc, CBattleUnitLogic::BUFF& buff, EFFECT_ACTIVE_CONTEXT& con,  
	vector<CBattleLogicEffectSkill::BUFF_MATCH_CONDITION>& conditions, 
	vector<CBattleLogicEffectSkill::BUFF_MATCH_OPTION>& options, int effectCntMax)
{
	CBattleUnitLogic::TYPE_BUFF_LIST::iterator cur=unit->buffs.begin();
	bool newBuffMatched = false;
	CBattleUnitLogic::BUFF* buffOfMsg = NULL;
	while(cur!=unit->buffs.end())
	{
		unsigned int i=0;
		bool end = false;
		for(; i<conditions.size() && !end; ++i)
		{
			switch (conditions[i])
			{
			case BUFF_MATCH_EFFECT:
				end = !(cur->effectType == buff.effectType);
				break;
			case BUFF_MATCH_SEQ:
				end = !(cur->fromSkillSeq == buff.fromSkillSeq);
				break;
			case BUFF_MATCH_SKILLID:
				end = !(cur->fromSkillID == buff.fromSkillID);
				break;
			case BUFF_MATCH_FROMIDX:
				end = !(buff.fromIdx >= cur->fromIdx);
				break;
			default:
				end = true;
			}
		}

		if(i!=conditions.size()) //not match
		{
			++cur;
			continue;
		}

		newBuffMatched = true;

		//do options
		i=0;
		end = false;
		for(; i<options.size() && !end; ++i)
		{
			switch (options[i])
			{
			case BUFF_MATCH_FILTER_SKILLID_BIGER:
				if(buff.fromSkillID <= cur->fromSkillID)
					end = true;
				break;
			case BUFF_MATCH_FILTER_SKILLID_BIGER_OR_EQUAL:
				if(buff.fromSkillID < cur->fromSkillID)
					end = true;
				break;
			case BUFF_MATCH_DISCARD:
				end = true;
				break;
			case BUFF_MATCH_REPLACE:
				*cur = buff;
				{
					//id變更了，發送buff結束
					bool isHome;
					if(unitIsSrc)
						isHome = con.mhd.isHomeTurn;
					else
						isHome = !con.mhd.isHomeTurn;
					con.mhd.pmsg->addBuffEndAction(buff.id, unit->idx, isHome, buff.fromIdx);				
				}
				buffOfMsg = &(*cur);
				end = true;
				break;
			case BUFF_MATCH_RESET_REMAIN:
				cur->remainCnt = buff.remainCnt;
				buffOfMsg = &(*cur);
				break;
			case BUFF_MATCH_INCREASE_EFFECTCNT:
				if(effectCntMax != cur->effectCnt)
				{
					cur->effectCnt++;
					buffOfMsg = &(*cur);
				}
				break;
			default:
				end = true;
			}
		}

		break;
	}

	//新增加
	if(!newBuffMatched)
	{
		unit->buffs.push_back(buff);
		buffOfMsg = &buff;
	}

	if(buffOfMsg!=NULL)
	{
		bool isHome;
		if(unitIsSrc)
			isHome = con.mhd.isHomeTurn;
		else
			isHome = !con.mhd.isHomeTurn;
		con.mhd.pmsg->addBuffBeginAction(buffOfMsg->id, unit->idx, isHome, buffOfMsg->fromIdx,
			buffOfMsg->fromSkillID, buffOfMsg->effectCnt, effectCntMax);
	}
	
}

void CBattleLogicEffectSkill::srcCastBuff(EFFECT_ACTIVE_CONTEXT& con, CBattleUnitLogic::BUFF& newBuff)
{
	newBuff.assignID();
	newBuff.fromSkillID = m_config.skillid;
	newBuff.effectType = m_config.skilltype;
	newBuff.fromSkillSeq = m_config.skillseq;
	newBuff.effectCnt = 1;

	if(m_config.vparams.size() < 1)
		return;
	newBuff.remainCnt = atoi(m_config.vparams[0].c_str());

	newBuff.fromIdx = con.mhd.pmsg->makeMsgUnitIdx(con.psrc->idx, con.mhd.isHomeTurn);
	
	for(unsigned int i=1; i<m_config.vparams.size(); ++i)
	{
		newBuff.param[i-1] = atoi(m_config.vparams[i].c_str());
	}
}


CBattleLogicEffectFactory* CBattleLogicEffectFactory::getInstance()
{
	if(m_pinstance == NULL)
	{
		m_pinstance = new CBattleLogicEffectFactory;
	}

	return m_pinstance;
}

void CBattleLogicEffectFactory::registEffect(CBattleLogicEffect* peffectProto, int which)
{
	REGIST_MAP* pmap;
	if(which == 0)
	{
		pmap = &m_skills;
	}
	else
	{
		pmap = &m_buffs;
	}

	int type = peffectProto->getType();
	if(pmap->find(type) != pmap->end())
	{
		return;
	}

	pmap->insert(make_pair(type, peffectProto));
}

CBattleLogicEffect* CBattleLogicEffectFactory::createEffectBySkill(int id)
{
	CBattleLogicEffect* ret = NULL;
	do
	{
		int type = CBattleLogicEffectSkill::getTypeById(id);
		if(type < 0)
			break;

		REGIST_MAP::iterator it = m_skills.find(type);
		if(it == m_skills.end())
			break;
		ret = it->second->clone();
		CBattleLogicEffectSkill* pskill = dynamic_cast<CBattleLogicEffectSkill*>(ret);
		if(pskill == NULL)
		{
			delete ret;
			ret = NULL;
			break;
		}
		pskill->bindSkill(id);

		ret = pskill;
	}while(0);

	return ret;
}

CBattleLogicEffect* CBattleLogicEffectFactory::createEffectByBuff(CBattleUnitLogic::BUFF* p)
{
	CBattleLogicEffect* ret = NULL;
	do
	{
		if(p == NULL)
			break;
		REGIST_MAP::iterator it = m_buffs.find(p->effectType);
		if(it == m_buffs.end())
			break;
		ret = it->second->clone();
		CBattleLogicEffectBuff* pbuff = dynamic_cast<CBattleLogicEffectBuff*>(ret);
		if(pbuff == NULL)
		{
			delete ret;
			ret = NULL;
			break;
		}
		pbuff->bindBuff(p);

		ret = pbuff;
	}while(0);

	return ret;
}


CBattleLogicEffectManager::CBattleLogicEffectManager()
{
}

CBattleLogicEffectManager::~CBattleLogicEffectManager()
{
	PRIORTY_MAP::iterator it;
	for(it = m_map.begin(); it!=m_map.end(); ++it)
	{
		PRIORTY_MAP_ITEM* pv = it->second;
		for(PRIORTY_MAP_ITEM::iterator vit = pv->begin(); vit != pv->end(); ++ vit)
		{
			delete (*vit);
		}
		delete pv;
		it->second = NULL;
	}
}

bool CBattleLogicEffectManager::addEffect(CBattleLogicEffect* p)
{
	bool ret = false;
	do{
		int pri = p->getPriority();
		if(m_map.find(pri) != m_map.end())
		{
			m_map[pri]->push_back(p);
		}
		else
		{
			PRIORTY_MAP_ITEM* pnewV = new PRIORTY_MAP_ITEM;
			pnewV->push_back(p);
			m_map.insert(make_pair(pri, pnewV));
		}
		ret = true;
	}while(0);

	return ret;
}


void CBattleLogicEffectManager::executeEffects(EFFECT_ACTIVE_CONTEXT& context)
{
	PRIORTY_MAP::iterator it;
	while(!m_map.empty())
	{
		it = m_map.begin();
		PRIORTY_MAP_ITEM* pv = it->second;
		m_map.erase(it);

		while(pv!=NULL && pv->size() > 0)
		{
			CBattleLogicEffect* p = (*pv)[pv->size()-1];
			pv->pop_back();
			p->active(context);
			delete p;
		}
		
		delete pv;
	}
}