#ifndef __SimplePizzaFactory_H__
#define __SimplePizzaFactory_H__
#include<string>

class Pizza;
using namespace std;

class SimplePizzaFactory
{
private:
	static SimplePizzaFactory*m_pInstance;
	
	SimplePizzaFactory();
	~SimplePizzaFactory();
public:
	Pizza*createPizza(const string&type);
	static SimplePizzaFactory*getInstance();
};
#endif