#ifndef __Control_H__
#define __Control_H__
#include<vector>
#include<cstdio>
#include<string>
#include<sstream>
class Command;
using namespace std;
//遥控器类 
//实现命令模式 实现与电器的解耦
class RemoteControl
{
private:
	vector<Command*> onCommands;
	vector<Command*> offCommands;
	Command*undoCommand;//撤销命令
public:
	RemoteControl(int count);
	~RemoteControl();
	void setCommand(int slot,Command*onCommand,Command*offCommand);
	void onButtonWasPushed(int slot);
	void offButtonWasPushed(int slot);
	void undoButtonWasPushes();

	string toString();
};
#endif