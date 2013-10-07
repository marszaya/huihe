#pragma once

#include "CWindowBase.h"
class CPveMap:public CCWindowBase
{
public:
	CPveMap(void);
	virtual ~CPveMap(void);

	static CPveMap* create(int mapId);
	bool initCPveMap(int mapId);

	void onBattleSelected(CCObject* obj);

	void onClose(CCObject* obj);

protected:
	virtual void onFrameMsg(CCObject* msg);

protected:
	int m_mapId;
	int m_sceneFlag;
};
