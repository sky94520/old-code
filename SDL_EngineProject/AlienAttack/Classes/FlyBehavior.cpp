#include "FlyBehavior.h"
#include "Enemy.h"
#include "EnemyLayer.h"
//-----------------------------------FlyStraightly----------------------
void FlyStraightly::fly(Enemy*enemy)
{
	if(enemy->isDying())
		return;
	//获取敌机速度
	Point heading = Point(-1.f,0.f);

	float speed = enemy->getSpeed();
	auto curPos = enemy->getPosition();
	auto nextPos = curPos +heading*speed;
	
	enemy->setPosition(nextPos);
	//设置敌机朝向
	enemy->setHeading(heading);
}
//--------------------------------FlyCrookedly---------------------------
FlyCrookedly::FlyCrookedly()
	:m_bFirst(true),m_velocity(-1.f,1.f)
{
}
void FlyCrookedly::fly(Enemy*enemy)
{
	if(enemy->isDying())
		return;

	if(m_bFirst)
	{
		m_bFirst = false;
		m_startPos = enemy->getPosition();
	}
	auto curPos = enemy->getPosition();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float speed = enemy->getSpeed();

	float minHeight = m_startPos.y - visibleSize.height/4;
	float maxHeight = m_startPos.y + visibleSize.height/4;

	if(curPos.y >= maxHeight)
		m_velocity.y = -1.f;
	else if(curPos.y <= minHeight)
		m_velocity.y = 1.f;
	
	Point nextPos = curPos + Point(speed*m_velocity.x,speed*m_velocity.y);
	enemy->setPosition(nextPos);
	//设置朝向
	enemy->setHeading(m_velocity);
}
//-----------------------------------FlyDown----------------------------
FlyDown::FlyDown(EnemyLayerDelegate*pDelegate)
	:m_pDelegate(pDelegate)
{
}
void FlyDown::fly(Enemy*enemy)
{
	//敌机死亡，则不进行更新
	if(enemy->isDying())
		return;
	float scrollSpeed = m_pDelegate->getMapScrollSpeed();

	Point heading = Point(-scrollSpeed,1.f);
	Point curPos = enemy->getPosition();
	Point nextPos = curPos + heading*enemy->getSpeed();

	enemy->setPosition(nextPos);
	enemy->setHeading(heading);
}
//------------------------------FlyWithMap-----------------------------
FlyWithMap::FlyWithMap(EnemyLayerDelegate*pDelegate)
	:m_pDelegate(pDelegate)
{
}
void FlyWithMap::fly(Enemy*enemy)
{
	float scrollSpeed = m_pDelegate->getMapScrollSpeed();
	Point velocity = Point(-scrollSpeed,0.f);

	auto curPos = enemy->getPosition();
	auto nextPos = curPos + velocity;

	enemy->setPosition(nextPos);
	enemy->setHeading(velocity);
}
//------------------------Boss1Fly------------------------------
Boss1Fly::Boss1Fly()
	:m_bFirst(true),m_velocity(-1.f,1.f)
{
}
void Boss1Fly::fly(Enemy*enemy)
{
	if(enemy->isDying())
		return;
	if(m_bFirst)
	{
		m_bFirst = false;
		m_startPos = enemy->getPosition();
	}
	auto curPos = enemy->getPosition();
	auto size = enemy->getContentSize();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float speed = enemy->getSpeed();

	float minHeight = m_startPos.y - visibleSize.height/4;
	float maxHeight = m_startPos.y + visibleSize.height/4;

	if(curPos.y >= maxHeight)
		m_velocity.y = -1.f;
	else if(curPos.y <= minHeight)
		m_velocity.y = 1.f;
	//判断飞机是否已经完全出界
	if(visibleSize.width - curPos.x > size.width/2)
		m_velocity.x = 0.f;
	Point nextPos = curPos + Point(speed*m_velocity.x,speed*m_velocity.y);
	enemy->setPosition(nextPos);
	//设置朝向
	enemy->setHeading(m_velocity);
}