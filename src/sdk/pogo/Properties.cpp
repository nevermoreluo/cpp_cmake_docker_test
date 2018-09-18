//
// (C) Electronic Arts 2005
//

#include <boost/algorithm/string.hpp>
#include "Properties.h"
#include "PogoCommon.h"
#include "tier0/dbg.h"
#include "PropsUtils.h"
#include "filesystem.h"
#include "ifilesystem.h"



using namespace Pogo;
using namespace boost;

const std::wstring Properties::HASH_KEY = L"pogo.timestamp";


//////////////////////////////////////////////////////////////////////
// Properties::Properties()
// Initializes the properties object
//////////////////////////////////////////////////////////////////////
Properties::Properties()
{

}

//////////////////////////////////////////////////////////////////////
// Properties::Properties( char *buf )
// Construct the properties from a UTF character buffer
//////////////////////////////////////////////////////////////////////
Properties::Properties( unsigned char *buf )
{
	int pos = 0;
	short utflen = buf[0] << 8 | buf[1];
	buf+=2;

	while( pos < utflen )
	{
		// Get the name
		unsigned short nameLen = buf[pos] << 8 | buf[pos+1];
		std::wstring key = Properties::FromUTF( buf + pos );
		pos += (nameLen + 2);

		// Get the value
		unsigned short valueLen = buf[pos] << 8 | buf[pos+1];
		std::wstring value = Properties::FromUTF( buf + pos );
		pos += (valueLen + 2);

		// Add the key/value pair
		Put( key, value );
	}
}

//////////////////////////////////////////////////////////////////////
// void Properties::Put( std::wstring key, std::wstring value )
// Adds the key to the properties with the given value
//////////////////////////////////////////////////////////////////////
void Properties::Put( const std::wstring &key, const std::wstring &value )
{
	mMap[key] = value;
}

//////////////////////////////////////////////////////////////////////
// std::wstring Properties::Get( string key, string defaultValue = "" )
// Returns the value of the given key, or the default value if not
// found.
//////////////////////////////////////////////////////////////////////
std::wstring Properties::Get( const std::wstring &key, std::wstring defaultValue )
{
	if( mMap.find( key ) != mMap.end() )
	{
		return( mMap[key] );
	}

	return( defaultValue );
}

std::string Properties::Get( const std::string &key, std::string defaultValue )
{
	std::wstring wKey = NarrowToWide( key );

	if( mMap.find( wKey ) != mMap.end() )
	{
		return( WideToNarrow( mMap[wKey] ) );
	}

	return( defaultValue );
}

//////////////////////////////////////////////////////////////////////
// Properties::Swap(filename)
// Swap the properties with the given object
//////////////////////////////////////////////////////////////////////
void Properties::Swap( Properties *props )
{
	Properties::PropertiesMap src = props->GetMap();
	mMap.swap(src);
}

//////////////////////////////////////////////////////////////////////
// Properties::Load(filename)
// Loads the properties from the given filename
//////////////////////////////////////////////////////////////////////
bool Properties::Load(const std::wstring &filename)
{
	return Load(filename, mMap);
}

