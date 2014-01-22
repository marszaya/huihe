#pragma once

#include "cocos2d.h"
#include <map>
#include <string>
using namespace std;
USING_NS_CC;
class CCUTextureHolder:public CCObject
{
protected:
	static CCUTextureHolder* sSharedInstance;

protected:
    CCDictionary* m_pTextures;
	CCDictionary* m_pFrames;

public:
	CCUTextureHolder(void);
	virtual ~CCUTextureHolder(void);

	static CCUTextureHolder* getSharedInstance();
	static void removeSharedInstance();

	void retainTexture(const char* name);
	void releaseTextrue(const char* name);

	void retainFrames(map<string, CCSpriteFrame*>& frames);
	//release 不咋可能了。。
};

