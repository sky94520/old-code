#include "SimplePizzaFactory.h"
#include "Pizza.h"

SimplePizzaFactory*SimplePizzaFactory::m_pInstance = nullptr;

SimplePizzaFactory::SimplePizzaFactory()
{
}
SimplePizzaFactory::~SimplePizzaFactory()
{
}
SimplePizzaFactory*SimplePizzaFactory::getInstance()
{
	if(m_pInstance == nullptr)
		m_pInstance = new SimplePizzaFactory();
	return m_pInstance;
}
Pizza*SimplePizzaFactory::createPizza(const string& type)
{
	Pizza*pizza = nullptr;
	if(type == "cheese")
		pizza = new CheesePizza();
	else if(type == "greek")
		pizza = new GreekPizza();

	return pizza;
}