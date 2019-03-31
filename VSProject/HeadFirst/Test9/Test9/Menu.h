#ifndef __Menu_H__
#define __Menu_H__
#include<vector>
#include<string>
#include<iostream>
#include "MenuComponent.h"
using namespace std;


class Menu:public MenuComponent
{
private:
	vector<MenuComponent*> menuComponents;
	string name;
	string description;
public:
	Menu(const string&name,const string&desc);
	virtual void add(MenuComponent*component);
	virtual void remove(MenuComponent*component);
	virtual MenuComponent*getChild(int i);
	virtual string getName()const;
	virtual string getDescription()const;;
	virtual void print();
	virtual Iterator*createIterator();
};
#endif