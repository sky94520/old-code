#include "BulletFactory.h"
#include "Bullet.h"
#include "FlyBehavior.h"

BulletFactory::BulletFactory()
{
}
BulletFactory::~BulletFactory()
{
}
bool BulletFactory::init()
{
	return true;
}
Bullet*BulletFactory::orderBullet(BulletType type)
{
	auto bullet = this->createBullet(type);
	//给bullet赋值
	bullet->setCurHp(1);
	bullet->setMaxHp(1);
	bullet->setAtk(1);
	bullet->setCurSpeed(4);
	//设置飞行
	bullet->setFlyBehavior(new SteadyFly());

	return bullet;
}
Bullet*BulletFactory::createBullet(BulletType type)
{
	Bullet*bullet = nullptr;
	switch(type)
	{
		case kBulletType_Common:bullet = Bullet::create();break;
	}
	return bullet;
}