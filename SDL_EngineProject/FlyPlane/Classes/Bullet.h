#ifndef __Bullet_H__
#define __Bullet_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"

using namespace SDL;
class Plane;

class Bullet:public Entity
{
private:
	Plane*m_pOwner;//对主人的引用
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	bool init();
	virtual void update(float dt);
	virtual void onDead();

	void setOwner(Plane*entity);
};
#endif