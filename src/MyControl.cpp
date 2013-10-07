#include "MyControl.h"
#include "StrTool.h"

CMyControl* CMyControl::sharedControl = NULL;

CMyControl::CMyControl(void)
{
	
}

CMyControl::~CMyControl(void)
{
	unregistAll();
}

CMyControl* CMyControl::getSharedControl()
{
	if(sharedControl == NULL)
	{
		sharedControl = new CMyControl();
	}

	return sharedControl;
}

