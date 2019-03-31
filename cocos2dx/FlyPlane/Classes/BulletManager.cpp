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
	//����λ��
	this->schedule(schedule_selector(BulletManager::moveUpdate),0.01f);
	return true;
}

void BulletManager::createBullets()
{
	//���ӵ��ĳ�ʼ��
	//��ʼ��������player
	for(int i = 0; i < MAX_BULLET;i++)
	{
		Bullet*bullet = Bullet::create();
		bullet->bindSprite(Sprite::createWithSpriteFrameName("bullet-dead1.png"));
		bullet->reset(Point(0,0));

		this->addChild(bullet);
		m_bulletArr.pushBack(bullet);
	}
}
//ֻ��������λ������
void BulletManager::moveUpdate(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for(auto bullet : m_bulletArr)
	{
		//�����ӵ�λ��
		if(bullet->isAlive() == true)
		{
			bullet->setPositionY(bullet->getPositionY() + bullet->getSpeed());
			//���ﶥ�� //���߷�����ײ
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
		//ʹһ���ӵ����û
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
		//����Ƿ���ײ
		if(bullet->isAlive() && plane->isCollided(bullet) == true)
		{
			bullet->hide();
			

			return true;
		}
	}
	return false;
}