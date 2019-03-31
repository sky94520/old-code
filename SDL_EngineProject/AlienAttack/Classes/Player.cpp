#include "Player.h"
Player::Player()
	:m_invulnerableTime(0.f),m_moveSpeed(0.f)
{
}
Player::~Player()
{
}
bool Player::init()
{
	this->bindSprite(Sprite::createWithSpriteFrameName("heli0.png"));
	
	return true;
}
void Player::ressurect(float invulnerableTime)
{
	//重新初始化
	this->setCurHp(this->getMaxHp());
	this->setDead(false);
	this->setHeading(Point(0.f,0.f));
	//设置无敌时间
	m_invulnerableTime = invulnerableTime;
	//设置闪烁动画
	Blink*blink = Blink::create(invulnerableTime,invulnerableTime*10);
	CallFunc*end = CallFunc::create([this](){
		this->m_invulnerableTime = 0.f;
	});
	auto sequence = Sequence::createWithTwoActions(blink,end);
	this->getSprite()->runAction(sequence);
}
void Player::runNormalAnimation()
{
	//停止sprite的所有动画
	this->getSprite()->stopAllActions();
	//运行正常动画
	auto normalAnimate = Entity::createAnimate("heli%d.png",0,4,0.1f,-1);
	this->getSprite()->runAction(normalAnimate);

	this->getSprite()->setRotation(0.f);
}
bool Player::isInvulnerable()const
{
	return m_invulnerableTime > 0.f;
}
void Player::setPlayerRotation(float rotation)
{
	this->getSprite()->setRotation(rotation);
}
void Player::onBindSprite()
{
}
void Player::onHurt(int damage)
{
}
void Player::onDead()
{
	//运行死亡动画
	auto deadAnimate = Entity::createAnimate("largeexplosion%d.png",0,8,0.1f,1);
	auto end = CallFunc::create([this]()
	{
		this->m_bDead = true;
		this->setVisible(false);
	});
	auto sequence = Sequence::create(deadAnimate,end,nullptr);
	//停止所有动画
	this->getSprite()->setRotation(0.f);
	this->getSprite()->stopAllActions();
	this->getSprite()->runAction(sequence);
}