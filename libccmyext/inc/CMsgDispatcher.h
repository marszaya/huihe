#pragma once
#include "cocos2d.h"
#include <map>
#include <set>
#include <vector>
#include "CMsgWithCmd.h"

USING_NS_CC;
using namespace std;

class CCEMsgDispatcher: public CCObject
{
public:
	struct HANDLE_NODE{

		HANDLE_NODE(CCObject* t, SEL_CallFuncO s, bool m, int p);

		HANDLE_NODE();

		HANDLE_NODE(const HANDLE_NODE& h);

		inline void insertNext(HANDLE_NODE* pn)
		{
			pn->next = this->next;
			this->next = pn;
		}

		inline HANDLE_NODE* removeNext()
		{
			HANDLE_NODE* pret = this->next;
			if(pret)
			{
				this->next = pret->next;
			}

			return pret;
		}

		CCObject* target;
		SEL_CallFuncO selector;
		int priority;
		HANDLE_NODE* next;
		bool packCmdInMsg;
	};

	struct REGIST_REQ_CACHE
	{
		int cmd;
		CCObject* target;
		SEL_CallFuncO selector;
		int priority;
		bool packCmdInMsg;
	};

	struct UNREGIST_REQ_CACHE
	{
		int cmd;
		CCObject* target;
	};

	class CInvokeLock
	{
	public:

		inline bool empty()
		{
			return m_cmds.empty();
		}

		inline bool isLock(int cmd)
		{
			return (m_cmds.find(cmd) != m_cmds.end());
		}

		inline void add(int cmd)
		{
			map<int, int>::iterator it = m_cmds.find(cmd);
			if(it == m_cmds.end())
			{
				m_cmds.insert(make_pair(cmd, 1));
			}
			else
			{
				it->second = it->second + 1;
			}
		}

		inline void sub(int cmd)
		{
			map<int, int>::iterator it = m_cmds.find(cmd);
			if(it != m_cmds.end())
			{
				if(it->second <= 1)
				{
					m_cmds.erase(it);
				}
				else
				{
					it->second = it->second - 1;
				}
			}
		}

	public:
		map<int, int> m_cmds;
	};

public:
	CCEMsgDispatcher(void);
	virtual ~CCEMsgDispatcher(void);

	static CCEMsgDispatcher* getSharedInstance();

	//>=minPriority 会被触发, handle可以调用stopInvoke()阻止之后的handle接收消息
	bool invokeCmd(int cmd, CCObject* msg=NULL, int minPriority=0);

	//一个cmd可绑定多个target
	//target弱引用，析构时记得unregist
	bool registCmdHandle(int cmd, CCObject* target, SEL_CallFuncO selector, 
		bool packCmdInMsg=false, int priority=0);

	bool unregistCmdHandle(int cmd, CCObject* target);

	void unregistAll();

	inline void stopInvoke()
	{
		m_tmpStopFlag = true;
	}

	inline void setEnable(bool v)
	{
		m_enable= v;
	}

	void setCmdEnable(int cmd, bool v);

protected:
	static CCEMsgDispatcher* sharedInstance;
	map<int ,HANDLE_NODE*> m_cmdMap;
	set<int> m_disableCmdSet;
	vector<REGIST_REQ_CACHE> m_reg;
	vector<UNREGIST_REQ_CACHE> m_unreg;
	bool m_enable;
	bool m_tmpStopFlag;
	CInvokeLock m_invokeLock;
};