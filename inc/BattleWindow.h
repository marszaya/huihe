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

	//��һ��ս��
	void onNext(CCObject* obj);

	//�Զ���һ��ս������ȡ��
	void onAuto(CCObject* obj);

	//�Ժ�ʵ������ս�� 

	//ÿִ֡��
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
	int m_nextFlag; //��ť״̬��ֻ�ܵ��һ��
	int m_autoFlag; //��ť״̬�����ε������ȡ��
	CCMenu* m_pbtnNext;
	CCMenu* m_pbtnAuto;
	CBattleSpeed* m_spd;
};
