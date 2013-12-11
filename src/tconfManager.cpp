#include "tconfManager.h"


CTconfManager::CTconfManager()
{
}

CTconfManager* CTconfManager::m_instance = NULL;

CTconfManager* CTconfManager::sharedInstance()
{
	if(m_instance == NULL)
		m_instance = new CTconfManager();
	return m_instance;
}

void CTconfManager::releaseInstance()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

CTconfManager::~CTconfManager()
{
	for(map<string, CTconfHelper*>::iterator it=m_allconf.begin(); it!=m_allconf.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}
}

CTconfHelper* CTconfManager::getConf(const char* confName)
{
	map<string, CTconfHelper*>::iterator it = m_allconf.find(confName);
	if(it == m_allconf.end())
	{
		return NULL;
	}

	return it->second;
}

void CTconfManager::setConf(const char* confName, CTconfHelper* conf)
{
	if(!conf->isValid())
		throw string(confName).append("|").append(conf->getError());
	m_allconf[confName] = conf;
}

#define TCONF_LOAD(confClass, filePath, idxCol) setConf( #confClass, new confClass(filePath, idxCol))

int CTconfManager::loadAll(const char* configDir)
{
	TCONF_LOAD(CAutoBattleTab, string(configDir).append("/conf/battle.bin").c_str(), 0);
	TCONF_LOAD(CAutoNPCTab, string(configDir).append("/conf/npc.bin").c_str(), 0);
	TCONF_LOAD(CAutoNPCAttrTab, string(configDir).append("/conf/npcAttr.bin").c_str(), 0);
	TCONF_LOAD(CAutoItemTab, string(configDir).append("/conf/item.bin").c_str(), 0);
	TCONF_LOAD(CAutoExprTab, string(configDir).append("/conf/expr.bin").c_str(), 0);
	TCONF_LOAD(CAutoStrTab, string(configDir).append("/conf/str.bin").c_str(), 0);
	TCONF_LOAD(CAutoEquipTab, string(configDir).append("/conf/equip.bin").c_str(), 0);
	TCONF_LOAD(CAutoShopTab, string(configDir).append("/conf/shop.bin").c_str(), 0);
	TCONF_LOAD(CAutoItemPackTab, string(configDir).append("/conf/itempack.bin").c_str(), 0);
	TCONF_LOAD(CAutoMapTab, string(configDir).append("/conf/map.bin").c_str(), 0);
	TCONF_LOAD(CAutoSkillTab, string(configDir).append("/conf/skill.bin").c_str(), 0);
	TCONF_LOAD(CAutoUnitShowTab, string(configDir).append("/conf/unitshow.bin").c_str(), 0);
	TCONF_LOAD(CAutoUnitTab, string(configDir).append("/conf/unit.bin").c_str(), 0);
	TCONF_LOAD(CAutoUnitBuyTab, string(configDir).append("/conf/unitbuy.bin").c_str(), 0);
	TCONF_LOAD(CAutoUnitRandomTab, string(configDir).append("/conf/unitrandom.bin").c_str(), 0);
	return 0;
}
