#pragma once

#include "tconf.pb.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <map>
#include <string>

using namespace std;

//#define TCONF_USE_XML


class CTconfHelper
{
protected:
	TconfTable m_table;
	ostringstream m_err;
	bool m_valid;
	int m_colIdx;
	map<string, int> m_colIdxMap;
	map<string, int> m_rowIdxMap;

public:
	CTconfHelper();
	virtual ~CTconfHelper();

	inline bool isValid()
	{
		return m_valid;
	}

	inline const TconfTable& getTable()
	{
		return this->m_table;
	}

	inline string getError()
	{
		return this->m_err.str();
	}

	const ::TconfRow* getRowByKey(const char*  key);

	inline const char* getRowValue(const ::TconfRow* prow, const char* colName)
	{
		int idx = getColIdx(colName);
		if(idx < 0)
			return NULL;
		return prow->values(idx).c_str();
	}

	inline const char* getValue(const char* key, const char* colName)
	{
		const ::TconfRow* p = getRowByKey(key);
		if(p==NULL)
			return NULL;
		return getRowValue(p, colName);
	}

protected:
	void init(const char* filePath, int colIdx=-1);

	int loadFromFile(const char* filePath);

#ifdef TCONF_USE_XML
	int loadFromXML(const char* filePath);
#endif

	virtual int selfCheck();

	int getColIdx(const char*  col);

	int createIdx();
};
