#pragma once
#include <string>
#include <vector>
using namespace std;

class CStrTool
{
public:
	CStrTool(void);
	~CStrTool(void);

	static string strDecimal(int num);
	static string strDecimalLL(long long num);
	static string strHex(int num);
	static string strHexLL(long long num);
	static long long strToLL(const char* str);
	//目前只支持\n
	static string escapeStr(const char* str, vector<string>* pVars=NULL);

	//delm是字符集合",:"表示遇到,或者:就分割
	//input自己注意是NULL结尾的字符串
	static void split(const char* input, const char* delim, vector<string>& output);
};
