#include "CeilingFan.h"
CeilingFan::CeilingFan(const string&location)
	:location(location),speed(OFF)
{
}
void CeilingFan::high()
{
	speed = HIGH;
	cout<<location<<" CeilingFan is high"<<endl;
}
void CeilingFan::medium()
{
	speed = MEDIUM;
}
void CeilingFan::low()
{
	speed = LOW;
}
void CeilingFan::off()
{
	speed = OFF;
	cout<<location<<" CeilingFan is off"<<endl;
}
CeilingFanSpeed CeilingFan::getSpeed()const
{
	return speed;
}