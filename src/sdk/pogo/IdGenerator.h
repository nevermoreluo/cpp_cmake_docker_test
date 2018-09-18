/*
 * CUpdateMask.h
 *
 *  Created by: 2011-11-25
 *  Creator: liukai
 */

#ifndef _ID_GENERATOR_H
#define _ID_GENERATOR_H

#include "NiSmartPointer.h"
#include "NiRefObject.h"
#include <string>
#include <limits>

template <typename T>
class CIdGenerator : public NiRefObject
{
public:
	explicit CIdGenerator(const std::string & strName) : m_strName(strName), m_nNextGuid(1)
	{

	}

public:
	void Set(T nVal) { m_nNextGuid = nVal; }

	T Generate();

	const T & GetNextAfterMaxUsed() const { return m_nNextGuid; }

private:
	std::string m_strName;
	T m_nNextGuid;
};

template <typename T>
T CIdGenerator<T>::Generate()
{
	if (m_nNextGuid >= (std::numeric_limits<T>::max() - 1))
	{
		// 日志并且结束程序
	}

	return m_nNextGuid++;
}

#endif // _ID_GENERATOR_H
