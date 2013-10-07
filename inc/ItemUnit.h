#pragma once
#include "CWindowBase.h"
#include "tconfManager.h"

class CItemUnit: public CCWindowBase
{
public:
	static int DEFAULT_HEIGHT;
	static int DEFAULT_WIDTH;

	enum SHOW_TYPE{
		SHOW_TYPE_SIMPLE,
		SHOW_TYPE_DETAIL
	};

public:
	CItemUnit(void);
	virtual ~CItemUnit(void);

	static CItemUnit* create(int subtype, int num=1, int type=SHOW_TYPE_DETAIL);
	bool initCItemUnit(int subtype, int num, int type);

	static CCSprite* createItemPic(int subtype);

	void updateCItemUnit(int num);

	inline const TconfRow* getConf()
	{
		return m_conf;
	}

protected:
	int m_id;
	int m_nameTag;
	int m_descTag;
	int m_numTag;
	const TconfRow* m_conf;
	CCWindowBase* m_picWin;
	string m_descCache;
};

