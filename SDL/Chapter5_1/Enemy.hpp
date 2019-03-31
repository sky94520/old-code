#include "SDLGameObject.h"

#pragma once
class Enemy:public SDLGameObject
{
  public:
     Enemy(const LoaderParams*pParams);
    ~Enemy();
	void draw();
	void update();
	void clean();
};
void Enemy::draw()
{
	SDLGameObject::draw();
}
void Enemy::update()
{
	m_currentFrame = int (((SDL_GetTicks() / 100) % 6));
	m_velocity.setX(2);
	SDLGameObject::update();
}
void Enemy::clean()
{
}
Enemy::Enemy(const LoaderParams*pParams):SDLGameObject(pParams)
{
}
Enemy::~Enemy()
{
}