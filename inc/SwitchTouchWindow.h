#pragma once

#include "CWindowBase.h"

/*
* ���ര��createʱ���л�touch delegate���У�ʹ֮ǰ�Ŀɴ�������ʧЧ������ʱ�ָ�
* ����Ϊ���������ڵĴ��ڣ�����alert����
*/
class CSwitchTouchWindow:public CCWindowBase
{
public:
	CSwitchTouchWindow(void);
	virtual ~CSwitchTouchWindow(void);

	static CSwitchTouchWindow* create(void);
	bool initCSwitchTouchWindow(void);
};

