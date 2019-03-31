#include<iostream>
#include<conio.h>
#include "Control.h"
#include "Light.h"
#include "Command.h"

using namespace std;

int main()
{
	//set 4 slot
	RemoteControl*remote = new RemoteControl(4);
	//Entity
	Light*livingRoomLight = new Light("Living Room");
	Light*kitchenLight = new Light("Kitcher");
	CeilingFan*ceilingFan = new CeilingFan("Living Room");
	//Command
	LightOnCommand*livingRoomLightOn = new LightOnCommand(livingRoomLight);
	LightOffCommand*livingRoomLightOff = new LightOffCommand(livingRoomLight);
	CeilingFanHighCommand*ceilingFanHigh = new CeilingFanHighCommand(ceilingFan);

	LightOnCommand*kitchenLightOn = new LightOnCommand(kitchenLight);
	LightOffCommand*kitchenLightOff = new LightOffCommand(kitchenLight);
	CeilingFanOffCommand*ceilingFanOff = new CeilingFanOffCommand(ceilingFan);

	remote->setCommand(0,livingRoomLightOn,livingRoomLightOff);
	remote->setCommand(1,kitchenLightOn,kitchenLightOff);
	remote->setCommand(2,ceilingFanHigh,ceilingFanOff);
	
	cout<<remote->toString()<<endl;

	remote->onButtonWasPushed(0);
	remote->undoButtonWasPushes();

	remote->offButtonWasPushed(0);

	remote->onButtonWasPushed(1);
	remote->offButtonWasPushed(1);

	remote->onButtonWasPushed(2);
	remote->undoButtonWasPushes();
	_getch();
	return 0;
}