#include "BulletLayer.h"
#include "B2EntityFactory.h"
#include "NetGunBullet.h"

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
	for(auto iter = m_bullets.begin();iter != m_bullets.end();)
	{
		auto bullet = *iter;

		if(bullet->isDead())
		{
			//������������������������
			if(bullet->isMakeFishingEntity())
			{
				auto fish = bullet->getCollidedFish();
				m_pDelegate->shootAt(bullet,fish);
			}
			//�Ƴ�
			iter = m_bullets.erase(iter);
			bullet->removeFromParent();
		}
		else
			iter++;
	}
}

void BulletLayer::addNetGunBullet(int level,const Point&bornPos,const Point&loc,float rotation)
{
	Point target = loc - bornPos;
	//������ǹ��
	auto bullet = B2EntityFactory::getInstance()->createNetGunBulletForLv(level);

	bullet->setPosition(bornPos);
	bullet->getSprite()->setRotation(rotation);

	this->addChild(bullet);
	//��ӵ�������
	m_bullets.push_back(bullet);

	//��ȡ�ӵ�������
	auto distance = bullet->getDistance();

	//��ȡ�ӵ���� �����÷���
	auto degree = SDL_ANGLE_TO_DEGREE(rotation);
	target = Point(distance * SDL_sinf(degree),distance * SDL_cosf(degree) * -1.f);
	//��ȡ�ӵ��ٶ�
	auto speed = bullet->getSpeed();
	float time = target.length()/speed;
	//���ж���
	MoveBy*move = MoveBy::create(time,target);

	CallFunc*end = CallFunc::create([bullet,this]()
	{
		bullet->collided(nullptr);//����bullet->setDead(true);
	});

	auto seq = Sequence::create(move,end,nullptr);

	bullet->runAction(seq);
}

void BulletLayer::addStrengthenBullet(const Point&bornPos,const Point&loc,float rotation)
{
	Point target = loc - bornPos;
	//������ǿ��
	auto bullet = B2EntityFactory::getInstance()->createStrengthenBullet();

	bullet->setPosition(bornPos);
	bullet->getSprite()->setRotation(rotation);

	this->addChild(bullet);
	//��ӵ�������
	m_bullets.push_back(bullet);

	//��ȡ�ӵ�������
	auto distance = bullet->getDistance();

	//��ȡ�ӵ���� �����÷���
	auto degree = SDL_ANGLE_TO_DEGREE(rotation);
	target = Point(distance * SDL_sinf(degree),distance * SDL_cosf(degree) * -1.f);
	//��ȡ�ӵ��ٶ�
	auto speed = bullet->getSpeed();
	float time = target.length()/speed;
	//���ж���
	MoveBy*move = MoveBy::create(time,target);

	CallFunc*end = CallFunc::create([bullet]()
	{
		bullet->collided(nullptr);
	});

	auto seq = Sequence::create(move,end,nullptr);

	bullet->runAction(seq);
}

void BulletLayer::addFogBullet(const Point&bornPos,const Point&loc,float rotation)
{
	Point target = loc - bornPos;
	//��������
	auto bullet = B2EntityFactory::getInstance()->createFogBullet();

	bullet->setPosition(bornPos);
	bullet->getSprite()->setRotation(rotation);

	this->addChild(bullet);
	//��ӵ�������
	m_bullets.push_back(bullet);

	//��ȡ�ӵ�������
	auto distance = bullet->getDistance();

	//��ȡ�ӵ���� �����÷���
	auto degree = SDL_ANGLE_TO_DEGREE(rotation);
	target = Point(distance * SDL_sinf(degree),distance * SDL_cosf(degree) * -1.f);
	//��ȡ�ӵ��ٶ�
	auto speed = bullet->getSpeed();
	float time = target.length()/speed;
	//���ж���
	MoveBy*move = MoveBy::create(time,target);

	CallFunc*end = CallFunc::create([bullet]()
	{
		bullet->collided(nullptr);
	});

	auto seq = Sequence::create(move,end,nullptr);

	bullet->runAction(seq);
}

void BulletLayer::setDelegate(BultLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}