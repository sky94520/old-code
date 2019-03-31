#ifndef __StringUtils_H__
#define __StringUtils_H__
#include<cstdarg>
#include<string>
#include<sstream>
#include "cocos2d.h"
USING_NS_CC;
namespace StringUtil
{
std::string format(const char*format,...);
//²ð·Ö×Ö·û´®
ValueVector split(std::string srcStr,const std::string& sSep);
template<typename T>
std::string toString(T t)
{
	std::stringstream ss;
	ss<<t;
	return ss.str();
}
//end the StringUtils
}
#endif