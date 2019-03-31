#ifndef __GameObject_H__
#define __GameObject_H__

#include<string>
#include<memory>

#include "Vector2D.h"
#include "LoaderParams.h"

class GameObject
{
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    //size
    int m_width;
    int m_height;
    //animation varables
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;
    //commen boolean variables
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;
    //rotation
    double m_angle;
    //blenging
    int m_alpha;
protected:
    GameObject():m_position(0,0),
        m_velocity(0,0),
        m_acceleration(0,0),
        m_width(0),
        m_height(0),
        m_currentRow(1),
        m_currentFrame(0),
        m_bUpdating(false),
        m_bDead(false),
        m_bDying(false),
        m_angle(0),
        m_alpha(255)
    {}
public:
    virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;

    virtual ~GameObject() {}
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    //object has collided,handle accordingly
    virtual void collision() = 0;
    //get the type of the object
    virtual std::string type() = 0;
    //getters for commen variables
    Vector2D &getPosition()
    {
        return m_position;
    }
    int getWidth()
    {
        return m_width;
    }
    int getHeight()
    {
        return m_height;
    }
    //scroll along with tile map
    void scroll(float scrollSpeed)
    {
        m_position.setX(m_position.getX() - scrollSpeed);
    }
    //is the object currently being updated?
    bool updateing()
    {
        return m_bUpdating;
    }
    //is the object dead
    bool dead()
    {
        return m_bDead;
    }
    bool dying()
    {
        return m_bDying;
    }
    void setUpdating(bool updating)
    {
        m_bUpdating = updating;
    }

};
#endif
