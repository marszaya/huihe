#include "RoleSelect.h"
#include "StdViewFactory.h"
#include "MyControl.h"

CRoleSelect::CRoleSelect(void)
{
	m_defaultUnitWidth=0;
    m_defaultUnitHight=0;
	m_defaultUnitGap=0;
	m_saveDelegate = NULL;
	m_unitNum = 0;
	m_curLocalIdx = 0;
	m_roleViewStartLocalIdx = 0;
	this->initPostMsg(CMyControl::getSharedControl()->getDispatcher());
	this->addPostMsg(CMyControl::CMD_DATA_ROLE_ATTR_MODIFIED);
}

CRoleSelect::~CRoleSelect(void)
{
}

CRoleSelect* CRoleSelect::create(int unitNum, CCUCommonDelegate* pd)
{
	CRoleSelect *pRet = new CRoleSelect();
	if(pRet && pRet->initCRoleSelect(unitNum, pd))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

void CRoleSelect::initUnitSize()
{
	m_defaultUnitWidth=CRoleUnit::DEFAULT_WIDTH;
	m_defaultUnitHight=CRoleUnit::DEFAULT_HEIGHT;
	m_defaultUnitGap = 8;
}

bool CRoleSelect::initCRoleSelect(int unitNum, CCUCommonDelegate* pd)
{
	bool ret=false;
	do{
		this->setDelegate(pd);
		m_unitNum = unitNum;
		m_curLocalIdx = 0;
		initUnitSize();


		//更新数据
		if(!CMyData::getSharedData()->createIdxForRoles(m_sortedIndex))
			break;

		if(m_sortedIndex.size() == 0)
			break;

		float windowHeight = unitNum*(m_defaultUnitHight+m_defaultUnitGap);
		float barX = m_defaultUnitWidth+10;
		float windowWidth = barX+20;

		this->setWindowSize(windowWidth,windowHeight);

		CCNode* hbar = CStdViewFactory::create9ScaleBg("mainScene/hBar.png", 
			17, windowHeight, 8, 8);
		if(!hbar)
			break;

		CCMyHelper::setPosBL(hbar, barX, 0);
		this->addChild(hbar);

		CCMenu* upbtn = CCMyHelper::createFrameButton("up.png", this, 
			menu_selector(CRoleSelect::onRoleUp), -1, "upSel.png", NULL,
			barX,windowHeight,CCMyHelper::POSITION_TYPE_TOP_LEFT);
		if(!upbtn)
			break;
		this->addChild(upbtn);

		CCMenu* downbtn = CCMyHelper::createFrameButton("down.png", this, 
			menu_selector(CRoleSelect::onRoleDown), -1, "downSel.png", NULL,
			barX,0,CCMyHelper::POSITION_TYPE_BOTTOM_LEFT);
		if(!downbtn)
			break;
		this->addChild(downbtn);

		for(int i=0; i<m_unitNum; ++i)
		{
			int cusTag = this->createCustomTag();
			//占位置
			m_saveTags.push_back(cusTag);
		}

		if(!updateRoleSelect(0))
			break;

		ret = true;
	}while(0);

	return ret;
}

void CRoleSelect::onRoleDown(CCObject* pnode)
{
	int last = CMyData::getSharedData()->allRoles()->roles_size();
	if(m_roleViewStartLocalIdx+m_unitNum < last)
		updateRoleSelect(m_roleViewStartLocalIdx+1);
}

void CRoleSelect::onRoleUp(CCObject* pnode)
{
	updateRoleSelect(m_roleViewStartLocalIdx-1);
}

bool CRoleSelect::updateRoleSelect(int startIdx)
{
	bool ret = false;
	do{
		if(startIdx < 0 || startIdx >= (int)m_sortedIndex.size())
			break;

		m_roleViewStartLocalIdx = startIdx;

		for(int i=0; i<m_unitNum; ++i)
		{
			int tag = this->m_saveTags[i];
			CCNode* proleView = this->getChildByTag(tag);
			if(proleView)
			{
				//清掉之前的
				this->removeChildByTag(tag, true);
			}

			int localIdx = startIdx+i;
			if(localIdx >= (int)m_sortedIndex.size())
				continue;

			int roleIdx = m_sortedIndex[localIdx];
			Role* prole = CMyData::getSharedData()->getRoleByIdx(roleIdx);
			if(!prole)
				continue;

			proleView = createRoleView(prole);
			if(proleView)
			{
				CCMyHelper::setPosTL(proleView, 0, (m_unitNum-i)*(CRoleUnit::DEFAULT_HEIGHT+m_defaultUnitGap));
				if(!CCMyHelper::attachMenuToNode(proleView, this, 
					callfuncO_selector(CRoleSelect::onSelectRole), roleIdx))
					break;
				this->addChild(proleView, 1, tag);

				//选中状态的，需要加描边
				if(m_curLocalIdx == localIdx)
				{
					CCNode* outer = CStdViewFactory::createBorderForNode(proleView);
					if(outer)
					{
						proleView->addChild(outer, -1);
					}
				}
			}
		}

		ret = true;
	}
	while(0);
	return ret;
}

CCWindowBase* CRoleSelect::createRoleView(Role* prole)
{
	return CRoleUnit::create(prole);
}

void CRoleSelect::setCurRoleIdx(int idx)
{
	do{
		Role* prole = CMyData::getSharedData()->getRoleByIdx(idx);
		if(!prole)
			break;

		int localidx = roleIdxToLocalIdx(idx);
		if(localidx < 0)
			break;

		m_curLocalIdx = localidx;
		
		//不在选择视野内的话，就移动下
		if(m_curLocalIdx < m_roleViewStartLocalIdx || m_curLocalIdx >= m_roleViewStartLocalIdx + m_unitNum)
		{
			int last = m_sortedIndex.size();
			int startIdx = idx;
			while(startIdx > 0)
			{
				if(startIdx+m_unitNum <= last)
				{
					break;
				}
				--startIdx;
			}
			updateRoleSelect(startIdx);
		}
	}while(0);
}

void CRoleSelect::onSelectRole(CCObject* pobj)
{
	//这里抓取下，更新自己的m_curLocalIdx
	do{
		CCNode* pnode = dynamic_cast<CCNode*>(pobj);
		if(!pnode)
			break;
		int tmp = roleIdxToLocalIdx(pnode->getTag());
		if(tmp < 0)
			break;
		m_curLocalIdx = tmp;
		updateRoleSelect(m_roleViewStartLocalIdx);
		//抛出
		m_saveDelegate->callbackO(pnode);
	}while(0);
}


void CRoleSelect::onFrameMsg(CCObject* msg)
{
	//更新数据
	if(!CMyData::getSharedData()->createIdxForRoles(m_sortedIndex))
	{
		return;
	}

	if(m_sortedIndex.size() == 0)
		return;

	int updateStartIdx = this->m_roleViewStartLocalIdx;

	if(updateStartIdx >= (int)m_sortedIndex.size())
	{
		updateStartIdx = 0;
	}

	if(m_curLocalIdx >= (int)m_sortedIndex.size())
	{
		m_curLocalIdx = 0;
	}

	this->updateRoleSelect(updateStartIdx);
}

int CRoleSelect::roleIdxToLocalIdx(int roleIdx)
{
	int ret = -1;
	do{
		for(unsigned int i=0; i<m_sortedIndex.size(); ++i)
		{
			if(roleIdx == m_sortedIndex[i])
			{
				ret = i;
				break;
			}
		}
	}while(0);
	return ret;
}
