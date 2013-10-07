#pragma once

#include "CSceneWindow.h"
#include "CBarBase.h"

class CBattleScene : public CCESceneWindow
{
public:
	void onLoginClose(CCObject* obj);

protected:
	virtual void onFrameMsg(CCObject* msg);
	virtual bool showMainWindow();
	virtual bool beforePreloadWindow();
	virtual bool onPreloadProcess();
	void updateLable();

	bool fillPreloader();
	bool fillPreloadUnit(int unitid);
	bool fillPreloadBattle(int backgroundId);
	bool fillPreloadEffect(int effectid);

protected:
	CCWindowBase* m_processView;
	CBarBase* m_processBar;
	int m_tagLableFile;
	int m_tagLableBytes;
	int m_savebackgroundId;
};

