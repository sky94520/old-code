#include "Duck.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"
Duck::Duck()
	:flyBehavior(nullptr),quackBehavior(nullptr)
{
}
Duck::~Duck()
{
}
void Duck::swim()
{
	cout<<"我正在游泳"<<endl;
}
void Duck::display()
{
}
void Duck::performFly()
{
	flyBehavior->fly();
}
void Duck::performQuack()
{
	quackBehavior->quack();
}
void Duck::setFlyBehavior(FlyBehavior*behavior)
{
	flyBehavior = behavior;
}
void Duck::setQuackBehavior(QuackBehavior*behavior)
{
	quackBehavior = behavior;
}