
#pragma once
#include "cocos2d.h"

USING_NS_CC;

//���ڵ����Ի��򣬲���������touch�ַ������
//useExtHandlesʹ��һ����ʱhandle�����滻��ԭ����target����
//1 useExtHandles(true) 
//2 create dialog with ok or cancel button
//3 ok or cancel button recieves event
//4 useExtHandles(false) 

class CCTouchDispatcherExt:public CCTouchDispatcher
{
public:
	CCTouchDispatcherExt(void);
	virtual ~CCTouchDispatcherExt(void);

public:
	void useExtHandles(bool v);

protected:
	CCArray* m_saveTargetHandles;
	bool m_useExtHandles;
};
