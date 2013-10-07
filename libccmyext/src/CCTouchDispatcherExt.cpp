#include "CCTouchDispatcherExt.h"

CCTouchDispatcherExt::CCTouchDispatcherExt()
{
	m_saveTargetHandles = NULL;
	m_useExtHandles = false;
}

CCTouchDispatcherExt::~CCTouchDispatcherExt(void)
{
}

void CCTouchDispatcherExt::useExtHandles(bool v)
{
	if(v != m_useExtHandles)
	{
		m_useExtHandles = v;
		if(m_useExtHandles)
		{
			CCArray* tmp = CCArray::createWithCapacity(4);
			tmp->retain();
			m_saveTargetHandles = m_pTargetedHandlers;
			m_pTargetedHandlers = tmp;
		}
		else
		{
			m_pTargetedHandlers->release();
			m_pTargetedHandlers = m_saveTargetHandles;
		}
	}
}
