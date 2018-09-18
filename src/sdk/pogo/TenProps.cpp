/*
 * TenProps.cpp
 *
 *  Created on: Nov 22, 2009
 *      Author: Andy
 */

#include "PogoCommon.h"
#include "TenProps.h"
#include "tier0/dbg.h"
#include <boost/tokenizer.hpp>
#include <iostream>

static std::string DEFNAME = "def.properties";
static std::string PREFIX = "def";
static std::string EXTENSION = ".properties";
static std::string LINE_SEPARATOR = "/";

using namespace Pogo;

TenProps::TenProps(const std::wstring& fname)
{
	if (fname.length() == 0)
	{
        Log("TenProps: WARNING! passed in filename null or empty! No properties loaded");
	}
	else
	{
		m_props = PropertiesPtr(new Properties());

		std::vector<std::wstring> fnames = p_getFiles(fname);

		for (size_t i = 0; i < fnames.size(); i ++)
		{
			m_props->Load(fnames[i]);
		}
	}
}

TenProps::~TenProps()
{
	m_props = PropertiesPtr();
}

	/**
	 * <p>
	 * Get the std::vector of files to be loaded from the given file name and locale.
	 * If the file name resolves to the absolute path "/a/b/c/my.properties",
	 * and the locale resolves to en_US, then the following files will make up
	 * the std::vector:
	 * </p>
	 * <ul>
	 * <li>/a/def.properties</li>
	 * <li>/a/def_en.properties</li>
	 * <li>/a/def_en_US.properties</li>
	 * <li>/a/b/def.properties</li>
	 * <li>/a/b/def_en.properties</li>
	 * <li>/a/b/def_en_US.properties</li>
	 * <li>/a/b/c/def.properties</li>
	 * <li>/a/b/c/def_en.properties</li>
	 * <li>/a/b/c/def_en_US.properties</li>
	 * <li>/a/b/c/my.properties</li>
	 * <li>/a/b/c/my_en.properties</li>
	 * <li>/a/b/c/my_en_US.properties</li>
	 * </ul>
	 * <p>
	 * When paths/files aren't found, warning msgs will be printed, but the code won't fail. At
	 * worst you'll end up with an empty Properties object.
	 * </p>
	 */
std::vector<std::wstring> TenProps::p_getFiles(const std::wstring& fname)
{
	std::vector<std::wstring> fnames;

	bool wasDefault = false;

	std::string ns = Pogo::WideToNarrow(fname);
	std::vector<std::string> pit = p_Explode(ns);

	for (size_t i = 0; i < pit.size(); i ++)
	{
		std::string name = pit[i] + LINE_SEPARATOR + DEFNAME;
		if (name.compare(ns) == 0)
			wasDefault = true;
		fnames.push_back(Pogo::NarrowToWide(name));
	}

	if (!wasDefault) {
		fnames.push_back(fname);
	}

	return fnames;
}

std::vector<std::string> TenProps::p_Explode(std::string& src)
{
	std::vector<std::string> output;

	boost::char_separator<char> separator(LINE_SEPARATOR.data());
	boost::tokenizer<boost::char_separator<char> > tokens(src, separator);
	boost::tokenizer<boost::char_separator<char> >::iterator token_iter;

	std::string path;

	for (token_iter = tokens.begin(); token_iter != tokens.end(); token_iter++)
	{
		path += LINE_SEPARATOR + *token_iter;
		output.push_back(path);
	}

	return output;
}
