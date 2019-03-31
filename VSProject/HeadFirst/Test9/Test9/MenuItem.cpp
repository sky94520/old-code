#include "MenuItem.h"
MenuItem::MenuItem(const string&name,const string&desc,double price,bool vegetarian)
	:name(name),description(desc),price(price),vegetarian(vegetarian)
{
}
string MenuItem::getName()const
{
	return name;
}
string MenuItem::getDescription()const
{
	return description;
}
double MenuItem::getPrice()const
{
	return price;
}
bool MenuItem::isVegetarian()const
{
	return vegetarian;
}
void MenuItem::print()
{
	cout<<"   "<<getName();
	if(isVegetarian())
		cout<<"(v)";
	cout<<","<<getPrice()<<endl;
	cout<<"      --"<<getDescription()<<endl;
}