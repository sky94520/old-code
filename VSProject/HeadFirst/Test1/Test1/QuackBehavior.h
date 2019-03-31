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
		cout<<"���ɽ�"<<endl;
	}
};
//------------------------Squeak-----------------------------------------------
class Squeak:public QuackBehavior
{
public:
	virtual void quack()
	{
		cout<<"֨֨��"<<endl;
	}
};
//---------------------------MuteQuack-----------------------------------------------------
class MuteQuack:public QuackBehavior
{
public:
	virtual void quack()
	{
		//ʲôҲ�����������
	}
};
#endif