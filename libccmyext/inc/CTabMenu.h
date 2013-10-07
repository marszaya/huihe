#pragma once

#include "CWindowBase.h"


class CCETabMenuItem:public CCMenuItem
{

public:
	CCETabMenuItem(void);
	virtual ~CCETabMenuItem(void);

	static CCETabMenuItem* create(CCNode* selSp, CCNode* unselSp, CCObject *target, SEL_MenuHandler selector);
	bool initCCETabMenuItem(CCNode* selSp, CCNode* unselSp, CCObject *target, SEL_MenuHandler selector);

	void setItemSelected(bool v);

	inline bool getItemSelected()
	{
		return m_isItemSelected;
	}

    virtual void activate();

protected:
	CCNode* m_selSprite;
	CCNode* m_unselSprite;
	bool m_isItemSelected;
};

class CCETabMenu:public CCWindowBase
{
public:
	//CCUCommonDelegate::CParamWrap 
	enum DELEGATE_CMD
	{
		ITEM_SELECTED
	};

public:
	CCETabMenu(void);
	virtual ~CCETabMenu(void);

	static CCETabMenu* create(CCUCommonDelegate* pd);
	bool initCCETabMenu(CCUCommonDelegate* pd);

	inline void setSpace(float v)
	{
		m_space = v;
	}

	bool addTab(int tag, CCNode* selSp, CCNode* unSelSp);

	void selectTab(int tag, bool invokeCallBack=true);

	inline int getSelectedTab()
	{
		return m_selectedTag;
	}

	void callbackTabSelected(CCNode* pnode);

protected:
	void resetPosition();

protected:
	CCMenu* m_menu;
	float m_space;
	int m_selectedTag;
	float m_lastX;
};
