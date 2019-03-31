#include "Enemy.h"
#include "BulletHandle.h"
#include "SoundManager.h"

void Enemy::load(std::unique_ptr<LoaderParams> const &pParams)
{
    ShooterObject::load(std::move(pParams));
    m_velocity.setX(0);
}
void Enemy::draw()
{
    ShooterObject::draw();
}
void Enemy::update()
{
    if(!m_bDying)
    {
        if(m_position.getY() < 100)
            m_velocity.setY(2);
        else if(m_position.getY() > 400)
            m_velocity.setY(-2);
		///
        if(m_bulletCounter == m_bulletFiringSpeed)
        {
            TheBulletHandle::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(-3, 0));
            TheBulletHandle::Instance()->addEnemyBullet(m_position.getX(), m_position.getY(), 16, 16, "bullet1", 1, Vector2D(3, 0));
            m_bulletCounter = 0;
        }
        m_bulletCounter++;
    }
    else
    {
    	m_velocity.setX(0);
        m_velocity.setY(0);
        doDyingAnimation();
    }
    m_velocity += m_acceleration;
    m_position += m_velocity;
    m_currentFrame = int(SDL_GetTicks()/100)%m_numFrames;
}
void Enemy::collision()
{
    m_health -= 1;
    std::cout<<"enemy health:"<<m_health<<"\n";
    if(m_health <= 0)
    {
        //if(!m_bPlayedDeathSound)
        {
            TheSoundManager::Instance()->playSound("explode", 0);

            m_textureID = "largeexplosion";
            m_currentFrame = 0;
            m_numFrames = 9;
            m_width = 60;
            m_height = 60;
            m_bDying = true;
        }
    }

}
void Enemy::doDyingAnimation()
{
	if(m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	//simple counter,fine with fixed frame rate
	m_dyingCounter++;
}
void Enemy::clean()
{
    this->~Enemy();
}
