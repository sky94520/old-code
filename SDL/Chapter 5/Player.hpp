//#include "SDLGameObject.h"
#include "SDLGameObject.h"
#include "InputHandle.hpp"

#pragma once
class Player:public SDLGameObject
{
private:
    void handleInput();
public:
  Player(const LoaderParams*pParams);
  ~Player();
	virtual void draw();
	virtual void update();
	virtual void clean();
};
Player::Player(const LoaderParams*pParams):SDLGameObject(pParams)
{
    //m_velocity.setX(1);
}
Player::~Player()
{
}
void Player::draw()
{
	SDLGameObject::draw();
}
void Player::update()
{
    m_position += m_velocity;

	m_currentFrame = int (((SDL_GetTicks() / 100) % 6));
	///handle event
	handleInput();
}
void Player::clean()
{
}
void Player::handleInput()
{
    /**if(TheInputHandle::Instance()->getMouseButtonState(LEFT))
    {
        m_velocity.setX(1);
    }
    else if(TheInputHandle::Instance()->getMouseButtonState(RIGHT))
    {
        m_velocity.setX(-1);
    }
    Vector2D*vec = TheInputHandle::Instance()->getMousePosition();
    m_velocity = (*vec - m_position)/100;*/

    if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        m_velocity.setX(2);
    }
    else if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        m_velocity.setX(-2);
    }
    else
    {
        m_velocity.setX(0);
    }
}
