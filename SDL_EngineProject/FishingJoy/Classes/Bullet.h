#ifndef __Bullet_H__
#define __Bullet_H__

#include "B2Entity.h"

enum class BulletType
{
	NetGunBullet,//��ǹ��
	StrengthenBullet,//��ǿ��
	FogBullet,//����
};
class Fish;

class Bullet:public B2Entity
{
	SDL_BOOL_SYNTHESIZE(m_bMakeFishingEntity,MakeFishingEntity);//����ʱ�Ƿ���������
	SDL_SYNTHESIZE(BulletType,m_bulletType,BulletType);//�ӵ�����
private:
	float m_speed;
	float m_distance;
	Fish*m_pCollidedFish;
public:
	Bullet();
	CREATE_FUNC(Bullet);
	bool init();
public:
	//��ȡ�ӵ��ٶ�
	virtual float getSpeed()const;
	void setSpeed(float speed);
	//��ȡ������
	virtual float getDistance()const;
	void setDistance(float distance);
	Fish*getCollidedFish()const;

	virtual void collided(Fish*fish);
};
#endif