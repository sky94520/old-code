#include<iostream>
#include<conio.h>

#include "Duck.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"

int main()
{
	//绿头鸭子
	Duck*duck = new MallardDuck();
	duck->setFlyBehavior(new FlyWithWings());
	duck->setQuackBehavior(new Quack());
	duck->display();
	duck->performFly();
	duck->performQuack();
	//橡皮鸭
	Duck*duck2 = new RubberDuck();
	duck2->setFlyBehavior(new FlyNoWay());
	duck2->setQuackBehavior(new MuteQuack());
	duck2->display();
	duck2->performFly();
	duck2->performQuack();

	duck2->setFlyBehavior(new FlyRocketPowered());
	duck2->performFly();
	//不至于直接退出
	_getch();

	return 0;
}