#pragma once
#include "tconfHelper.h"
#include "AutoBattleTab.h"
#include "AutoNPCTab.h"
#include "AutoNPCAttrTab.h"
#include "AutoItemTab.h"
#include "AutoExprTab.h"
#include "AutoStrTab.h"
#include "AutoEquipTab.h"
#include "AutoShopTab.h"
#include "AutoItemPackTab.h"
#include "AutoMapTab.h"
#include "AutoSkillTab.h"
#include "AutoUnitShowTab.h"
#include "AutoUnitTab.h"
#include "AutoUnitBuyTab.h"
#include "AutoUnitRandomTab.h"
#include <map>
using namespace std;

#define TCONF_GET(confClass) dynamic_cast<confClass*>(CTconfManager::sharedInstance()->getConf(#confClass))

class CTconfManager
{
public:
	map<string, CTconfHelper*> m_allconf;

protected:
	static CTconfManager* m_instance;

protected:
	CTconfManager();
	~CTconfManager();

public:
	static CTconfManager* sharedInstance();

	static void releaseInstance();

	void setConf(const char* confName, CTconfHelper* conf);


	CTconfHelper* getConf(const char* confName);

	int loadAll(const char* configDir);
};