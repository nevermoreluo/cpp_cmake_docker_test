//
// (C) Electronic Arts 2006
// 

#pragma once

namespace Pogo
{
// This class is used as a base for helping with RTTI objects used
// in the Pogo framework. When you derive from this class, you will
// be able to use the IS_TYPE(x,y) macro to determine the type
// of an object. It is also possible to manually use a dynamic_cast
// to determine the type of an object derived from Object.
class Object
{
public:
	// The class needs at least one virtual member, so why not 
	// just use the destructor?
	virtual ~Object(){}
};

}
