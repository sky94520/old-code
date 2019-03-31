#include "Menu.h"
Menu::Menu(const string&name,const string&desc)
	:name(name),description(desc)
{
}
void Menu::add(MenuComponent*component)
{
	menuComponents.push_back(component);
}
void Menu::remove(MenuComponent*component)
{
	;
}
MenuComponent*Menu::getChild(int i)
{
	if(i <0 || i > menuComponents.size())
		return nullptr;
	return menuComponents.at(i);
}
string Menu::getName()const
{
	return name;
}
string Menu::getDescription()const
{
	return description;
}
void Menu::print()
{
	cout<<"\n"<<getName();
	cout<<","<<getDescription()<<endl;
	cout<<"-----------------------------------------"<<endl;

	auto iterator = this->createIterator();
	while(iterator->hasNext())
	{
		auto item = iterator->next();
		item->print();
	}
}
Iterator*Menu::createIterator()
{
	return new CompositeIterator(menuComponents);
}