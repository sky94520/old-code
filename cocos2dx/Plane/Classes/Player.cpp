#include "Player.h"
#include "GameLayer.h"
Player::Player()
{
}
Player::~Player()
{
}
bool Player::init()
{
	//绑定精灵
	bindSprite(Sprite::createWithSpriteFrameName("plane1.png"));
	reset();
	return true;
}
void Player::reset()
{
	//设置血量
	setHitPoints(1);
	setCurHP(getHitPoints());
	setDamage(1);

	setVisible(true);
	//开始新的动画
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//开始默认动画
	auto anim = Entity::createAnimate("plane%d.png",1,2,0.15f,-1);
	this->getSprite()->runAction(anim);
}
void Player::onTouchMoved(Touch*touch,Event*event)
{
	auto director = Director::getInstance();
	auto pos1 = director->convertToGL(touch->getPreviousLocationInView());
	auto pos2 = director->convertToGL(touch->getLocationInView());

	auto end = getPosition() + pos2 - pos1;
	//确保飞机在现实范围内
	Rect r1 = Rect(0,0,director->getVisibleSize().width,director->getVisibleSize().height);
	if(r1.containsPoint(end))
		this->setPosition(end);
}
void Player::onHurt()
{
}
void Player::onDead()
{
	//停止动画
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//开始死亡动画
	auto deadAnim = Entity::createAnimate("plane-dead%d.png",1,4,0.05f,1);
	DelayTime*delay = DelayTime::create(deadAnim->getDuration());
	CallFunc*callfunc = CallFunc::create([this](){
		this->setVisible(false);
		NotificationCenter::getInstance()->postNotification("player sub");
	});
	this->getSprite()->runAction(deadAnim);
	this->runAction(Sequence::createWithTwoActions(delay,callfunc));
}