#include "Player.h"
#include "Game.h"
#include "TextureManager.h"
#include "BulletHandle.h"
#include "SoundManager.h"

Player::Player():ShooterObject()
    ,m_invulnerable(false),
    m_invulnerableTime(200),
    m_invulnerableCounter(0)
{
}
Player::~Player()
{
}
void Player::load(std::unique_ptr<LoaderParams>const &pParams)
{
    ShooterObject::load(pParams);
    // can set up the players inherited values here
    // set up bullets
    m_bulletFiringSpeed = 30;
    m_moveSpeed = 3;
    // we want to be able to fire instantly
    m_bulletCounter = m_bulletFiringSpeed;
    // time it takes for death explosion
    m_dyingTime = 100;
}
void Player::draw()
{
    TheTextureManager::Instance()->drawFrame(m_textureID,(int)m_position.getX(),(int)m_position.getY(),m_width,m_height,m_currentRow,m_currentFrame,m_angle,m_alpha,SDL_FLIP_HORIZONTAL);
}
void Player::update()
{
    //if the level is complete then fly off the screen
    if(TheGame::Instance()->getLevelComplete())
    {
        if(m_position.getX() >= TheGame::Instance()->getGameWidth())
            TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
        else
        {
            m_velocity.setX(3);
            m_velocity.setY(0);
            ShooterObject::update();
            handleAnimation();
        }
    }
    else
    {
        /*if the player is not doing its death
        animation then update it normally*/
        if(!m_bDying)
        {
            //reset velocity
            m_velocity.setX(0);
            m_velocity.setY(0);
            //get input
            handleInput();
            //do normal position += velocity update
            ShooterObject::update();
            //update the animation
            handleAnimation();
        }
        else//if the player is doing the death animation
        {
            m_currentFrame = int((SDL_GetTicks()/100) % m_numFrames);
            //if the death animation has completed
            if(m_dyingCounter == m_dyingTime)
            {
                //ressurect the player
                ressurect();
            }
            m_dyingCounter++;
        }
    }
}
void Player::clean()
{
}
void Player::handleInput()
{
    if(!m_bDead)
    {
        if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_UP))
        {
            m_velocity.setY(-2);
        }
        else if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
        {
            m_velocity.setY(2);
        }
        else if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
        {
            m_velocity.setX(2);
        }
        else if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
        {
            m_velocity.setX(-2);
        }
        else
        {
            m_velocity.setX(0);
            m_velocity.setY(0);
        }
        if(TheInputHandle::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
            if(m_bulletCounter == m_bulletFiringSpeed)
            {
            	TheSoundManager::Instance()->playSound("boom",0);
                TheBulletHandle::Instance()->addPlayerBullet(m_position.getX() + m_width,m_position.getY() + m_height/2,11,11,"bullet1",0,Vector2D(10,0));
                m_bulletCounter = 0;
            }
            m_bulletCounter++;
        }
        else
        {
            m_bulletCounter = m_bulletFiringSpeed;
        }
    }//end m_bDead

}
void Player::ressurect()
{
    TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);

    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;

    m_textureID = "player";

    m_currentFrame = 0;
    m_numFrames = 5;
    m_width = 101;
    m_height = 46;

    m_dyingCounter = 0;
    m_invulnerable = true;
}
/*处理动画，即着重处理m_alpha m_angle*/
void Player::handleAnimation()
{
    //如果不受伤害的，应该让玩家知道， 闪烁
    if(m_invulnerable)
    {
        //invulnerability is finshed,set values back
        //处理闪烁次数
        if(m_invulnerableCounter == m_invulnerableTime)
        {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        }
        else//otherwise.flash the alpha on and off
        {
            if(m_alpha == 255)
            {
                m_alpha = 0;
            }
            else
            {
                m_alpha = 255;
            }
        }
        //increment our counter
        m_invulnerableCounter++;
    }
    /*如果没死，就改变角度，来增加移动效果*/
    if(!m_bDead)
    {
        if(m_velocity.getX() < 0)
        {
            m_angle = -10.0;
        }
        else if(m_velocity.getX() > 0)
        {
            m_angle = 10.0;
        }
        else
        {
            m_angle = 0.0;
        }
    }
    /**/
    m_currentFrame = int(((SDL_GetTicks()/(100))%m_numFrames));
}
void Player::collision()
{
}
