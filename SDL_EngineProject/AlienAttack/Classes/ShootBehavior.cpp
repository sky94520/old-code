#include "ShootBehavior.h"
#include "Enemy.h"
#include "EnemyLayer.h"

SingleShooter::SingleShooter(EnemyLayerDelegate*pDelegate)
	:m_pDelegate(pDelegate)
{
}
void SingleShooter::shoot(Enemy*enemy)
{
	if(enemy->isDying())
		return;
	auto bulletType = enemy->getBulletType();
	Point pos = enemy->getPosition();
	Size size = enemy->getContentSize();

	Point startPos = Point(pos.x - size.width/2,pos.y);
	//根据飞机朝向来设定子弹朝向
	const Point&heading = enemy->getHeading();
	//向左直行
	m_pDelegate->addEnemyBullet(startPos,enemy->getBulletType(),heading);
}
//-------------------------------EsketletorShooter-----------------------------
EsketletorShooter::EsketletorShooter(EnemyLayerDelegate*pDelegate)
	:m_pDelegate(pDelegate)
{
}
void EsketletorShooter::shoot(Enemy*enemy)
{
	if(enemy->isDying())
		return;

	auto curPos = enemy->getPosition();
	auto size = enemy->getContentSize();

	BulletType bulletType = enemy->getBulletType();

	Point pos1 = Point(curPos.x - size.width/2,curPos.y);
	Point pos2 = Point(curPos.x + size.width/2,curPos.y);
	//发射子弹
	m_pDelegate->addEnemyBullet(pos1,bulletType,Point(-1.f,0.f));
	m_pDelegate->addEnemyBullet(pos2,bulletType,Point(1.f,0.f));
}
//------------------------TurretShooter-----------------------------
TurretShooter::TurretShooter(EnemyLayerDelegate*pDelegate)
	:m_pDelegate(pDelegate)
{
}
void TurretShooter::shoot(Enemy*enemy)
{
	if(enemy->isDying())
		return;

	auto curPos = enemy->getPosition();
	auto size = enemy->getContentSize();

	BulletType bulletType = enemy->getBulletType();

	Point pos1 = Point(curPos.x - size.width/2,curPos.y);
	Point pos2 = Point(curPos.x + size.width/2,curPos.y);
	Point pos3 = Point(curPos.x,curPos.y - size.height/2);
	//发射子弹
	m_pDelegate->addEnemyBullet(pos1,bulletType,Point(-1.f,-1.f));
	m_pDelegate->addEnemyBullet(pos2,bulletType,Point(1.f,-1.f));
	m_pDelegate->addEnemyBullet(pos3,bulletType,Point(0.f,-1.f));
}
//-----------------------RoofTurretShooter-------------------------------------
RoofTurretShooter::RoofTurretShooter(EnemyLayerDelegate*pDelegate)
	:m_pDelegate(pDelegate)
{
}
void RoofTurretShooter::shoot(Enemy*enemy)
{
	if(enemy->isDying())
	return;

	auto curPos = enemy->getPosition();
	auto size = enemy->getContentSize();

	BulletType bulletType = enemy->getBulletType();

	Point pos1 = Point(curPos.x - size.width/2,curPos.y);
	Point pos2 = Point(curPos.x + size.width/2,curPos.y);
	Point pos3 = Point(curPos.x,curPos.y + size.height/2);
	//发射子弹
	m_pDelegate->addEnemyBullet(pos1,bulletType,Point(-1.f,1.f));
	m_pDelegate->addEnemyBullet(pos2,bulletType,Point(1.f,1.f));
	m_pDelegate->addEnemyBullet(pos3,bulletType,Point(0.f,1.f));
}