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
	//����ID
	this->m_id = std::string("Bullet");
	//�����ٶ�
	this->m_speed = 5;
	m_sprite = NULL;
	//�������þ���
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
//��������
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