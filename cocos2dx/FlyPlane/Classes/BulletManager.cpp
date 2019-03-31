#include "BulletManager.h"
#include "PlaneAction.h"

BulletManager::BulletManager()
{
	
}
BulletManager::~BulletManager()
{
}
bool BulletManager::init()
{
	createBullets();
	//增加位移
	this->schedule(schedule_selector(BulletManager::moveUpdate),0.01f);
	return true;
}

void BulletManager::createBullets()
{
	//对子弹的初始化
	//初始条件，绑定player
	for(int i = 0; i < MAX_BULLET;i++)
	{
		Bullet*bullet = Bullet::create();
		bullet->bindSprite(Sprite::createWithSpriteFrameName("bullet-dead1.png"));
		bullet->reset(Point(0,0));

		this->addChild(bullet);
		m_bulletArr.pushBack(bullet);
	}
}
//只负责增加位移坐标
void BulletManager::moveUpdate(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for(auto bullet : m_bulletArr)
	{
		//增加子弹位移
		if(bullet->isAlive() == true)
		{
			bullet->setPositionY(bullet->getPositionY() + bullet->getSpeed());
			//到达顶端 //或者发生碰撞
			if(bullet->getPositionY() >= visibleSize.height)
			{
				bullet->hide();
			}
		}
	}
}
void BulletManager::addBullet(Point point)
{
	for(auto bullet : m_bulletArr)
	{
		//使一个子弹类变得活动
		if(bullet->isAlive() == false)
		{
			bullet->reset(point);
			bullet->show();

			break;
		}
	}
}
bool BulletManager::detecteCollided(Entity*plane)
{
	for(auto bullet : m_bulletArr)
	{
		//检测是否碰撞
		if(bullet->isAlive() && plane->isCollided(bullet) == true)
		{
			bullet->hide();
			

			return true;
		}
	}
	return false;
}