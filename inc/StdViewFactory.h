#pragma once

#include "CBtnBase.h"
#include "CPageNav.h"
#include "SwitchTouchWindow.h"

class CStdViewFactory
{
public:
	enum DIALOG_TYPE{
		DIALOG_TYPE_CONFIRM,
		DIALOG_TYPE_ALERT
	};
	enum DIALOG_DELEGATE_CMD{
		DIALOG_OK,
		DIALOG_CANCEL
	};
public:
	CStdViewFactory(void);
	~CStdViewFactory(void);

	static void initFactory();

	static CCMenu* createBtn(CCObject *rec, SEL_MenuHandler selector, const char* label,
		int tag=-1, float posx=0, float posy=0, 	CCMyHelper::POSITION_TYPE postype=CCMyHelper::POSITION_TYPE_CENTER);

	static CCMenu* createCloseBtn(CCObject *rec, SEL_MenuHandler selector, int tag=-1);

	static CCCheckBox* createCheckBox(const char* onImg, const char* offgImg,
		bool isopen, int tag=-1);

	//sign < 0 表示负数用-号前缀
	//sign = 0表示不使用+号前缀
	//sign > 0 使用+号前缀
	static CCLabelAtlas* createNum(unsigned int number, int sign, float scale=0);

	//type=0, 拉伸
	//type=1, 平铺
	static CCNode* create9ScaleBg(const char* img, float width, float height, 
		float cornerX, float cornerY, int type=0);

	inline static CCNode* createSmallBg(float width, float height)
	{
		return create9ScaleBg("mainScene/samllBg.png", width, height, 16, 16, 1);
	}

	inline static CCNode* createPopUpBg(float width=STD_POP_WINDOW_WIDTH, 
		float height=STD_POP_WINDOW_HEIGHT)
	{
		return create9ScaleBg("mainScene/popUp.png", width, height, 170, 50, 0);
	}

	static bool configPageNav(CCEPageNav* pageNav);

	static bool createTabNode(const char* label,CCNode*& outputSel, CCNode*& outputUnSel);

	static CCNode* createBorderForNode(CCNode* target);

	static CCWindowBase* createDialog(const char* msg, CCUCommonDelegate* pdelegate, 
		DIALOG_TYPE type=DIALOG_TYPE_CONFIRM, bool needSwitchTouch=true);

	static const float STD_POP_WINDOW_WIDTH;
	static const float STD_POP_WINDOW_HEIGHT;
	static CCMyHelper::FONT_INFO LABEL_FONT;
};
