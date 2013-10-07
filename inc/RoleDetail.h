#pragma once

#include "CWindowBase.h"

/*
* ����ս������ϸ��Ϣ
*/
class CRoleDetail:public CCWindowBase
{
public:
	enum CONST_VALUES{
		LABEL_HEIGHT=20,
		LABEL_WDITH = 100,
		GAP = 5
	};
public:
	CRoleDetail(void);
	virtual ~CRoleDetail(void);

	static CRoleDetail* create(int roleIdx);
	bool initCRoleDetail(int roleIdx);

	bool updateRoleDetail();

	virtual void onFrameMsg(CCObject* msg);
protected:
	int m_roleIdx;
	CCSprite* m_pic;
	CCWindowBase* m_labelWin;
};
