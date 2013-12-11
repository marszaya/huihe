#pragma once

#include "CWindowBase.h"
//#include "MyData.h"
#include "BattleMap.h"
#include "BattleFightUnit.h"
#include "MyControl.h"
#include "BattleFightLogic.h"

#include "CWindowBase.h"
class CBattleSpeed:public CCWindowBase
{
public:
	CBattleSpeed(void);
	virtual ~CBattleSpeed(void);

	static CBattleSpeed* create();
	bool initCBattleSpeed();

	inline int getSpeed()
	{
		return m_speed;
	}

protected:
	void onPlus(CCObject* obj);
	void onMinus(CCObject* obj);

public:
	int m_speed;
	int m_speedMin;
	int m_speedMax;
	int m_tag;
public:
	const static int SWIDTH=140;
	const static int SHEIGHT=50;
};

class CBattleWindow:public CCWindowBase
{
public:
	CBattleWindow(void);
	~CBattleWindow(void);

	static CBattleWindow* create(int backgroundId);
	bool initCBattleWindow(int backgroundId);

	inline CBattleWindowMap* getBattleMap()
	{
		return m_map;
	}

	void onClose(CCObject* obj);

	//下一步战斗
	void onNext(CCObject* obj);

	//自动下一步战斗，可取消
	void onAuto(CCObject* obj);

	//以后实现跳过战斗 

	//每帧执行
	virtual void update(float dt);

protected:
	void enableNext();
	void disableNext();
	void disableAuto();
	void enableAuto();

	void showResult();
	virtual void onFrameMsg(CCObject* msg);

protected:
	CBattleWindowMap* m_map;
	CBattleFightLogic m_logic;
	int m_nextFlag; //按钮状态，只能点击一次
	int m_autoFlag; //按钮状态，二次点击可以取消
	CCMenu* m_pbtnNext;
	CCMenu* m_pbtnAuto;
	CBattleSpeed* m_spd;
};
