#ifndef __FlowerPot_H__
#define __FlowerPot_H__
#include<string>
#include "VesselPlant.h"

using namespace std;

class FlowerPot : public VesselPlant
{
public:
	FlowerPot();
	~FlowerPot();
	static FlowerPot*create(const string&plantName);
	bool init(const string&plantName);
	virtual void updateHook(float dt);
};
#endif