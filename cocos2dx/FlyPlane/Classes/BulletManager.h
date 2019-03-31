#ifndef __BulletManager_H__
#define __BulletManager_H__

#include "Bullet.h"
#include "cocos2d.h"

#define MAX_BULLET 10

USING_NS_CC;

class BulletManager : public Node
{
public:
	CREATE_FUNC(BulletManager);
	virtual bool init();

	BulletManager();
	~BulletManager();

	void moveUpdate(float dt);

	void addBullet(Point point);
	//检测与敌机的碰撞的外接口
	bool detecteCollided(Entity*plane);
private:
	void createBullets();
private:
	Vector<Bullet*> m_bulletArr;
};
#endif