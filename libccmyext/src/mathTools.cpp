#include "mathTools.h"
#include <time.h>
CMZMathTools::CMZMathTools(void)
{
	m_rseed = (int)(time(NULL))-155;
}

CMZMathTools::~CMZMathTools(void)
{
}

CMZMathTools gGameTools;