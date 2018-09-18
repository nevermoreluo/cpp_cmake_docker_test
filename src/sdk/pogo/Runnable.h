//
// (C) Electronic Arts 2005
// 

#pragma once

#include "Object.h"

namespace Pogo
{

// Runnable - An abstract class that has a Run() method. This can be
// used for threading or events
class Runnable : public Object
{
public:
	virtual void Run() = 0;
};

}
