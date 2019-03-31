#ifndef __FlyBehavior_H__
#define __FlyBehavior_H__
#include<iostream>
using namespace std;

class FlyBehavior
{
public:
	virtual ~FlyBehavior(){}
	virtual void fly()=0;
};
//---------------------------FlyWithWings--------------------------------------------------
class FlyWithWings:public FlyBehavior
{
public:
	virtual void fly()
	{
		cout<<"我在用翅膀飞行"<<endl;
	}
};
//------------------------FlyNoWay-----------------------------------------------------
class FlyNoWay:public FlyBehavior
{
public:
	virtual void fly()
	{
		cout<<"我不会飞"<<endl;
	}
};
//--------------------------FlyRocketPowered-------------------------------------------------------------
class FlyRocketPowered:public FlyBehavior
{
public:
	virtual void fly()
	{
		cout<<"我正在用火箭飞"<<endl;
	}
};
#endif