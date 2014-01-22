#include "CMsgDispatcher.h"
#include "StrTool.h"

CCEMsgDispatcher* CCEMsgDispatcher::sharedInstance= NULL;

CCEMsgDispatcher::HANDLE_NODE::HANDLE_NODE(CCObject* t, SEL_CallFuncO s, bool m, int p)
{
	next = NULL;
	priority = p;
	target = t;
	selector = s;
	packCmdInMsg = m;
}

CCEMsgDispatcher::HANDLE_NODE::HANDLE_NODE()
{
	next = NULL;
	priority = 0;
	target = NULL;
	selector = NULL;
	packCmdInMsg = false;
}

CCEMsgDispatcher::HANDLE_NODE::HANDLE_NODE(const HANDLE_NODE& h)
{
	next = h.next;
	priority = h.priority;
	target = h.target;
	selector = h.selector;
	packCmdInMsg = h.packCmdInMsg;
}



CCEMsgDispatcher::CCEMsgDispatcher(void)
{
	m_enable = true;
}

CCEMsgDispatcher::~CCEMsgDispatcher(void)
{
	unregistAll();
}

CCEMsgDispatcher* CCEMsgDispatcher::getSharedInstance()
{
	if(sharedInstance == NULL)
	{
		sharedInstance = new CCEMsgDispatcher();
	}

	return sharedInstance;
}

bool CCEMsgDispatcher::invokeCmd(int cmd, CCObject* msg, int minPriority)
{
	bool ret = false;
	do{
		if(!m_enable)
			break;

		if(m_disableCmdSet.find(cmd) != m_disableCmdSet.end())
			break;

		map<int ,HANDLE_NODE*>::iterator it = m_cmdMap.find(cmd);
		if(it == m_cmdMap.end())
			break;
		HANDLE_NODE* pn = it->second;
		m_tmpStopFlag = false;
		
		//call back would modify map
		//同一个命令不允许循环调用
		if(m_invokeLock.isLock(cmd))
		{
			::CCMessageBox(
				string("CCEMsgDispatcher::invokeCmd locked: ").append(CStrTool::strDecimal(cmd)).c_str(),
				"debug");
			break;
		}

		m_invokeLock.add(cmd);

		while(pn && !m_tmpStopFlag && pn->priority >= minPriority)
		{
			bool inDel = false;
			//缓存在删除列表中的项不执行
			for(unsigned di=0; di<m_unreg.size(); ++di)
			{
				if(cmd == m_unreg[di].cmd &&pn->target == m_unreg[di].target)
				{
					inDel = true;
					break;
				}
			}

			if(!inDel)
			{
				if(pn->packCmdInMsg)
				{
					CCEMsgWithCmd* tmpMsg = new CCEMsgWithCmd(cmd, msg);
					(pn->target->*(pn->selector))(tmpMsg);
					tmpMsg->release();
				}
				else
				{
					(pn->target->*(pn->selector))(msg);
				}
			}

			pn = pn->next;
			ret = true;
		}
		
		m_invokeLock.sub(cmd);
		
		if(m_reg.size()!=0)
		{
			for(size_t i=0; i<m_reg.size(); ++i)
			{
				registCmdHandle(m_reg[i].cmd, m_reg[i].target,
					m_reg[i].selector, m_reg[i].packCmdInMsg, m_reg[i].priority);
			}

			m_reg.clear();
		}

		if(m_unreg.size()!=0)
		{
			for(size_t i=0; i<m_unreg.size(); ++i)
			{
				unregistCmdHandle(m_unreg[i].cmd, m_unreg[i].target);
			}

			m_unreg.clear();		
		}

		ret = true;
	}while(0);

	return ret;
}


bool CCEMsgDispatcher::registCmdHandle(int cmd, CCObject* target, SEL_CallFuncO selector, 
	bool packCmdInMsg,int priority)
{
	bool ret = false;
	do{
		if(m_invokeLock.isLock(cmd))
		{
			REGIST_REQ_CACHE ca;
			ca.cmd = cmd;
			ca.target = target;
			ca.selector = selector;
			ca.priority = priority;
			ca.packCmdInMsg = packCmdInMsg;
			m_reg.push_back(ca);
			break;
		}

		map<int ,HANDLE_NODE*>::iterator it = m_cmdMap.find(cmd);
		HANDLE_NODE* pn = NULL;
		if(it == m_cmdMap.end()) //插入占位
		{
			m_cmdMap.insert(make_pair(cmd, pn));
			it = m_cmdMap.find(cmd);
			if(it == m_cmdMap.end())
			{
				break;
			}
		}

		pn = it->second;
		bool found = false;
		bool invalidTarget = false;
		HANDLE_NODE* pnPre = NULL;
		HANDLE_NODE* pnToInsert = NULL;

		while(pn)
		{
			if(priority > pn->priority && !found)
			{
				found = true;
				pnToInsert = pnPre;
			}

			if(pn->target == target)
			{
				invalidTarget = true;
				break;
			}

			pnPre = pn;
			pn = pn->next;
		}

		if(invalidTarget)
		{
			::CCMessageBox(
				string("CCEMsgDispatcher::registCmdHandle target existed: ").append(CStrTool::strDecimal(cmd)).c_str(),
				"debug");
			break;
		}

		pn = new HANDLE_NODE(target, selector, packCmdInMsg, priority);
		if(pnToInsert)
			pnToInsert->insertNext(pn);
		else
		{
			pn->next = it->second;
			it->second = pn;
		}

		ret = true;
	}while(0);

	return ret;
}

bool CCEMsgDispatcher::unregistCmdHandle(int cmd, CCObject* target)
{
	bool ret = false;
	do{
		if(m_invokeLock.isLock(cmd))
		{
			UNREGIST_REQ_CACHE ca;
			ca.cmd = cmd;
			ca.target = target;
			m_unreg.push_back(ca);
			break;
		}

		map<int ,HANDLE_NODE*>::iterator it = m_cmdMap.find(cmd);
		if(it == m_cmdMap.end())
			break;
		HANDLE_NODE* pn = it->second;
		HANDLE_NODE* pnPre = NULL;
		while(pn)
		{
			if(pn->target == target)
			{
				if(pnPre)
				{
					//not first
					pnPre->removeNext();
				}
				else
				{
					//first
					if(pn->next)
					{
						//has next
						it->second = pn->next;
					}
					else
					{
						//no next
						m_cmdMap.erase(it);
					}
				}

				delete pn;
				ret = true;
				break;
			}

			pnPre = pn;
			pn = pn->next;
		}
	}while(0);

	return ret;
}

void CCEMsgDispatcher::unregistAll()
{
	if(!m_invokeLock.empty())
	{
		::CCMessageBox("CCEMsgDispatcher::unregistAll lock not empty", "debug");

		return;
	}

	HANDLE_NODE* pn;
	HANDLE_NODE* pnDel;
	map<int ,HANDLE_NODE*>::iterator it;
	for(it = m_cmdMap.begin(); it!=m_cmdMap.end(); ++it)
	{
		pn = it->second;
		while(pn)
		{
			pnDel = pn;
			pn = pn->next;
			delete pnDel;
		}
	}
	m_cmdMap.clear();
}

void CCEMsgDispatcher::setCmdEnable(int cmd, bool v)
{
	if(v)
	{
		m_disableCmdSet.erase(cmd);
	}
	else
	{
		if(m_disableCmdSet.find(cmd) == m_disableCmdSet.end())
			m_disableCmdSet.insert(cmd);
	}
}