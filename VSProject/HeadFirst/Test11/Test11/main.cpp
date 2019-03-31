#include<iostream>
#include<conio.h>
#include "State.h"
#include "GumballMachine.h"

using namespace std;

int main()
{
	GumballMachine*machine = new GumballMachine(1);
	machine->toString();

	machine->insertQuarter();
	machine->turnCrank();

	machine->refill(10);

	machine->toString();
	machine->insertQuarter();
	machine->turnCrank();

	_getch();
	return 0;
}