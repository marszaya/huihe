#pragma once
#include "cocos2d.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;
USING_NS_CC;

class CCPreLoad:public CCObject
{
public:
	enum RESOURCE_TYPE{
		RESOURCE_TYPE_PIC=1,
		RESOURCE_TYPE_FRAMES=2
	};
public:
	CCPreLoad();
	~CCPreLoad(void);

	static CCPreLoad* create(const char* configXML, bool checkSize=false);
	bool initCCPreLoad(const char* configXML, bool checkSize=false);

public:
	
	int addPreLoadPic(const char* pic);
	int addPreLoadFrames(const char* pic);

	int dumpXML(ostream& out);

	//fileName will be write to the dir is which .exe file is in
	inline int dumpXMLToExeDir(const char* fileName)
	{	
		string tmp  = CCFileUtils::sharedFileUtils()->getWritablePath().append(fileName);
		return dumpXMLToFile(tmp.c_str());
	}

	inline int dumpXMLToResDir(const char* fileName)
	{
		string tmp = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
		return dumpXMLToFile(tmp.c_str());
	}

	int dumpXMLToFile(const char* fileName);

	int loadAll();
	inline void resetFetch()
	{
		if(m_tmpKeyArr)
		{
			m_tmpKeyArr->release();
			m_tmpKeyArr = NULL;
		}
		m_tmpIdx = -1;
		m_tmpFileSize = 0;
		m_tmpLoadedBytes = 0;
		m_tmpLoadedFile = 0;
		m_tmpTotalBytes = 0;
		m_tmpFileName = "";
		m_tmpFrames.clear();
	}

	//return -1=error, 0=no more, 1=ok
	int fetchNext();
	int loadCurFile();

	inline int getFileTotal()
	{
		if(!m_dict)
			return 0;
		return m_dict->count();
	}

	int getLoadedBytes()
	{
		return m_tmpFileSize;
	}

	int getLoadedTotalBytes()
	{
		return m_tmpLoadedBytes;
	}

	inline int getLoadedFiles()
	{
		return  m_tmpLoadedFile;
	}
	
	int getTotalBytes();

	inline int getCachedTotalBytes()
	{
		return m_tmpTotalBytes;
	}

	inline void setCheckSize(bool v)
	{
		m_checkSize = v;
	}

	inline bool getCheckSize()
	{
		return m_checkSize;
	}

	inline string getCurFileName()
	{
		return m_tmpFileName;
	}

	inline map<string, CCSpriteFrame*>& currentFrames()
	{
		return m_tmpFrames;
	}

protected:
	int dumpToXMLSingle(CCDictionary* dict, ostream& out);
	int addSingle(const char* pic, int type, int size=0);
	int initFetch();
	int loadSingle(const char* key, CCDictionary* dict);

	bool cacheFramesForPlist(const char* plist, const char* textureFileName);

protected:
	CCDictionary* m_dict;
	CCArray* m_tmpKeyArr;
	int m_tmpIdx;
	int m_tmpFileSize;
	int m_tmpLoadedBytes;
	int m_tmpLoadedFile;
	int m_tmpTotalBytes;
	map<string, CCSpriteFrame*> m_tmpFrames;
	bool m_checkSize;
	bool m_currentIsFrames;
	string m_tmpFileName;
};


