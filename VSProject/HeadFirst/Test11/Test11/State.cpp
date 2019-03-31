#include "State.h"
#include "GumballMachine.h"
State::State(GumballMachine*machine)
	:gumballMachine(machine)
{
}
void State::insertQuarter()
{
	cout<<"你投入了25美分"<<endl;
}
void State::ejectQuarter()
{
	cout<<"你并没有往机器里塞入钱！！！"<<endl;
}
bool State::turnCrank()
{
	cout<<"你转动了曲柄，但是并没有往里面投入25美分"<<endl;
	return false;
}
void State::dispense()
{
	cout<<"请先支付25美分"<<endl;
}
//-----------------------NoQuarterState-----------------------------------------
NoQuarterState::NoQuarterState(GumballMachine*machine)
	:State(machine)
{
}
void NoQuarterState::insertQuarter()
{
	cout<<"You inserted a quarter"<<endl;
	gumballMachine->setState(gumballMachine->getHasQuarterState());
}
//--------------------HasQuarterState-------------------------------------------
HasQuarterState::HasQuarterState(GumballMachine*machine)
	:State(machine)
{
}
void HasQuarterState::ejectQuarter()
{
	cout<<"返还25美分"<<endl;
	gumballMachine->setState(gumballMachine->getNoQuarterState());
}
bool HasQuarterState::turnCrank()
{
	cout<<"你转动了曲柄"<<endl;
	int random = rand()%10;
	if(random == 0)
		gumballMachine->setState(gumballMachine->getWinnerState());
	else
		gumballMachine->setState(gumballMachine->getSoldState());
	return true;
}
//---------------------------SoldState------------------------------------------
SoldState::SoldState(GumballMachine*machine)
	:State(machine)
{
}
void SoldState::dispense()
{
	//发放糖果
	gumballMachine->releaseBall();
	//根据当前数量转换状态
	if(gumballMachine->getCount() > 0)
		gumballMachine->setState(gumballMachine->getNoQuarterState());
	else
	{
		cout<<"糖果机已经没有糖果了"<<endl;
		gumballMachine->setState(gumballMachine->getSoldOutState());
	}
}
//---------------------------------SoldOutState-------------------------------
SoldOutState::SoldOutState(GumballMachine*machine)
	:State(machine)
{
}
void SoldOutState::insertQuarter()
{
	cout<<"糖果机已经没有糖果了！！"<<endl;
}
void SoldOutState::ejectQuarter()
{
	cout<<"糖果机已经没有糖果了！！"<<endl;
}
bool SoldOutState::turnCrank()
{
	cout<<"糖果机已经没有糖果了！！"<<endl;
	return false;
}
void SoldOutState::dispense()
{
	cout<<"糖果机已经没有糖果了！！"<<endl;
}
//------------------------------------------WinnerState----------------------------
WinnerState::WinnerState(GumballMachine*machine)
	:State(machine)
{
}
void WinnerState::dispense()
{
	//到达这个只能保证有不少于1个的糖果
	gumballMachine->releaseBall();
	int counts = gumballMachine->getCount();
	
	if(counts > 0)
	{
		gumballMachine->releaseBall();
		cout<<"恭喜，你是一个赢家！！！"<<endl;
	}
	if(counts == 0)
		gumballMachine->setState(gumballMachine->getSoldOutState());
	else
		gumballMachine->setState(gumballMachine->getNoQuarterState());
}