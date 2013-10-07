#ifndef __CHARCODE_CVT_H__
#define __CHARCODE_CVT_H__
#include <windows.h>
#include <tchar.h>
#include <string>

class CMZIconvUtil
{
public:
	/*
	static int easyIconv(std::string &inOutStr£¬const char* toCode£¬const char* formCode)
	{
		iconv_t iconvH;  
		iconvH = iconv_open(formCode£¬toCode);

		if(iconvH == 0)  
		{   
¡¡¡¡			return -1;
		}

		const char* strChar = inOutStr.c_str();
		const char** pin = &strChar;
		size_t strLength = inOutStr.length();
		char* outbuf = (char*)malloc(strLength*4);
		memset(outbuf£¬0£¬strLength*4);  
		size_t outLength = strLength*4;

		if(-1 == iconv(iconvH£¬pin£¬&strLength£¬&outbuf£¬&outLength))
		{
				iconv_close(iconvH);
				free(outbuf);
				return -1;
		}

		inOutStr = outbuf;
		free(outbuf);
		iconv_close(iconvH); 
		return 0;
	}

	static GBKToUTF8(std::string &inOutStr)
	{
		return easyIconv(inOutStr, "gb2312"£¬"utf-8");
	}*/

	static std::string WCharToUTF8( LPCWSTR pwchar)
	{
		std::string strOutUTF8;
		int n = WideCharToMultiByte(CP_UTF8, 0, pwchar, -1, NULL, 0, NULL, NULL);
		char * str2 = new char[n];
		WideCharToMultiByte(CP_UTF8, 0, pwchar, -1, str2, n, NULL, NULL);
		strOutUTF8 = str2;
		delete[]str2;
		str2 = NULL;
		return strOutUTF8;
	}

	static std::string GBKToUTF8(const std::string& strGBK)
	{
		std::string strOutUTF8 = "";
		WCHAR * str1;
		int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
		str1 = new WCHAR[n];
		MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
		n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
		char * str2 = new char[n];
		WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
		strOutUTF8 = str2;
		delete[]str1;
		str1 = NULL;
		delete[]str2;
		str2 = NULL;
		return strOutUTF8;
	}

	static std::string UTF8ToGBK(const std::string& strUTF8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
		unsigned short * wszGBK = new unsigned short[len + 1];
		memset(wszGBK, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);

		len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
		char *szGBK = new char[len + 1];
		memset(szGBK, 0, len + 1);
		WideCharToMultiByte(CP_ACP,0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
		//strUTF8 = szGBK;
		std::string strTemp(szGBK);
		delete[]szGBK;
		delete[]wszGBK;
		return strTemp;
	}

};


#endif