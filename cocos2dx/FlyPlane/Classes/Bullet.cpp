#include "Bullet.h"
Bullet::Bullet()
{
	m_isAlive = false;
}
Bullet::~Bullet()
{
}
bool Bullet::init()
{
	//设置ID
	this->m_id = std::string("Bullet");
	//设置速度
	this->m_speed = 5;
	m_sprite = NULL;
	//在外面获得精灵
	return true;
}
void Bullet::show()
{
	if(m_sprite != NULL)
	{
		this->setVisible(true);
		m_isAlive = true;
	}
}
void Bullet::hide()
{
	if(m_sprite != NULL)
	{
		this->setVisible(false);
		this->m_isAlive = false;

	}
}
//重置坐标
void Bullet::reset(Point point)
{
	if(m_sprite != NULL)
	{
		setPosition(point);
	}
}
int Bullet::getSpeed()
{
	return this->m_speed;
}
bool Bullet::isAlive()
{
	return this->m_isAlive;
}