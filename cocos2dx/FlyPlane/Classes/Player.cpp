#include "Player.h"

Player::Player()
{

}
Player::~Player()
{

}
bool Player::init()
{
	this->m_id = std::string("Player");
	//调试使用，使每次生命为5
	this->m_hitPoints = 5;

	return true;
}
Point Player::getTagPosition()
{
	return this->getPosition();
}
void Player::setTagPosition(Point point)
{
	//this->setPosition(point);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size playerSize = this->getContentSize();

	Point playerPoint = this->getPosition();
	Point spritePoint = m_sprite->getPosition();

//	log("m_sprite x = %s,y = %s",Value(spritePoint.x).asString().c_str(),Value(spritePoint.y).asString().c_str());
//	log("player x = %s,y = %s",Value(playerPoint.x).asString().c_str(),Value(playerPoint.y).asString().c_str());

//	log(Value(playerSize.width).asString().c_str()); 
	if(playerPoint.x - playerSize.width/2 < 0)
	{
		this->setPosition(Point(playerSize.width/2,playerPoint.y));
		return;
	}

	this->runAction(MoveBy::create(0.001f,point));

}
void Player::setTouchController(TouchController*iTouchController)
{
	m_touchController = iTouchController;
	m_touchController->setTouchListener(this);
}