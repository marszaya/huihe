#include "BuffIconWindow.h"
#include "tconfManager.h"
#include "StrTool.h"
#include "StdViewFactory.h"

CBuffIconWindow::CBuffIconWindow(void)
{
}

CBuffIconWindow::~CBuffIconWindow(void)
{
}

CBuffIconWindow* CBuffIconWindow::create(int iconID, int effectCnt)
{
	CBuffIconWindow *pRet = new CBuffIconWindow();
	if(pRet && pRet->initCBuffIconWindow(iconID, effectCnt))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CBuffIconWindow::initCBuffIconWindow(int iconID, int effectCnt)
{
	bool ret=false;
	do{
		m_taglabel = -1;
		CCSprite* psprite = CCMyHelper::createZeroAnchorFrameSprite(createBuffFrameName(iconID).c_str());
		if(!psprite)
		{
			break;
		}

		psprite->setScale(0.4);
		this->addChild(psprite);
		
		changeEffectCnt(effectCnt);
		
		ret = true;
	}while(0);

	return ret;
}

void CBuffIconWindow::changeEffectCnt(int effectCnt)
{
	this->updateLabel(m_taglabel, CStrTool::strDecimal(effectCnt).c_str(),
		CCMyHelper::FONT_INFO(ccc3(255,0,0),10,CStdViewFactory::LABEL_FONT.name.c_str()), 
		CCMyHelper::POS_INFO(2,2,CCMyHelper::POSITION_TYPE_BOTTOM_LEFT));
}

string CBuffIconWindow::createBuffFrameName(int id)
{
	char buff[32] = {0};
	CAutoSkillTab* pskillconf = TCONF_GET(CAutoSkillTab);
	if(pskillconf == NULL)
	{
		return "";
	}

	sprintf(buff, "buff%s.png", pskillconf->getValue(CStrTool::strDecimal(id).c_str(), pskillconf->SEQ));
	return buff;
}