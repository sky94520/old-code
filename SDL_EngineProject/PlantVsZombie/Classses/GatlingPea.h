#ifndef __GatlingPea_H__
#define __GatlingPea_H__

#include "Repeater.h"

class GatlingPea : public Repeater
{
public:
	static GatlingPea* create(const string& plantName);
	bool init(const string& plantName);
};
#endif