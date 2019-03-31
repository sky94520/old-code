#include "Player.h"
#include "StaticData.h"

Player::Player()
	:m_nMoney(0),m_nStrength(0)
	,m_direction(Direction::Down)
	,m_bDelegated(false)
{
}

Player::~Player()
{
}

Player* Player::create(const string& name,Direction dir)
{
	auto player = new Player();

	if (player && player->init(name,dir))
		player->autorelease();
	else
		SDL_SAFE_DELETE(player);

	return player;
}

bool Player::init(const string& name,Direction dir)
{
	m_playerName = name;
	m_direction = dir;
	//获取对应动画
	auto animation = StaticData::getInstance()->getAnimationOfDirection(m_playerName,m_direction);
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	this->bindSpriteWithSpriteFrame(firstFrame);
	this->getSprite()->setAnchorPoint(Point(0.5f,0.7f));

	return true;
}