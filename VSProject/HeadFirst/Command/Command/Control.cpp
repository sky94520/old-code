#include "Control.h"
#include "Command.h"

RemoteControl::RemoteControl(int count)
{
	Command*noCommand = new NoCommand();
	for(int i=0;i<count;i++)
	{
		onCommands.push_back(noCommand);
		offCommands.push_back(noCommand);
	}
	undoCommand = noCommand;
}
void RemoteControl::setCommand(int slot,Command*onCommand,Command*offCommand)
{
	onCommands.at(slot) = onCommand;
	offCommands.at(slot) = offCommand;
}
void RemoteControl::onButtonWasPushed(int slot)
{
	onCommands.at(slot)->execute();
	undoCommand = onCommands.at(slot);
}
void RemoteControl::offButtonWasPushed(int slot)
{
	offCommands.at(slot)->execute();
	undoCommand = offCommands.at(slot);
}
void RemoteControl::undoButtonWasPushes()
{
	undoCommand->undo();
}
string RemoteControl::toString()
{
	ostringstream buff;
	buff<<"----------------------Remote Control------------------"<<endl;

	for(int i=0;i<onCommands.size();i++)
	{
		buff<<"[slot"<<i<<"]:"<<onCommands.at(i)->toString()<<"      "<<offCommands.at(i)->toString()<<endl;
	}
	return buff.str();
}