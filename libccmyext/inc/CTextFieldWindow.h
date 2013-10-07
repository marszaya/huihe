#pragma once
#include "cocos2d.h"
#include "CWindowBase.h"
#include <string>
USING_NS_CC;
using namespace std;

class CCTextFieldTTFPos: public CCTextFieldTTF
{
public:
	CCTextFieldTTFPos();
	virtual ~CCTextFieldTTFPos();

	static CCTextFieldTTFPos* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    virtual void setString(const char *text);
	void bindPos(const CCPoint& pos, CCMyHelper::POSITION_TYPE postype=CCMyHelper::POSITION_TYPE_BOTTOM_LEFT);
	
	void setCallBack(CCObject* target, SEL_CallFuncO func);

	inline void setMaxLen(int maxLen)
	{
		m_maxLen = maxLen;
	}

	inline void bindString(string* psave)
	{
		m_psave = psave;
	}

protected:
	CCPoint m_pos;
	CCMyHelper::POSITION_TYPE m_postype;
	int m_maxLen;
	string* m_psave;
	SEL_CallFuncO m_callback;
	CCObject* m_cbobj;
};

class CCTextFieldWindow:public CCWindowBase
{
public:
	CCTextFieldWindow(void);
	virtual ~CCTextFieldWindow(void);
 	static CCTextFieldWindow* create(float width, float height, 
		const CCMyHelper::FONT_INFO& font, int maxLen);
	bool initWithFontConfig(float width, float height, 
		const CCMyHelper::FONT_INFO& font, int maxLen);

	void setHintSprite(CCSprite* sp);

	inline void enableInput()
	{
		if(m_pfield)
		{
			m_pfield->attachWithIME();
		}
	}

	inline void disableInput()
	{
		if(m_pfield)
		{
			m_pfield->detachWithIME();
		}
	}

	inline const char*  getInputStr()
	{
		if(m_pfield)
		{
			return m_pfield->getString();
		}
	}

	inline void bindString(string* psave)
	{
		if(m_pfield)
		{
			m_pfield->bindString(psave);
		}
	}

	inline void setString(const char* str)
	{
		if(m_pfield)
		{
			m_pfield->setString(str);
			updateHintPos();
		}
	}

protected:
	virtual void textCallBack(CCObject* obj);

protected:
	void updateHintPos();

protected:
	CCTextFieldTTFPos* m_pfield;
	CCSprite* m_hint;
};
