#include "Player.h"

Player::Player() : Entity()
{
    this->m_damage = 0;
    this->m_hitPoints = 0;
    this->m_speed = 0;
}
Player::~Player()
{
    delete m_sprite;
}
void Player::show()
{
    gotoXY(0,0);
    cout<<"               人物属性"<<endl;
    cout<<"体质 "<<m_hitPoints<<endl;
    cout<<"力量 "<<m_damage<<endl;
    cout<<"速度 "<<m_speed<<endl;
}
