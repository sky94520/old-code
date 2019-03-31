#ifndef __StringUtil_H__
#define __StringUtil_H__
#include<string>
#include<vector>
#include "cocos2d.h"
USING_NS_CC;
class StringUtil
{
private:
	static StringUtil*m_pInstance;

	StringUtil();
	~StringUtil();
public:
	static StringUtil*getInstance();
	//²ð·Ö×Ö·û´®
	ValueVector split(std::string srcStr,std::string sSep);
	//void getNext(std::string ,int next[]);
};
#endif