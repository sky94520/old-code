#include "Light.h"
Light::Light(const string&name)
	:name(name)
{
}
void Light::on()
{
	cout<<name<<" Light is on"<<endl;
}
void Light::off()
{
	cout<<name<<" Light is off"<<endl;
}