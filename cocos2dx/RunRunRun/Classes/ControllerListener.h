//#pragma once
#ifndef __ControllerListener_H__
#define __ControllerListener_H__
#include "cocos2d.h"

USING_NS_CC;

class ControllerListener
{
public:
	virtual void setTagPosition(int x,int y) = 0;
	virtual Point getTagPosition() = 0; 
};
#endif