#pragma once

#include "CSceneWindow.h"

class CBattleMapScene:public CCESceneWindow
{
public:
	CBattleMapScene(void);
	virtual ~CBattleMapScene(void);

protected:
	virtual bool showMainWindow();
};
