#include "Enemy.h"

void Enemy::load(std::unique_ptr<LoaderParams> const &pParams)
{
    ShooterObject::load(pParams);
    m_velocity.setX(0);
}
void Enemy::draw()
{
    ShooterObject::draw();
}
void Enemy::update()
{
    ShooterObject::update();
    m_currentFrame = int(((SDL_GetTicks()/100) % m_numFrames));//m_numFrames
    if(m_position.getY() < 100)
    m_velocity.setY(2);
    else if(m_position.getY() > 400)
    m_velocity.setY(-2);
}
void Enemy::clean()
{

}
