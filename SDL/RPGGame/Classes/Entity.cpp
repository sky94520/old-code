#include "Entity.h"
//���ø����Ĭ�Ϲ�����
Entity::Entity() : Point()
{
    this->m_sprite = new Sprite;
 /**   this->m_damage = 0;
    this->m_hitPoints = 0;
    this->m_speed = 0;*/
}
Entity::~Entity()
{
    delete this->m_sprite;
}
void Entity::bindSprite(Sprite iSprite)
{
    *this->m_sprite = iSprite;
}
Sprite Entity::getSprite()
{
    return *this->m_sprite;
}
