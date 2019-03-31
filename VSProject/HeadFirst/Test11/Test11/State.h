#ifndef __State_H__
#define __State_H__
#include<iostream>
using namespace std;

class GumballMachine;

class State
{
protected:
	GumballMachine*gumballMachine;
	State(GumballMachine*machine);
public:
	virtual ~State(){}
	virtual void insertQuarter();//投入25美分
	virtual void ejectQuarter();//弹出25美分
	virtual bool turnCrank();//转动曲柄
	virtual void dispense();//分配糖果
};
//-----------------------NoQuarterState-----------------------------------------
class NoQuarterState:public State
{
public:
	NoQuarterState(GumballMachine*machine);
	virtual void insertQuarter();
};
//--------------------HasQuarterState-------------------------------------------
class HasQuarterState:public State
{
public:
	HasQuarterState(GumballMachine*machine);
	virtual void ejectQuarter();
	virtual bool turnCrank();
};
//---------------------------SoldState------------------------------------------
class SoldState:public State
{
public:
	SoldState(GumballMachine*machine);
	virtual void dispense();
};
//---------------------------------SoldOutState-------------------------------
class SoldOutState:public State
{
public:
	SoldOutState(GumballMachine*machine);
	virtual void insertQuarter();
	virtual void ejectQuarter();
	virtual bool turnCrank();
	virtual void dispense();
};
//----------------------------------WinnerState----------------------------------
class WinnerState:public State
{
public:
	WinnerState(GumballMachine*machine);
	virtual void dispense();
};
#endif