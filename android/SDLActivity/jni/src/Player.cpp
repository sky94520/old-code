#include "Player.h"
Player::Player()
{
}
Player::~Player()
{
}
bool Player::init()
{
	bindSprite(Sprite::createWithSpriteFrameName("smallplane_1.png"));
	return true;
}
void Player::revive()
{
	//暂时使body不参与碰撞，即无敌
	b2Body*body = static_cast<b2Body*>(this->getUserData());
	body->SetActive(false);
	this->setVisible(true);
	//闪烁动画
	auto blink = Blink::create(1.5f,5);
	//恢复碰撞
	auto delayTime = DelayTime::create(blink->getDuration());
	auto end = CallFunc::create([body](){
		body->SetActive(true);
	});
	//先停止动画
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//运行动作
	this->getSprite()->runAction(blink);
	this->runAction(Sequence::create(delayTime,end,nullptr));
}
void Player::onDead()
{
	//死亡动画
	auto deadAnimate = Entity::createAnimate("smallplane_d%d.png",1,4,0.1,1);
	auto delayTime = DelayTime::create(deadAnimate->getDuration());
	auto onAlive = CallFunc::create([this](){
		this->setAlive(false);
		this->setVisible(false);
	});
	this->getSprite()->runAction(deadAnimate);
	this->runAction(Sequence::create(delayTime,onAlive,NULL));
	SoundManager::getInstance()->playEffect("music/bigplane_bomb.wav",0);
}