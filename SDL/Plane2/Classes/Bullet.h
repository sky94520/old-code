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
        /*TheTextureManager::Instance()->draw(m_textureID,
        									m_position.getX(),
        									m_position.getY(),
        									m_width,
        									m_height);*/
        ShooterObject::draw();
    }
    virtual void collision()
    {
        m_bDead = true;
    }
    virtual void update()
    {
        m_velocity.setX(m_heading.getX());
        m_velocity.setY(m_heading.getY());

        m_velocity += m_acceleration;
        m_position += m_velocity;
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
