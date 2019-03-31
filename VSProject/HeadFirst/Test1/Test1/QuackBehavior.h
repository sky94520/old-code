#ifndef __QuackBehavior_H__
#define __QuackBehavior_H__
#include<iostream>
using namespace std;

class QuackBehavior
{
public:
	virtual ~QuackBehavior(){}
	virtual void quack()=0;
};
//-----------------------Quack-----------------------------------------------
class Quack:public QuackBehavior
{
public:
	virtual void quack()
	{
		cout<<"呱呱叫"<<endl;
	}
};
//------------------------Squeak-----------------------------------------------
class Squeak:public QuackBehavior
{
public:
	virtual void quack()
	{
		cout<<"吱吱叫"<<endl;
	}
};
//---------------------------MuteQuack-----------------------------------------------------
class MuteQuack:public QuackBehavior
{
public:
	virtual void quack()
	{
		//什么也不做，不会叫
	}
};
#endif