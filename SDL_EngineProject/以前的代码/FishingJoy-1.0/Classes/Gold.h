#ifndef __Gold_H__
#define __Gold_H__
#include "Entity.h"
class Gold:public Entity
{
public:
	Gold();
	~Gold();
	CREATE_FUNC(Gold);
	bool init();
};
#endif