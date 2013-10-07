#pragma once
#include "CWindowBase.h"

class CAttrLabel:public CCWindowBase
{
public:
	CAttrLabel(void);
	virtual ~CAttrLabel(void);


	void changeValue(const char* v);

	static CAttrLabel* createHpLabel(int v, bool withSign = false);
	static CAttrLabel* createAtkLabel(int v, bool withSign = false);
	static CAttrLabel* createDefLabel(int v, bool withSign = false);
	static CAttrLabel* createSpdLabel(int v, bool withSign = false);
	static CAttrLabel* createNameLabel(const char* name);
	static CAttrLabel* createShortNameLabel(const char* name);
	static CAttrLabel* createLevelLabel(int level);
	static CAttrLabel* createShortLevelLabel(int level);
	static CAttrLabel* createExpLabel(long long expr);
	static CAttrLabel* createGoldLabel(long long gold);
	static CAttrLabel* createMoneyLabel(long long money);
	static CAttrLabel* createEffectLabelById(int effectId, int effectValue, bool withSign = false);

protected:
	void showLabel();
	static CAttrLabel* create();

protected:
	int m_hintID;
	const char* m_iconFrame;
	string m_value;
	int m_valueLabel;
	int m_vlx;
	int m_vly;
	string m_bgName;
	int m_windowWidth;
	int m_windowHeight;
	CCMyHelper::FONT_INFO m_font;
};