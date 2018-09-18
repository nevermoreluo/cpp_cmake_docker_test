//
// (C) Electronic Arts 2006
// 

#pragma once

#include <exception>
#include <string>

// This can be useful for traces of the end user does not have dbghelp.dll or imghelp.dll
#define TRACE_PARAMS Pogo::Exception::FormatCallerInfo(__FILE__, __FUNCTION__, __LINE__ )

namespace Pogo
{
	// The Pogo base exception class
	class Exception : public std::exception
	{
	protected:
		// Description of the exception
		std::string mDesc;
	
	public:
		// Get information about where the exception was thrown
		Exception( std::string desc, std::string traceInfo = "" );

#ifdef _LINUX
		virtual ~Exception() throw() {}
#endif

		// Correctly formats caller information
		static std::string FormatCallerInfo( std::string file, std::string function, int line );

		// Return the description of the exception
		virtual const std::string &GetDesc(){ return mDesc; }
	};
}
