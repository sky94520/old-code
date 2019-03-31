#include "Carrier.h"
Carrier::Carrier()
	:m_pPlant(nullptr)
{
}
Carrier::~Carrier()
{
}
void Carrier::setPlant(Plant*plant)
{
	m_pPlant = plant;
}
Plant* Carrier::getPlant()const
{
	return m_pPlant;
}