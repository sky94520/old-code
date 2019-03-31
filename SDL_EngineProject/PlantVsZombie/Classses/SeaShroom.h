#ifndef __SeaShroom_H__
#define __SeaShroom_H__
#include "FireShroom.h"

class SeaShroom : public FireShroom
{
public:
	static SeaShroom*create(const string& plantName);
	bool init(const string& plantName);
protected:
	virtual void updateAtkState(float dt);
	virtual void changeState(State state);
};
#endif