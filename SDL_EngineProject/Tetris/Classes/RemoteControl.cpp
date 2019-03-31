#include "RemoteControl.h"
#include "Command.h"
RemoteControl::RemoteControl()
	:m_pUndoCommand(nullptr)
{
}
RemoteControl::~RemoteControl()
{
	for(auto iter=m_commands.begin();iter != m_commands.end();)
	{
		auto command = iter->second;
		iter = m_commands.erase(iter);
		delete command;
	}
}
void RemoteControl::addCommand(const string&id,Command*command)
{
	m_commands.insert(make_pair(id,command));
}
void RemoteControl::onButtonPressed(const string&id)
{
	auto iter = m_commands.find(id);
	if(iter != m_commands.end())
	{
		auto command = m_pUndoCommand = iter->second;
		command->execute();
	}
}
void RemoteControl::undoButtonPressed()
{
	if(m_pUndoCommand)
		m_pUndoCommand->undo();
}