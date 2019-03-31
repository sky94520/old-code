#ifndef __StaticData_H__
#define __StaticData_H__
#include "cocos2d.h"
USING_NS_CC;
class StaticData:public Ref
{
private:
	ValueMap m_valueMap;
	static StaticData*m_pInstance;
private:
	StaticData();
	~StaticData();
	bool init();
public:
	static StaticData*getInstance();
	void purge();
	Value getValueForKey(const std::string&key)const;
	std::string getStringForKey(const std::string&key)const;
};
#endif