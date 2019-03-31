#ifndef __Defender_H__
#define __Defender_H__
#include "Plant.h"

class Defender : public Plant
{
public:
	Defender();
	~Defender();

	bool init();
};
#endif