#include "Lawn.h"
Lawn::Lawn()
{
}
Lawn::~Lawn()
{
}
bool Lawn::init()
{
	//test
	bindSprite(Sprite::create("Resources/greytest.png"));
	setContentSize(Size(80,100));
	return true;
}
std::string Lawn::getCarrierType()const
{
	return "Lawn";
}