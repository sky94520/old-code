#ifndef __Control_H__
#define __Control_H__
#include<vector>
#include<cstdio>
#include<string>
#include<sstream>
class Command;
using namespace std;
//ң������ 
//ʵ������ģʽ ʵ��������Ľ���
class RemoteControl
{
private:
	vector<Command*> onCommands;
	vector<Command*> offCommands;
	Command*undoCommand;//��������
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