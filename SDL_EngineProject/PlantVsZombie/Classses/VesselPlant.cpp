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
	//��ʼ������
	m_pCarrier = new Carrier();
	//����Ϊ����ֲ������
	this->setPlantType(PlantType::Vessel);
	//�����ڲ�����
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