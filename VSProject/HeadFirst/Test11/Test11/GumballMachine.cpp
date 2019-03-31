#include "GumballMachine.h"

GumballMachine::GumballMachine(int count)
	:soldOutState(nullptr),noQuarterState(nullptr)
	,hasQuarterState(nullptr),soldState(nullptr),winnerState(nullptr)
	,count(count)
{
	soldOutState = new SoldOutState(this);
	noQuarterState = new NoQuarterState(this);
	hasQuarterState = new HasQuarterState(this);
	soldState = new SoldState(this);
	winnerState = new WinnerState(this);
	//³õÊ¼»¯
	if(count > 0)
		state = noQuarterState;
}
void GumballMachine::insertQuarter()
{
	state->insertQuarter();
}
void GumballMachine::ejectQuarter()
{
	state->ejectQuarter();
}
void GumballMachine::turnCrank()
{
	bool bRet = state->turnCrank();
	if(bRet)
		state->dispense();
}
void GumballMachine::setState(State*state)
{
	this->state = state;
}
void GumballMachine::releaseBall()
{
	cout<<"A gumball comes rolling out the slot..."<<endl;
	if(count != 0)
	{
		count -= 1;
	}
}
void GumballMachine::refill(int count)
{
	this->count = count;
	state = noQuarterState;
}
void GumballMachine::toString()
{
	cout<<"Mighty Gumball"<<endl;
	cout<<"couts:"<<this->count<<endl;
}