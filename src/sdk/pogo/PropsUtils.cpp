//
// (C) Electronic Arts 2006
// 

#include"boost/algorithm/string.hpp"
#include"boost/tokenizer.hpp"
#include"boost/lexical_cast.hpp"

#include "PogoCommon.h"
#include "PropsUtils.h"
#include "Exception.h"
#include "tier0/dbg.h"

using namespace Pogo;
using namespace std;

#define FIX_PROPS() { if (!props) props = m_spProperties.get(); }

int StringToInt( const wstring &input )
{
	return( wcstol( input.c_str(), NULL, 10 ) );
}

PropertiesPtr PropsUtils::m_spProperties = PropertiesPtr(new Properties());

bool PropsUtils::LoadProperties(const std::wstring& file)
{
	TenProps ten(file);

	m_spProperties->Copy(ten.GetProps().get());

	return true;

//	return m_spProperties->Load(file);
}


bool PropsUtils::DoesPropExist(wstring name, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();

	wstring prop = props->Get( name );

	// Make sure property exists
	if( prop.length() == 0 )
		return false;

	// otherwise we can make the vector
	return true;
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::CanMakeString(...)
// Checks if can get a wstring from the properties file
//////////////////////////////////////////////////////////////////////
bool PropsUtils::CanMakeString( wstring name, Pogo::Properties *props )
{
	FIX_PROPS();

	wstring value = props->Get( ( name ) );
	if( value.length() == 0 )
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeString(...)
// Gets a wstring from the properties file
//////////////////////////////////////////////////////////////////////
wstring PropsUtils::MakeString( wstring name, wstring defValue, Pogo::Properties *props )
{
	FIX_PROPS();
	
	wstring value = props->Get( ( name ) );
	if( value.length() == 0 )
		value = defValue;

	return( value );
}

wstring PropsUtils::MakeFormatString(wstring name, wstring param, Pogo::Properties *props /* = NULL  */)
{
	vector<wstring> params;
	params.push_back(param);
	return MakeFormatString(name, params, props);
}

wstring PropsUtils::MakeFormatString(wstring name, vector<wstring> params, Pogo::Properties *props /* = NULL  */)
{
	// get base wstring
	wstring result = MakeString(name);

	// do replacements
	vector<wstring>::iterator iter;
	int idx = 0;
	for (iter = params.begin(); iter != params.end(); ++iter) {
		wstring token = L"{" + boost::lexical_cast<wstring,int>(idx) + L"}";
		boost::replace_all( result, token, *iter);
		idx++;
	}

	// return results
	return result;
}


//////////////////////////////////////////////////////////////////////
// PropsUtils::CanMakeInt()
// Checks if can make an integer from the given property
//////////////////////////////////////////////////////////////////////
bool PropsUtils::CanMakeInt(wstring name, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();

	wstring prop = props->Get( name );

	// Make sure property exists
	if( prop.length() == 0 )
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeInt()
// Makes an integer from the given property
//////////////////////////////////////////////////////////////////////
int PropsUtils::MakeInt(wstring name, int defValue, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();

	wstring prop = props->Get( name );

	// Make sure property exists
	if( prop.length() == 0 )
		return( defValue );

	return( Pogo::atoi(prop.data()) );
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeBoolean()
// Creates a boolean value
//////////////////////////////////////////////////////////////////////
bool PropsUtils::MakeBoolean(wstring name, bool defValue, Pogo::Properties *props )
{
	FIX_PROPS();
	
	wstring prop = props->Get( name );
	
	// Make sure property exists
	if( prop.length() == 0 )
		return( defValue );

	boost::to_lower( prop );
	if( prop == L"yes" || prop == L"y" || prop == L"true" || prop == L"t" || prop == L"1" )
		return(true);
	else
		return(false);
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeDouble()
// Makes a double from the given property
//////////////////////////////////////////////////////////////////////
double PropsUtils::MakeDouble(wstring name, double defValue, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();
	double dummyDouble = 0.0f;
	wstring prop = props->Get( name );

	// Make sure property exists
	if( prop.length() == 0 )
		return( defValue );

	dummyDouble = boost::lexical_cast<double>(prop);
	return( dummyDouble );
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeIntVector(...)
// Creates a vector filled with integers from the given property
//////////////////////////////////////////////////////////////////////
vector<int> PropsUtils::MakeIntVector(wstring name, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();

	wstring prop = props->Get( name );
	
	// Make sure property exists
	if( prop.length() == 0 )
		throw PropsException( (name), L"Property not found", TRACE_PARAMS );

	typedef boost::tokenizer<boost::char_separator<wchar_t>, wstring::const_iterator, wstring > tokenizer;
	boost::char_separator<wchar_t> sep(L", ");
	tokenizer tok(prop, sep);

	vector<int> numbers;
	for( tokenizer::iterator i = tok.begin(); i != tok.end(); ++i )
	{
		numbers.push_back( Pogo::atoi( i->c_str() ) );
	}

	return( numbers );
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeIntVectorCSV(...)
// Creates a vector filled with integers from the given property
// Only comma is regarded to be the separator in the property.
//////////////////////////////////////////////////////////////////////
vector<int> PropsUtils::MakeIntVectorCSV(wstring name, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();

	wstring prop = props->Get( name );

	// Make sure property exists
	if( prop.length() == 0 )
		throw PropsException( (name), L"Property not found", TRACE_PARAMS );

	typedef boost::tokenizer<boost::char_separator<wchar_t>, wstring::const_iterator, wstring> tokenizer1;
	boost::char_separator<wchar_t> sep(L", ");
	tokenizer1 tok(prop, sep);

	vector<int> numbers;
	for( tokenizer1::iterator i = tok.begin(); i != tok.end(); ++i )
	{
		numbers.push_back( Pogo::atoi( i->c_str() ) );
	}

	return( numbers );
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::CanMakeStringVector(...)
// Checks if can create a vector filled with strings from a props file
//////////////////////////////////////////////////////////////////////
bool PropsUtils::CanMakeStringVector(wstring name, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();

	// Use a boost tokenizer to read in the params
	wstring prop = props->Get( ( name ) );

	// Make sure property exists
	if( prop.length() == 0 )
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeStringVector(...)
// Creates a vector filled with strings from a props file
//////////////////////////////////////////////////////////////////////
vector<wstring> PropsUtils::MakeStringVector(wstring name, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();
	
	// Use a boost tokenizer to read in the params
	wstring prop = props->Get( ( name ) );
	vector<wstring> strings;

	// Make sure property exists
	if( prop.length() == 0 )
		return(strings);

	typedef boost::tokenizer<boost::char_separator<wchar_t>, wstring::const_iterator, wstring> tokenizer1;
	boost::char_separator<wchar_t> sep(L", ");
	tokenizer1 tok(prop, sep);

	for( tokenizer1::iterator i = tok.begin(); i != tok.end(); ++i )
	{
		strings.push_back( *i );
	}

	return( strings );
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeDoubleVector(...)
// Creates a vector composed of floating point numbers
//////////////////////////////////////////////////////////////////////
vector<double> PropsUtils::MakeDoubleVector(wstring name, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();

	// Use a boost tokenizer to read in the params
	wstring prop = props->Get( name );
	
	// Make sure property exists
	if( prop.length() == 0 )
		throw PropsException( (name), L"Property not found", TRACE_PARAMS );

	typedef boost::tokenizer<boost::char_separator<wchar_t>, wstring::const_iterator, wstring> tokenizer1;
	boost::char_separator<wchar_t> sep(L", ");
	tokenizer1 tok(prop, sep);

	vector<double> numbers;
	for( tokenizer1::iterator i = tok.begin(); i != tok.end(); ++i )
	{
		numbers.push_back( Pogo::atof( i->c_str() ) );
	}

	return( numbers );
}

//////////////////////////////////////////////////////////////////////////
// Returns the first valid prop from prop list that exists, or 
// an empty wstring
//////////////////////////////////////////////////////////////////////////
wstring PropsUtils::GetFirstValidProp( const vector<wstring> &propList, Properties *props )
{
	FIX_PROPS();

	vector<wstring>::const_iterator iter;
	for (iter = propList.begin(); iter != propList.end(); ++iter) {
		if (PropsUtils::DoesPropExist(*iter, props)) {
			return (*iter);
		}
	}
	return wstring(L"");
}

//////////////////////////////////////////////////////////////////////
// PropsUtils::MakeVersion(...)
// Creates a version info object
//////////////////////////////////////////////////////////////////////
Version PropsUtils::MakeVersion(wstring name, Pogo::Properties *props /* = NULL  */)
{
	FIX_PROPS();

	// Get the face
	if( !boost::iends_with( name, L".version" ) )
		name += L".version";

	// Use a boost tokenizer to read in the params
	wstring prop = props->Get( ( name ) );

	// Make sure property exists
	if( prop.length() == 0 )
		throw PropsException( (name), L"Property not found", TRACE_PARAMS );

	// Return the version
	return( Version(prop) );
}