bool Properties::Load(const std::wstring &filename, PropertiesMap& pmap)
{
	// Check to see if the file is unicode
	std::string file = Pogo::WideToNarrow(filename);

	FileHandle_t fh = g_pFileSystem->Open(file.data(), "rb");

	if (!g_pFileSystem->IsOk(fh))
		return false;

	int len = g_pFileSystem->Size(fh);

	scoped_ptr<char> buf(new char[len]);

	int ir = g_pFileSystem->Read(buf.get(), len, fh);

	g_pFileSystem->Close(fh);

	if (ir != len)
	{
		return false;
	}

	int count = 0;
	// Check for UTF-8 encoding
	bool utf8 = false;
	byte* b = (byte*)buf.get();
	if( b[0] == 0xEF && b[1] == 0xBB && b[2] == 0xBF )
	{
		utf8 = true;
		count += 3;
	}

	// Go through each line in the file, and parse it
	std::string text;

	while( count < len)
	{
		// Read the entire line
		text.clear();

		while( count < len )
		{
			// Get the next character from the file, make sure its not
			// either a newline or EOF
			char c = (char)b[count++];

			if( c == '\n' || count >= len )
				break;

			// Add the character to the line
			text.push_back( c );
		}

		// Skip empty lines
		if( text.length() <= 0 || text.length() == std::string::npos )
			continue;

		// Get the wide-string version of the line
		std::wstring line;

		if( utf8 )
			line = UTF8ToWide( text );
		else
			line = NarrowToWide(text);

		// Skip comment lines
		if( line.find( L"#" ) < line.find_first_not_of( L"#" ) )
			continue;

		// Parse the line for the equals sign (make sure there is one)
		size_t idxEquals = line.find(L"=");
		if( idxEquals == std::wstring::npos || idxEquals <= 0 )
			continue;

		// Get the key/value pair
		std::wstring key = line.substr( 0, idxEquals );
		std::wstring value = line.substr( idxEquals + 1, line.length() - idxEquals );

		// Trim the strings on left and right
		const std::wstring SPACES = L" \t\r\n";
		key.erase( 0, key.find_first_not_of( SPACES ) );
		value.erase( 0, value.find_first_not_of( SPACES ) );

		// Trim on right
		size_t idx = key.find_last_not_of( SPACES );
		if( idx != std::wstring::npos )
			key.erase( idx + 1 );

		idx = value.find_last_not_of( SPACES );
		if( idx != std::wstring::npos )
			value.erase( idx + 1 );

		pmap[key] = value;
	}

	//std::wstring fileHash = Get( HASH_KEY );
	//if( fileHash.length() == 0 || fileHash != GenerateHash() )
	//{
	//	return false;
	//}
	return( true );
}

//////////////////////////////////////////////////////////////////////
// Adds the hash-key to an already generated properties file
//////////////////////////////////////////////////////////////////////
void Properties::AddHashToFile( const std::wstring &filename )
{
	Properties props;
	props.Load( filename );

	std::wstring hashKey = props.GenerateHash( false );

	// Load the lines of the file
	std::vector<std::wstring> lines;

	// Note that AddHashToFile will NOT be using PakFile system as writing is needed
#ifdef _WIN32
	FILE *fp = _wfopen( filename.c_str(), L"rb" );
#elif _LINUX
	FILE *fp = fopen( Pogo::WideToNarrow(filename).c_str(), "rb" );
#endif
	if( !fp )
		return;

	// Check for UTF-8 encoding
	bool utf8 = false;
	byte b1 = fgetc(fp);byte b2 = fgetc(fp);byte b3 = fgetc(fp);
	if( b1 == 0xEF && b2 == 0xBB && b3 == 0xBF )
		utf8 = true;
	else
		fseek( fp, 0, SEEK_SET );

	std::string text;
	while( !feof(fp) )
	{
		// Read the entire line
		text.clear();

		while( !feof(fp) )
		{
			// Get the next character from the file, make sure its not
			// either a newline or EOF
			char c = fgetc(fp);
			if( c == (unsigned short)'\n' || feof(fp) )
				break;

			// Add the character to the line
			text.push_back( c );
		}

		std::wstring line;
		if( utf8 )
			line = UTF8ToWide( text );
		else
			line = NarrowToWide( text );

		lines.push_back( line );
	}

	// Go through each line and look for HASH_KEY to replace
	for( size_t i = 0; i < lines.size(); i++ )
	{
		if( lines[i].find(HASH_KEY + L"=" ) == 0 )
		{
			std::vector<std::wstring>::iterator itr = lines.begin() + i;
			lines.erase(itr);
			break;
		}
	}

	fclose(fp);

	// Add the hash key
	lines.push_back( HASH_KEY + L"=" + hashKey );

	// Create the file stream
#ifdef _WIN32
	fp = _wfopen( filename.c_str(), L"wb" );
#elif _LINUX
	fp = fopen( Pogo::WideToNarrow(filename).c_str(), "wb" );
#endif
	if( !fp )
		return;

	// Put utf-8 identifier
	fputc( 0xEF, fp );
	fputc( 0xBB, fp );
	fputc( 0xBF, fp );

	// Output the new props file
	for( size_t i = 0; i < lines.size(); i++ )
	{
		std::wstring line = lines[i];

		if( i < lines.size() - 1 )
			line += L"\n";
		WriteLine( fp, line );
	}

	fclose(fp);
}

