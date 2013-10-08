#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "LoginScene.h"
#include "projectConfig.h"
#include "logToFile.h"
#include "CCTouchDispatcherExt.h"
#include "tconfManager.h"
#include "StdViewFactory.h"
#include "AppMacros.h"
#include "CCConfiguration.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
//    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();

/// my settings
	//3d会模糊
	pDirector->setProjection(kCCDirectorProjection2D);
	//加了临时屏蔽其他menu
	CCTouchDispatcherExt* ptd = new CCTouchDispatcherExt();
	if(!ptd)
	{
		return false;
	}

	if(!(ptd->init()))
	{
		return false;
	}

	pDirector->setTouchDispatcher(ptd);
/// end my settings

	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);

	CCSize frameSize = pEGLView->getFrameSize();
/*
    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
#endif
*/
	
	 vector<string> searchPath;
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

    // if the frame's height is larger than the height of medium resource size, select large resource.
/*	if (frameSize.height > mediumResource.size.height)
	{
        searchPath.push_back(largeResource.directory);

        pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    {
        searchPath.push_back(smallResource.directory);

        pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }
	*/
#ifdef _DEBUG
    // turn on display FPS
    pDirector->setDisplayStats(true);
#endif

/// my settings
	//系统配置
	CCConfiguration* pAppConf = CCConfiguration::sharedConfiguration();
	pAppConf->loadConfigFile("../../../appconf.xml");

#ifdef _DEBUG
	pAppConf->dumpInfo();
#endif

	string theResPath = pAppConf->getCString(PROJECT_CONF_KEY_RES_PATH);

	// set searching path
	searchPath.push_back(theResPath);

	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

	//MZGLOGOPEN("F:\\win8 dev\\cocos2d-2.0-x-2.0.3\\cocos2d-2.0-x-2.0.3\\huihe\\log.txt");
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / atoi(pAppConf->getCString(PROJECT_CONF_KEY_FRAME_PER_S)));

	//初始化数值配置和view factory
	try{
		CTconfManager::sharedInstance()->loadAll(theResPath.c_str());
	}
	catch(const string& e)
	{
		CCMessageBox(string("Load Conf Error: ").append(e).c_str(), "error");
		return false;
	}

	//初始化factory
	CStdViewFactory::initFactory();
/// end my settings
    // create a scene. it's an autorelease object
    CCScene *pScene = CCESceneWindow::createScene(new CLoginScene);

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    //SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
