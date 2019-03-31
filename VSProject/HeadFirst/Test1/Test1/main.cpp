#include<iostream>
#include<conio.h>

#include "Duck.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"

int main()
{
	//��ͷѼ��
	Duck*duck = new MallardDuck();
	duck->setFlyBehavior(new FlyWithWings());
	duck->setQuackBehavior(new Quack());
	duck->display();
	duck->performFly();
	duck->performQuack();
	//��ƤѼ
	Duck*duck2 = new RubberDuck();
	duck2->setFlyBehavior(new FlyNoWay());
	duck2->setQuackBehavior(new MuteQuack());
	duck2->display();
	duck2->performFly();
	duck2->performQuack();

	duck2->setFlyBehavior(new FlyRocketPowered());
	duck2->performFly();
	//������ֱ���˳�
	_getch();

	return 0;
}