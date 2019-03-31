#ifndef __Duck_H__
#define __Duck_H__
#include<iostream>
using namespace std;

class QuackBehavior;
class FlyBehavior;

class Duck
{
private:
	FlyBehavior*flyBehavior;
	QuackBehavior*quackBehavior;
public:
	Duck();
	~Duck();
	virtual void swim();//会游泳
	virtual void display();//类似于绘图，目前仅仅是输出到控制台
	void performFly();
	void performQuack();
	void setFlyBehavior(FlyBehavior*behavior);
	void setQuackBehavior(QuackBehavior*behavior);
};
//绿头鸭子
class MallardDuck:public Duck
{
public:
	virtual void display()
	{
		cout<<"绿头鸭子"<<endl;
	}
};
//红头鸭子
class RedheadDuck:public Duck
{
public:
	void display()
	{
		cout<<"红头鸭子"<<endl;
	}
};
//橡皮鸭
class RubberDuck:public Duck
{
public:
	void display()
	{
		cout<<"橡皮鸭子"<<endl;
	}
};

#endif