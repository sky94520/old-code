#include "Bullet.h"
#include "Plane.h"

Bullet::Bullet()
	:m_pOwner(nullptr)
{
}
Bullet::~Bullet()
{
	SDL_SAFE_RELEASE(m_pOwner);
	m_pOwner = nullptr;
}
bool Bullet::init()
{
	this->bindSprite(Sprite::createWithSpriteFrameName("bullet1.png"));
	return true;
}
void Bullet::update(float dt)
{
	Entity::update(dt);
}
void Bullet::onDead()
{
	//�����ٶ�Ϊ0
	//this->setCurSpeed(0);
	//�ӵ���������
	auto animate = Entity::createAnimate("bullet_d%d.png",1,1,0.1,1);

	DelayTime*delayTime = DelayTime::create(animate->getDuration());
	//�ӵ������ã�ͬʱ֪ͨӵ���߿��Զ�һ�η������
	CallFunc*end = CallFunc::create([this]()
	{
		this->setAlive(false);
		m_pOwner->setBulletNum(m_pOwner->getBulletNum() + 1);
		SDL_SAFE_RELEASE(m_pOwner);
		m_pOwner = nullptr;
	});
	//���ж���
	this->runAction(Sequence::create(delayTime,end,NULL));
	this->getSprite()->runAction(animate);
}
void Bullet::setOwner(Plane*owner)
{
	m_pOwner = owner;
	SDL_SAFE_RETAIN(owner);
}