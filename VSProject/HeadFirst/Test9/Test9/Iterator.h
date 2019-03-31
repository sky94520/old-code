#ifndef __Iterator_H__
#define __Iterator_H__
#include<vector>
using namespace std;

class MenuComponent;

class Iterator
{
public:
	virtual ~Iterator(){}
	virtual MenuComponent*next()=0;
	virtual bool hasNext()=0;
};
//---------------------------------------NullIterator----------------------------
class NullIterator:public Iterator
{
public:
	NullIterator(){}
	virtual MenuComponent*next(){return nullptr;}
	virtual bool hasNext(){return false;}
};
//---------------------------------------CompositeIterator-----------------------
class CompositeIterator:public Iterator
{
private:
	vector<MenuComponent*>::iterator curIter;
	vector<MenuComponent*>::iterator endIter;
public:
	CompositeIterator(vector<MenuComponent*>& menuComponents)
	{
		curIter = menuComponents.begin();
		endIter = menuComponents.end();
	}
	virtual MenuComponent*next()
	{
		return *curIter++;
	}
	virtual bool hasNext()
	{
		return endIter != curIter;
	}
};
#endif