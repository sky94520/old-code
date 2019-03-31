#include "PizzaStore.h"
#include "Pizza.h"
#include "SimplePizzaFactory.h"

Pizza*PizzaStore::orderPizza(const string&type)
{
	Pizza*pizza = this->createPizza(type);

	pizza->prepare();
	pizza->bake();
	pizza->cut();
	pizza->box();

	return pizza;
}