#include "PogoCommon.h"
#include "Exception.h"

#ifdef __linux__
#include <string.h>
#endif


using namespace Pogo;

//////////////////////////////////////////////////////////////////////
// Exception::Exception(...)
// Creates an exception complete with stack trace, etc. 
//////////////////////////////////////////////////////////////////////
Exception::Exception( std::string desc, std::string traceInfo )
{ 
	// Add the trace info if it is available
	mDesc = traceInfo + desc;
//	Log::Add( (mDesc) );
}

//////////////////////////////////////////////////////////////////////
// Exception::FormatCallerInfo(...)
// Correctly formats a string containing information about the calling
// function. 
//////////////////////////////////////////////////////////////////////
std::string Exception::FormatCallerInfo( std::string file, std::string function, int line )
{
	const int BUF_SIZE = 2048;

	char buf[BUF_SIZE];
	memset(buf, 0, BUF_SIZE);

#ifdef _WIN32
	size_t idxFile = file.find_last_of("\\");
#elif __linux__
	size_t idxFile = file.find_last_of("/");
#endif

	std::string filename = file.substr( idxFile + 1, file.length() - idxFile - 1 );

	Pogo::snprintf(buf, BUF_SIZE-1, "[%s::%s():%d] -> ", filename.c_str(), function.c_str(), line);

	return buf;
}
