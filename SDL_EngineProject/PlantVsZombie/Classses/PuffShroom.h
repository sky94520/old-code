#ifndef __PuffShroom_H__
#define __PuffShroom_H__
#include "FireShroom.h"

class PuffShroom : public FireShroom
{
public:
	PuffShroom();
	~PuffShroom();

	static PuffShroom*create(const string& plantName);
	bool init(const string& plantName);
protected:
	virtual void updateAtkState(float dt);
	virtual void changeState(State state);
};
#endif