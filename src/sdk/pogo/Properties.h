//
// (C) Electronic Arts 2005
// 

#pragma once
#include <map>
#include <string>
#include "boost/smart_ptr.hpp"
#include "PogoCommon.h"

typedef void* FileHandle_t;

namespace Pogo{
class Properties
{
public:
	static const std::wstring HASH_KEY; // = L"TimeStamp";
	static const short XOR_VALUE = 12345;
	//static const short ENCRYPT_KEY = 14321;

	// The map object
	typedef std::map< std::wstring, std::wstring, std::less<std::wstring> > PropertiesMap;

private:
	PropertiesMap mMap;

public:
	// Default constructor
	Properties();
	
	// Construct the properties from a UTF character buffer
	Properties( unsigned char *buf );

	// Destructor
	~Properties(){}

	// Loads properties from a file
	bool Load( const std::wstring &filename);
	
	bool Load(const std::wstring &filename, PropertiesMap& pmap);

	// Save the properties to a file
	bool Save( const std::wstring &filename );

	// Generates a hash code
	std::wstring GenerateHash( bool updateProps = false );

	// Adds the hash key to the end of a file
	static void AddHashToFile( const std::wstring &filename );
	
	// Puts a key/value pair into the props
	void Put( const std::wstring &key, const std::wstring &value );

	// Gets a key from the props
	std::wstring Get( const std::wstring &key, std::wstring defaultValue = L"" );
	
	// Narrow param version
	std::string Get( const std::string &key, std::string defaultValue = "" );

	// Returns a string representation of the properties
	std::wstring ToString();

	// Convert the properties to a Java-Compatible UTF string
	int ToUTF( unsigned char *buf, int bufLen );
	
	// Copies properties from the given object and adds them to this one
	virtual void Copy( Properties *props );

	// Helper function to convert a UNICODE string to a UTF string
	static int ToUTF( const std::wstring &str, unsigned char *buf, int bufLen );

	// Helper function to convert a UTF buffer to a UNICODE string
	static std::wstring FromUTF( unsigned char *buf );
	
	// Writes a line to the given file (UNICODE)
	static void WriteLine( FileHandle_t fh, const std::wstring &line );

	// Returns the number of keys
	const PropertiesMap &GetMap();

	// Clears the properties
	virtual void Clear();

	// Check whether the props is empty
	bool IsEmpty();

	// swap the properties with the given object
	virtual void Swap( Properties *props );

};

// Properties pointer type
typedef boost::shared_ptr<class Properties> PropertiesPtr;
}
