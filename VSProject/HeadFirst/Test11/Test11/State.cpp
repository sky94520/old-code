#include "State.h"
#include "GumballMachine.h"
State::State(GumballMachine*machine)
	:gumballMachine(machine)
{
}
void State::insertQuarter()
{
	cout<<"��Ͷ����25����"<<endl;
}
void State::ejectQuarter()
{
	cout<<"�㲢û��������������Ǯ������"<<endl;
}
bool State::turnCrank()
{
	cout<<"��ת�������������ǲ�û��������Ͷ��25����"<<endl;
	return false;
}
void State::dispense()
{
	cout<<"����֧��25����"<<endl;
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
	cout<<"����25����"<<endl;
	gumballMachine->setState(gumballMachine->getNoQuarterState());
}
bool HasQuarterState::turnCrank()
{
	cout<<"��ת��������"<<endl;
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
	//�����ǹ�
	gumballMachine->releaseBall();
	//���ݵ�ǰ����ת��״̬
	if(gumballMachine->getCount() > 0)
		gumballMachine->setState(gumballMachine->getNoQuarterState());
	else
	{
		cout<<"�ǹ����Ѿ�û���ǹ���"<<endl;
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
	cout<<"�ǹ����Ѿ�û���ǹ��ˣ���"<<endl;
}
void SoldOutState::ejectQuarter()
{
	cout<<"�ǹ����Ѿ�û���ǹ��ˣ���"<<endl;
}
bool SoldOutState::turnCrank()
{
	cout<<"�ǹ����Ѿ�û���ǹ��ˣ���"<<endl;
	return false;
}
void SoldOutState::dispense()
{
	cout<<"�ǹ����Ѿ�û���ǹ��ˣ���"<<endl;
}
//------------------------------------------WinnerState----------------------------
WinnerState::WinnerState(GumballMachine*machine)
	:State(machine)
{
}
void WinnerState::dispense()
{
	//�������ֻ�ܱ�֤�в�����1�����ǹ�
	gumballMachine->releaseBall();
	int counts = gumballMachine->getCount();
	
	if(counts > 0)
	{
		gumballMachine->releaseBall();
		cout<<"��ϲ������һ��Ӯ�ң�����"<<endl;
	}
	if(counts == 0)
		gumballMachine->setState(gumballMachine->getSoldOutState());
	else
		gumballMachine->setState(gumballMachine->getNoQuarterState());
}