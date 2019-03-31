#include "PlayerLayer.h"
#include "Player.h"
#include "PlayerLayer.h"
#include "DynamicData.h"

PlayerLayer::PlayerLayer()
	:m_pPlayer(nullptr),m_pDelegate(nullptr)
{
}
PlayerLayer::~PlayerLayer()
{
}
bool PlayerLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pPlayer = Player::create();
	Size playerSize = m_pPlayer->getContentSize();
	//设置位置
	m_pPlayer->setPosition(playerSize.width/2,visibleSize.height/2);
	//设置属性
	int maxHp = DynamicData::getInstance()->getPlayerMaxHp();
	float speed = DynamicData::getInstance()->getPlayerSpeed();

	m_pPlayer->setMaxHp(maxHp);
	m_pPlayer->setCurHp(maxHp);
	m_pPlayer->setMoveSpeed(speed);
	//设置主角属性一开始为死亡
	m_pPlayer->setDead(true);
	//运行正常动画
	m_pPlayer->runNormalAnimation();

	this->addChild(m_pPlayer);

	return true;
}
void PlayerLayer::update(float dt)
{
	//是否有生命 todo
	if(m_pPlayer->isDead())
	{
		bool bContinue = DynamicData::getInstance()->alterPlayerLives(-1);
		//游戏继续进行
		if(bContinue)
			this->ressurect();
		else//游戏结束
		{
			m_pDelegate->gameOver();
		}
	}
	if(m_pPlayer->isDying())
		return;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point nextPos = m_pPlayer->getHeading()*m_pPlayer->getMoveSpeed() + m_pPlayer->getPosition();
	//获取主角大小
	Size s = m_pPlayer->getContentSize();
	//获取主角左上角坐标
	Point pos = nextPos - Point(s.width/2,s.height/2);
	//相交就不能移动
	if(pos.x < 0 || pos.x + s.width > visibleSize.width || pos.y < 0.f || pos.y + s.height > visibleSize.height)
		;
	else
		m_pPlayer->setPosition(nextPos);
}
void PlayerLayer::playerMove(const Point&velocity)
{
	if(m_pPlayer->isDying())
		return;
	m_pPlayer->setHeading(Point(velocity.x*2.f,velocity.y*2.f));

	float angle = 0.f;

	if(velocity.x > 0.f)
		angle = 10.f;
	else if(velocity.x < 0.f)
		angle = -10.f;
	else
		angle = 0.f;

	m_pPlayer->setPlayerRotation(angle);
}
void PlayerLayer::resetPlayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size playerSize = m_pPlayer->getContentSize();
	//设置位置
	m_pPlayer->setPosition(playerSize.width/2,visibleSize.height/2);

}
Player*PlayerLayer::getPlayer()
{
	return m_pPlayer;
}
void PlayerLayer::ressurect()
{
	//设置无敌时间
	float invulnerableTime = DynamicData::getInstance()->getPlayerInvulnerableTime();
	//运行正常动画并设置无敌
	m_pPlayer->setVisible(true);
	m_pPlayer->runNormalAnimation();
	m_pPlayer->ressurect(invulnerableTime);
	//设置主角位置
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size playerSize = m_pPlayer->getContentSize();
	m_pPlayer->setPosition(playerSize.width/2,visibleSize.height/2);
}
void PlayerLayer::setDelegate(PlayerLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}