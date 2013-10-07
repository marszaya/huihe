#include "RoleBattleFormat.h"
#include "StdViewFactory.h"
#include "MyData.h"
#include "STRTABLE.h"
#include "RoleUnit.h"
#include "BattleFormatConf.h"
#include "AttrLabel.h"

CRoleBattleFormat::CRoleBattleFormat(void)
{
	m_ptable = NULL;
	m_hasChange = false;
}

CRoleBattleFormat::~CRoleBattleFormat(void)
{
}

CRoleBattleFormat* CRoleBattleFormat::create(int idx)
{
	CRoleBattleFormat *pRet = new CRoleBattleFormat();
	if(pRet && pRet->initCRoleBattleFormat(idx))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CRoleBattleFormat::initCRoleBattleFormat(int idx)
{
	bool ret=false;
	do{
		setCurrentRoleIdx(idx);
		RoleSet* prs = CMyData::getSharedData()->allRoles();
		if(!prs)
			break;

		for(int i=0; i<CBattleFormatConf::getSharedInstance()->getTotal(); ++i)
		{
			if(i<prs->battlelist_size())
			{
				if(prs->battlelist(i).id() != "")
				{
					bool found = false;
					for(int j=0; j<prs->roles_size(); ++j)
					{
						if(prs->battlelist(i).id() == prs->roles(j).id().id())
						{
							m_vRoleIdx.push_back(j);
							found = true;
							break;
						}
					}
					if(found)
						continue;
				}
			}
			
			m_vRoleIdx.push_back(-1);
		}

		updateCRoleBattleFormat();
		ret = true;
	}while(0);

	return ret;
}

bool CRoleBattleFormat::updateCRoleBattleFormat()
{
	bool ret = false;
	do{
		unsigned int i=0;
		for( i=0; i<m_vRoleIdx.size(); ++i)
		{
			CCWindowBase* cellWindow = createCellWindow(i);
			if(!cellWindow)
				break;

			if(i==0)
			{
				if(m_ptable)
				{
					this->removeChild(m_ptable, true);
				}

				m_ptable = CCLayoutTable::create(cellWindow->getWindowWidth(),
					cellWindow->getWindowHeight(),
					CBattleFormatConf::getSharedInstance()->getYMax(),
					CBattleFormatConf::getSharedInstance()->getXMax());

				if(!m_ptable)
					break;

				//m_ptable->showLines();

				this->setWindowSize(m_ptable->getContentSize().width,
					m_ptable->getContentSize().height);
				this->addChild(m_ptable);
			}

			m_ptable->addItem(cellWindow, 
				CBattleFormatConf::getSharedInstance()->getYByIdx(i), 
				CBattleFormatConf::getSharedInstance()->getXByIdx(i));
		}

		if(i!=m_vRoleIdx.size())
			break;

		ret = true;
	}while(0);
	return ret;
}

bool CRoleBattleFormat::pushRole(int posIdx)
{
	bool ret = false;
	do{
		if(posIdx < 0 || posIdx > (int)m_vRoleIdx.size())
			break;

		for(unsigned int i=0; i<m_vRoleIdx.size(); ++i)
		{
			if(m_vRoleIdx[i] == m_currentRoleIdx)
			{
				m_vRoleIdx[i] = -1;
				break;
			}
		}

		m_vRoleIdx[posIdx] = m_currentRoleIdx;
		m_hasChange = true;
		ret = updateCRoleBattleFormat();
	}while(0);
	return ret;
}

bool CRoleBattleFormat::popRole(int posIdx)
{
	bool ret = false;
	do{
		if(posIdx < 0 || posIdx > (int)m_vRoleIdx.size())
			break;
		m_vRoleIdx[posIdx] = -1;
		m_hasChange = true;
		ret = updateCRoleBattleFormat();
	}while(0);
	return ret;
}

bool CRoleBattleFormat::saveFormat()
{
	bool ret = false;
	do{
		if(!CMyData::getSharedData()->saveBattleList(this->m_vRoleIdx))
			break;
		m_hasChange = false;
		ret = true;
	}while(0);
	return ret;
}

CCWindowBase* CRoleBattleFormat::createCellWindow(int posIdx)
{
	CCWindowBase* ret = NULL;
	do{
		if(posIdx < 0 || posIdx > (int)m_vRoleIdx.size())
			break;

		int roleIdx = m_vRoleIdx[posIdx];

		CCWindowBase* cellWin = CCWindowBase::create();
		if(!cellWin)
			break;

		CCNode* bg = CStdViewFactory::createSmallBg(120,120);
		if(!bg)
			break;
		cellWin->setWindowBG(bg);
		cellWin->windowSizeFitBG();

		if(roleIdx >= 0)
		{
			Role* prole = CMyData::getSharedData()->getRoleByIdx(roleIdx);
			if(!prole)
				break;

			CCSprite* rolePic =  CRoleUnit::createPic(prole->showtype());
			if(!rolePic)
				break;

			CCMyHelper::setPosC(rolePic, cellWin->getWindowWidth()/2, cellWin->getWindowHeight()/2);
			cellWin->addChild(rolePic);

			CCMenu* close = CStdViewFactory::createCloseBtn(this, 
				menu_selector(CRoleBattleFormat::onPop), posIdx);

			if(!close)
				break;

			cellWin->setCloseBtn(close, -5, -5);
		}
		else
		{
			CCMenu* btn = CStdViewFactory::createBtn(this, 
				menu_selector(CRoleBattleFormat::onPush), CONST_STR_BTN_BATTLE_LIST_PUSH,
				posIdx, cellWin->getWindowWidth()/2, cellWin->getWindowHeight()/4);
			if(!btn)
				break;
			cellWin->addChild(btn);

			int effectId = 0;
			int effectValue = 0;
			CBattleFormatConf::getSharedInstance()->getEffectByIdx(posIdx, effectId, effectValue);
			if(effectId != Item::EFFECT_NONE)
			{
				CAttrLabel* label = CAttrLabel::createEffectLabelById(effectId, effectValue,true);
				if(!label)
					break;
				CCMyHelper::setPosC(label, cellWin->getWindowWidth()/2, cellWin->getWindowHeight()/4*3);
				cellWin->addChild(label);
			}
		}

		ret = cellWin;
	}while(0);
	return ret;
}

void CRoleBattleFormat::onPush(CCObject* param)
{
	do{
		CCNode* pnode = dynamic_cast<CCNode*>(param);
		if(!pnode)
			break;

		pushRole(pnode->getTag());
	}while(0);
}

void CRoleBattleFormat::onPop(CCObject* param)
{
	do{
		CCNode* pnode = dynamic_cast<CCNode*>(param);
		if(!pnode)
			break;

		popRole(pnode->getTag());
	}while(0);
}