//////////////////////////////////////////////////////////////////////
// Saves the properties to a file (UNICODE)
//////////////////////////////////////////////////////////////////////
bool Properties::Save( const std::wstring &filename )
{
	// Create the file if it does not exist
//	if( !FileManager::Exists( filename ) )
//	{
//		HANDLE hFile = FileManager::Create( filename );
//		if( hFile != INVALID_HANDLE_VALUE && hFile != NULL )
//		{
//			CloseHandle( hFile );
//		}
//	}

	// Try to clear read-only flag
/*	DWORD dwFileAttributes = GetFileAttributesW( filename.c_str() );
	if( dwFileAttributes != INVALID_FILE_ATTRIBUTES && ( dwFileAttributes & FILE_ATTRIBUTE_READONLY ) )
	{
		// Remove readonly flag
		dwFileAttributes ^= FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( filename.c_str(), dwFileAttributes );
	}
*/

	FileHandle_t fh = g_pFileSystem->Open(Pogo::WideToNarrow(filename).c_str(), "wb");

	if( !g_pFileSystem->IsOk(fh) )
		return false;

	// Write out the utf-8 identifier
	byte utfm[] = {0xEF, 0xBB, 0xBF};
	g_pFileSystem->Write(utfm, sizeof(utfm), fh);

	// Generate a hash code
	GenerateHash( true );

	for( PropertiesMap::iterator i = mMap.begin(); i != mMap.end(); i++ )
	{
		std::wstring line = i->first + L"=" + Get(i->first);
		line += L"\n";

		//fs << line;
		WriteLine( fh, line );
	}

	g_pFileSystem->Close(fh);

	return(true);
}

//////////////////////////////////////////////////////////////////////
// Writes a unicode line to a file
//////////////////////////////////////////////////////////////////////
void Properties::WriteLine( FileHandle_t fh, const std::wstring &line )
{
	if( line.size() == 0 )
		return;

	// Write in TEXT for now :(
	std::string text = WideToUTF8( line );
	g_pFileSystem->Write( text.data(), (int)(sizeof(std::string::value_type)*text.length()), fh );
}

//////////////////////////////////////////////////////////////////////
// Generates a hash string to be used as a key
//////////////////////////////////////////////////////////////////////
std::wstring Properties::GenerateHash( bool updateProps )
{
	std::wstring hash;
	unsigned long value = 0;

	// Remove the hash key from the calculation
	if( mMap.find( HASH_KEY ) != mMap.end() )
		mMap.erase( HASH_KEY );

	for( PropertiesMap::iterator i = mMap.begin(); i != mMap.end(); i++ )
	{
		std::wstring keyValue = i->first + i->second;
		for( size_t idx = 0; idx < keyValue.length(); idx++ )
		{
			value += keyValue[idx] ^ XOR_VALUE;
		}
	}

	hash = Pogo::MakeNumberWideString(value);

	if( updateProps )
		Put( HASH_KEY, hash );
	return( hash );
}

//////////////////////////////////////////////////////////////////////
// int Properties::ToUTF()
// Converts the properties into a Java-Compatible UTF string
//////////////////////////////////////////////////////////////////////
int Properties::ToUTF( unsigned char *buf, int bufLen )
{
	// Start at pos 2, as to leave room for the length information
	unsigned int pos = 2;

	// Create a buffer for encoding key/value pairs
	unsigned char *pairBuf = new unsigned char[bufLen];

	for( PropertiesMap::iterator i = mMap.begin(); i != mMap.end(); i++ )
	{
		// Get the key/value pair, convert it to UTF
		std::wstring key = (*i).first;
		std::wstring value = (*i).second;

		// Copy the key into the buffer
		int keyLength = ToUTF( key, pairBuf, bufLen );
		memcpy( buf + pos, (char *)pairBuf, keyLength );
		pos += keyLength;

		int valueLength = ToUTF( value, pairBuf, bufLen );
		memcpy( buf + pos, (char *)pairBuf, valueLength );
		pos += valueLength;
	}

	// Free the pair buffer
	delete[] pairBuf;
	unsigned short utflen = (pos - 2);
	buf[0] = (char)((utflen >> 8) & 0xFF);
	buf[1] = (char)(utflen & 0xFF);

	return( pos );
}

//////////////////////////////////////////////////////////////////////
// std::wstring Properties::ToString()
// Returns a string representation of the properties object
//////////////////////////////////////////////////////////////////////
std::wstring Properties::ToString()
{
	std::wstring theString;

	for( PropertiesMap::iterator i = mMap.begin(); i != mMap.end(); i++ )
	{
		// Get the key/value pair, convert it to UTF
		std::wstring key = (*i).first;
		std::wstring value = (*i).second;

		theString += ( key + L"=" + value + L", " );
	}

	if( theString.length() >= 2 )
		return ( theString.substr( 0, theString.length() - 2 ) );
	else
		return( theString );
}

