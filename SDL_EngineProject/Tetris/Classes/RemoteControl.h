#ifndef __RemoteControl_H__
#define __RemoteControl_H__
#include<map>
#include<string>

using namespace std;
class Command;

class RemoteControl
{
private:
	map<string,Command*> m_commands;
	Command*m_pUndoCommand;
public:
	RemoteControl();
	~RemoteControl();
	void addCommand(const string&id,Command*command);
	void onButtonPressed(const string&id);
	void undoButtonPressed();
};
#endif