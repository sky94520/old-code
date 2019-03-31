#include "ShooterPeaBullet.h"

ShooterPeaBullet::ShooterPeaBullet()
{
}

ShooterPeaBullet::~ShooterPeaBullet()
{
}

ShooterPeaBullet*ShooterPeaBullet::create(Type type)
{
	auto bullet = new ShooterPeaBullet();

	if (bullet && bullet->init(type))
		bullet->autorelease();
	else
		SDL_SAFE_DELETE(bullet);

	return bullet;
}

bool ShooterPeaBullet::init(Type type)
{
	m_type = type;
	//设置子弹类型
	this->setBulletType(BulletType::ShooterPeaBullet);

	m_pInnerBullet = this->makePlant(type);
	auto size = m_pInnerBullet->getContentSize();

	this->setContentSize(size);
	this->setPosition(size.width/2,size.height/2);
	this->addChild(m_pInnerBullet);

	this->setProperties(m_pInnerBullet);

	return true;
}

bool ShooterPeaBullet::transformType(Type type)
{
	if (type == m_type)
		return false;
	m_type = type;
	//移除原来的子弹
	m_pInnerBullet->removeFromParent();

	m_pInnerBullet = this->makePlant(type);
	this->addChild(m_pInnerBullet);

	this->setProperties(m_pInnerBullet);

	return true;
}

ShooterPeaBullet::Type ShooterPeaBullet::getShooterPeaBulletType()const
{
	return m_type;
}

void ShooterPeaBullet::onHurt()
{
	m_pInnerBullet->hurt();
	//血量 伤害 攻击类型跟随
	m_nHitPoint = m_pInnerBullet->getHitPoint();
	this->setProperties(m_pInnerBullet);
	//TODO 停止动作的运行
	this->stopAllActions();
}

void ShooterPeaBullet::contactEnd()
{
	m_pInnerBullet->contactEnd();
	//血量 伤害攻击类型跟随
	this->setProperties(m_pInnerBullet);
}

Rect ShooterPeaBullet::getCollisionBoundingBox()const
{
	auto rect = m_pInnerBullet->getCollisionBoundingBox();

	rect.origin += this->getPosition();

	return rect;
}

Bullet*ShooterPeaBullet::makePlant(Type type)
{
	Bullet*bullet = nullptr;

	switch (type)
	{
	case Type::PeaBullet:
		{
			bullet = PeaBullet::create();
		}break;
	case Type::SnowPeaBullet:
		{
			bullet = SnowPeaBullet::create();
		}break;
	case Type::FirePeaBullet:
		{
			bullet = FirePeaBullet::create();
		}break;
	}
	//设置死亡回调函数
	bullet->setDeadCallback(SDL_CALLBACK_0(ShooterPeaBullet::dead,this));

	return bullet;
}

void ShooterPeaBullet::setProperties(Bullet*bullet)
{
	this->setAttackType(m_pInnerBullet->getAttackType());
	this->setDamage(m_pInnerBullet->getDamage());
	this->setDuration(m_pInnerBullet->getDuration());
}

void ShooterPeaBullet::dead()
{
	this->setDead(true);
}