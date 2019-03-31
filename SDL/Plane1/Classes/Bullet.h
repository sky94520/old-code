#ifndef __Bullet_H__
#define __Bullet_H__

#include<string>
#include<iostream>

#include "Vector2D.h"
#include "ShooterObject.h"

class PlayerBullet : public ShooterObject
{
private:
    Vector2D m_heading;
public:
    PlayerBullet():ShooterObject()
    {
        //std::cout<<"PlayerBullet is builded!\n";
        m_dyingTime = 5;
    }
    virtual ~PlayerBullet()
    {
        //std::cout<<"PlayerBullet is Released!\n";
    }
    virtual std::string type()
    {
        return std::string("PlayerBullet");
    }
    virtual void load(std::unique_ptr<LoaderParams> const &pParams,Vector2D &heading)
    {
        ShooterObject::load(std::move(pParams));
        m_heading = heading;
    }
    virtual void draw()
    {
        ShooterObject::draw();
    }
    virtual void collision()
    {
        m_textureID = "smallexplosion";
        m_numFrames = 2;
        m_currentFrame = 0;
        m_width = 20;
        m_height = 20;
        m_bDying = true;
    }
    virtual void update()
    {
        if(!m_bDying)
        {
            m_velocity.setX(m_heading.getX());
            m_velocity.setY(m_heading.getY());

            m_velocity += m_acceleration;
            m_position += m_velocity;
        }
        else///the bullet is dying
        {
            ///播放完毕，消失
            if(m_dyingCounter == m_dyingTime)
            {
                m_bDead = true;
            }
            else
                m_dyingCounter++;
        }
        if(m_bDying)
            m_currentFrame = int(SDL_GetTicks()/100)%m_numFrames;
    }
    virtual void clean()
    {
        ShooterObject::clean();
    }
};
class EnemyBullet : public PlayerBullet
{
public:
    EnemyBullet():PlayerBullet()
    {
    }
    virtual ~EnemyBullet() {}
    virtual std::string type()
    {
        return std::string("EnemyBullet");
    }
};
#endif
