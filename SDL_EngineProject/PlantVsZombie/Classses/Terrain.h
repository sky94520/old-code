#ifndef __Terrain_H__
#define __Terrain_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"
#include "Carrier.h"

using namespace SDL;

class Terrain:public Entity,public Carrier
{
public:
	Terrain();
	~Terrain();
	CREATE_FUNC(Terrain);
	bool init();
};
//-----------------------------Lawn--------------------------
class Lawn : public Terrain
{
public:
	CREATE_FUNC(Lawn);
	bool init();
	//±»»ÙÃð¹½ÆÆ»µ
	void destroyByDoomShroom();
};
#endif