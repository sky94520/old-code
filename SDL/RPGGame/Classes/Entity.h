#ifndef __Entity_H__
#define __Entity_H__
#define Sprite char
#include "Point.h"
/**����:
   ����       �����˺� m_damage �����˺����������ӷ���
   ����       ����HP m_hitPoints ����hp������
   ����       �����ٶ� m_speed �����ٶȣ���������

*/
class Entity : public Point
{
protected:
  Sprite*m_sprite;
  ///����
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
