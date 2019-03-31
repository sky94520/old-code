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
	//�󶨾���
	bindSprite(Sprite::createWithSpriteFrameName("plane1.png"));
	reset();
	return true;
}
void Player::reset()
{
	//����Ѫ��
	setHitPoints(1);
	setCurHP(getHitPoints());
	setDamage(1);

	setVisible(true);
	//��ʼ�µĶ���
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//��ʼĬ�϶���
	auto anim = Entity::createAnimate("plane%d.png",1,2,0.15f,-1);
	this->getSprite()->runAction(anim);
}
void Player::onTouchMoved(Touch*touch,Event*event)
{
	auto director = Director::getInstance();
	auto pos1 = director->convertToGL(touch->getPreviousLocationInView());
	auto pos2 = director->convertToGL(touch->getLocationInView());

	auto end = getPosition() + pos2 - pos1;
	//ȷ���ɻ�����ʵ��Χ��
	Rect r1 = Rect(0,0,director->getVisibleSize().width,director->getVisibleSize().height);
	if(r1.containsPoint(end))
		this->setPosition(end);
}
void Player::onHurt()
{
}
void Player::onDead()
{
	//ֹͣ����
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//��ʼ��������
	auto deadAnim = Entity::createAnimate("plane-dead%d.png",1,4,0.05f,1);
	DelayTime*delay = DelayTime::create(deadAnim->getDuration());
	CallFunc*callfunc = CallFunc::create([this](){
		this->setVisible(false);
		NotificationCenter::getInstance()->postNotification("player sub");
	});
	this->getSprite()->runAction(deadAnim);
	this->runAction(Sequence::createWithTwoActions(delay,callfunc));
}