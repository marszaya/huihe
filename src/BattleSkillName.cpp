#include "BattleSkillName.h"
#include "CActionReleaser.h"
#include "tconfManager.h"
#include "StrTool.h"
#include "STRTABLE.h"
#include "StdViewFactory.h"

CBattleSkillName::CBattleSkillName(void)
{
	m_skillId = -1;
}

CBattleSkillName::~CBattleSkillName(void)
{
}

CBattleSkillName* CBattleSkillName::create(int skillId)
{
	CBattleSkillName *pRet = new CBattleSkillName();
	if(pRet && pRet->initCBattleSkillName(skillId))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleSkillName::initCBattleSkillName(int skillId)
{
	bool ret=false;
	do{

		CAutoSkillTab* skill = TCONF_GET(CAutoSkillTab);
		if(!skill)
			break;

		const char* skillNameId = skill->getValue(CStrTool::strDecimal(skillId).c_str(), skill->NAME);
		if(skillNameId == NULL)
			break;

		m_skillName = CStrTableHelper::getStrById(skillNameId);

		m_skillId = skillId;

		CCLabelTTF* label = CCLabelTTF::create(m_skillName.c_str(), 
			CStdViewFactory::LABEL_FONT.name.c_str(), 16);
		if(!label)
			break;

		label->setColor(ccc3(255,0,0));

		CCMyHelper::setPosC(label, 0, 0);
		this->addChild(label);
	
		ret = true;
	}while(0);

	return ret;
}

bool CBattleSkillName::addToWindow(CCWindowBase* parentWin, float dt)
{
	bool ret = false;
	do{
		float dt1 = dt*0.3;
		float dt2 = dt*0.4;
		float dt3 = dt*0.3;

		CCSpawn* phase1 = CCSpawn::createWithTwoActions(
			CCFadeIn::create(dt1),
			CCMoveBy::create(dt1, ccp(0, 30))
		);
		if(!phase1)
			break;

		CCDelayTime* phase2 = CCDelayTime::create(dt2);
		if(!phase2)
			break;

		CCSpawn* phase3 = CCSpawn::createWithTwoActions(
			CCFadeOut::create(dt3),
			CCMoveBy::create(dt3, ccp(0, 30))
		);
		if(!phase3)
			break;

		CCFiniteTimeAction* allAction = CCSequence::create(phase1,phase2, phase3,NULL);
		if(!allAction)
			break;

		parentWin->addChild(this);
		CCEActionReleaser::create(this, parentWin, allAction);
		ret = true;
	}while(0);
	return ret;
}
