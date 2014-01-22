#include "BattleFightLogic.h"
#include "mathTools.h"
#include "DataUtil.h"
#include "StrTool.h"
#include "BattleFormatConf.h"
#include "tconfManager.h"
#include "BattleSkillLogic.h"
#include "BattleBuffLogic.h"
#include "BattleLogicDef.h"

CBattleFightLogic::CBattleFightLogic(void)
{
	m_win = false;
	m_saveBattleConf = NULL;
	m_skipNonManualStep = true;
}

CBattleFightLogic::~CBattleFightLogic(void)
{
}

void CBattleFightLogic::initBattle()
{
	do{
		m_saveBattleConf = NULL;
		
		initHomeTeam();
		initAwayTeam();
		
		m_win = false;
		m_context.clear();
	}while(0);
}

int CBattleFightLogic::doGameAuto()
{
	int ret = GAME_STEP_ERROR;
	do
	{
		ret = doGameStep();
	}while(ret == GAME_STEP_CONTINUE);

	return ret;
}

int CBattleFightLogic::doGameStep()
{
	if(needWait())
	{
		//CCLog("need wait");
		return GAME_STEP_CONTINUE;
	}

	int ret = GAME_STEP_ERROR;
	switch(m_context.state)
	{
		case BATTLE_STATE_INIT:
			ret = onGameStart();
			break;
		case BATTLE_STATE_ROUND_START:
			ret = onRoundStart();
			break;
		case BATTLE_STATE_ROUND_END:
			ret = onRoundEnd();
			break;
		case BATTLE_STATE_UNIT:
			ret = tryUnitActive();
			break;
		case BATTLE_STATE_END:
			ret = onGameEnd();
			break;
		default:
			//不可能。。
			break;
	}

	return ret;
}

int CBattleFightLogic::onGameStart()
{
	//CCLog("game start");
	//初始buff计算

	//开始第一个回合
	this->startNextRound();
	return gotoNextStep();
}

int CBattleFightLogic::onGameEnd()
{
	//CCLog("game end");

	//发送game结束消息
	if(m_win)
	{
		m_msg.msg.mutable_result()->set_win(1);
	}
	else
	{
		m_msg.msg.mutable_result()->set_win(0);
	}

	//返回
	return CAME_STEP_END;
}

int CBattleFightLogic::onRoundStart()
{
	//CCLog("round start %d", m_context.m_round);
	//发送回合开始消息
	m_msg.addNewRound();
	this->startAttack();
	return gotoNextStep();
}

int CBattleFightLogic::onRoundEnd()
{
	//CCLog("round end %d", m_context.m_round);
	this->startNextRound();
	return gotoNextStep();
}

int CBattleFightLogic::onUnitActive(CBattleUnitLogic* psrc)
{
	//固定的流程
	EFFECT_CONDITION_TYPE fixedSteps[] = {
		EFFECT_CONDITION_ACTION_START, 
		EFFECT_CONDITION_BEFORE_ATTACK,
		EFFECT_CONDITION_ATTACK, //普通攻击
		EFFECT_CONDITION_ACTION_END
	};

	//初始化
	EFFECT_ACTIVE_CONTEXT activeContext;
	activeContext.phost = this;
	activeContext.psrc = psrc;
	activeContext.pdst = NULL;
	activeContext.mhd.init(&m_msg, m_context.m_homeTeamTurn);

	for(unsigned int i=0; i < sizeof(fixedSteps)/sizeof(fixedSteps[0]); ++i)
	{
		activeContext.control.clear();

		if(fixedSteps[i] != EFFECT_CONDITION_ATTACK)
		{
			CBattleLogicEffectManager manager;
			//选择effect
			createEffectFromUnit(psrc, fixedSteps[i], manager);

			manager.executeEffects(activeContext);
		}
		else
		{
			//普通攻击
			CBattleLogicEffectDefaultAttack effect;
			effect.active(activeContext);
		}

		//死了，一了百了
		if(!psrc->isAlive())
			return 0;

		if(activeContext.control.breakFlag)
			break;
	}
	
	checkBuffEnd(psrc);

	return 0;
}

int CBattleFightLogic::tryUnitActive()
{
	//CCLog("try active isHome=%d", m_context.m_homeTeamTurn);
	//激活自己
	CBattleTeamLogic* pActiveTeam = getActiveTeam();
	CBattleUnitLogic* psrc = pActiveTeam->nextActUnit(); //选择自己

	if(psrc == NULL)//没有可以行动的单位
	{
		//CCLog("no active");
		this->setTeamActed();
		if(!this->checkRoundOver())
		{
			this->switchTeam();
		}
		return gotoNextStep();
	}

	//激活此单位
	int ret = onUnitActive(psrc);
	if(ret < 0)
	{
		CCLog("game error");
		//错误
		return GAME_STEP_ERROR;
	}

	//有可能结束game的地方都检查。。。
	if(checkEnd())
		return gotoNextStep(); 

	//交换队伍
	this->switchTeam();
	return gotoNextStep();
}

