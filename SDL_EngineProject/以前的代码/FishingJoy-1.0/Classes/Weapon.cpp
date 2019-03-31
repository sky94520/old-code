#include "Weapon.h"
#include "Cannon.h"
#include "Bullet.h"
#include "FishingNet.h"
Weapon::Weapon()
	:m_pCannon(nullptr),m_pBullet(nullptr),m_pFishingNet(nullptr)
	,m_bulletType(BulletType::kBulletType_1)
{
}
Weapon::~Weapon()
{
}
bool Weapon::init()
{
	m_pCannon = Cannon::create();
	m_pBullet = Bullet::create();
	m_pBullet->setDelegate(this);
	m_pBullet->setVisible(false);
	m_pFishingNet = FishingNet::create();
	m_pFishingNet->setDelegate(this);
	m_pFishingNet->setVisible(false);
	this->addChild(m_pFishingNet,10);

	this->addChild(m_pBullet);
	this->addChild(m_pCannon);
	//设置大小
	setContentSize(m_pCannon->getContentSize());
	return true;
}
bool Weapon::shootTo(const Point&target)
{
	//设置朝向
	Point startPos = getWorldPosition();
	Point delta = startPos - target;
	float d = sqrt(pow(delta.x,2)+pow(delta.y,2));
	float radin = std::asin(delta.y/d);
	//设置角度
	float rotation = delta.x>=0?radin*180/PI - 90:fabs(radin*180/PI - 90);

	float distance = m_pCannon->getRouteDistance();

	Point realPos=Point(distance/d*delta.x,distance/d*delta.y);

	//设置子弹位置
	Size cannonSize = m_pCannon->getContentSize();
	if(rotation > 0)
		m_pBullet->setPosition(cannonSize.width/2,0);
	else
		m_pBullet->setPosition(0,0);
	m_pBullet->flyTo(Point::ZERO - realPos,rotation);
	//发射音效
	SoundManager::getInstance()->playEffect("sound_shot.mp3",0);
	return true;
}
bool Weapon::isShooting()const
{
	return m_pBullet->isVisible();
}
void Weapon::aimAt(const Point&target)
{
	m_pCannon->aimAt(target);
}
void Weapon::addCannonLevel()
{
	m_pCannon->addLevel();
}
void Weapon::subCannonLevel()
{
	m_pCannon->subLevel();
}
void Weapon::end()
{
	//SoundManager::getInstance()->playEffect("bgm_fire.wav",0);
	//在子弹里出现渔网
	m_pBullet->end();
}
CannonType Weapon::getCannonType()const
{
	return m_pCannon->getCannonType();
}
int Weapon::getCannonLevel() const
{
	return static_cast<int>(m_pCannon->getCannonType());
}
void Weapon::showAt(const Point&pos)
{
	m_pFishingNet->showAt(pos);
}
BulletType Weapon::getBulletType()const
{
	return m_bulletType;
}
void Weapon::setBulletType(BulletType type)
{
	m_bulletType = type;
}