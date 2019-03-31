#include "SnowMan.h"

SnowMan::SnowMan()
{
}

SnowMan::~SnowMan()
{
}

SnowMan*SnowMan::create(const string&plantName)
{
	auto plant = new SnowMan();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool SnowMan::init(const string&plantName)
{

	return true;
}

void SnowMan::updateHook(float dt)
{
}