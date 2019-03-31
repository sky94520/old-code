#ifndef __StringUtil__
#define __StringUtil__

#include "cocos2d.h"
USING_NS_CC;
class StringUtil : public Ref
{
public:
	static StringUtil*getInstance();

	virtual bool init();
	ValueVector split(const char*srcStr,const char*aSep);
private:
	static StringUtil*m_StringUtil;

};
#endif