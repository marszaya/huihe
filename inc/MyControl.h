#pragma once
#include "cocos2d.h"
#include <map>
#include <set>
#include <vector>
#include "CMsgDispatcher.h"
USING_NS_CC;
using namespace std;

class CMyControl: public CCEMsgDispatcher
{
public:
	enum{
		CMD_WINDOW_SELF_LOOP, //给自己发的命令
		CMD_LOGIN,
		CMD_MAINSCENE_POPUPCLOSE,
		CMD_BATTLE_RESULT_CLOSE,
		CMD_ITEM_EQUIP,
		CMD_DATA_ACCOUNT_MODIFIED,
		CMD_DATA_BAG_MODIFIED,
		CMD_DATA_ROLE_ATTR_MODIFIED,
		CMD_DATA_ROLE_EQUIP_MODIFIED,
		CMD_DATA_ROLE_HIRED,
		CMD_DATA_ROLE_FIRED,
		CMD_DATA_ROLE_HIRED_NO_MONEY,
		CMD_DATA_UNIT_OWN_MAX,
		CMD_DATA_UNIT_FIGHT_MAX,
		CMD_DATA_BATTLE_LIST_CHANGED
	};

public:
	CMyControl(void);
	~CMyControl(void);

	static CMyControl* getSharedControl();

	//>=minPriority 会被触发, handle可以调用stopInvoke()阻止之后的handle接收消息
	inline bool invokeCmd(int cmd, CCObject* msg=NULL, int minPriority=0)
	{
		return m_dispatcher.invokeCmd(cmd, msg, minPriority);
	}

	//一个cmd下 target::selector 是唯一的
	inline bool registCmdHandle(int cmd, CCObject* target, SEL_CallFuncO selector, bool packCmdInParam=false, int priority=0)
	{
		return m_dispatcher.registCmdHandle(cmd, target, selector, packCmdInParam, priority);
	}

	inline bool unregistCmdHandle(int cmd, CCObject* target)
	{
		return m_dispatcher.unregistCmdHandle(cmd, target);
	}

	inline void unregistAll()
	{
		m_dispatcher.unregistAll();
	}

	inline void stopInvoke()
	{
		m_dispatcher.stopInvoke();
	}

	inline void setEnable(bool v)
	{
		m_dispatcher.setEnable(v);
	}

	inline void setCmdEnable(int cmd, bool v)
	{
		m_dispatcher.setCmdEnable(cmd, v);
	}

	inline CCEMsgDispatcher* getDispatcher()
	{
		return &m_dispatcher;
	}

protected:
	static CMyControl* sharedControl;
	CCEMsgDispatcher m_dispatcher;
};
