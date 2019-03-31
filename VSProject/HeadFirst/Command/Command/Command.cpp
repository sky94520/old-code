#include "Command.h"
#include "Light.h"
void NoCommand::execute()
{
	cout<<"This is no command"<<endl;
}
void NoCommand::undo()
{
}
string NoCommand::toString()const
{
	return "NoCommand";
}
//-----------------------------LightOnCommand--------------------------------
LightOnCommand::LightOnCommand(Light*light)
{
	m_pLight = light;
}
void LightOnCommand::execute()
{
	m_pLight->on();
}
void LightOnCommand::undo()
{
	m_pLight->off();
}
string LightOnCommand::toString()const
{
	return "LightOnCommand";
}
//---------------------------LightOffCommand-----------------------------------
LightOffCommand::LightOffCommand(Light*light)
{
	m_pLight = light;
}
void LightOffCommand::execute()
{
	m_pLight->off();
}
void LightOffCommand::undo()
{
	m_pLight->on();
}
string LightOffCommand::toString()const
{
	return "LightOffCommand";
}
//-------------------------------------CeilingFanHighCommand--------------------------
CeilingFanHighCommand::CeilingFanHighCommand(CeilingFan*ceilingFan)
	:ceilingFan(ceilingFan)
{
}
void CeilingFanHighCommand::execute()
{
	prevSpeed = ceilingFan->getSpeed();
	ceilingFan->high();
}
void CeilingFanHighCommand::undo()
{
	if(prevSpeed == HIGH)
		ceilingFan->high();
	else if(prevSpeed == MEDIUM)
		ceilingFan->medium();
	else if(prevSpeed == LOW)
		ceilingFan->low();
	else if(prevSpeed == OFF)
		ceilingFan->off();
}
string CeilingFanHighCommand::toString()const
{
	return "CeilingFanHighCommand";
}
//----------------------------------------CeilingFanOffCommand-------------------------------------------
CeilingFanOffCommand::CeilingFanOffCommand(CeilingFan*ceilingFan)
	:ceilingFan(ceilingFan)
{
}
void CeilingFanOffCommand::execute()
{
	prevSpeed = ceilingFan->getSpeed();
	ceilingFan->off();
}
void CeilingFanOffCommand::undo()
{
	if(prevSpeed == HIGH)
		ceilingFan->high();
	else if(prevSpeed == MEDIUM)
		ceilingFan->medium();
	else if(prevSpeed == LOW)
		ceilingFan->low();
	else if(prevSpeed == OFF)
		ceilingFan->off();
}
string CeilingFanOffCommand::toString()const
{
	return "CeilingFanOffCommand";
}
//----------------------------------------MacroCommand--------------------------------------------
MacroCommand::MacroCommand()
{
}
void MacroCommand::push(Command*command)
{
	commands.push_back(command);
}
void MacroCommand::execute()
{

}
string MacroCommand::toString()const
{
	ostringstream buff;
	for(auto c:commands)
		buff<<c->toString()<<",";
	return buff.str();
}