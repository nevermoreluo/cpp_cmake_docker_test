/******************************************************************************
*file name    : imodule.h
*owner        : 
*description  : 
*modified     : 2008-6-1 16:25:07
******************************************************************************/ 

/*
$Author$
$Source$
$RCSfile$
$Date$
$Log$
*/

#ifndef IMODULE_H
#define IMODULE_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "Runnable.h"
#include "boost/shared_ptr.hpp"

namespace Pogo
{
	typedef boost::shared_ptr<class Properties> PropertiesPtr;
}

class IMoudle : public IAppSystem
{
public:
	enum RUN_RETURN
	{
		RUN_RETURN_ERROR = -1,
		RUN_RETURN_SUCCESS = 0
	};

public:
	virtual InitReturnVal_t Init(const Pogo::PropertiesPtr& props) = 0;

	// called by the module container
	// return: RUN_RETURN_ERROR, RUN_RETURN_SUCCESS.
	virtual RUN_RETURN Run(void) = 0;
};

#endif // IMODULE_H
