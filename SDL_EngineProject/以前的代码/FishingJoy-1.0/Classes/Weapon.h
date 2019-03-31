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
	FishingNet*m_pFishingNet;//渔网 该渔网是下面集合的第一个渔网
	BulletType m_bulletType;//子弹类型
public:
	Weapon();
	~Weapon();
	CREATE_FUNC(Weapon);
	bool init();
public:
	//调用Cannon的函数 发射子弹
	bool shootTo(const Point&target);
	//是否正在发射子弹
	bool isShooting()const;
	// 调用Bullet函数
	void aimAt(const Point&target);
	//进行渔网判定

	void addCannonLevel();
	void subCannonLevel();

	void end();
	//获取炮台当前级别
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