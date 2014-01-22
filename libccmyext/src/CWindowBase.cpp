#include "CWindowBase.h"
#include "CMyHelper.h"

void CCWindowBase::menuCallBackCloseApp(CCObject* psender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
		CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
#endif
}

CCWindowBase::CCWindowBase(void)
{
	m_width = 0;
	m_height = 0;
	m_customTagMax = TAG_CUSTOMBASE;
	m_textAlignH =kCCTextAlignmentLeft;
	m_textAlignV = kCCVerticalTextAlignmentTop;
	m_saveDelegate = NULL;
	m_saveDispatcher = NULL;
	m_ignoreDumplicateCmd = true;
}

void CCWindowBase::setDelegate(CCUCommonDelegate* pdelegate)
{
	if(pdelegate)
		pdelegate->retain();
	if(m_saveDelegate)
		m_saveDelegate->release();
	m_saveDelegate = pdelegate;
}

void CCWindowBase::passCmdToDelegateFromNodeTag(CCObject* menuItemNode)
{
	do{
		CCNode* pnode = dynamic_cast<CCNode*>(menuItemNode);
		if(!pnode)
			break;
		//抛出
		if(m_saveDelegate)
		{
			m_saveDelegate->notifyTargetWithCmd(pnode->getTag());
		}
	}while(0);
}

CCWindowBase::~CCWindowBase(void)
{
	if(m_saveDelegate)
	{
		m_saveDelegate->release();
		m_saveDelegate = NULL;
	}

	if(m_saveDispatcher)
	{
		for(unsigned int i = 0; i<m_registedCmds.size(); ++i)
		{
			m_saveDispatcher->unregistCmdHandle(m_registedCmds[i], this);
		}
		m_registedCmds.clear();
		m_saveDispatcher->release();
		m_saveDispatcher = NULL;
	}
}

 CCWindowBase* CCWindowBase::create()
{
	CCWindowBase *pRet = new CCWindowBase();
	if(pRet)
    {
        pRet->autorelease();
    }

	return pRet;
}

