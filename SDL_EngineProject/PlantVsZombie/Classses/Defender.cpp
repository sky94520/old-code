#include "Defender.h"

Defender::Defender()
{
}

Defender::~Defender()
{
}

bool Defender::init()
{
	this->setPlantType(PlantType::Defender);

	return true;
}