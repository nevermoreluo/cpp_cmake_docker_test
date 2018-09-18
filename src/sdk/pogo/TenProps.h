/*
 * TenProps.h
 *
 *  Created on: Nov 22, 2009
 *      Author: Andy
 */

#ifndef TENPROPS_H_
#define TENPROPS_H_

#include "Properties.h"

namespace Pogo
{
class TenProps
{
public:
	TenProps(const std::wstring& filename);

	virtual ~TenProps();

public:
	PropertiesPtr& GetProps() { return m_props; }

private:
	std::vector<std::wstring> p_getFiles(const std::wstring& fname);
	std::vector<std::string> p_Explode(std::string& src);
private:
	std::wstring m_filename;
	PropertiesPtr m_props;
};

}

#endif /* TENPROPS_H_ */
