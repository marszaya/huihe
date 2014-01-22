#pragma once

#include "MyData.h"
#include "CMyHelper.h"
#include "CSceneWindow.h"
#include <vector>
using namespace std;

class CMainScene : public CCESceneWindow
{
public:
	enum BtnTags{
		BTN_TAG_INIT=100,
		BTN_TAG_BTN_ROLE,
		BTN_TAG_BTN_BAG,
		BTN_TAG_BTN_BATTLE,
		BTN_TAG_BTN_SHOP,
		BTN_TAG_BTN_ROLE_HIRE,
		BTN_TAG_BTN_ROLE_BATTLE_LIST
	};

	enum ChildTags{
		CHILD_LAYER_ACCOUNT=1,
		CHILD_POPUP_ROLE,
		CHILD_POPUP_BAG,
		CHILD_POPUP_BATTLE,
		CHILD_POPUP_SHOP,
		CHILD_POPUP_ROLE_HIRE,
		CHILD_POPUP_ROLE_BATTLE_LIST
	};

	
public:
	CMainScene();

	//menu callback function
	void onBtn(CCObject* target);

	//CMD callback
	virtual void onFrameMsg(CCObject* msg);

protected:

	virtual bool showMainWindow();

	//设置主界面按钮
	bool setBtn(int tag, const char* img, const char* img2, const CCPoint & initPos, CCMyHelper::POSITION_TYPE postype=CCMyHelper::POSITION_TYPE_CENTER);

protected:
	void disableBtn(int tag);
	void enableBtn(int tag);
	inline void disableBtns()
	{
		for(unsigned int i=0; i<m_allBtns.size(); ++i)
		{
			disableBtn(m_allBtns[i]);
		}
	}
	inline void enableBtns()
	{
		for(unsigned int i=0; i<m_allBtns.size(); ++i)
		{
			enableBtn(m_allBtns[i]);
		}
	}


protected:
	vector<int> m_allBtns;
	int m_nextSceneFlag;
};
