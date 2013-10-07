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
	//Ŀǰֻ֧��\n
	static string escapeStr(const char* str, vector<string>* pVars=NULL);

	//delm���ַ�����",:"��ʾ����,����:�ͷָ�
	//input�Լ�ע����NULL��β���ַ���
	static void split(const char* input, const char* delim, vector<string>& output);
};
