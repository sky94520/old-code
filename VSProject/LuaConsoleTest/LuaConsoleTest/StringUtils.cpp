#include "StringUtils.h"

namespace StringUtils
{
std::string format(const char*format,...)
{
	std::string ret;
	va_list args;
	va_start(args,format);
	char*buf = (char*)malloc(1024*100);
	if(buf)
	{
		vsnprintf(buf,1024*100,format,args);
		ret = buf;
		free(buf);
	}
	va_end(args);
	return ret;
}
ValueVector split(std::string srcStr,const std::string& sSep)
{
	ValueVector stringList;
	int size = srcStr.size();

	int startIndex = 0;
	int endIndex = 0;
	endIndex = srcStr.find(sSep);

	std::string lineStr;
	while(endIndex > 0)
	{
		lineStr = srcStr.substr(startIndex,endIndex);
		stringList.push_back(Value(lineStr));
		srcStr = srcStr.substr(endIndex+1,size);

		endIndex = srcStr.find(sSep);
	}
	if(srcStr.compare("") != 0)
		stringList.push_back(Value(srcStr));
	return stringList;
}
//end namespace StringUtils
}