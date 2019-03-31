#ifndef __B2EntityFactory_H__
#define __B2EntityFactory_H__

#include<list>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;

class b2Entity;
class Fish;
class NetGunBullet;
class FishingNet;
class Laser;
class SkillManager;
class StarFish;
class Bullet;
class Pearl;
class Fog;

class B2EntityFactory
{
private:
	static B2EntityFactory*s_pInstance;
	list<Fish*> m_fishesPool;//�㻺���
	SkillManager*m_pSkillManager;
private:
	B2EntityFactory();
	~B2EntityFactory();
public:
	static B2EntityFactory*getInstance();
	void purge();
	bool init();
	//����id���ɶ�Ӧ����
	Fish*createFishForID(int id);
	//���ɺ���
	StarFish*createStarFish(float startTime);
	//���ݵȼ����ɶ�Ӧ����ǹ��
	NetGunBullet*createNetGunBulletForLv(int level);
	//��������
	Bullet*createFogBullet();
	//��������
	FishingNet*createFishingNet(int level);
	//����ǿ����
	Bullet*createStrengthenBullet();
	//���ɼ���
	Laser*createLaser();
	//��������
	Pearl*createPearl();
	//��������
	Fog*createFog(Fish*fish);
	//���������뻺���
	void pushFishToPool(Fish*fish);
};
#endif