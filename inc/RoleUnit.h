#pragma once
#include "CWindowBase.h"
#include "tconfManager.h"
#include "MyData.h"

/*
* ’ΩΩ´Àı¬‘œ‘ æ
*/
class CRoleUnit: public CCWindowBase
{
public:
	static const int DEFAULT_HEIGHT=100;
	static const int DEFAULT_WIDTH=180;

public:
	CRoleUnit(void);
	virtual ~CRoleUnit(void);

	static CRoleUnit* create(const Role* prole);
	bool initCRoleUnit(const Role* prole);

	void updateCRoleUnit(const Role* prole);

	inline const TconfRow* getConf()
	{
		return m_conf;
	}

	static CCSprite* createPic(int picid);

	inline const char* getRoleId()
	{
		return m_roleID.c_str();
	}

protected:
	string m_roleID;
	CCSprite* m_pic;
	const TconfRow* m_conf;
};
