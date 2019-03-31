#ifndef __Torchwood_H__
#define __Torchwood_H__
#include "Plant.h"

class Torchwood : public Plant
{
public:
	static Torchwood*create(const string&plantName);
	bool init(const string&plantName);

	virtual void updateHook(float dt);
};
#endif