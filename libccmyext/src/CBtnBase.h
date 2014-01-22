#pragma once
#include "cocos2d.h"
#include "CMyHelper.h"
#include <string>

using namespace std;
USING_NS_CC;
class CCBtnBase: public CCMenuItemSprite
{
public:
	struct Config{
		string normalImg;
		string selectedImg;
		string disableImg;
		float x1;
		float x2;
		float y1;
		float y2;
		float gap;
		string fontName;
		float fontSize;
		ccColor3B fontColor;

		Config()
		{
			x1 = 0;
			x2 = 0;
			y1 = 0;
			y2 = 0;
			gap = 10;
			fontColor = ccWHITE;
		}
	};
public:
	CCBtnBase(void);
	virtual ~CCBtnBase(void);

	static CCBtnBase* create(CCObject *rec, SEL_MenuHandler selector, 
		const Config* pconfig, const char* label);

	bool initWithConfig(CCObject *rec, SEL_MenuHandler selector, 
		const Config* pconfig, const char* label);

	static CCMenu* createMenu(CCObject *rec, SEL_MenuHandler selector, 
		const Config* pconfig, const char* label, int tagId=-1, float posx=0, float posy=0, 
		CCMyHelper::POSITION_TYPE postype=CCMyHelper::POSITION_TYPE_CENTER);
};


//checkbox·â×°
class CCCheckBox: public CCMenu
{
public:
	CCCheckBox(void);
	virtual ~CCCheckBox(void);

	static CCCheckBox* create(const char* onImg, const char* offImg,
		CCObject* target, SEL_MenuHandler selector, bool imgIsFrame =false,
		int tagId=-1);

	bool initCCCheckBox(const char* onImg, const char* offImg,
		CCObject* target, SEL_MenuHandler selector, bool imgIsFrame = false,
		int tagId=-1);

	inline bool getState()
	{
		return m_state;
	}

	void setState(bool v);

	void catchMenu(CCObject* target);

protected:
	CCMenuItemToggle* m_toggle;
	CCMenuItem* m_select;
	CCMenuItem* m_unselect;
	bool m_state;
	CCObject* m_saveTarget;
	SEL_MenuHandler m_saveSelector;
	bool m_block;
};
