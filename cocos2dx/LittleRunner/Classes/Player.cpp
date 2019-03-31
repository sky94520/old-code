#include "Player.h"

Player::Player()
{
	m_isJumping = false;
	m_iHP = 1000;
}
Player::~Player()
{
}
bool Player::init()
{
	return true;
}
void Player::jump()
{
	//调试部分
	Point playerPoint = this->getPosition();
	Point spritePoint = m_sprite->getPosition();
	log("player x=%s,y=%s",Value(playerPoint.x).asString().c_str(),Value(playerPoint.y).asString().c_str());
	log("sprite x=%s,y=%s",Value(spritePoint.x).asString().c_str(),Value(spritePoint.y).asString().c_str());

	if (getSprite() == NULL)
		return;
	//如果主角在跳跃状态，则不重复执行
	if (m_isJumping)
		return;
	m_isJumping = true;

	auto jump = JumpBy::create(1.5f,Point(0,0),200,1);

	auto callFunc = CallFunc::create([&](){
	    m_isJumping = false;
	});

	auto jumpActions = Sequence::create(jump,callFunc,NULL);
	this->runAction(jumpActions);
}
void Player::hit()
{
	if (getSprite() == NULL)
		return ;
	//扣血效果
	FlowWord*flowWord = FlowWord::create();
	this->addChild(flowWord);
	flowWord->showWord("-15",getSprite()->getPosition());


	m_iHP -= 15;
	if(m_iHP < 0)
		m_iHP = 0;
	//act
	auto backMove = MoveBy::create(.1f,Point(-20,0));
	auto forwardMove = MoveBy::create(0.1f,Point(20,0));
	auto backRotate = RotateBy::create(0.1f,-5,0);
	auto forwardRotate = RotateBy::create(0.1f,5,0);

	auto backActions = Spawn::create(backMove,backRotate,NULL);
	auto forwardActions = Spawn::create(forwardMove,forwardRotate,NULL);
	
	auto actions = Sequence::create(backActions,forwardActions,NULL);

	stopAllActions();
	resetData();
	runAction(actions);
}
int Player::getiHP()
{
	return m_iHP;
}
void Player::resetData()
{
	if (m_isJumping)
		m_isJumping = false;
	setPosition(getSprite()->getContentSize().width,50);
	setScale(1.0f);
	setRotation(0);
}