﻿#include "Enemy.h"

Enemy::Enemy()
:SDLGameObject()
{
}
Enemy::~Enemy()
{

}
void Enemy::load(const LoaderParams*pParams)
{
    SDLGameObject::load(pParams);
    m_velocity.setY(2);
}
void Enemy::draw()
{
    SDLGameObject::draw();
}
void Enemy::update()
{
    if(m_position.getY() < 0)
    {
        m_velocity.setY(2);
    }
    else if(m_position.getY() > 400)
    {
        m_velocity.setY(-2);
    }
    SDLGameObject::update();
     m_currentFrame = int(((SDL_GetTicks()/100) % m_numFrames));//m_numFrames
}
void Enemy::clean()
{

}
