//
// (C) Electronic Arts 2006
//
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"
#include <vector>
#include "Version.h"

// Define the version if we did not pass it in via the compiler
#ifndef POGO_VERSION
#define POGO_VERSION L"2.0.0.0"
#endif

using namespace Pogo;
using namespace std;
using namespace boost;

Version Version::CURRENT_VERSION( POGO_VERSION );

//////////////////////////////////////////////////////////////////////
// Version::Version
// Create the version object
//////////////////////////////////////////////////////////////////////
Version::Version()
{
	mVersion = 0x00000000L;
	mVersionString = L"0.0.0.0";
}

//////////////////////////////////////////////////////////////////////
// Version::Version(...)
// Creates a version from a string
//////////////////////////////////////////////////////////////////////
Version::Version(wstring version)
{
	// Get the version
	mVersionString = version;

	// Split the string up 
	vector<wstring> numbers;
	split( numbers, version, is_any_of(L".") );
	
	// TODO: Throw an exception here?
	if( numbers.size() != 4 || version.length() == 0 )
	{
		mVersion = 0x00000000L;
		mVersionString = L"0.0.0.0";
		return;
	}

	// Extract version info
	unsigned char major = lexical_cast<int>(numbers[0]);
	unsigned char minor = lexical_cast<int>(numbers[1]);
	unsigned char rev = lexical_cast<int>(numbers[2]);
	unsigned char build = lexical_cast<int>(numbers[3]);

	// Build the version number
	mVersion = ( major << 24 ) | ( minor << 16 ) | ( rev << 8 ) | build;
}

//////////////////////////////////////////////////////////////////////
// Initialize based on 4 integers
//////////////////////////////////////////////////////////////////////
Version::Version( int major, int minor, int rev, int build )
{
	// Build the version number
	mVersion = ( major << 24 ) | ( minor << 16 ) | ( rev << 8 ) | build;
	mVersionString = lexical_cast<wstring>(major) + L"." + lexical_cast<wstring>(minor) + L"." 
		+ lexical_cast<wstring>(rev) + L"." + lexical_cast<wstring>(build);

}

//////////////////////////////////////////////////////////////////////
// Version::GetVersion()
// Returns the unsigned long version number	which can be compared
// using normal operators <, <=, etc. 
//////////////////////////////////////////////////////////////////////
unsigned long Version::GetVersion()
{
	return mVersion;
}

//////////////////////////////////////////////////////////////////////
// Returns the string version
//////////////////////////////////////////////////////////////////////
const wstring &Version::ToString()
{
	return( mVersionString );
}
