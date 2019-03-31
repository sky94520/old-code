#ifndef __Brick_H__
#define __Brick_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Box2D/Box2D.h"
#include "IBrick.h"

using namespace SDL;
using namespace std;

class Brick:public IBrick,public Node
{
private:
	b2Body*m_pBody;
public:
	Brick();
	~Brick();
	static Brick*create(b2Body*body);
	bool initWithArray(b2Body*body);

	virtual void setFriction(float friction);
	virtual void setRestitution(float restitution);
	virtual void setVelocity(float velocityX,float velocityY);
	virtual void setBrickScale(float x,float y);
	virtual void setBodyType(unsigned int type);
	virtual void setFixedRotation(bool fixed);
};
#endif