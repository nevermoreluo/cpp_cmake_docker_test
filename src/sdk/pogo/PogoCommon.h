 //
// (C) Electronic Arts 2006
// 
//	Module: EventListener
//	Author: Joey Chang x83016
//  	Desc:	Defines common types, includes, etc.
//
#pragma once
#include <assert.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "boost/smart_ptr.hpp"
#include "boost/cast.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/lexical_cast.hpp"
#include <time.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char byte;

#include "UpdateMaskSingle.h"
#include "IdGenerator.h"

#define IS_TYPE(x,y) (dynamic_cast<y *>(x) != NULL)

#ifdef _DEBUG
#define POGO_ASSERT(x)	if (!(x)) { assert(x); }
#else
#define POGO_ASSERT(x)
#endif

#ifndef _WIN32
typedef unsigned long DWORD;
typedef unsigned long DWORD_PTR, *PDWORD_PTR;
typedef unsigned short WORD;
typedef long LONG;
#endif

namespace Pogo
{
	enum TIME_TYPE
	{
		// 秒
		TIME_TYPE_SECOND						= 1,
		// 分钟
		TIME_TYPE_MINUTE						= TIME_TYPE_SECOND * 60,
		// 小时
		TIME_TYPE_HOUR							= TIME_TYPE_MINUTE * 60,
		// 天
		TIME_TYPE_DAY							= TIME_TYPE_HOUR * 24,
		// 周
		TIME_TYPE_WEEK							= TIME_TYPE_DAY * 7,
		// 年
		TIME_TYPE_YEAR							= TIME_TYPE_DAY * 365,
	};

#ifdef _WIN32
	long GetBrowserVersion(unsigned long *pdwMajor, unsigned long *pdwMinor, unsigned long *pdwBuild);
	std::string GetRegKey(std::string path, std::string value);
#endif

	// PogoUtils - Miscellaneous utility functions for Pogo
	std::string WideToNarrow( const std::wstring &source );
	std::wstring NarrowToWide( const std::string &source );
	std::wstring StringToUpper(const std::wstring& theString);
	std::wstring StringToLower(const std::wstring& theString);
	void CreateThread(class Runnable *thread);
	std::string WideToUTF8( const std::wstring &source );
	std::wstring UTF8ToWide( const std::string &source );
	std::wstring MakeString( const std::vector<std::wstring> &input );
	std::string MakeNumberString( int number );			// this routine is intended to make a more human-readable (but non-localized) string by adding commas
	std::wstring MakeNumberWideString( int number );	// this routine is intended to make a more human-readable (but non-localized) string by adding commas
	std::vector<std::wstring> MakeStringVector( const std::wstring &input );
	bool StringVectorContains(const std::vector<std::wstring> &vec, const std::wstring &string);
	std::string MakeNumberToStringEx(int nNumber, std::string strSplit);

	bool GZipUnzip(const char *infile, const char *outfile);

	void mkDir(const std::string& path);
	void mkDir(const std::wstring& path);

	int swnprintf(wchar_t *wcs, size_t maxlen, const wchar_t *format, ... );
	int snprintf(char *wcs, size_t maxlen, const char *format, ... );

	int atoi(const char *str);
	int atoi(const wchar_t *str);

	float atof(const char *str);
	float atof(const wchar_t *str);

	void zeroMemory(void *mem, size_t length);

	void setCurrentDir(const char *path);

	void sleep(int ms);

	std::string unicode_2_string_ex(const char* str_unicode);
	std::string string_2_unicode_ex(const char* str);
	std::vector<std::string> explode(const char *sep, std::string src);

	uint GetTodayTime(int nHours, int nMinutes);
	// 使用该函数可以获得周一的任意时间点事件
	uint GetWeekTime(int nMinutes = 0, int nHours = 0, int nWeeks = 1);
	// 计算整点时间 例如13:30分 计算后得 13:00 by lk 2011-11-29
	int CaclOnTheHour(int nCurrTime);

#ifndef WIN32
#define MAKELONG(a, b) ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xFFFF)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xFFFF))) << 16))
#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xFFFF))
#define HIWORD(l) ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xFFFF))
#endif

	int MakeLong(int a, int b);
	int LowWord(int l);
	int HighWord(int l);

	unsigned int ConvertStrToTime(const char * pszDate);
}
