#pragma once

#include "CWindowBase.h"
#include <string>
using namespace std;

class CBuffIconWindow:public CCWindowBase
{
public:
	CBuffIconWindow(void);
	virtual ~CBuffIconWindow(void);

	static CBuffIconWindow* create(int iconID, int effectCnt=1);
	bool initCBuffIconWindow(int iconID, int effectCnt=1);
	void changeEffectCnt(int effectCnt);

protected:
	string createBuffFrameName(int id);
	int m_taglabel;
};
