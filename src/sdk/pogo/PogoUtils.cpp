
#ifdef _WIN32
#include <windows.h>		// for WideCharToMultiByte and MultiByteToWideChar
#include <Shlwapi.h>
#include <direct.h>
#pragma warning (disable : 4267)
#elif __linux__
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#endif

#include "vstdlib/strtools.h"
#include <boost/tokenizer.hpp>
#include "PogoCommon.h"
#include <boost/smart_ptr.hpp>
#include <vector>
#include "boost/algorithm/string.hpp"
#include "tier0/dbg.h"

using namespace Pogo;
using namespace boost;

#ifdef __linux__
//static iconv_t s_conv_ansi_utf8 = iconv_open("ANSI", "UTF8");
//static iconv_t s_conv_utf8_ansi = iconv_open("UTF8", "ANSI");

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

namespace Pogo
{
	// Define a wide-character tokenizer
	typedef tokenizer< escaped_list_separator<wchar_t>, std::wstring::const_iterator, std::wstring > WideTokenizer;
	typedef unsigned char byte;

void zeroMemory(void *mem, size_t length)
{
	memset(mem, 0, length);
}

std::string WideToNarrow( const std::wstring &source )
{
	size_t len = source.length() * 2;
	scoped_ptr<char> buf(new char[len + 1]);
	zeroMemory( buf.get(), (len + 1) );
#ifdef _WIN32
	WideCharToMultiByte(CP_ACP, 0, source.c_str(), (int)source.length(), buf.get(), (int)(len), NULL, NULL);
#elif __linux__
	setlocale(LC_ALL, "");
	wcstombs(buf.get(), source.c_str(), len);
#endif

	return(buf.get());
}

std::wstring NarrowToWide( const std::string &source )
{
	int len = source.length() + 1;

	scoped_ptr<wchar_t> buf(new wchar_t[len]);
	zeroMemory( buf.get(), (source.length() + 1) * sizeof(short) );
#ifdef _WIN32
	MultiByteToWideChar(CP_ACP, 0, source.c_str(), (int)source.length(), buf.get(), (int)(source.length()) * sizeof(short) );
#elif __linux__
	setlocale(LC_ALL, "");
	mbstowcs(buf.get(), source.c_str(), len);
#endif
	return( buf.get() );
}

std::wstring StringToUpper(const std::wstring& theString)
{
	return boost::algorithm::to_upper_copy(theString);
}

std::wstring StringToLower(const std::wstring& theString)
{
	return boost::algorithm::to_lower_copy(theString);
}

std::string WideToUTF8( const std::wstring &source )
{
#ifdef _WIN32
	int bytesNeeded = WideCharToMultiByte( CP_UTF8, 0, source.c_str(), (int)source.length(), NULL, 0, NULL, NULL);
	scoped_ptr<char> buf(new char[bytesNeeded + 1]);
	WideCharToMultiByte( CP_UTF8, 0, source.c_str(), (int)source.length(), buf.get(), bytesNeeded, NULL, NULL);
#elif __linux__
	setlocale(LC_ALL, ".UTF8");
	int bytesNeeded = wcstombs(NULL, source.c_str(), 0);
	scoped_ptr<char> buf(new char[bytesNeeded + 1]);
	wcstombs(buf.get(), source.c_str(), bytesNeeded);
#endif

	buf.get()[bytesNeeded] = 0;

	return(buf.get());
}

std::wstring UTF8ToWide( const std::string &source )
{
#ifdef _WIN32
	int charsNeeded = MultiByteToWideChar(CP_UTF8, 0, source.c_str(), (int)source.length(), NULL, 0 );
	scoped_ptr<wchar_t> buf(new wchar_t[charsNeeded + 1]);
	MultiByteToWideChar(CP_UTF8, 0, source.c_str(), (int)source.length(), buf.get(), charsNeeded );
#elif __linux__
	setlocale(LC_ALL, ".UTF8");
	int charsNeeded = mbstowcs(NULL, source.c_str(), 0);
	scoped_ptr<wchar_t> buf(new wchar_t[charsNeeded + 1]);
	mbstowcs(buf.get(), source.c_str(), charsNeeded);
#endif

	buf.get()[charsNeeded] = L'\0';

	return( buf.get() );
}

std::string MakeNumberString( int number )
{
	// this routine is intended to make a more human-readable (but non-localized) std::string by adding commas
	char buf[255];
#ifdef _WIN32
	std::string output = _itoa( number, buf, 10 );
#elif __linux__
	sprintf(buf, "%d", number);
	std::string output = buf;
#endif

	// Add commas
/*	for( int i = (int)num.length(); i > 0; i-=3 )
	{
		int startIdx = max( 0, i-3 );
		int length = min( 3, i );

		output = std::string(",") + num.substr( startIdx, length ) + output;
	}
*/
	// Remove errant first comma
	if(output[0] == ',')
		output.erase(0,1);
	return(output);
}

std::string MakeNumberToStringEx(int nNumber, std::string strSplit)
{
	char buf[255];
#ifdef _WIN32
	std::string output = _itoa(nNumber, buf, 10);
#elif __linux__
	sprintf(buf, "%d", nNumber);
	std::string output = buf;
#endif

	if(output[0] == strSplit[0])
		output.erase(0,1);
	return(output);
}

std::wstring MakeNumberWideString( int number )
{
	// this routine is intended to make a more human-readable (but non-localized) std::string by adding commas
	return NarrowToWide( MakeNumberString(number) );
}

#ifdef _WIN32
std::string GetRegKey( std::string path, std::string value )
{
	const int BUF_SIZE = 2048;

	// Open the key
	HKEY hKey;
	LONG lRet = RegOpenKeyExW( HKEY_LOCAL_MACHINE, NarrowToWide(path).c_str(), 0, KEY_QUERY_VALUE, &hKey );
    if( lRet != ERROR_SUCCESS )
	{
		RegCloseKey(hKey);
		return("");
	}


	// Get the value
	char buf[BUF_SIZE];
	DWORD bufLen = BUF_SIZE;
    lRet = RegQueryValueExW( hKey, NarrowToWide(value).c_str(), NULL, NULL,(LPBYTE) buf, &bufLen);
	if( lRet != ERROR_SUCCESS )
	{
		RegCloseKey(hKey);
		return("");
	}

	// Close the key, return the value
	RegCloseKey(hKey);
	return(buf);
}
#endif

std::wstring MakeString( const std::vector<std::wstring> &input )
{
	std::wstring output;
	for( size_t i = 0; i < input.size(); i++ )
	{
		output += input[i];
		if( i < input.size() - 1 )
			output += L",";
	}
	return(output);
}


//////////////////////////////////////////////////////////////////////
// Makes a std::vector of strings from a std::string
//////////////////////////////////////////////////////////////////////
std::vector<std::wstring> MakeStringVector( const std::wstring &input )
{
	std::vector<std::wstring> strings;

	if( input.length() == 0 )
		return strings;

	WideTokenizer tok(input);
	for( WideTokenizer::iterator i = tok.begin(); i != tok.end(); ++i )
	{
		strings.push_back( *i );
	}

	return( strings );
}

//////////////////////////////////////////////////////////////////////
// Returns true if the given std::vector contains a std::string
//////////////////////////////////////////////////////////////////////
bool StringVectorContains(const std::vector<std::wstring> &vec, const std::wstring &string)
{
	for( size_t i = 0; i < vec.size(); i++ )
	{
		if( vec[i] == string )
			return(true);
	}
	return(false);
}

//////////////////////////////////////////////////////////////////////
// Returns the internet explorer version installed on the machine
//////////////////////////////////////////////////////////////////////
#ifdef _WIN32
HRESULT GetBrowserVersion(LPDWORD pdwMajor, LPDWORD
						  pdwMinor, LPDWORD pdwBuild)
{
	HINSTANCE   hBrowser;

	if(IsBadWritePtr(pdwMajor, sizeof(DWORD))
		|| IsBadWritePtr(pdwMinor, sizeof(DWORD))
		|| IsBadWritePtr(pdwBuild, sizeof(DWORD)))
		return E_INVALIDARG;

	*pdwMajor = 0;
	*pdwMinor = 0;
	*pdwBuild = 0;

	//Load the DLL.
	hBrowser = LoadLibrary(TEXT("shdocvw.dll"));

	if(hBrowser)
	{

		HRESULT  hr = S_OK;
		DLLGETVERSIONPROC pDllGetVersion;
		pDllGetVersion =
			(DLLGETVERSIONPROC)GetProcAddress(hBrowser,
			("DllGetVersion"));

		if(pDllGetVersion)
		{

			DLLVERSIONINFO    dvi;
			ZeroMemory(&dvi, sizeof(dvi));
			dvi.cbSize = sizeof(dvi);
			hr = (*pDllGetVersion)(&dvi);

			if(SUCCEEDED(hr))
			{
				*pdwMajor = dvi.dwMajorVersion;
				*pdwMinor = dvi.dwMinorVersion;
				*pdwBuild = dvi.dwBuildNumber;
			}

		}
		else
		{
			//If GetProcAddress failed, there is a problem
			// with the DLL.

			hr = E_FAIL;
		}
		FreeLibrary(hBrowser);
		return hr;
	}
	return E_FAIL;
}
#endif


void mkDir(const std::string& path)
{
#ifdef _WIN32
	_mkdir(path.data());
#elif __linux__
	mkdir(path.data(), 755);
#endif
}

void mkDir(const std::wstring& path)
{
	mkDir(WideToNarrow(path));
}

int swnprintf(wchar_t *wcs, size_t maxlen, const wchar_t *format, ... )
{
	va_list argptr;
	va_start(argptr, format);

#ifdef _WIN32
	return _snwprintf(wcs, maxlen, format, argptr);
#elif __linux__
	return vswprintf(wcs, maxlen, format, argptr);
#endif
}

int snprintf(char *str, size_t maxlen, const char *format, ... )
{
	va_list argptr;
	va_start(argptr, format);

#ifdef _WIN32
	return _snprintf(str, maxlen, format, argptr);
#elif __linux__
	return vsnprintf(str, maxlen, format, argptr);
#endif
}

int atoi(const char *str)
{
#ifdef _WIN32
	return ::atoi(str);
#elif __linux__
	return ::atoi(str);
#endif
}

int atoi(const wchar_t *str)
{
	return atoi(WideToNarrow(str).data());
}

float atof(const char *str)
{
#ifdef _WIN32
	return (float)::atof(str);
#elif __linux__
	return ::atof(str);
#endif
}

float atof(const wchar_t *str)
{
	return atof(WideToNarrow(str).data());
}

void setCurrentDir(const char *path)
{
#ifdef _WIN32
	::SetCurrentDirectoryA(path);
#elif __linux__
	chdir(path);
#endif
}

void sleep(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#elif __linux__
	usleep(ms*1000);
#endif
}


std::string unicode_2_string_ex(const char* str_unicode)
{
	size_t len = Q_strlen(str_unicode);

	std::string os;

	size_t i = 0;

	char *token = Q_strstr( (char*)str_unicode, "&#" );

	while (token)
	{
		token += 2;

		if (token - str_unicode >= (int)len)
		{
			break;
		}

		size_t size = (token-2)-(str_unicode+i);

		if (size < 0)
		{
			break;
		}

		i += size + 2;

		char num_str[32] = {0};

		size_t nc = 0;

		for (; nc + i < len && nc < 5; nc ++)
		{
			if (token[nc] == ';')
			{
				break;
			}

			num_str[nc] = token[nc];
		}

		if (nc + i == len || token[nc] == ';')
		{
			uint num = 0;

			sscanf(num_str+1, "%x", &num);

			wchar_t str_num[16] = {0};

			*str_num = num;

			os += WideToNarrow(str_num);

			i += nc + 1;
		}

		token = Q_strstr( str_unicode+i, "&#" );
	}

	if (len - i > 0)
	{
		os += (str_unicode+i);
	}

	return os;
}

std::string string_2_unicode_ex(const char* str)
{
	std::wstring ws = NarrowToWide(str);

	char str_word[32];

	std::string os;

	for (size_t i = 0; i < ws.length(); i ++)
	{
		Q_snprintf(str_word, sizeof(str_word), "&#x%x;", ws[i]);

		os += str_word;
	}

	return os;
}

std::vector<std::string> explode(const char *sep, std::string src)
{
	std::vector < std::string > output;
	boost::char_separator<char> separator(sep);
	boost::tokenizer < boost::char_separator<char> > tokens(src, separator);
	boost::tokenizer<boost::char_separator<char> >::iterator token_iter;

	for (token_iter = tokens.begin(); token_iter != tokens.end(); token_iter++)
		output.push_back(*token_iter);

	return output;
}

uint GetTodayTime(int nHours, int nMinutes)
{
#ifndef WIN32
	struct tm tm2;
	time_t now = ::time(0);
	localtime_r(&now, &tm2);
	tm2.tm_sec = 0;
	tm2.tm_hour = nHours;
	tm2.tm_min = nMinutes;

	time_t tt = mktime(&tm2);

	return tt;
#else
	struct tm tm2;
	time_t now = ::time(0);
	tm2 = *localtime(&now);
	tm2.tm_sec = 0;
	tm2.tm_hour = nHours;
	tm2.tm_min = nMinutes;
	time_t tt = mktime(&tm2);

	return tt;
#endif
}

uint GetWeekTime(int nMinutes/* = 0*/, int nHours/* = 0*/, int nWeeks/* = 1*/)
{
#ifndef WIN32
	struct tm tm2;
	time_t now = ::time(0);
	localtime_r(&now, &tm2);
	tm2.tm_sec = 0;
	tm2.tm_min = nMinutes;
	tm2.tm_hour = nHours;
	tm2.tm_wday = nWeeks;

	time_t tt = mktime(&tm2);

	return tt;
#else
	struct tm tm2;
	time_t now = ::time(0);
	tm2 = *localtime(&now);
	tm2.tm_sec = 0;
	tm2.tm_min = nMinutes;
	tm2.tm_hour = nHours;
	time_t tt = mktime(&tm2);
	tm2.tm_wday = nWeeks;

	return tt;
#endif
}

int MakeLong(int a, int b)
{
	int nResult = 0;

#ifndef _WIN32
	nResult = MAKELONG(a, b);
#else
	nResult = MAKELONG(a, b);
#endif

	return nResult;
}

int LowWord(int l)
{
	int nResult = 0;

#ifndef _WIN32
	nResult = LOWORD(l);
#else
	nResult = LOWORD(l);
#endif

	return nResult;
}

int HighWord(int l)
{
	int nResult = 0;

#ifndef _WIN32
	nResult = HIWORD(l);
#else
	nResult = HIWORD(l);
#endif

	return nResult;
}

int CaclOnTheHour(int nCurrTime)
{
#ifndef WIN32
	struct tm tm2;
	time_t now = nCurrTime;
	localtime_r(&now, &tm2);
	tm2.tm_sec = 0;
	tm2.tm_min = 0;

	time_t tt = mktime(&tm2);

	return tt;
#else
	struct tm tm2;
	time_t now = nCurrTime;
	tm2 = *localtime(&now);
	tm2.tm_sec = 0;
	tm2.tm_min = 0;
	time_t tt = mktime(&tm2);

	return tt;
#endif
}

unsigned int ConvertStrToTime(const char * pszDate)
{
	if (pszDate == 0)
	{
		Msg("ConvertStrToTime ++++++++++++++++++++++++++++++\n");
		return -1;
	}
	std::string str1 = pszDate;
	int nPos = str1.find('-');
	if (nPos == -1)
	{
		Msg("ConvertStrToTime ==============================\n");
		return -1;
	}
	std::string strYear = str1.substr(0, nPos);
	str1 = str1.substr(nPos + 1, str1.size());
	struct tm tm2;
	tm2.tm_year = Pogo::atoi(strYear.c_str()) - 1900;
	nPos = str1.find('-');
	if (nPos == -1)
	{
		Msg("ConvertStrToTime !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		return -1;
	}
	std::string strMon = str1.substr(0, nPos);
	str1 = str1.substr(nPos + 1, str1.size());
	tm2.tm_mon = Pogo::atoi(strMon.c_str()) - 1;
	nPos = str1.find(static_cast<char>(32));
	if (nPos == -1)
	{
		Msg("ConvertStrToTime -------------------------------\n");
		return -1;
	}
	std::string strDay = str1.substr(0, nPos);
	str1 = str1.substr(nPos + 1, str1.size());
	tm2.tm_mday = Pogo::atoi(strDay.c_str());
	nPos = str1.find(':');
	if (nPos == -1)
	{
		Msg("ConvertStrToTime :::::::::::::::::::::::::::::::\n");
		return -1;
	}
	std::string strHour = str1.substr(0, nPos);
	str1 = str1.substr(nPos + 1, str1.size());
	tm2.tm_hour = Pogo::atoi(strHour.c_str());
	nPos = str1.find(':');
	if (nPos == -1)
	{
		Msg("ConvertStrToTime :::::::::::::::::::::::::::::::\n");
		return -1;
	}
	std::string strMin = str1.substr(0, nPos);
	str1 = str1.substr(nPos + 1, str1.size());
	tm2.tm_min = Pogo::atoi(strMin.c_str());
	std::string strSec = str1;
	tm2.tm_sec = Pogo::atoi(strSec.c_str());

	Msg("%s-%s-%s %s:%s:%s\n", strYear.c_str(), strMon.c_str(), strDay.c_str(), strHour.c_str(), strMin.c_str(), strSec.c_str());
	Msg("%d-%d-%d %d:%d:%d\n", tm2.tm_year, tm2.tm_mon, tm2.tm_mday, tm2.tm_hour, tm2.tm_min, tm2.tm_sec);
	time_t tt = mktime(&tm2);

	return static_cast<unsigned int>(tt);
}

}
