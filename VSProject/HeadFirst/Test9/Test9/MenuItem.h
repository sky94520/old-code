#ifndef __MenuItem_H__
#define __MenuItem_H__
#include<iostream>
#include<string>
#include "MenuComponent.h"
using namespace std;
/*²Ëµ¥Ïî*/
class MenuItem:public MenuComponent
{
private:
	string name;
	string description;
	double price;
	bool vegetarian;
public:
	MenuItem(const string&name,const string&desc,double price,bool vegetarian);
	virtual string getName()const;
	virtual string getDescription()const;
	virtual double getPrice()const;
	virtual bool isVegetarian()const;
	virtual void print();
};
#endif