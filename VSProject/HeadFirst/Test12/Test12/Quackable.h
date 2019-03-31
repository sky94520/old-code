#ifndef __Quackable_H__
#define __Quackable_H__

class Quackable
{
public:
	virtual ~Quackable(){}
	virtual void quack()=0;
};
#endif