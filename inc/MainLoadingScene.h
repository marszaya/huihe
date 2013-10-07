#pragma once

#include "CSceneWindow.h"

class CMainLoadingScene : public CCESceneWindow
{
public:
	void onLoginClose(CCObject* obj);

protected:
	virtual void onFrameMsg(CCObject* msg);
	virtual bool showMainWindow();
	virtual bool beforePreloadWindow();
	virtual bool onPreloadProcess();
	void updateLable();

protected:
	CCWindowBase* m_processView;
	int m_tagLableFile;
	int m_tagLableBytes;
};

