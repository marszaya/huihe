#include "ItemUnit.h"
#include "StdViewFactory.h"
#include "StrTool.h"
#include "MyData.h"
#include "DataUtil.h"

//#include "AttrLabel.h"

int CItemUnit::DEFAULT_HEIGHT= 80;
int CItemUnit::DEFAULT_WIDTH=160;

CItemUnit::CItemUnit(void)
{
	m_id = 0;
	m_nameTag = -1;
	m_descTag = -1;
	m_picWin = NULL;
}

CItemUnit::~CItemUnit(void)
{
}

CItemUnit* CItemUnit::create(int itemid, int num, int type)
{
	CItemUnit *pRet = new CItemUnit();
	if(pRet && pRet->initCItemUnit(itemid, num, type))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CItemUnit::initCItemUnit(int itemid, int num, int type)
{
	bool ret=0;
	do{
		m_id = itemid;
		CCSprite* sp = createItemPic(itemid);
		CC_BREAK_IF(!sp);

		m_picWin = CCWindowBase::create();
		if(!m_picWin)
			break;
		m_picWin->setWindowBG(sp);
		m_picWin->windowSizeFitBG();

		if(type == SHOW_TYPE_SIMPLE)
		{
			this->setWindowSize(m_picWin->getWindowWidth(), m_picWin->getWindowHeight());
			this->addChild(m_picWin);
		}
		else
		{
			this->setWindowSize(DEFAULT_WIDTH,DEFAULT_HEIGHT);
			//this->setColorBG(ccGREEN, 200);
			CCMyHelper::setPosC(m_picWin, DEFAULT_HEIGHT/2, DEFAULT_HEIGHT/2);
			this->addChild(m_picWin);

			CAutoItemTab* pitemtab = TCONF_GET(CAutoItemTab);
			CAutoStrTab* pstrtab = TCONF_GET(CAutoStrTab);

			m_conf = pitemtab->getRowByKey(CStrTool::strDecimal(itemid).c_str());
			CC_BREAK_IF(m_conf == NULL);
			
			const char* desc = pitemtab->getRowValue(m_conf, pitemtab->DESC);
			CC_BREAK_IF(desc == NULL);

			const char* name = pitemtab->getRowValue(m_conf, pitemtab->NAME);
			CC_BREAK_IF(name == NULL);

			const char* strname = pstrtab->getValue(name, pstrtab->V);
			CC_BREAK_IF(strname == NULL);

			m_nameTag = this->updateLabel(m_nameTag, strname, 
				CStdViewFactory::LABEL_FONT, 
				CCMyHelper::POS_INFO(DEFAULT_HEIGHT, DEFAULT_HEIGHT-25,
					CCMyHelper::POSITION_TYPE_BOTTOM_LEFT)
			);

			const char* strdesc = pstrtab->getValue(desc, pstrtab->V);
			if(strdesc != NULL)
			{
				m_descCache = strdesc;
			}
		}

		updateCItemUnit(num);
		ret = true;
	}while(0);

	return ret;
}

CCSprite* CItemUnit::createItemPic(int itemid)
{
	CCSprite* ret = NULL;
	do{
		char buff[32] = {0};
		sprintf(buff, "item/i%d.png", itemid);
		CCSprite* sp = CCMyHelper::createZeroAnchorSprite(buff);
		CC_BREAK_IF(!sp);

		ret = sp;
	}while(0);

	return ret;
}

void CItemUnit::updateCItemUnit(int num)
{
	CAutoItemTab* pitemtab = TCONF_GET(CAutoItemTab);
	if(!pitemtab)
		return;

	const char* countable = pitemtab->getRowValue(this->m_conf, pitemtab->COUNTABLE);
	if(countable == NULL)
		return;

	const char* majorType = pitemtab->getRowValue(this->m_conf, pitemtab->MAJORTYPE);
	if(majorType == NULL)
		return;

	vector<string> vars;
	//数字显示
	if(num >= 0)
	{
		if(atoi(countable) == 0)
		{
			if(atoi(majorType) != Item::MAJOR_TYPE_EQUIP)	//非堆叠物品不显示
			{
			}
			else
			{
				//num为装备等级
				CCMyHelper::FONT_INFO fontInfo = CStdViewFactory::LABEL_FONT;
				fontInfo.color = ccYELLOW;
				if(num > 0)
				{
					m_numTag = m_picWin->updateLabel(m_numTag, 
						string("+").append(CStrTool::strDecimal(num)).c_str(), 
						fontInfo, 
						CCMyHelper::POS_INFO(
							m_picWin->getWindowWidth()-2,  2,
							CCMyHelper::POSITION_TYPE_BOTTOM_RIGHT)
					);
				}

				vars.push_back(
					CStrTool::strDecimal(CDataUtil::getEquipAttrValue(m_id,num))
					);
			}
		}
		else
		{
			//显示个数
			CCMyHelper::FONT_INFO fontInfo = CStdViewFactory::LABEL_FONT;
			fontInfo.color = ccYELLOW;

			m_numTag = m_picWin->updateLabel(m_numTag, CStrTool::strDecimal(num).c_str(), 
				fontInfo, 
				CCMyHelper::POS_INFO(
					m_picWin->getWindowWidth()-2,  2,
					CCMyHelper::POSITION_TYPE_BOTTOM_RIGHT)
			);
		}
	}

	//描述
	if(m_descCache.length() > 0)
	{
		m_descTag = this->updateLabel(m_descTag, CStrTool::escapeStr(m_descCache.c_str(),&vars).c_str(),  
			CStdViewFactory::LABEL_FONT, 
			CCMyHelper::POS_INFO(DEFAULT_HEIGHT, DEFAULT_HEIGHT-28,
				CCMyHelper::POSITION_TYPE_TOP_LEFT)
		);
	}
}

