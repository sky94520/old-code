#include "Player.h"
Player::Player()
	:m_pPlayerArrow(nullptr)
{
}
Player::~Player()
{
}
bool Player::init()
{
	bindSprite(Sprite::createWithSpriteFrameName("playerbody.png"));
	this->setAnchorPoint(ccp(0.7,0.3f));
	//创建弓箭部分
	m_pPlayerArrow = Sprite::createWithSpriteFrameName("playerarrow.png");
	m_pPlayerArrow->setAnchorPoint(ccp(0.3f,0.6f));
	m_pPlayerArrow->setPosition(ccp(0.f,0.f));
	this->addChild(m_pPlayerArrow);
	return true;
}
void Player::aimAt(const Point&pos)
{
	//获取相对坐标
	auto target = this->convertToNodeSpace(pos);
	auto result = pos - this->getPosition();
	auto radians = result.getAngle();
	auto degree = CC_RADIANS_TO_DEGREES(-1 * radians);
	//判断在合适位置
	if(degree >= -180 && degree <= -90)
		degree = -90;
	else if(degree >= 90 && degree <= 180)
		degree = 90;
	//设置旋转
	m_pPlayerArrow->setRotation(degree);
}
void Player::shootTo(const Point&pos)
{
	auto anim = Entity::createAnimate("player%d.png",1,9,0.05f,1);
	m_pSprite->runAction(anim);
}