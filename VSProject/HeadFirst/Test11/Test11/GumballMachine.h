#ifndef __GumballMachineState_H__
#define __GumballMachineState_H__
#include<iostream>
#include<string>
using namespace std;

#include "State.h"

class GumballMachine
{
private:
	State*soldOutState;
	State*noQuarterState;
	State*hasQuarterState;
	State*soldState;
	State*winnerState;

	State*state;
	int count;
public:
	GumballMachine(int count);
	void insertQuarter();
	void ejectQuarter();
	void turnCrank();
	void setState(State*state);
	void releaseBall();
	void refill(int count);

	void toString();

	int getCount()const
	{
		return count;
	}
	State*getSoldOutState()const
	{
		return soldOutState;
	}
	State*getNoQuarterState()const
	{
		return noQuarterState;
	}
	State*getHasQuarterState()const
	{
		return hasQuarterState;
	}
	State*getSoldState()const
	{
		return soldState;
	}
	State*getWinnerState()const
	{
		return winnerState;
	}
};
#endif