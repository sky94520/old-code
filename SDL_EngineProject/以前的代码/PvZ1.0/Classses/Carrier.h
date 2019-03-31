#ifndef __Carrier_H__
#define __Carrier_H__
#include "Entity.h"
class Plant;
/*ֲ������壬����ݵأ�ˮ�أ�����*/
class Carrier : public Entity
{
protected:
	Plant*m_pPlant;
public:
	Carrier();
	virtual ~Carrier();

	void setPlant(Plant*);
	Plant*getPlant()const;

	virtual std::string getCarrierType()const=0;
};
#endif