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
	//��ʱʹbody��������ײ�����޵�
	b2Body*body = static_cast<b2Body*>(this->getUserData());
	body->SetActive(false);
	this->setVisible(true);
	//��˸����
	auto blink = Blink::create(1.5f,5);
	//�ָ���ײ
	auto delayTime = DelayTime::create(blink->getDuration());
	auto end = CallFunc::create([body](){
		body->SetActive(true);
	});
	//��ֹͣ����
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//���ж���
	this->getSprite()->runAction(blink);
	this->runAction(Sequence::create(delayTime,end,nullptr));
}
void Player::onDead()
{
	//��������
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