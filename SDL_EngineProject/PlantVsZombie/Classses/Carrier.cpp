#include "Carrier.h"
#include "Plant.h"
#include "Defender.h"

Carrier::Carrier()
	:m_pInnerPlant(nullptr),m_bDestroyed(false)
	,m_nRow(0),m_terrainType(TerrainType::None)
	,m_pDefender(nullptr)
{
}

Carrier::~Carrier()
{
	SDL_SAFE_RELEASE_NULL(m_pInnerPlant);
	SDL_SAFE_RELEASE_NULL(m_pDefender);
}

void Carrier::setInnerPlant(Plant*plant)
{
	SDL_SAFE_RETAIN(plant);

	if (m_pInnerPlant != nullptr)
	{
		SDL_SAFE_RELEASE_NULL(m_pInnerPlant);
	}
	m_pInnerPlant = plant;
}

void Carrier::clearInnerPlant()
{
	SDL_SAFE_RELEASE_NULL(m_pInnerPlant);
}

Plant*Carrier::getInnerPlant()const
{
	return m_pInnerPlant;
}

void Carrier::setDefender(Defender*defender)
{
	SDL_SAFE_RETAIN(defender);

	SDL_SAFE_RELEASE_NULL(m_pDefender);
	m_pDefender = defender;
}

Defender* Carrier::getDefender()const
{
	return m_pDefender;
}

void Carrier::clearDefender()
{
	SDL_SAFE_RELEASE_NULL(m_pDefender);
}