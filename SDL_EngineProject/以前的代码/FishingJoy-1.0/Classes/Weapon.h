#ifndef __Weapon_H__
#define __Weapon_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "Bullet.h"
#include "Cannon.h"
#include "FishingNet.h"
#include "sundry.h"
class Fish;
using namespace SDL;
class Weapon:public Node,public BulletDelegate,public FishingNetDelegate
{
private:
	Cannon*m_pCannon;
	Bullet*m_pBullet;
	FishingNet*m_pFishingNet;//���� �����������漯�ϵĵ�һ������
	BulletType m_bulletType;//�ӵ�����
public:
	Weapon();
	~Weapon();
	CREATE_FUNC(Weapon);
	bool init();
public:
	//����Cannon�ĺ��� �����ӵ�
	bool shootTo(const Point&target);
	//�Ƿ����ڷ����ӵ�
	bool isShooting()const;
	// ����Bullet����
	void aimAt(const Point&target);
	//���������ж�

	void addCannonLevel();
	void subCannonLevel();

	void end();
	//��ȡ��̨��ǰ����
	virtual CannonType getCannonType()const;
	int getCannonLevel()const;
	Rect getBulletCollisionRect()const
	{
		return m_pBullet->getBulletCollisionRect();
	}
	Rect getFishingNetCollisionRect()const
	{
		return m_pFishingNet->getFishingNetCollisionRect();
	}
	BulletType getBulletType()const;
	void setBulletType(BulletType type);
private:
	void showAt(const Point&pos);
};
#endif