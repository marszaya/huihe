#pragma once

#include "CWindowBase.h"
#include "CActionNode.h"
#include "CActionProcedure.h"
#include "CActionParam.h"
#include <map>
#include <string>
using namespace std;

class CCEActionManager:public CCWindowBase
{
public:
	CCEActionManager(void);
	virtual ~CCEActionManager(void);

	static CCEActionManager* create(void);
	bool initCCEActionManager(void);
	void onActionNotify(CCObject* obj);

protected:
	int startProcedure(CCEActionProcedure* p);
	CCEActionProcedure* getProcedure(int tag);
	void removeProcedure(int tag);
	void removeAllProcedures();
	virtual void onProcedureEnd(int tag);

protected:
	map<int, CCEActionProcedure*> m_procedures;
	int m_maxProcedureTag;
};
