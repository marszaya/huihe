#ifndef __LOG_TO_FILE_H__
#define __LOG_TO_FILE_H__

#include <stdlib.h>
#include <stdio.h>

#define CCU_LOGOPEN(filePath) gTheGlobeLog.open(filePath)
#define CCU_LOGF(format, ...) fprintf(gTheGlobeLog.getFp(), format, ##__VA_ARGS__)

class CCULogToFile
{
protected:
	FILE* m_pf;
	bool m_isOpen;

public:
	CCULogToFile()
	{
		setFp(stdout);
	}

	~CCULogToFile()
	{
		closeNowFile();
	}

	bool open(const char* filePath);

	inline void setFp(FILE* pf)
	{
		closeNowFile();
		m_pf = pf;
	}

	inline FILE* getFp()
	{
		return m_pf;
	}

protected:
	int closeNowFile();
};

extern CCULogToFile gTheGlobeLog;

#endif