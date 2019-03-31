#include "Bullet.h"
Bullet::Bullet()
	:m_nSpeed(0)
{
}
Bullet::~Bullet()
{
}
bool Bullet::init()
{
	setHitPoints(1);
	setDamage(1);
	setSpeed(1000);

	bindSprite(Sprite::createWithSpriteFrameName("bullet.png"));
	return true;
}
void Bullet::onHurt()
{
}
void Bullet::onDead()
{
	//Í£Ö¹ËùÓÐ¶¯»­
	this->stopAllActions();
	this->getSprite()->stopAllActions();

	auto deadAnim = Entity::createAnimate("bullet-dead.png",1,1,0.1f,1);
	DelayTime*delay = DelayTime::create(deadAnim->getDuration() - 0.01f);
	CallFunc*callfunc = CallFunc::create([this](){
		this->setVisible(false);
	});
	this->getSprite()->runAction(deadAnim);
	this->runAction(Sequence::createWithTwoActions(delay,callfunc));
}