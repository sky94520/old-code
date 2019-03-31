#ifndef __ArrowAction_H__
#define __ArrowAction_H__
#include "cocos2d.h"
USING_NS_CC;
typedef struct 
{
	Vec2 startPos;
	Vec2 middlePos;
	Vec2 endPos;
public:
	float length()
	{
		 
	}
}ArrowConfig;
class ArrowAction:public ActionInterval
{
private:
	ArrowConfig _arrowConfig;
public:
	ArrowAction();
	~ArrowAction();
	static ArrowAction*create(const Vec2&startPos,const Vec2&middle);
	bool init(const Vec2&startPos,const Vec2&middle);
public:
	virtual void startWithTarget(Node*target);
	virtual void update(float time);
};
#endif