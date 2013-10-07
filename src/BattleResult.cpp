#include "BattleResult.h"
#include "ItemUnit.h"
#include "StrTool.h"
#include "StdViewFactory.h"
#include "MyControl.h"

CBattleResult::CBattleResult(void)
{
	m_tagResult = -1;
	m_tagLabelExpr = -1;
	m_tagLabelGold = -1;
	m_pitemTable = NULL;
}

CBattleResult::~CBattleResult(void)
{
}

CBattleResult* CBattleResult::create()
{
	CBattleResult *pRet = new CBattleResult();
	if(pRet && pRet->initCBattleResult())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBattleResult::initCBattleResult()
{
	bool ret=false;
	do{
		m_pitemTable = CCLayoutTable::create(CItemUnit::DEFAULT_WIDTH,
			CItemUnit::DEFAULT_HEIGHT,1,6);
		if(!m_pitemTable)
			break;

		this->setWindowSize(600, 400);
		this->setColorBG(ccBLACK, 200);
		CCMyHelper::setPosBL(m_pitemTable, 50, 100);
		this->addChild(m_pitemTable);

		CCMenu* pbtn = CStdViewFactory::createBtn(this, menu_selector(CBattleResult::onClose),
			"go back", -1, 200,50);
		if(!pbtn)
			break;
		this->addChild(pbtn);

		ret = true;
	}while(0);

	return ret;
}

void CBattleResult::showResult(CBattleResultParam& param)
{
	if(param.m_win == 0)
		m_tagResult = this->updateLabel(m_tagResult, "lose", 
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(50, 300,CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
		);
	else
	{
		m_tagResult = this->updateLabel(m_tagResult, "win", 
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(50, 300,CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
		);

		m_tagLabelExpr = this->updateLabel(
			m_tagLabelExpr, string("expr += ").append(CStrTool::strDecimal(param.m_expup)).c_str(), 
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(50, 260,CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
		);

		m_tagLabelGold = this->updateLabel(
			m_tagLabelGold, string("gold += ").append(CStrTool::strDecimal(param.m_goldup)).c_str(), 
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(200, 260,CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
		);

		for(int i=0; i<param.m_items.items_size(); ++i)
		{
			Item* ptmp = param.m_items.mutable_items(i);
			m_pitemTable->addItem(CItemUnit::create(ptmp->subtype(), ptmp->num()),0,i);
		}
	}
}

void CBattleResult::onClose(CCObject* ob)
{
	CMyControl::getSharedControl()->invokeCmd(CMyControl::CMD_BATTLE_RESULT_CLOSE);
}
