#ifndef __Pizza_H__
#define __Pizza_H__
class Pizza
{
public:
	void prepare();
	void bake();
	void cut();
	void box();
};
class CheesePizza:public Pizza
{
public:
	CheesePizza();
};
class GreekPizza:public Pizza
{
public:
	GreekPizza();
};
#endif