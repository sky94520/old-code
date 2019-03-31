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
	virtual void swim();//����Ӿ
	virtual void display();//�����ڻ�ͼ��Ŀǰ���������������̨
	void performFly();
	void performQuack();
	void setFlyBehavior(FlyBehavior*behavior);
	void setQuackBehavior(QuackBehavior*behavior);
};
//��ͷѼ��
class MallardDuck:public Duck
{
public:
	virtual void display()
	{
		cout<<"��ͷѼ��"<<endl;
	}
};
//��ͷѼ��
class RedheadDuck:public Duck
{
public:
	void display()
	{
		cout<<"��ͷѼ��"<<endl;
	}
};
//��ƤѼ
class RubberDuck:public Duck
{
public:
	void display()
	{
		cout<<"��ƤѼ��"<<endl;
	}
};

#endif