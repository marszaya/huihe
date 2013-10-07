#include "STRTABLE.h"
#include "tconfManager.h"

const char* CStrTableHelper::sStrNotFound = "???";

const char* CStrTableHelper::getStrById(const char* id) 
{
	CAutoStrTab* strtab = TCONF_GET(CAutoStrTab);
	const char* v = strtab->getValue(id, strtab->V);
	if(v)
	{
		return v;
	}
	else
	{
		return sStrNotFound;
	}
}