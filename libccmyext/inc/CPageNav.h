#pragma once

#include "CWindowBase.h"
#include "CCommonDelegate.h"
class CCEPageNav:public CCWindowBase
{
public:
	enum DELEGATE_CMD{
		GO_PRE,
		GO_NEXT
	};

	enum POSITION_VALUE{
		DEFAULT_GAP=50
	};

public:
	CCEPageNav(void);
	virtual ~CCEPageNav(void);

	static CCEPageNav* create(CCUCommonDelegate* pd);
	bool initCCEPageNav(CCUCommonDelegate* pd);
	
	void setPreBtn(CCSprite* normal, CCSprite* selected=NULL, CCSprite* disable=NULL);
	void setNextBtn(CCSprite* normal, CCSprite* selected=NULL, CCSprite* disable=NULL);
	void setLabel(CCMyHelper::FONT_INFO pageFont, int pageNum=1);
	virtual void alignByGap(int gap);
	void updatePageNum(int num);

	void onPreBtn(CCObject* target);
	void onNextBtn(CCObject* target);

public:
	int m_pageLabelTag;
	CCMyHelper::FONT_INFO m_font;
	CCNode* m_pre;
	CCNode* m_next;
};
