#include "BattleFightLogic.h"
#include "mathTools.h"
#include "DataUtil.h"
#include "StrTool.h"
#include "BattleFormatConf.h"
#include "tconfManager.h"

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
			ret = doAttackStep();
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
	//初始buff计算

	//开始第一个回合
	this->startNextRound();
	return gotoNextStep();
}

int CBattleFightLogic::onGameEnd()
{
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
	//发送回合开始消息
	m_msg.addNewRound();
	this->startAttack();
	return gotoNextStep();
}

int CBattleFightLogic::onRoundEnd()
{
	this->startNextRound();
	return gotoNextStep();
}

int CBattleFightLogic::doAttackStep()
{
	//一次攻击
	CBattleTeamLogic* pActiveTeam = getActiveTeam();
	CBattleTeamLogic* pUnActiveTeam = getUnActiveTeam();
	CBattleUnitLogic* pdst = pUnActiveTeam->randomFront(); //选择对手
	CBattleUnitLogic* psrc = pActiveTeam->nextActUnit(); //选择自己

	if(psrc == NULL)//没有可以行动的单位
	{
		this->setTeamActed();
		if(!this->checkRoundOver())
		{
			this->switchTeam();
		}
		return gotoNextStep();
	}

	psrc->setActed(true);

	if(pdst == NULL)
	{
		//理论上不可能
		return gotoNextStep();
	}

	if(doSkillAttack(psrc, pdst, true)!=0)
	{
		return GAME_STEP_ERROR;
	}

	//有可能结束game的地方都检查。。。
	if(isEnd())
		return gotoNextStep(); 
	
	if(doAttack(psrc, pdst)!=0)
	{
		return GAME_STEP_ERROR;
	}

	//有可能结束game的地方都检查。。。
	if(isEnd())
		return gotoNextStep(); 

	if(doSkillAttack(psrc, pdst, false)!=0)
	{
		return GAME_STEP_ERROR;
	}

	//有可能结束game的地方都检查。。。
	if(isEnd())
		return gotoNextStep(); 

	//交换队伍
	this->switchTeam();
	return gotoNextStep();
}

int CBattleFightLogic::doSkillAttack(CBattleUnitLogic* src, CBattleUnitLogic* dst, bool isBeforeAttack)
{
	int ret = -1;
	do{
		CAutoSkillTab* skillconfTab = TCONF_GET(CAutoSkillTab);
		if(!skillconfTab)
			break;

		for(unsigned int i=0; i<src->skills.size(); ++i)
		{
			int skillId = src->skills[i];
			const TconfRow* prow = skillconfTab->getRowByKey(CStrTool::strDecimal(skillId).c_str());
			if(!prow)
				break;
			
			const char* strtype = skillconfTab->getRowValue(prow, skillconfTab->TYPE);
			if(strtype == NULL)
				break;

			const char* strparams = skillconfTab->getRowValue(prow, skillconfTab->PARAMS);
			if(strtype == NULL)
				break;

			int skillType = atoi(strtype);
			if(skillType == 1)
			{
				int dmg = atoi(strparams);
				if(dst->hp <= dmg)
				{
					dst->hp = 0;
					dst->setAlive(false);
				}
				else
				{
					dst->hp -= dmg;
				}

				BattleAction* pba = newAtkMsgAction(BattleAction::ACTION_SKILL, src->idx, dst->idx,skillType);
				pba->add_params(CStrTool::strDecimal(dmg));
				pba->add_params(CStrTool::strDecimal(dst->hp));

				//设立结束检查点
				if(checkEnd())
				{
					return 0;
				}
			}
		}

		ret = 0;
	}while(0);
	return ret;
}


int CBattleFightLogic::doAttack(CBattleUnitLogic* src, CBattleUnitLogic* dst)
{
	int dmg = src->atk - dst->def;
	if(dmg <= 0)
		dmg = 1;

	if(dst->hp <= dmg)
	{
		dst->hp = 0;
		dst->setAlive(false);
	}
	else
	{
		dst->hp -= dmg;
	}

	BattleAction* pba = newAtkMsgAction(BattleAction::ACTION_DMG, src->idx, dst->idx);
	pba->add_params(CStrTool::strDecimal(dmg));
	pba->add_params(CStrTool::strDecimal(dst->hp));

	return 0;
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
