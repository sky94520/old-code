#include "BulletLayer.h"
#include "Bullet.h"
#include "BehaviorManager.h"
#include "MoveBehavior.h"

BulletLayer::BulletLayer()
	:m_pDelegate(nullptr)
{
}
BulletLayer::~BulletLayer()
{
}
bool BulletLayer::init()
{

	return true;
}
void BulletLayer::update(float dt)
{
	//��enemy���ӵ�����״̬����
	for(auto iter = m_enemyBullets.begin();iter != m_enemyBullets.end();)
	{
		auto bullet = *iter;
		if(this->isObsolete(bullet))
		{
			iter = m_enemyBullets.erase(iter);
			this->pushItemToPool(bullet);
		}
		else
		{
			bullet->performMove(dt);
			iter++;
		}
	}
	//��mario���ӵ����и���
	for(auto iter = m_playerBullets.begin();iter != m_playerBullets.end();)
	{
		auto bullet = *iter;
		if(this->isObsolete(bullet))
		{
			iter = m_playerBullets.erase(iter);
			this->pushItemToPool(bullet);
		}
		else
		{
			bullet->performMove(dt);
			iter++;
		}
	}
}
void BulletLayer::addPlayerBullet(BulletType bulletType,const Point&startPos,const Point&heading,const string&id)
{
	Bullet*playerBullet = nullptr;
	switch(bulletType)
	{
	case BulletType::Mario:
		{
			MarioBullet*bullet = this->popAvaiableItemFromPool<MarioBullet*>(BulletType::Mario);

			bullet->setVisible(true);
			bullet->setPosition(startPos);
			//ȷ���ӵ�����
			bullet->setVelocity(Point(heading.x*7.f,heading.y*6.f));
			bullet->runNormalAnimation();
			bullet->setCustomName(id);

			playerBullet = bullet;
		}
		break;
	}
	//��ӵ�ѭ��������
	m_playerBullets.push_back(playerBullet);
}
void BulletLayer::addEnemyBullet(BulletType bulletType,const Point&heading)
{
}
void BulletLayer::setDelegate(BulletLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
bool BulletLayer::isObsolete(Bullet*bullet)
{
	//���ӵ������������ʱΪ����״̬
	if(bullet->isDead())
		return true;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Rect r = bullet->getBoundingBox();
	//todo
	if(r.origin.y > visibleSize.height)
		return true;
	return false;
}
template<typename T>
T BulletLayer::popAvaiableItemFromPool(BulletType type)
{
	T bullet = nullptr;
	//���һ�������Ƿ��ж�����ӵ�
	auto iter = m_bulletPool.find(type);
	//���û�и�vector������յ�vector
	if(iter == m_bulletPool.end())
	{
		m_bulletPool.insert(make_pair(type,list<Bullet*>()));
	}
	else
	{
		list<Bullet*>&bullets = iter->second;
		//������ȡ��
		if(bullets.empty() == false)
		{
			bullet = dynamic_cast<T>(bullets.front());
			bullets.pop_front();
		}
	}
	//�����µ�bullet
	if(bullet == nullptr)
	{
		bullet = this->createBullet<T>(type);
		//��ӵ���Ӧ�Ĳ�
		auto layer = m_pDelegate->getEntityLayer();
		layer->addChild(bullet);
	}
	return bullet;
}
void BulletLayer::pushItemToPool(Bullet*bullet)
{
	//����bullet���Ҷ�Ӧ������
	auto bulletType = bullet->getBulletType();
	auto iter = m_bulletPool.find(bulletType);
	list<Bullet*> bullets;

	if(iter == m_bulletPool.end())
	{
		bullets = list<Bullet*>();
		m_bulletPool.insert(make_pair(bulletType,bullets));
	}
	else
		bullets = iter->second;
	bullets.push_back(bullet);
	//�����ӵ�������
	bullet->setVisible(false);
	bullet->reset();
}
template<typename T>
T BulletLayer::createBullet(BulletType type)
{
	T b = nullptr;
	if(type == BulletType::Mario)
	{
		auto bullet = MarioBullet::create();
		bullet->setDamage(1);
		bullet->setDead(false);
		bullet->setMaxHp(1);
		bullet->setCurHp(1);
		bullet->setMaxHeight(30);//todo
		//������Ϊ
		auto moveBehavior = BehaviorManager::getInstance()->getMoveBehaviorByType(kMoveWithoutGravityType);
		bullet->setMoveBehavior(moveBehavior);

		b = bullet;
	}
	return b;
}