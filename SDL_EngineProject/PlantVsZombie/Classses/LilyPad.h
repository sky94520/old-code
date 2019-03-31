#ifndef __LilyPad_H__
#define __LilyPad_H__
#include<string>
#include "VesselPlant.h"

using namespace std;

class LilyPad : public VesselPlant
{
public:
	LilyPad();
	~LilyPad();
	static LilyPad*create(const string&plantName);
	bool init(const string&plantName);
	virtual void updateHook(float dt);
};
#endif