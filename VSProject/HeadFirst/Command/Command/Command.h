#ifndef __Command_H__
#define __Command_H__
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include "CeilingFan.h"

using namespace std;

class Light;

class Command
{
public:
	virtual ~Command(){}
	virtual void execute()=0;
	virtual void undo()=0;//undo
	virtual string toString()const=0;
};
//----------------------------NoCommand----------------------------------
class NoCommand:public Command
{
public:
	virtual void execute();
	virtual void undo();
	virtual string toString()const;
};
//----------------------------LightOnCommand--------------------------------
class LightOnCommand:public Command
{
private:
	Light*m_pLight;
public:
	LightOnCommand(Light*light);
	virtual void execute();
	virtual void undo();
	virtual string toString()const;
};
//----------------------------LightOffCommand---------------------------------
class LightOffCommand:public Command
{
private:
	Light*m_pLight;
public:
	LightOffCommand(Light*light);
	void execute();
	virtual void undo();
	virtual string toString()const;
};
//-----------------------------CeilingFanHighCommand----------------------------
class CeilingFanHighCommand:public Command
{
private:
	CeilingFan*ceilingFan;
	CeilingFanSpeed prevSpeed;
public:
	CeilingFanHighCommand(CeilingFan*ceilingFan);
	virtual void execute();
	virtual void undo();
	virtual string toString()const;
};
//----------------------------CeilingFanOffCommand-----------------------------
class CeilingFanOffCommand:public Command
{
private:
	CeilingFan*ceilingFan;
	CeilingFanSpeed prevSpeed;
public:
	CeilingFanOffCommand(CeilingFan*ceilingFan);
	virtual void execute();
	virtual void undo();
	virtual string toString()const;
};
//-----------------------------MacroCommand------------------------------------------
class MacroCommand:public Command
{
private:
	vector<Command*> commands;
public:
	MacroCommand();
	void push(Command*command);
	virtual void execute();
	virtual string toString()const;
};
#endif