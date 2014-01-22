#include "logToFile.h"
//#include "windows.h"

CCULogToFile gTheGlobeLog;

bool CCULogToFile::open(const char* filePath)
{
	closeNowFile();
	m_pf = fopen(filePath, "w");
	if(m_pf == NULL)
	{
		return false;
	}

	m_isOpen = true;
	return true;
}

int CCULogToFile::closeNowFile()
{
	if(m_pf && m_isOpen)
	{
			fclose(m_pf);
	}

	m_pf = NULL;
	m_isOpen = false;

	return 0;
}