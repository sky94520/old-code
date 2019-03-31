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
		cout<<"�����ó�����"<<endl;
	}
};
//------------------------FlyNoWay-----------------------------------------------------
class FlyNoWay:public FlyBehavior
{
public:
	virtual void fly()
	{
		cout<<"�Ҳ����"<<endl;
	}
};
//--------------------------FlyRocketPowered-------------------------------------------------------------
class FlyRocketPowered:public FlyBehavior
{
public:
	virtual void fly()
	{
		cout<<"�������û����"<<endl;
	}
};
#endif