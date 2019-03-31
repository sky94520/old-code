#ifndef __PizzaStore_H__
#define __PizzaStore_H__
#include<string>
class Pizza;
using namespace std;

class PizzaStore
{
public:
	Pizza*orderPizza(const string&type);

	virtual Pizza*createPizza(const string&type)=0;
};
class NYStylePizzaStore:public PizzaStore
{
public:
	virtual Pizza*createPizza(const string*type);
};
#endif