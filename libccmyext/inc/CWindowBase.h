#pragma once
#include "cocos2d.h"
#include "CMyHelper.h"
#include "CMsgDispatcher.h"
#include "CCommonDelegate.h"
#include <vector>
USING_NS_CC;
using namespace std;

class CCWindowBase: public CCNode
{
public:
	enum TAGS{
		TAG_BACKGROUND=1,
		TAG_CLOSEBTN=2,
		TAG_CUSTOMBASE=100
	};
public:
	CCWindowBase(void);
	virtual ~CCWindowBase(void);

	static CCWindowBase* create();
	static CCWindowBase* create(float width, float height);

	inline void fullWindowSize()
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		setWindowSize(size.width, size.height);
	}

	//should call setWindowBG before
	void windowSizeFitBG();

	void setWindowSize(float width, float height);

	void setWindowBG(CCNode* bg, bool enableScale=false);

	void setCloseBtn(CCMenu* pmenu, float xoffset=0, float yoffset=0);

	void setColorBG(const ccColor3B& color = ccBLACK, GLubyte opaque = 255);

	//tagHint=-1 新建, 否则更新
	//fail ret=-1  or  ok ret=tag
	int updateLabel(int tagHint, const char* str, 
		const CCMyHelper::FONT_INFO& font,
		const CCMyHelper::POS_INFO& pos, int zorder=1);

	inline int createCustomTag()
	{
		return ++m_customTagMax;
	}

	inline float getWindowWidth()
	{
		return m_width;
	}

	inline float getWindowHeight()
	{
		return m_height;
	}

	inline void setTextAlignH(CCTextAlignment ta)
	{
		m_textAlignH = ta;
	}

	inline void setTextAlignV(CCVerticalTextAlignment ta)
	{
		m_textAlignV = ta;
	}

	inline CCTextAlignment getTextAlignH()
	{
		return m_textAlignH;
	}

	inline CCVerticalTextAlignment getTextAlignV()
	{
		return m_textAlignV;
	}

	virtual void visit(void);

	//在一些回调函数中删除子节点是有风险的
	//比如子节点是Menu，回调是删除这个Menu
	//此函数把删除操作延后到下一帧
	inline void removeChildOnNextFrame(CCNode* child)
	{
		m_childrenToRemove.push_back(child);
	}
	
	//parent存在且为CCWindowBase时有效
	inline bool removeSelfOnNextFrame()
	{
		if(m_pParent)
		{
			CCWindowBase* pp = dynamic_cast<CCWindowBase*>(m_pParent);
			if(pp)
			{
				pp->removeChildOnNextFrame(this);
				return true;
			}
		}

		return false;
	}

	//callback by msg dispather
	//work with  initPostMsg add addPostMsg add onFrameMsg
	void postMsg(CCObject* msg);

	//for public use
	void postMsgDirect(int cmd, CCObject* param);

	//delegate functions 
	void setDelegate(CCUCommonDelegate* pdelegate);
	void passCmdToDelegateFromNodeTag(CCObject* menuItemNode);

protected:
	virtual void onFrameMsg(CCObject* msg);
	bool addPostMsg(int cmd, int priority=0);
	bool initPostMsg(CCEMsgDispatcher* p, bool ignoreDumplicateCmd=true);
	int getCmdFromPostMsg(CCObject* msg);
	CCObject* getParamFromPostMsg(CCObject* msg); 

protected:
	float m_width;
	float m_height;
	int m_customTagMax;
	CCArray m_msgArray;
	CCTextAlignment m_textAlignH;
	CCVerticalTextAlignment m_textAlignV;
	CCUCommonDelegate* m_saveDelegate;
	vector<int> m_registedCmds;
	CCEMsgDispatcher* m_saveDispatcher;
	bool m_ignoreDumplicateCmd;
	vector<CCNode*> m_childrenToRemove;
};
