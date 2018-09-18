//
// (C) Electronic Arts 2006
// 

#pragma once

#include <vector>
#include <boost/array.hpp>
#include <boost/smart_ptr.hpp>
#include "PogoCommon.h"
#include "Properties.h"
#include "Exception.h"
#include "Version.h"
#include "TenProps.h"

namespace Pogo
{
	// This exception can be thrown when parsing props files
	class PropsException : public Exception
	{
	public:
		PropsException( std::wstring name, std::wstring desc = L"", std::string traceInfo = "") : 
		  Exception( "[" + WideToNarrow(name) + "] " + WideToNarrow(desc), traceInfo ) {}
	};

	// The propsutils class is used for creating objects from properties files
	// This class consists mostly of static utility functions
	class PropsUtils
	{
	public:
		static bool LoadProperties(const std::wstring& file);

		// Checks if prop exists
		static bool DoesPropExist(std::wstring name, Pogo::Properties *props = NULL );

		// Creates an integer
		static bool CanMakeInt(std::wstring name, Pogo::Properties *props  = NULL );
		static int MakeInt( std::wstring name, int defValue = 0, Pogo::Properties *props = NULL );

		// Makes a boolean value
		static bool MakeBoolean( std::wstring name, bool defValue = false, Pogo::Properties *props = NULL );

		// Creates a double
		static double MakeDouble( std::wstring name, double defValue = 0.0, Pogo::Properties *props = NULL );

		// Makes a vector of integers
		static std::vector<int> MakeIntVector( std::wstring wname, Pogo::Properties *props = NULL );

		// Makes a vector of integers
		static std::vector<int> MakeIntVectorCSV( std::wstring wname, Pogo::Properties *props = NULL );

		// check if can get a string
		static bool CanMakeString( std::wstring name, Pogo::Properties *props = NULL );

		// Gets a string
		static std::wstring MakeString( std::wstring name, std::wstring defValue = L"", Pogo::Properties *props = NULL );

		// Gets a string and formats it using the passed in values
		static std::wstring MakeFormatString( std::wstring name, std::wstring param, Pogo::Properties *props = NULL );
		static std::wstring MakeFormatString( std::wstring name, std::vector<std::wstring> params, Pogo::Properties *props = NULL);

		static bool CanMakeStringVector(std::wstring name, Pogo::Properties *props = NULL);

		// Makes a vector of strings
		static std::vector<std::wstring> MakeStringVector( std::wstring name, Pogo::Properties *props = NULL );

		// Makes a vector of doubles
		static std::vector<double> MakeDoubleVector( std::wstring name, Pogo::Properties *props = NULL );

		// Makes a version information object
		static class Version MakeVersion( std::wstring name, Pogo::Properties *props = NULL );

		// Retrieve the first prop from the vector that exists, or an empty string.
		static std::wstring GetFirstValidProp( const std::vector<std::wstring> &propList, Properties *props = NULL );

	public:
		static PropertiesPtr m_spProperties;
	};
}
