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
	void onDeadCalback();//�����ص�����
	void end();//����ǽ��ʱ����
};
#endif