#ifndef __VesselPlant_H__
#define __VesselPlant_H__
#include "Plant.h"

class Carrier;

class VesselPlant : public Plant
{
private:
	Carrier*m_pCarrier;//�ڲ�������
public:
	VesselPlant();
	~VesselPlant();

	bool init(TerrainType terrainType);

	void setRow(int row);
	Carrier*getInnerCarrier();
};
#endif