CCWindowBase* CCWindowBase::create(float width, float height)
{
	CCWindowBase *pRet = new CCWindowBase();
	if(pRet)
    {
		pRet->setWindowSize(width, height);
		pRet->setAnchorPoint(ccp(0,0));
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CCWindowBase::setWindowSize(float width, float height)
{
	m_width = width;
	m_height = height;
	setContentSize(CCSizeMake(width, height));
}

void CCWindowBase::setWindowBG(CCNode* bg, bool enableScale)
{
	const CCSize& bgsize = bg->getContentSize();
	if(enableScale && bgsize.width != m_width && bgsize.width != 0)
	{
		bg->setScaleX(m_width/bgsize.width);
	}

	if(enableScale && bgsize.height != m_height && bgsize.height != 0)
	{
		bg->setScaleY(m_height/bgsize.height);
	}

	CCMyHelper::setPosBL(bg, 0, 0);

	if(this->getChildByTag(TAG_BACKGROUND))
		this->removeChildByTag(TAG_BACKGROUND, true);
	this->addChild(bg, -1,TAG_BACKGROUND);
}

void CCWindowBase::windowSizeFitBG()
{
	CCNode* pbg = this->getChildByTag(TAG_BACKGROUND);
	if(pbg)
	{
		CCSize size = pbg->getContentSize();
		this->setWindowSize(size.width, size.height);
	}
}


void CCWindowBase::setCloseBtn(CCMenu* pmenu, float xoffset, float yoffset)
{
	CCMyHelper::setPositionByTopRight(pmenu, m_width+xoffset, m_height+yoffset);
	this->removeChildByTag(TAG_CLOSEBTN, true);
	this->addChild(pmenu, 999, TAG_CLOSEBTN);
}

void CCWindowBase::setColorBG(const ccColor3B& color, GLubyte opaque)
{
	CCLayerColor* pbg = CCLayerColor::create(ccc4(color.r, color.g, color.b, opaque),m_width, m_height);
	if(!pbg)
	{
		return;
	}
	if(this->getChildByTag(TAG_BACKGROUND))
		this->removeChildByTag(TAG_BACKGROUND, true);
	CCMyHelper::setPosBL(pbg, 0,0);
	this->addChild(pbg, 0, TAG_BACKGROUND);
}

int CCWindowBase::updateLabel(int tagHint, const char* str, 
		const CCMyHelper::FONT_INFO& font,
		const CCMyHelper::POS_INFO& pos, int zorder)
{
	int ret = -1;
	do{
		CCLabelTTF* plabel;
		CCNode* pnode;
		if(tagHint > 0 && (pnode = this->getChildByTag(tagHint)))
		{
			DYNAMIC_CAST_CCASERT2(pnode, CCLabelTTF, plabel);
			ret = tagHint;
			this->removeChild(pnode,true);
		}
		else
		{
			ret = createCustomTag();
		}

		plabel = CCLabelTTF::create(str, font.name.c_str(), font.size, CCSizeZero,
			this->m_textAlignH, this->m_textAlignV);
		CC_BREAK_IF(!plabel);
		plabel->setAnchorPoint(ccp(0,0));
		plabel->setColor(font.color);
		this->addChild(plabel, zorder, ret);

		CCMyHelper::setPosition(plabel, pos.type, pos.x, pos.y);
	}while(0);

	return ret;
}

void CCWindowBase::visit(void)
{
	//删除子节点
	for(unsigned int i=0; i<m_childrenToRemove.size(); ++i)
	{
		removeChild(m_childrenToRemove[i], true);
	}
	m_childrenToRemove.clear();

	//查看消息队列
	if(m_msgArray.count() > 0)
	{
		for(unsigned int i=0; i<m_msgArray.count(); ++i)
		{
			CCObject* pmsg = m_msgArray.objectAtIndex(i);
			onFrameMsg(pmsg);
		}
		m_msgArray.removeAllObjects();
	}

	CCNode::visit();
}

void CCWindowBase::onFrameMsg(CCObject* pmsg)
{
	
}

void CCWindowBase::postMsgDirect(int cmd, CCObject* param)
{
	do
	{
		CCEMsgWithCmd* pmsg = new CCEMsgWithCmd(cmd, param);
		postMsg(pmsg);
		pmsg->release();
	}while(0);
}

void CCWindowBase::postMsg(CCObject* pmsg)
{
	//过滤掉重复的命令
	do{
		if(m_ignoreDumplicateCmd)
		{
			bool hasDumplicate = false;
			for(unsigned int i=0; i<m_msgArray.count(); ++i)
			{
				int cmd = getCmdFromPostMsg(m_msgArray.objectAtIndex(i));
				int cmd2 = getCmdFromPostMsg(pmsg);
				if(cmd ==cmd2	)
				{
					hasDumplicate = true;
					break;
				}
			}
			
			if(hasDumplicate)
				break;
		}
		m_msgArray.addObject(pmsg);
	}while(0);
}

int CCWindowBase::getCmdFromPostMsg(CCObject* msg)
{
	int ret = -1;
	do{
		CCEMsgWithCmd* p = dynamic_cast<CCEMsgWithCmd*>(msg);
		if(!p)
			break;

		ret = p->m_cmd;
	}while(0);
	return ret;
}

CCObject* CCWindowBase::getParamFromPostMsg(CCObject* msg)
{
	CCObject* ret = NULL;
	do{
		CCEMsgWithCmd* p = dynamic_cast<CCEMsgWithCmd*>(msg);
		if(!p)
			break;
		ret = p->m_msg;
	}while(0);
	return ret;
}

bool CCWindowBase::initPostMsg(CCEMsgDispatcher* p, bool v)
{
	bool ret = false;
	do{
		//只能初始化一次
		if(m_saveDispatcher != NULL)
			break;
		m_saveDispatcher = p;
		m_saveDispatcher->retain();
		m_ignoreDumplicateCmd = v;
		ret = true;
	}while(0);
	return ret;
}

bool CCWindowBase::addPostMsg( int cmd, int priority)
{
	bool ret = false;
	do{
		if(!m_saveDispatcher)
			break;

		for(unsigned int i = 0; i<m_registedCmds.size(); ++i)
		{
			if(cmd == m_registedCmds[i])
				break;
		}

		if(m_saveDispatcher->registCmdHandle(cmd, this, callfuncO_selector(CCWindowBase::postMsg), true, priority))
		{
			m_registedCmds.push_back(cmd);
		}

		ret = true;
	}while(0);
	return ret;
}
