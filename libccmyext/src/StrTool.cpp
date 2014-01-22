#include "StrTool.h"
#include <stdlib.h>

CStrTool::CStrTool(void)
{
}

CStrTool::~CStrTool(void)
{
}

string CStrTool::strDecimal(int num)
{
	char buff[32];
	sprintf(buff, "%d", num);
	return buff;
}

string CStrTool::strDecimalLL(long long num)
{
	char buff[64];
	sprintf(buff, "%lld", num);
	return buff;
}

string CStrTool::strHex(int num)
{
	char buff[32];
	sprintf(buff, "0x%x", num);
	return buff;
}

string CStrTool::strHexLL(long long num)
{
	char buff[64];
	sprintf(buff, "0x%llx", num);
	return buff;
}

string CStrTool::escapeStr(const char* str, vector<string>* pVars)
{
	//长度只会短不会长
	int newstrlen = 0;
	string ret;
	ret.reserve(strlen(str)*2);
	do{
		int i=0;
		for(; str[i]!=0; ++i)
		{
			char cur = str[i];
			if(cur == '\\')
			{
				char next = str[i+1];
				if(next=='n')
				{
					++i;
					ret.push_back('\n');
					continue;
				}
			}
			else if(pVars && cur == '$')
			{
				char next = str[i+1];
				if(next >= '1' && next < '9')
				{
					//$1~$9
					unsigned int idx = next - '1';
					if(idx < pVars->size())
					{
						++i;
						ret.append(pVars->at(idx));
						continue;
					}
				}
			}

			ret.push_back(cur);
		}
	}while(0);
	return ret;
}

void CStrTool::split(const char* input, const char* delim, vector<string>& output)
{
	int start = 0;
	int i=0;
	for(; input[i]!=0; ++i)
	{
		for(int j=0; delim[j]!=0; ++j)
		{
			if(input[i] == delim[j])
			{
				if(i>start)
				{
					output.push_back(string(input+start, i-start));
				}
				else if(i == start)
				{
					output.push_back("");
				}
				start = i+1;
				break;
			}
		}
	}

	if(i>start)
	{
		output.push_back(string(input+start, i-start));
	}
	else if(i == start)
	{
		output.push_back("");
	}
}

long long CStrTool::strToLL(const char* str)
{
#ifdef _WINDOWS
	return _atoi64(str);
#else
	return atoll(str);
#endif
}
