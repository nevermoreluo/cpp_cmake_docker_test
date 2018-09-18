//
// (C) Electronic Arts 2005
// 

#pragma once

#include <string>

namespace Pogo
{
	class Version
	{
	protected:

		// The unsigned long version #
		unsigned long mVersion;
		
		// The string version
		std::wstring mVersionString;
		
	public:
		// The current version
		static Version CURRENT_VERSION;

		// The build ID (retail, oberon, etc)
		static const std::wstring BUILD_ID;

		// Initialize the version object
		Version();

		// Initialize from a string
		Version(std::wstring version);
		
		// Initialize based on integers
		Version( int major, int minor, int rev, int build );

		// Return the comparable unsigned long version
		unsigned long GetVersion();

		// Gets the string version
		const std::wstring &ToString();
	};
}
