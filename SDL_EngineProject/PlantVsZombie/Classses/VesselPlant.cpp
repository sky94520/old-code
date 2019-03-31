#include "VesselPlant.h"
#include "Carrier.h"

VesselPlant::VesselPlant()
	:m_pCarrier(nullptr)
{
}

VesselPlant::~VesselPlant()
{
	SDL_SAFE_DELETE(m_pCarrier);
}

bool VesselPlant::init(TerrainType terrainType)
{
	//初始化塔基
	m_pCarrier = new Carrier();
	//设置为容器植物类型
	this->setPlantType(PlantType::Vessel);
	//设置内部类型
	m_pCarrier->setTerrainType(terrainType);

	return true;
}

void VesselPlant::setRow(int row)
{
	m_pCarrier->setRow(row);
}

Carrier*VesselPlant::getInnerCarrier()
{
	return m_pCarrier;
}