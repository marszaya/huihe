#include "BattleFightUnit.h"
#include "StrTool.h"
#include "MyControl.h"
#include "BattleFightLogic.h"
#include "FightEffect.h"
#include "BattleSkillName.h"


CBattleFightUnit::CBattleFightUnit(void)
{
	m_pslide = NULL;
	m_fightUnit = NULL;
	m_x = 0;
	m_y = 0;
	m_flip = false;
	m_actionParam = NULL;
	m_dmgTag = -1;
	m_hpbar = NULL;
	m_energyBar = NULL;
	m_hpbarLableTag = -1;
	m_energyLableTag = -1;
	m_pdata = NULL;
	m_spd = 1;
}

CBattleFightUnit::~CBattleFightUnit(void)
{
	if(m_actionParam != NULL)
	{
		m_actionParam->release();
		m_actionParam = NULL;
	}
}

CBattleFightUnit* CBattleFightUnit::create(int unitid)
{
	CBattleFightUnit *pRet = new CBattleFightUnit();
	if(pRet && pRet->initCBattleFightUnit(unitid))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleFightUnit::initCBattleFightUnit(int unitid)
{
	bool ret=false;
	do{
		m_fightUnit = CFightUnit::create(unitid);
		CC_BREAK_IF(!m_fightUnit);

		this->addChild(m_fightUnit);
		
		//血条初始化
		m_hpbar = CBarBase::create("mainScene/greenBar.png");
		CC_BREAK_IF(!m_hpbar);
		m_hpbar->setAnchorPoint(ccp(0.5,0.5));
		m_hpbar->setScaleX(0.5);
		CCMyHelper::setPosC(m_hpbar, 0, 60);
		this->addChild(m_hpbar);
		m_hpbar->setPercent(100);

		//能量条初始化
		m_energyBar = CBarBase::create("mainScene/yellowBar.png");
		CC_BREAK_IF(!m_energyBar);
		m_energyBar->setAnchorPoint(ccp(0.5,0.5));
		m_energyBar->setScaleX(0.5);
		CCMyHelper::setPosC(m_energyBar, 0, 80);
		this->addChild(m_energyBar);
		m_energyBar->setPercent(0);

		//形象
		m_pslide = CCESlideWindow::create();
		CC_BREAK_IF(!m_pslide);
		CCMyHelper::setPosC(m_pslide, 0, 50);
		this->addChild(m_pslide);
		m_pslide->startPlay();

		m_spd = 1;
		ret = true;
	}while(0);

	return ret;
}


void CBattleFightUnit::updateHp()
{
	if(!m_hpbar)
		return;

	int now=m_pdata->hp;
	int max=m_pdata->hpmax;
	m_hpbar->setPercent(float(now)/max*100);
	m_hpbarLableTag = this->updateLabel(m_hpbarLableTag,
		CStrTool::strDecimal(now).append("/").append(CStrTool::strDecimal(max)).c_str(),
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(0, 60, CCMyHelper::POSITION_TYPE_CENTER)
		);
}

void CBattleFightUnit::updateEnergy()
{
	if(!m_energyBar)
		return;

	int now = m_pdata->energy;
	int max = 1000;
	m_energyBar->setPercent(float(now)/max*100);
	m_energyLableTag = this->updateLabel(m_energyLableTag,
		CStrTool::strDecimal(now).append("/").append(CStrTool::strDecimal(max)).c_str(),
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(0, 80, CCMyHelper::POSITION_TYPE_CENTER)
		);
}

void CBattleFightUnit::actionMoveToPos(CCPoint pos)
{
	m_fightUnit->move(m_spd);
	CCMoveTo* pmove = CCMoveTo::create(1.0/m_spd, pos);
	this->callAction(pmove);
}

void CBattleFightUnit::actionDoAttack(int skillId)
{
	m_fightUnit->attack(m_spd);
	float dt = m_fightUnit->getAnime()->getCurDuration();

	if(skillId >= 0)
	{
		addSkillName(skillId, dt);
	}

	this->callAction(CCDelayTime::create(dt));
	updateEnergy();
}

void CBattleFightUnit::actionShowDmg(int dmg, int skillid)
{
	if(m_dmgTag!=-1)
		return;
	
	float effectDt = 0;
	addEffect(1, effectDt);

	float dmgDt = 1.0/m_spd;
	addDmgNumber(dmg, dmgDt);

	float maxDt = dmgDt > effectDt ? dmgDt : effectDt;
	this->callAction(CCDelayTime::create(maxDt));

	updateHp();

	if(skillid>=0)
		addSkillName(skillid, maxDt);
}

void CBattleFightUnit::actionDelay(float dt)
{
	this->callAction(CCDelayTime::create(dt));
}

void CBattleFightUnit::actionEffect(int effectid)
{
	float effectDt = 0;
	addEffect(effectid, effectDt);
	this->callAction(CCDelayTime::create(effectDt));
}

void CBattleFightUnit::callbackHideDmgLabel()
{
	this->removeChildByTag(m_dmgTag, true);
	m_dmgTag = -1;
}

void CBattleFightUnit::addDmgNumber(int dmg, float duration)
{
	m_dmgTag = this->createCustomTag();

	CCNode* plabel = CStdViewFactory::createNum(dmg, -1);
	plabel->setAnchorPoint(ccp(0.5,0.5));
	plabel->setPosition(ccp(0, 40));
	this->addChild(plabel, 1, m_dmgTag);

	CCMoveTo* plabelmove = CCMoveTo::create(duration, ccp(0, 70));
	
	plabel->runAction(
			CCSequence::create(
				plabelmove, 
				CCCallFunc::create(this, callfunc_selector(CBattleFightUnit::callbackHideDmgLabel)), 
				NULL
			)
		);
}

void CBattleFightUnit::addEffect(int effectid, float& durationOut)
{
	int tag =  this->createCustomTag();
	CFightEffect* pe = CFightEffect::create(effectid);
	if(pe)
	{
		pe->setScale(0.5);
		this->addChild(pe, 10, tag);
		if(!this->m_fightUnit->getFlip())
		{
			//受到攻击的方向与特效方向相反
			pe->setFlip(true);
		}
		pe->play(m_spd);
		durationOut = pe->getAnime()->getCurDuration();
		this->runAction(
			CCSequence::create(
				CCDelayTime::create(durationOut),
				CCCallFuncO::create(this, 
					callfuncO_selector(CBattleFightUnit::callbackRemoveEffect),
					CCString::createWithFormat("%d", tag)
				),
				NULL
			)
		);
	}
}

void CBattleFightUnit::addSkillName(int skillid, float duration)
{
	CBattleSkillName* skillName = CBattleSkillName::create(skillid);
	if(skillName)
	{
		CCMyHelper::setPosC(skillName, 0, 60);
		skillName->addToWindow(this, duration);
	}
}

void CBattleFightUnit::callbackRemoveEffect(CCObject* p)
{
	CCString* pstr = dynamic_cast<CCString*>(p);
	if(pstr)
	{
		this->removeChildByTag(pstr->intValue(), true);
	}
}


void CBattleFightUnit::addBuffIcon(int iconid, int fromIdx)
{
	if(m_pslide == NULL)
		return;
	
	CCSprite* psprite = CCMyHelper::createZeroAnchorFrameSprite(createBuffFrameName(iconid).c_str());
	psprite->setScale(0.4);
	char tmp[64]={0};
	sprintf(tmp, "%d_%d", iconid, fromIdx);
	m_pslide->addSlide(psprite, tmp);
}

void CBattleFightUnit::delBuffIcon(int iconid, int fromIdx)
{
	if(m_pslide == NULL)
		return;
	char tmp[64]={0};
	sprintf(tmp, "%d_%d", iconid, fromIdx);
	m_pslide->delSlide(tmp);
}