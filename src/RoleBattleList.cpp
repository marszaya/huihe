#include "RoleBattleList.h"
#include "StdViewFactory.h"
#include "MyData.h"
#include "MyControl.h"
#include "CMsgWithCmd.h"
#include "STRTABLE.h"

CRoleBattleList::CRoleBattleList(void)
{
	m_roleSel = NULL;
	m_curRoleIdx = 0;
	m_roleFormat = NULL;
	m_roleDetail = NULL;
	m_dialog = NULL;
}

CRoleBattleList::~CRoleBattleList(void)
{
}

CRoleBattleList* CRoleBattleList::create()
{
	CRoleBattleList *pRet = new CRoleBattleList();
	if(pRet && pRet->initCRoleBattleList())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CRoleBattleList::initCRoleBattleList()
{
	bool ret=false;
	do{
		m_roleSel = NULL;
		m_curRoleIdx = 0;
		m_roleFormat = NULL;
		m_roleDetail = NULL;

		int windowWidth = 900;
		int windowHeight = 600;

		CCNode* pbg = CStdViewFactory::createPopUpBg(windowWidth,windowHeight);

		if(!pbg)
		{
			break;
		}

		this->setWindowBG(pbg);
		this->windowSizeFitBG();

		CCMenu* closeBtn = CStdViewFactory::createCloseBtn(this, menu_selector(CRoleBattleList::onClose));
		CC_BREAK_IF(!closeBtn);
		this->setCloseBtn(closeBtn);
		
		if(!createRoleFormat())
			break;

		updateRoleSelect();
		updateRoleDetail();

		ret = true;
	}while(0);

	return ret;
}


void CRoleBattleList::onFrameMsg(CCObject* msg)
{
	do
	{
		int cmd = this->getCmdFromPostMsg(msg);
		if(cmd == CMyControl::CMD_WINDOW_SELF_LOOP)
		{
			CMyControl::getSharedControl()->invokeCmd(CMyControl::CMD_MAINSCENE_POPUPCLOSE, this);
		}
	}while(0);
}

void CRoleBattleList::onClose(CCObject* target)
{
	do{
		if(!m_roleFormat || !(m_roleFormat->hasChange()) || m_dialog)
		{
			break;
		}

		//提示有未保存的阵形
		m_dialog = CStdViewFactory::createDialog("has unsaved change, close window now ?", 
			CCUCommonDelegate::create(this, 
				callfuncO_selector(CRoleBattleList::onDialogueClose)
			)
		);

		if(!m_dialog)
		{
			break;
		}

		CCMyHelper::setPosC(m_dialog, this->getWindowWidth()/2, this->getWindowHeight()/2);
		this->addChild(m_dialog);

		return;
	}while(0);

	this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
}


bool CRoleBattleList::updateRoleSelect()
{
	bool ret = false;
	do{
		if(m_roleSel)
		{
			this->removeChild(m_roleSel, true);
		}

		m_roleSel = CRoleSelect::create( ROLE_VIEW_NUM,
			CCUCommonDelegate::create(this, callfuncO_selector(CRoleBattleList::onRoleSelected))
		);

		if(!m_roleSel)
			break;
		CCMyHelper::setPosBL(m_roleSel,15,15);
		this->addChild(m_roleSel);

		ret = true;
	}while(0);

	return ret;
}

void CRoleBattleList::onRoleSelected(CCObject* pobj)
{
	do{
		CCUCommonDelegate::CParamWrap* param = dynamic_cast<CCUCommonDelegate::CParamWrap*>(pobj);
		if(!param)
			break;

		CCNode* pnode = dynamic_cast<CCNode*>(param->m_cbParam);
		if(!pnode)
			break;

		m_curRoleIdx = m_roleSel->getCurRoleIdx();
		if(m_roleFormat)
		{
			m_roleFormat->setCurrentRoleIdx(m_curRoleIdx);
		}
		updateRoleDetail();
	}while(0);
}

bool CRoleBattleList::updateRoleDetail()
{
	bool ret = false;
	do{
		if(m_roleDetail)
			this->removeChild(m_roleDetail, true);

		m_roleDetail = CRoleDetail::create(m_curRoleIdx);
		if(!m_roleDetail)
			 break;
		
		CCMyHelper::setPosTL(m_roleDetail, 245, m_height-60);
		this->addChild(m_roleDetail);

		ret = true;
	}while(0);
	return ret;
}

bool CRoleBattleList::createRoleFormat()
{
	bool ret = false;
	do{
		if(m_roleFormat)
			break;

		m_roleFormat = CRoleBattleFormat::create(m_curRoleIdx);
		if(!m_roleFormat)
			break;

		CCMyHelper::setPosBL(m_roleFormat, 245, 55);
		this->addChild(m_roleFormat);

		CCMenu* saveBtn = CStdViewFactory::createBtn(this, menu_selector(CRoleBattleList::onSave),
			CONST_STR_BTN_BATTLE_LIST_SAVE, -1, m_width-80, 35);
		if(!saveBtn)
			break;
		this->addChild(saveBtn);
		ret = true;
	}while(0);
	return ret;
}

void CRoleBattleList::onSave(CCObject* param)
{
	do{
		if(m_roleFormat)
		{
			if(m_dialog)
				break;

			const char* hintMsg = NULL;
			if(!m_roleFormat->saveFormat())
			{
				//错误提示
				hintMsg = "save errer";
			}
			else
			{
				//成功提示
				hintMsg = "save ok";
			}

			m_dialog = CStdViewFactory::createDialog(hintMsg, 
				CCUCommonDelegate::create(this, 
					callfuncO_selector(CRoleBattleList::onDialogueSave)
				), 
				CStdViewFactory::DIALOG_TYPE_ALERT
			);

			if(!m_dialog)
				break;

			CCMyHelper::setPosC(m_dialog, this->getWindowWidth()/2, this->getWindowHeight()/2);
			this->addChild(m_dialog);
		}
	}while(0);
}

void CRoleBattleList::onDialogueClose(CCObject* param)
{
	do{
		int cmd = CCUCommonDelegate::parseCmdFromObj(param);
		this->removeChildOnNextFrame(m_dialog);
		m_dialog = NULL;
		if(cmd == CStdViewFactory::DIALOG_OK)
		{
			this->postMsgDirect(CMyControl::CMD_WINDOW_SELF_LOOP, NULL);
		}
	}while(0);
}

void CRoleBattleList::onDialogueSave(CCObject* param)
{
	do{
		this->removeChildOnNextFrame(m_dialog);
		m_dialog = NULL;
	}while(0);
}