#include "CSceneWindow.h"

CCESceneWindow::CCESceneWindow(void)
{
	m_preloadFileNumPerFrame = 5;
	m_preloader = NULL;
	m_preloadCheckSize = false;
	m_preloadXml = NULL;
}

CCESceneWindow::~CCESceneWindow(void)
{
	cleanPreload();
}

void CCESceneWindow::cleanPreload()
{
	if(m_preloadXml)
	{
		delete m_preloadXml;
		m_preloadXml = NULL;
	}

	if(m_preloader)
	{
		delete m_preloader;
		m_preloader = NULL;
	}
}


CCScene* CCESceneWindow::createScene(CCESceneWindow* subClassObj, const char* preloadListXml, 
		bool cleanTextureCache, bool checkTextrueSize)
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
		
		scene->setAnchorPoint(ccp(0,0));
		
		CCESceneWindow *pwin = subClassObj;
		if(pwin && pwin->initCCESceneWindow(preloadListXml, cleanTextureCache, checkTextrueSize))
		{
			scene->addChild(pwin);
			pwin->release();
		}
		else
		{
			CC_SAFE_DELETE(pwin);
		}
    } while (0);

    return scene;
}

bool CCESceneWindow::initCCESceneWindow(const char* preloadListXml, 
		bool cleanTextureCache, bool checkTextrueSize)
{
	bool ret=false;
	do{
		m_preloadCheckSize = checkTextrueSize;

		if(cleanTextureCache)
		{
			CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
			CCTextureCache::sharedTextureCache()->removeUnusedTextures();
		}

		if(preloadListXml)
		{
			m_preloadXml = new CCString(preloadListXml);
			m_preloader = new CCPreLoad();
			if(!m_preloader || !m_preloader->initCCPreLoad(preloadListXml, m_preloadCheckSize))
				break;

			m_preloader->getTotalBytes();

			if(!beforePreloadWindow())
				break;
		
			this->schedule(schedule_selector(CCESceneWindow::schedulePreload), 0.3, kCCRepeatForever, 0.5);
		}
		else
		{
			if(!showMainWindow())
				break;
		}
		ret = true;
	}while(0);

	return ret;
}

bool CCESceneWindow::beforePreloadWindow()
{
	return true;
}

bool CCESceneWindow::onPreloadProcess()
{
	return true;
}

bool CCESceneWindow::showMainWindow()
{
	return true;
}

void CCESceneWindow::schedulePreload(float f)
{
	bool end = true;
	for(int i=0; i<m_preloadFileNumPerFrame; ++i)
	{
		end = true;
		int ret = m_preloader->fetchNext();
		if(ret < 0)
			break;

		if(ret == 0)
		{
			if(m_preloadCheckSize)
				m_preloader->dumpXMLToResDir(m_preloadXml->getCString());
			cleanPreload();
			showMainWindow();
			break;
		}

		if(m_preloader->loadCurFile()!=0)
			break;

		if(!onPreloadProcess())
			break;

		end = false;
	}

	if(end)
	{
		this->unschedule(schedule_selector(CCESceneWindow::schedulePreload));
	}
}