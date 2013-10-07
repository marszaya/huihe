#include "CMsgWithCmd.h"

CCEMsgWithCmd::CCEMsgWithCmd(int cmd, CCObject* msg)
{
	m_cmd = cmd;
	m_msg = msg;
	if(m_msg)
	{
		m_msg->retain();
	}
}

CCEMsgWithCmd::~CCEMsgWithCmd(void)
{
	if(m_msg)
	{
		m_msg->release();
		m_msg = NULL;
	}
}


