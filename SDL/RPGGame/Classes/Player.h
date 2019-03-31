#pragma once
#include "Entity.h"


class Player : public Entity
{
 private:
  int m_damage;
  int m_hitPoints;
  int m_speed;
 public:
    Player();
    ~Player();
    ///重载<<
    friend ostream & operator<<(ostream &out,const Player &iPlayer);
    void show();
};
ostream& operator<<(ostream &out,const Player &iPlayer)
{
    gotoXY(0,0);
    out<<"               人物属性 ";
    out<<" HP "<<iPlayer.m_hitPoints;
    out<<" Damage "<<iPlayer.m_damage;
    out<<" Speed "<<iPlayer.m_speed;
    return out;
}
