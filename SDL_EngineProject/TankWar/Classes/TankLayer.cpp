#include "TankLayer.h"
#include "Tank.h"

TankLayer::TankLayer()
{
}

TankLayer::~TankLayer()
{

}

bool TankLayer::init()
{
	//TODO
	auto tank = Tank::create("tank_blue");
	tank->setPosition(400.f, 400.f);
	this->addChild(tank);

	m_tanks.push_back(tank);

	return true;
}

