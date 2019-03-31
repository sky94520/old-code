#include "Bullet.h"
Bullet::Bullet()
	:m_damage(0),m_speed(0.f),m_pDeadAction(nullptr),m_type(kBulletType_None)
{
}
Bullet::~Bullet()
{
	SDL_SAFE_RELEASE_NULL(m_pDeadAction);
}
Bullet*Bullet::create(Sprite*sprite)
{
	auto bullet = new Bullet();
	if(bullet && bullet->init(sprite))
		bullet->autoRelease();
	else
		SDL_SAFE_DELETE(bullet);
	return bullet;
}
bool Bullet::init()
{
	return true;
}
bool Bullet::init(Sprite*sprite)
{
	//清除掉原来的sprite
	if(m_pSprite)
		m_pSprite->removeFromParent();

	if(sprite == nullptr || sprite->getParent() != nullptr)
		return false;
	this->bindSprite(sprite);
	return true;
}
void Bullet::reset()
{
	m_damage = 0.f;
	m_speed = 0.f;
	m_bDead = false;
	SDL_SAFE_RELEASE_NULL(m_pDeadAction);
	m_type = kBulletType_None;
	if(m_pSprite)
	{
		m_pSprite->removeFromParent();
		m_pSprite = nullptr;
	}
}
void Bullet::onDead()
{
	//没有死亡动画，直接死亡
	if(m_pDeadAction == nullptr)
	{
		m_bDead = true;
		return;
	}
	DelayTime*delayTime = DelayTime::create(m_pDeadAction->getDuration());
	CallFunc*end = CallFunc::create([this](){
		this->m_bDead = true;
	});
	auto sequence = Sequence::createWithTwoActions(delayTime,end);
	
	this->runAction(sequence);
	this->getSprite()->runAction(m_pDeadAction);
}