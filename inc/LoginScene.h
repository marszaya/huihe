#pragma once

#include "CSceneWindow.h"

class CLoginScene : public CCESceneWindow
{
public:
	void onLoginClose(CCObject* obj);

protected:
	virtual void onFrameMsg(CCObject* msg);
	virtual bool showMainWindow();
};
 