//////////////////////////////////////////////////////////////////////
// int Properties::ToUTF( std::wstring str, char *buf, int bufLen )
// Helper function to convert a string to a Java-Compatible
// UTF string.
//////////////////////////////////////////////////////////////////////
int Properties::ToUTF( const std::wstring &str, unsigned char *buf, int bufLen )
{
	// This code copied from Java source, and slightly modified
	unsigned short c,utflen=0;
	for (unsigned int i = 0; i < str.length(); i++) {
	    c = str[i];
	    if ((c >= 0x0001) && (c <= 0x007F)) {
			utflen++;
	    } else if (c > 0x07FF) {
			utflen += 3;
	    } else {
			utflen += 2;
	    }
	}

	// String too long
    if (utflen > bufLen)
	    return(0);

	// Build the UTF string
	unsigned short pos = 0;
	buf[pos++] = (char)((utflen >> 8) & 0xFF);
	buf[pos++] = (char)(utflen & 0xFF);
	for (unsigned int i = 0; i < str.length(); i++) {
	    c = str[i];
	    if ((c >= 0x0001) && (c <= 0x007F)) {
			buf[pos++] = (char)c;
	    } else if (c > 0x07FF) {
			buf[pos++] = (char)((0xE0 | ((c >> 12) & 0x0F)));
			buf[pos++] = (char)((0x80 | ((c >>  6) & 0x3F)));
			buf[pos++] = (char)((0x80 | (c & 0x3F)));
	    } else {
			buf[pos++] = (char)((0xC0 | ((c >>  6) & 0x1F)));
			buf[pos++] = (char)((0x80 | (c & 0x3F)));
	    }
	}

	return(utflen + 2);
}

//////////////////////////////////////////////////////////////////////
// std::wstring Properties::FromUTF( char *buf )
// Creates a UNICODE string from a character buffer
//////////////////////////////////////////////////////////////////////
std::wstring Properties::FromUTF( unsigned char *buf )
{
	unsigned short utflen = buf[0] << 8 | buf[1];
	buf+=2;
	unsigned short count = 0, c = 0, char2 = 0, char3 = 0;
	std::wstring str;

	while (count < utflen) {
     	c = (int) buf[count] & 0xff;
		switch (c >> 4) {
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
				// 0xxxxxxx
				count++;
				str += c;
			break;

			case 12: case 13:
				// 110x xxxx   10xx xxxx
				count += 2;
				if (count > utflen)
					return(L"");
				char2 = (int) buf[count-1];
				if ((char2 & 0xC0) != 0x80)
					return(L"");
						str += ((((c & 0x1F) << 6) | (char2 & 0x3F)));
			break;

			case 14:
				// 1110 xxxx  10xx xxxx  10xx xxxx
				count += 3;
				if (count > utflen)
					return(L"");
				char2 = (int) buf[count-2];
				char3 = (int) buf[count-1];
				if (((char2 & 0xC0) != 0x80) || ((char3 & 0xC0) != 0x80))
					return(L"");

				str += ((unsigned short)(((c     & 0x0F) << 12) |
                    						((char2 & 0x3F) << 6)  |
                    						((char3 & 0x3F) << 0)));
			break;
			default:
			// 10xx xxxx,  1111 xxxx
			return(L"");
		}
	}

	return( str );
}

//////////////////////////////////////////////////////////////////////
// Takes all the key/value pairs from the given properties object
// and adds them to this one.
//////////////////////////////////////////////////////////////////////
void Properties::Copy(Properties *props)
{
	Properties::PropertiesMap src = props->GetMap();
	for( Properties::PropertiesMap::iterator i = src.begin(); i != src.end(); i++ )
	{
		// Get the key/value pair
		std::wstring key = (*i).first;
		std::wstring value = (*i).second;

		// Add the property
		Put( key, value );
	}
}

//////////////////////////////////////////////////////////////////////
// Returns a reference to the properties hash map
//////////////////////////////////////////////////////////////////////
const Properties::PropertiesMap &Properties::GetMap()
{
	return(mMap);
}

//////////////////////////////////////////////////////////////////////
// Clears the map
//////////////////////////////////////////////////////////////////////
void Properties::Clear()
{
	mMap.clear();
}

bool Properties::IsEmpty()
{
	return mMap.empty();
}
