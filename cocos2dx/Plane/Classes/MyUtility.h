#ifndef __MyUtility_H__
#define __MyUtility_H__
#include<string>
#include "cocos2d.h"
USING_NS_CC;
class MyUtility:public Ref
{
public:
	static std::string getCurrentTime();//获取当前系统时间
	static std::string gbk_to_utf8(const std::string&text);//主要用于windows
	static std::string getUTF8Char(const std::string&key);//读取value
};
#endif