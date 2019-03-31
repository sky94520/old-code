#ifndef __MenuComponent_H__
#define __MenuComponent_H__
#include<string>
#include "Iterator.h"

using namespace std;

class MenuComponent
{
public:
	virtual void add(MenuComponent*c){}
	virtual void remove(MenuComponent*c){}
	virtual MenuComponent* getChild(int i){return nullptr;}
	virtual string getName()const{return "";}
	virtual string getDescription()const{return "";};
	virtual double getPrice()const{return 0;}
	virtual bool isVegetarian()const{return true;}
	virtual void print(){}
	virtual Iterator*createIterator(){return new NullIterator();}
};
#endif