#ifndef __Entity_H__
#define __Entity_H__
#define Sprite char
#include "Point.h"
/**属性:
   力量       基础伤害 m_damage 增加伤害，少许增加防御
   体质       基础HP m_hitPoints 增加hp，防御
   敏捷       基础速度 m_speed 攻击速度，增加闪避

*/
class Entity : public Point
{
protected:
  Sprite*m_sprite;
  ///属性
/*  int m_damage;
  int m_hitPoints;
  int m_speed;*/

public:
  Entity();
  ~Entity();
  void bindSprite(Sprite iSprite);
  Sprite getSprite();
};
#endif
