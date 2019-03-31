#ifndef __Object_H__
#define __Object_H__
#include<Windows.h>

class Object
{
public:
	virtual ~Object(){}

	virtual void draw()=0;
	virtual void update()=0;
	virtual void clean()=0;
};
#endif