void CBattleFightLogic::initHomeTeam()
{
	CMyData* pdata = CMyData::getSharedData();
	RoleSet* prs = pdata->allRoles();
	for(int i=0; i<prs->battlelist_size(); ++i)
	{
		if(prs->battlelist(i).has_id())
		{
			string id = prs->battlelist(i).id();
			Role* p = pdata->getRoleById(id.c_str());
			if(!p)
				continue;
			m_home.setUnitByRole(i,p,m_msg.msg.mutable_initstate()->mutable_hometeam());
		}
	}
}

void CBattleFightLogic::initAwayTeam()
{
	do
	{
		CAutoBattleTab* conf = TCONF_GET(CAutoBattleTab);
		if(conf == NULL)
			break;
		int battleId = CMyData::getSharedData()->getCurrentBattle();
		m_saveBattleConf = conf->getRowByKey(CStrTool::strDecimal(battleId).c_str());
		const char* units = conf->getRowValue(m_saveBattleConf, conf->UNITS);
		if(units==NULL)
			break;

		vector<string> vout;
		CStrTool::split(units, ",", vout);

		for(unsigned int vi=0; vi<vout.size(); ++vi)
		{
			if(atoi(vout[vi].c_str()) <= 0)
				continue;
			m_away.setUnitByConf(vi, vout[vi].c_str(), m_msg.msg.mutable_initstate()->mutable_awayteam());
		}
	}while(0);
}

void CBattleFightLogic::getReward(CBattleResultParam* param)
{
	if(isWin())
	{
		param->m_win = 1;
		CAutoBattleTab* conf = TCONF_GET(CAutoBattleTab);
		CDataUtil::getItemFromConfStr(
			conf->getRowValue(m_saveBattleConf, conf->ITEM),
			&(param->m_items));

		param->m_expup = atoi(conf->getRowValue(m_saveBattleConf, conf->EXPR));
		param->m_goldup = atoi(conf->getRowValue(m_saveBattleConf, conf->GOLD));

		CMyData::getSharedData()->modifyGold(param->m_goldup);
		CMyData::getSharedData()->modifyExpr(param->m_expup);

		for(int i=0; i<param->m_items.items_size(); ++i)
		{
			CMyData::getSharedData()->addItem(param->m_items.items(i).subtype(), 
				param->m_items.items(i).num());
		}
	}
	else
	{
		param->m_win = 0;
		param->m_expup = 0;
		param->m_goldup = 0;
	}
}

void CBattleFightLogic::startNextRound()
{
	m_context.state = BATTLE_STATE_ROUND_START;
	++(m_context.m_round);
	m_context.m_homeTeamTurn = true;
	m_context.m_homeActed = m_context.m_awayActed = false;
	m_home.clearAct();
	m_away.clearAct();
}

void CBattleFightLogic::checkBuffEnd(CBattleUnitLogic* activedUnit)
{
	CBattleUnitLogic* punit = activedUnit;
	if(punit!=NULL && punit->isAlive())
	{
		CBattleUnitLogic::TYPE_BUFF_LIST::iterator cur;
		CBattleUnitLogic::TYPE_BUFF_LIST::iterator it=punit->buffs.begin();
		while(it!=punit->buffs.end())
		{
			cur = it;
			++it;
			cur->updateCnt();
			if(cur->isEnd())
			{
				m_msg.addBuffEndAction(cur->id, punit->idx, m_context.m_homeTeamTurn, cur->fromIdx);
				punit->buffs.erase(cur);
			}
		}
	}
}


bool CBattleFightLogic::createEffectFromUnit(CBattleUnitLogic* ptarget, EFFECT_CONDITION_TYPE condition,
	CBattleLogicEffectManager& manager)
{
	//遍历skill
	unsigned int i=0;
	for(i=0; i<ptarget->skills.size(); ++i)
	{
		int skillid = ptarget->skills[i];
		CBattleLogicEffect* newSkillEffect = CBattleLogicEffectFactory::getInstance()->createEffectBySkill(skillid);
		if(newSkillEffect!=NULL)
		{
			if(newSkillEffect->getCondition() != condition)
			{
				delete newSkillEffect;
			}
			else
			{
				if(!manager.addEffect(newSkillEffect))
				{
					delete newSkillEffect;
				}
			}
		}
	}

	//遍历buff
	CBattleUnitLogic::TYPE_BUFF_LIST::iterator it;
	for(it=ptarget->buffs.begin(); it!=ptarget->buffs.end(); ++it)
	{
		CBattleLogicEffect* newBuffEffect = CBattleLogicEffectFactory::getInstance()->createEffectByBuff(&(*it));
		if(newBuffEffect!=NULL)
		{
			if(newBuffEffect->getCondition() != condition)
			{
				delete newBuffEffect;
			}
			else 
			{
				if(!manager.addEffect(newBuffEffect))
				{
					delete newBuffEffect;
				}
			}
		}
	}

	return true;
}