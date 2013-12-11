#include <stdlib.h>
#include "DataUtil.h"
#include "StrTool.h"

bool CDataUtil::getItemFromConfStr(const char* confStr, ItemSet* pitemOutput)
{
	vector<string> vout;
	CStrTool::split(confStr, ",", vout);
	for(unsigned int i=0; i<vout.size(); ++i)
	{
		vector<string> vitem;
		CStrTool::split(vout[i].c_str(), ":", vitem);
		if(vitem.size() < 2)
		{
			return false;
		}
		
		Item* p = pitemOutput->add_items();
		p->set_subtype(atoi(vitem[0].c_str()));
		p->set_num(atoi(vitem[1].c_str()));
	}

	return true;
}

int CDataUtil::getEquipAttrIdx(int subtype)
{
	int ret = -1;
	do{
		CAutoEquipTab* peqtab = TCONF_GET(CAutoEquipTab);
		if(!peqtab)
			break;
		const char* attrIdxStr = peqtab->getValue(CStrTool::strDecimal(subtype).c_str(), peqtab->ATTRIDX);
		if(attrIdxStr == NULL)
			break;

		ret = atoi(attrIdxStr);
	}while(0);
	return ret;
}

int CDataUtil::getEquipAttrValue(int subtype, int level)
{
	int ret = -1;
	do{
		CAutoEquipTab* peqtab = TCONF_GET(CAutoEquipTab);
		if(!peqtab)
			break;

		const char* attrValueStr = peqtab->getValue(CStrTool::strDecimal(subtype).c_str(), peqtab->ATTRVALUE);
		if(attrValueStr == NULL)
			break;

		const char* attrLevelValueStr = peqtab->getValue(CStrTool::strDecimal(subtype).c_str(), peqtab->ATTRLEVELUPVALUE);
		if(attrLevelValueStr == NULL)
			break;

		ret = atoi(attrValueStr)+atoi(attrLevelValueStr)*level;
	}while(0);
	return ret;
}

int CDataUtil::getEffectType(int itemid)
{
	CAutoItemTab* pitemtab = TCONF_GET(CAutoItemTab);
	const char* str = pitemtab->getValue(CStrTool::strDecimal(itemid).c_str(), pitemtab->USAGETYPE);
	if(str!=NULL)
	{
		return atoi(str);
	}

	return -1;
}

int CDataUtil::getEffectValue(int itemid)
{
	CAutoItemTab* pitemtab = TCONF_GET(CAutoItemTab);
	const char* str = pitemtab->getValue(CStrTool::strDecimal(itemid).c_str(), pitemtab->USAGEPARAM);
	if(str!=NULL)
	{
		return atoi(str);
	}

	return -1;
}

int CDataUtil::getSellPrice(int itemid)
{
	CAutoItemTab* pitemtab = TCONF_GET(CAutoItemTab);
	const char* str = pitemtab->getValue(CStrTool::strDecimal(itemid).c_str(), pitemtab->SELLPRICE);
	if(str!=NULL)
	{
		return atoi(str);
	}

	return -1;
}

int CDataUtil::getMajorType(int itemid)
{
	CAutoItemTab* pitemtab = TCONF_GET(CAutoItemTab);
	const char* str = pitemtab->getValue(CStrTool::strDecimal(itemid).c_str(), pitemtab->MAJORTYPE);
	if(str!=NULL)
	{
		return atoi(str);
	}

	return -1;
}

int CDataUtil::getFightUnitMaxByLevel(int userlevel)
{
	if(userlevel < 10)
	{
		return 2;
	}
	else if(userlevel < 20)
	{
		return 3;
	}
	else if(userlevel < 30)
	{
		return 4;
	}
	else if(userlevel < 40)
	{
		return 5;
	}
	else
	{
		return 6;
	}
}

int CDataUtil::getOwnUnitMaxByLevel(int userlevel)
{
	return 30;
}