#include "Brick.h"
Brick::Brick()
	:m_pBody(nullptr)
{
}
Brick::~Brick()
{
	m_pBody = nullptr;
}
Brick*Brick::create(b2Body*body)
{
	auto brick = new Brick();
	if(brick && brick->initWithArray(body))
		brick->autoRelease();
	else
		SDL_SAFE_DELETE(brick);
	return brick;
}
bool Brick::initWithArray(b2Body*body)
{
	m_pBody = body;
	return true;
}
void Brick::setFriction(float friction)
{
}
void Brick::setRestitution(float restitution)
{
}
void Brick::setVelocity(float velocityX,float velocityY)
{
}
void Brick::setBrickScale(float x,float y)
{
}
void Brick::setBodyType(unsigned int type)
{
}
void Brick::setFixedRotation(bool fixed)
{
}