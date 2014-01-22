#include "CSwitchTouchWindow.h"
#include "CCTouchDispatcherExt.h"

CSwitchTouchWindow::CSwitchTouchWindow(void)
{
}

CSwitchTouchWindow::~CSwitchTouchWindow(void)
{
	CCTouchDispatcherExt* td = dynamic_cast<CCTouchDispatcherExt*>(CCDirector::sharedDirector()->getTouchDispatcher());
	if(td)
	{
		td->useExtHandles(false);
	}
}

CSwitchTouchWindow* CSwitchTouchWindow::create()
{
	CSwitchTouchWindow *pRet = new CSwitchTouchWindow();
	if(pRet && pRet->initCSwitchTouchWindow())
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CSwitchTouchWindow::initCSwitchTouchWindow()
{
	bool ret=false;
	do{

		CCTouchDispatcherExt* td = dynamic_cast<CCTouchDispatcherExt*>(CCDirector::sharedDirector()->getTouchDispatcher());
		if(td)
		{
			td->useExtHandles(true);
		}

		ret = true;
	}while(0);

	return ret;
}

