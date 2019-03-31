#ifndef __Lawn_H__
#define __Lawn_H__
#include "Carrier.h"
class Lawn:public Carrier
{
public:
	Lawn();
	~Lawn();
	CREATE_FUNC(Lawn);
	bool init();

	virtual std::string getCarrierType()const;
};
#endif