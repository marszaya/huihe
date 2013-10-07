#include "AttrLabel.h"
#include "StdViewFactory.h"
#include "tconfManager.h"
#include "StrTool.h"
#include "item.pb.h"

CAttrLabel::CAttrLabel(void)
{
	m_hintID=-1;
	m_iconFrame=NULL;
	m_valueLabel = -1;
	m_vlx = 0;
	m_vly = 0;
	m_bgName = "mainScene/attrBg.png";
	m_windowWidth = 0;
	m_windowHeight = 0;
	m_font = CStdViewFactory::LABEL_FONT;
}

CAttrLabel::~CAttrLabel(void)
{

}

void CAttrLabel::showLabel()
{
	do{

		if(m_bgName.length() > 0)
		{
			CCSprite* bg = CCMyHelper::createZeroAnchorSprite("mainScene/attrBg.png");
			if(!bg)
				break;
			m_windowWidth = bg->getContentSize().width;
			m_windowHeight = bg->getContentSize().height;
			this->setWindowBG(bg);
			this->windowSizeFitBG();
		}
		else
		{
			this->setWindowSize(m_windowWidth, m_windowHeight);
		}
		
		int xoffset = 4;
		if(m_iconFrame!=NULL)
		{
			CCSprite* icon = CCMyHelper::createZeroAnchorFrameSprite(m_iconFrame);
			if(!icon)
				break;
			int theW= 18;
			CCMyHelper::setPosC(icon, xoffset+theW/2,m_windowHeight/2);
			this->addChild(icon);
			xoffset += theW;
		}

		if(m_hintID>0)
		{
			CAutoStrTab* pstrtab = TCONF_GET(CAutoStrTab);
			const char* strdesc = pstrtab->getValue(CStrTool::strDecimal(m_hintID).c_str(), pstrtab->V);
			if(strdesc == NULL)
				break;
			
			int theW= 38;
			this->updateLabel(-1, strdesc, m_font, 
				CCMyHelper::POS_INFO(xoffset+theW/2, m_windowHeight/2, CCMyHelper::POSITION_TYPE_CENTER)
				);
			xoffset += theW;
		}
		
		m_vlx = xoffset/2+m_windowWidth/2;
		m_vly = m_windowHeight/2;

		changeValue(m_value.c_str());
	}while(0);
}

void CAttrLabel::changeValue(const char* v)
{
	m_value = v;
	m_valueLabel = updateLabel(m_valueLabel, v, m_font, 
		CCMyHelper::POS_INFO(m_vlx, m_vly, CCMyHelper::POSITION_TYPE_CENTER)
		);
}

CAttrLabel* CAttrLabel::createHpLabel(int v, bool withSign)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		if(withSign && v>0)
		{
			pRet->m_value = "+";
		}
		else
		{
			pRet->m_value = "";
		}
		pRet->m_value += CStrTool::strDecimal(v);
		pRet->m_hintID = 21001;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createAtkLabel(int v, bool withSign)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		if(withSign && v>0)
		{
			pRet->m_value = "+";
		}
		else
		{
			pRet->m_value = "";
		}
		pRet->m_value += CStrTool::strDecimal(v);
		pRet->m_hintID = 21003;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createDefLabel(int v, bool withSign)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		if(withSign && v>0)
		{
			pRet->m_value = "+";
		}
		else
		{
			pRet->m_value = "";
		}
		pRet->m_value += CStrTool::strDecimal(v);
		pRet->m_hintID = 21002;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createSpdLabel(int v, bool withSign)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		if(withSign && v>0)
		{
			pRet->m_value = "+";
		}
		else
		{
			pRet->m_value = "";
		}
		pRet->m_value += CStrTool::strDecimal(v);
		pRet->m_hintID = 21004;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createNameLabel(const char* name)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		pRet->m_value = name;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createShortNameLabel(const char* name)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		pRet->m_bgName = "";
		pRet->m_windowWidth = 80;
		pRet->m_windowHeight = 20;
		pRet->m_value = name;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createLevelLabel(int level)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		pRet->m_value = CStrTool::strDecimal(level);
		pRet->m_hintID = 21102;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createShortLevelLabel(int level)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		pRet->m_bgName = "";
		pRet->m_windowWidth = 80;
		pRet->m_windowHeight = 20;
		pRet->m_value = CStrTool::strDecimal(level);
		pRet->m_hintID = 21102;
		pRet->showLabel();
	}
	return pRet;
}
	
CAttrLabel* CAttrLabel::createExpLabel(long long expr)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		pRet->m_value = CStrTool::strDecimalLL(expr);
		pRet->m_hintID = 21101;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createGoldLabel(long long gold)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		pRet->m_iconFrame = "qianbi.png";
		pRet->m_value = CStrTool::strDecimalLL(gold);
		pRet->m_hintID = 21103;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::createMoneyLabel(long long money)
{
	CAttrLabel *pRet = create();
	if(pRet)
	{
		pRet->m_iconFrame = "yuanbao.png";
		pRet->m_value = CStrTool::strDecimalLL(money);
		pRet->m_hintID = 21104;
		pRet->showLabel();
	}
	return pRet;
}

CAttrLabel* CAttrLabel::create()
{
	CAttrLabel *pRet = new CAttrLabel();
	if(pRet)
    {
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}


CAttrLabel* CAttrLabel::createEffectLabelById(int effectId, int effectValue, bool withSign)
{
	CAttrLabel* ret = NULL;
	do{
		if(effectId == Item::EFFECT_HP)
		{
			return createHpLabel(effectValue,withSign);
		}
		else if(effectId == Item::EFFECT_AD)
		{
			return createAtkLabel(effectValue,withSign);
		}
		else if(effectId == Item::EFFECT_ARMOR)
		{
			return createDefLabel(effectValue,withSign);
		}
		else if(effectId == Item::EFFECT_SPD)
		{
			return createSpdLabel(effectValue,withSign);
		}
		else
		{
			break;
		}
	}while(0);
	return ret;
}
