#pragma once

#include "CWindowBase.h"
#include "CPreLoad.h"

class CCESceneWindow:public CCWindowBase
{
public:
	CCESceneWindow(void);
	virtual ~CCESceneWindow(void);

	//preloadListXml == NULL 将跳过preload流程
	//需要在beforePreloadWindow()中自定义preload的内容，preloadListXml=""
	static CCScene* createScene(CCESceneWindow* subClassObj, 
		const char* preloadListXml=NULL, bool cleanTextureCache=true, bool checkTextrueSize=true);

	void schedulePreload(float f);

protected:
	bool initCCESceneWindow(const char* preloadListXml, bool cleanTextureCache, bool checkTextrueSize);
	virtual bool beforePreloadWindow();
	virtual bool onPreloadProcess();
	virtual bool showMainWindow();
	void cleanPreload();

protected:
	CCString* m_preloadXml;
	bool m_preloadCheckSize;
	int m_preloadFileNumPerFrame;
	CCPreLoad* m_preloader;
};
