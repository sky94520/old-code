#ifndef __TouchListener_H__
#define __TouchListener_H__

#include "cocos2d.h"
USING_NS_CC;

class TouchListener
{
public:
	virtual Point getTagPosition() = 0;
	virtual void setTagPosition(Point point) = 0;
};
#endif