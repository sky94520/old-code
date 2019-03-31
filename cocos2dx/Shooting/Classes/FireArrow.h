#ifndef __FireArrow_H__
#define __FireArrow_H__
#include "Arrow.h"
class FireArrow:public Arrow
{
public:
	FireArrow();
	~FireArrow();
	CREATE_FUNC(FireArrow);
	bool init();
public:
	virtual void start(const Point&from,const Point&to);
	virtual void dead();
private:
	void onDeadCalback();//死亡回调函数
	void end();//碰到墙体时调用
};
#endif