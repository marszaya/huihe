#include "BattleMap.h"
#include "CMyHelper.h"
#include "BattleWindow.h"
#include "BattleProcedureBeCast.h"
#include "BattleProcedureAttack.h"
#include "BattleProcedureAttackRaged.h"
#include "logToFile.h"
#include "FightEffect.h"
#include "CActionReleaser.h"
#include "CActionEffectAfterImage.h"
#include "tconfManager.h"
#include "StrTool.h"
#include "BattleFormatConf.h"
#include <vector>
using namespace std;

CBattleWindowMap::CBattleWindowMap(void)
{
	m_rowMax = 0;
	m_colMax = 0;
	m_debugLabelTag = -1;
	m_ptable = NULL;
	m_spd = NULL;
	m_isPlaying = false;
}

CBattleWindowMap::~CBattleWindowMap(void)
{
}

CBattleWindowMap* CBattleWindowMap::create(int row, int col, float cellw, float cellh)
{
	CBattleWindowMap *pRet = new CBattleWindowMap();
	if(pRet && pRet->initCBattleWindowMap(row, col, cellw, cellh))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleWindowMap::initCBattleWindowMap(int row, int col, float cellw, float cellh)
{
	bool ret=false;
	do{
		debugString("debug");
		m_ptable = CCLayoutTable::create(cellw, cellh, row, col);
		CC_BREAK_IF(!m_ptable);
		m_rowMax = row;
		m_colMax = col;
		m_cellW = cellw;
		m_cellH = cellh;
		this->addChild(m_ptable);
m_ptable->showLines();
		this->setWindowSize(col*cellw, row*cellh);
		ret = true;
	}while(0);

	return ret;
}

int CBattleWindowMap::addFightUnit(int unitId, int x, int y, bool flip, CBattleUnitLogic* pdata)
{
	int retTag = -1;
	do{
		CC_BREAK_IF(!m_ptable);
		CC_BREAK_IF(x<0 || y< 0 || x>=m_colMax || y> m_rowMax);

		CBattleFightUnit* pnewUnit = CBattleFightUnit::create(unitId);
		CC_BREAK_IF(!pnewUnit);
		pnewUnit->initExt(x, y, flip, pdata, getSpd());
		pnewUnit->bindManager(this);

		retTag = this->createCustomTag();
		pdata->tagId = retTag;
		m_ptable->addItem(pnewUnit, y, x, retTag);
		pnewUnit->updateHp();
	}while(0);

	return retTag;
}

bool CBattleWindowMap::removeFightUnit(int tagId)
{
	bool ret=false;
	do{
		CC_BREAK_IF(!m_ptable->getChildByTag(tagId));
		m_ptable->removeChildByTag(tagId, true);
	}while(0);

	return ret;
}

CBattleFightUnit* CBattleWindowMap::getFightUnit(int tagId)
{
	CBattleFightUnit* pret=NULL;
	do{
		CCNode* pnode = m_ptable->getChildByTag(tagId);
		CC_BREAK_IF(!pnode);
		DYNAMIC_CAST_CCASERT2(pnode, CBattleFightUnit, pret);
	}while(0);

	return pret;
}

void CBattleWindowMap::doAttack(int srcTagId, vector<int>& dstTagIds, vector<int>& dmgs, int skillId)
{
	do{
		if(dstTagIds.size()==0 || dstTagIds.size() != dmgs.size())
			break;

		CBattleFightUnit* src = getFightUnit(srcTagId);
		if(!src)
			break;

		//分远近
		int showtype = src->getFightUnit()->getUnitID();
		CAutoUnitShowTab* unitshow = TCONF_GET(CAutoUnitShowTab);
		if(!unitshow)
			break;

		const char* isranged = unitshow->getValue(CStrTool::strDecimal(showtype).c_str(), unitshow->RANGED);
		if(isranged == NULL)
			break;
		int branged = atoi(isranged);

		const char* bulletConf = unitshow->getValue(CStrTool::strDecimal(showtype).c_str(), unitshow->BULLET);
		if(bulletConf == NULL)
			break;

		CBattleProcedureAttack* procedureAttack = NULL;
		if(branged == 0)
		{
			//近戰
			procedureAttack = CBattleProcedureAttack::create();
		}
		else
		{
			//遠程
			CBattleProcedureAttackRaged* tmp = CBattleProcedureAttackRaged::create();
			if(tmp==NULL)
				break;

			tmp->bulletConf = bulletConf;

			procedureAttack = static_cast<CBattleProcedureAttack*>(tmp);
		}

		if(procedureAttack == NULL)
			break;


		//技能表現需要id
		procedureAttack->skillId = skillId;

		//攻擊方配置
		CCPoint pos;
		m_ptable->getPos(src->m_y, src->m_x,  &pos, src);
		procedureAttack->srcInfo.set(srcTagId,pos.x, pos.y,0);
		src->m_spd = this->getSpd(); //播放速度

		for(unsigned int i=0; i < dstTagIds.size(); ++i)
		{
			CBattleFightUnit* dst =  getFightUnit(dstTagIds[i]);
			if(!dst)
				break;

			dst->m_spd = this->getSpd(); //播放速度
			
			CBattleMapAttackInfo desInfo;
			m_ptable->getPos(dst->m_y, dst->m_x,  &pos, dst);
			//修正位置
			if(dst->getFightUnit()->getFlip())
			{
				pos.x -= 20;
			}
			else
			{
				pos.x += 20;
			}

			desInfo.set(dstTagIds[i], pos.x, pos.y, dmgs[i]);
			procedureAttack->dstInfos.push_back(desInfo);
		}

		this->startProcedure(procedureAttack);
	}while(0);
}

int CBattleWindowMap::getSpd()
{
	if(m_spd)
	{
		return m_spd->getSpeed();
	}
	else
		return 1;
}


void CBattleWindowMap::showBullets(const char* bulletConf,
	const CCPoint& srcPos, const CCPoint& dstPos, float* dtOut)
{
	do{
		int spd = getSpd();
		
		float dt = 1.0/spd;
		if(dtOut!=NULL)
		{
			*dtOut = dt;
		}

		vector<string> output;
		CStrTool::split(bulletConf,".", output);
		if(output.size() != 2)
			break;
		int effectID = atoi(output[0].c_str());
		int effectSubID = atoi(output[1].c_str());
		CCNode* effcetNode = NULL;

		//暫時這樣寫
		if(effectSubID == 1)
		{
			CCEActionEffectAfterImage::CAfterImageConfig conf(
				CFightEffectImg::getFrameName(effectID, effectSubID).c_str(),
				1, 0.05/spd, 3, 0.5, 0.3, 255, 155);

			CCEActionEffectAfterImage* fightEffect = CCEActionEffectAfterImage::create(conf);
			if(!fightEffect)
				break;

			CCMoveTo* pmv = CCMoveTo::create(dt, ccp(dstPos.x-srcPos.x, dstPos.y - srcPos.y));
			if(!pmv)
				break;

			CCRotateBy* protate = CCRotateBy::create(dt, 360);
			if(!protate)
				break;
		
			fightEffect->addActionToImage(pmv);
			fightEffect->addActionToImage(protate);
			fightEffect->setChildAnchorPoint(ccp(0.5,0.5));
			fightEffect->beginAfterImage();
			fightEffect->setPosition(srcPos);
			effcetNode = static_cast<CCNode*>(fightEffect);
		}
		else
		{
			CCSprite* psimg = CCMyHelper::createZeroAnchorFrameSprite(CFightEffectImg::getFrameName(effectID, effectSubID).c_str());
			if(srcPos.x > dstPos.x) //反方向
			{
				psimg->setFlipX(true);
			}
			psimg->runAction(CCMoveTo::create(dt, ccp(dstPos.x-srcPos.x, dstPos.y - srcPos.y)));
			psimg->setPosition(srcPos);
			effcetNode = psimg;
		}

/*		CFightEffectImg* fightEffect = CFightEffect::create(effectID, effectSubID);
		if(!fightEffect)
			break;

		fightEffect->setPosition(srcPos);
*/
		if(effcetNode)
		{
			this->addChild(effcetNode, 10);
			CCEActionReleaser::create(effcetNode, this, CCDelayTime::create(dt));
		}

	}while(0);
}

void CBattleWindowMap::showDmg(int tagId, int dmg, int skillid)
{
	CBattleProcedureBeCast* pp = CBattleProcedureBeCast::create();
	pp->m_tag = tagId;
	pp->m_dmg = dmg;
	pp->m_skillId = skillid;
	this->startProcedure(pp);
}


bool CBattleWindowMap::playFromMsg(CBattleFightMsg& msg)
{
	//还在播放中
	if(this->m_isPlaying)
		return true;

	BattleAction* pact = msg.readAction();
	if(pact == NULL)
	{
		BattleRound* pround = msg.readRound();
		if(pround == NULL)
		{
			//没有新的msg发生
			return false;
		}
		
		//切换到新的回合了
		//int nowRound = msg.getCurRound();

		pact = msg.readAction();
		if(pact == NULL) //一般不会为空的
			return false;
	}

	do
	{
		//解析pact
		int acttype = pact->type();
		
		if(acttype== pact->ACTION_DMG)
		{
			CBattleUnitLogic* psrc = this->getUnitLogicByMsgIdx(pact->srcunitidx());
			if(psrc == NULL)
				break;

			if(pact->params_size() == 0)
				break;
			psrc->energy = atoi(pact->params(0).c_str());//同步能量

			vector<int> desids;
			vector<int> dmgs;
			for(int subi=0; subi<pact->subactions_size() ; ++subi)
			{
				BattleAction* psubact = pact->mutable_subactions(subi);
				CBattleUnitLogic* pdst = this->getUnitLogicByMsgIdx(psubact->dstunitidxes(0));
				if(pdst == NULL)
					break;

				if(psubact->params_size() !=2)
					break;

				int dmg = atoi(psubact->params(0).c_str());
				pdst->hp = atoi(psubact->params(1).c_str());//同步血量
				desids.push_back(pdst->tagId);
				dmgs.push_back(dmg);
			}
			doAttack(psrc->tagId, desids, dmgs, pact->id());
			m_isPlaying = true;
		}
		else if(acttype==pact->ACTION_DIE)
		{
			CBattleUnitLogic* psrc = this->getUnitLogicByMsgIdx(pact->srcunitidx());
			if(psrc == NULL)
				break;
			this->removeFightUnit(psrc->tagId);
		}
		else if(acttype == pact->ACTION_BECAST)
		{
			CBattleUnitLogic* psrc = this->getUnitLogicByMsgIdx(pact->srcunitidx());
			if(psrc == NULL)
				break;

			if(pact->params_size() < 1)
				break;

			CAutoSkillTab* pskillconf = TCONF_GET(CAutoSkillTab);
			if(pskillconf == NULL)
				break;

			const char* strEffectType = pskillconf->getValue(CStrTool::strDecimal(pact->id()).c_str(), pskillconf->TYPE);
			if(strEffectType == NULL)
				break;

			if(atoi(strEffectType) == 3) //伤血的表现
			{
				if(pact->params_size() != 3)
					break;

				this->showDmg(psrc->tagId, atoi(pact->params(1).c_str()));
				psrc->hp = atoi(pact->params(2).c_str());
				CBattleFightUnit* punit = getFightUnit(psrc->tagId);
				if(punit == NULL)
					break;
				punit->updateHp();
			}
			m_isPlaying = true;
		}
		else if(acttype == pact->ACTION_BUFF_BEGIN)
		{
			if(pact->dstunitidxes_size() == 0)
				break;
			CBattleUnitLogic* psrc = this->getUnitLogicByMsgIdx(pact->dstunitidxes(0));
			if(psrc == NULL)
				break;
			CBattleFightUnit* punit = getFightUnit(psrc->tagId);
			if(punit == NULL)
				break;

			if(pact->params_size() < 2)
			{
				break;
			}
			punit->addBuffIcon(pact->id(), atoi(pact->params(0).c_str()), atoi(pact->params(1).c_str()));
		}
		else if(acttype == pact->ACTION_BUFF_END)
		{
			if(pact->dstunitidxes_size() == 0)
				break;
			CBattleUnitLogic* psrc = this->getUnitLogicByMsgIdx(pact->dstunitidxes(0));
			if(psrc == NULL)
				break;
			CBattleFightUnit* punit = getFightUnit(psrc->tagId);
			if(punit == NULL)
				break;
			punit->delBuffIcon(pact->id());
		}
		else
			break;

		
	}while(0);
	
	return true;
}

int CBattleWindowMap::initTeamFromMsgTeam(BattleTeam* pmsgteam, CBattleTeamLogic& localTeam, bool isAway)
{
	for(int i=0; i<pmsgteam->units_size(); ++i)
	{
		BattleUnit* punit = pmsgteam->mutable_units(i);
		//写入local team
		CBattleUnitLogic* pUnitData = localTeam.setUnitByRole(punit->idx(), punit->mutable_roleinfo(), NULL);
		if(pUnitData == NULL)
			return -1;
		//加入可视化对象
		CBattleFormatConf* pbconf = CBattleFormatConf::getSharedInstance();
		bool isFlip;
		int x,y;
		if(isAway)
		{
			isFlip = true;
			x = this->m_colMax - 1 - pbconf->getXByIdx(punit->idx());
			y = pbconf->getYByIdx(punit->idx());
		}
		else
		{
			isFlip = false;
			x = pbconf->getXByIdx(punit->idx());
			y = pbconf->getYByIdx(punit->idx());
		}


		int ret = addFightUnit(punit->mutable_roleinfo()->showtype(),
				x, y, isFlip, pUnitData);

		if(ret < 0)
		{
			return -1;
		}		
	}
	return 0;
}


int CBattleWindowMap::initTeamFromMsg(CBattleFightMsg& msg)
{
	int ret=-1;
	do
	{
		if(!msg.msg.has_initstate())
			break;

		BattleInitState* pstate = msg.msg.mutable_initstate();
		if(!pstate->has_hometeam() || !pstate->has_awayteam())
			break;
		
		if(initTeamFromMsgTeam(pstate->mutable_hometeam(),m_hometeam,false)!=0)
			break;

		if(initTeamFromMsgTeam(pstate->mutable_awayteam(),m_awayteam,true)!=0)
			break;

		ret = 0;
	}while(0);
	return ret;
}

CBattleUnitLogic* CBattleWindowMap::getUnitLogicByMsgIdx(int msgIdx)
{
	bool isHome;
	int lidx = CBattleFightMsg::makeLocalUnitIdx(msgIdx, isHome);
	if(isHome)
	{
		return m_hometeam.unitAt(lidx);
	}
	else
	{
		return m_awayteam.unitAt(lidx);
	}
}

void CBattleWindowMap::onProcedureEnd(int tag)
{
	m_isPlaying = false;
}
