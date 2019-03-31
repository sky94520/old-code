#include "BulletLayer.h"
#include "Bullet.h"
#include "ZombieBase.h"
#include "ShooterPeaBullet.h"

BulletLayer::BulletLayer()
	:m_pDelegate(nullptr)
{
}

BulletLayer::~BulletLayer()
{
}

bool BulletLayer::init()
{
	return true;
}

void BulletLayer::update(float dt)
{
	for (auto it = m_bullets.begin();it != m_bullets.end();)
	{
		auto bullet = *it;
		//移除该子弹
		if (bullet->isDead())
		{
			bullet->removeFromParent();
			it = m_bullets.erase(it);
		}
		else
		{
			this->checkCollisionBetweenZombieAndBullet(bullet);
			it++;
		}
	}
}

Bullet*BulletLayer::addPeaBullet()
{
	//设置基础属性
	PeaBullet*bullet = PeaBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Common);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

Boom*BulletLayer::addBoom()
{
	//设置基础属性
	auto bullet = Boom::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Boom);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

CabbageBullet*BulletLayer::addCabbageBullet()
{
	//设置基础属性
	auto bullet = CabbageBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Track);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

CornpultBullet*BulletLayer::addCornpultBullet(bool isButter)
{
	//设置基础属性
	auto bullet = CornpultBullet::create(isButter);
	bullet->setDead(false);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

SnowPeaBullet*BulletLayer::addSnowPeaBullet()
{
	//设置基础属性
	auto bullet = SnowPeaBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Deceleration);
	bullet->setHitPoint(1);
	//设置debuff的持续时间
	bullet->setDuration(10.f);

	m_bullets.push_back(bullet);

	return bullet;
}

FirePeaBullet*BulletLayer::addFirePeaBullet()
{
	//设置基础属性
	auto bullet = FirePeaBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::FireAndKillDeceleration);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

ShooterPeaBullet*BulletLayer::addShooterPeaBullet(ShooterPeaBullet::Type type)
{
	//设置基础属性
	auto bullet = ShooterPeaBullet::create(type);
	bullet->setDead(false);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

FumeShroomBullet*BulletLayer::addFumeShroomBullet()
{
	auto bullet = FumeShroomBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Penetrate);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

ShroomBullet* BulletLayer::addShroomBullet()
{
	auto bullet = ShroomBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Common);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

vector<Bullet*>& BulletLayer::getBulletList()
{
	return m_bullets;
}

void BulletLayer::setDelegate(BulletLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

FiniteTimeAction* BulletLayer::lineRoute(Bullet *bullet,const Point& deltaPos,float speed,bool bRight)
{
	//设置动作
	auto length = deltaPos.length();

	auto move = MoveBy::create(length/300.f,deltaPos);
	CallFunc*end = CallFunc::create([bullet]()
	{
		bullet->setDead(true);
	});
	//运行动作
	auto seq = Sequence::createWithTwoActions(move,end);

	return seq;
}

FiniteTimeAction* BulletLayer::jumpRoute(Bullet *bullet,const Point& startPos,const Point& endPos,float speed)
{
	auto x = SDL_fabs(endPos.x - startPos.x);
	float y = -200.f;
	//先简单实现长度的计算
	auto length = sqrt(pow(x,2.0) + pow(y,2.0));
	auto duration = (float)length / speed;

	JumpTo*jump = JumpTo::create(duration,endPos,y,1);
	CallFunc*end = CallFunc::create([bullet]()
	{
		bullet->setDead(true);
	});
	auto seq = Sequence::createWithTwoActions(jump,end);
	
	return seq;
}

void BulletLayer::checkCollisionBetweenZombieAndBullet(Bullet*bullet)
{
	auto row = bullet->getRow();

	auto zombies = m_pDelegate->getZombiesOfRow(row);
	auto r = bullet->getCollisionBoundingBox();

	for (auto it = zombies.begin();it != zombies.end();it++)
	{
		auto zombie = *it;
		//子弹当前即将死亡，则退出这次循环
		if (bullet->isDying())
			break;
		//子弹已经攻击过这个僵尸了，不再进行攻击
		if (bullet->isHasAttacked(zombie))
			continue;

		auto rect = zombie->getCollisionBoundingBox();
		//僵尸收到伤害
		if (r.intersectRect(rect))
		{
			this->handleCollision(bullet,zombie);
		}
	}
	//子弹碰撞结束
	bullet->contactEnd();
}

void BulletLayer::handleCollision(Bullet*bullet,ZombieBase*zombie)
{
	auto attackType = bullet->getAttackType();
	bool isTrack = Bullet::isTrackBullet(attackType);
	bool bIsHurt = false;
	//当前子弹是Boom 则无法避免
	if (bullet->getAttackType() == AttackType::Boom)
	{
		bIsHurt = true;
	}//僵尸是和子弹能发生碰撞
	else if (zombie->isActiveForBullet())
	{
		//是追踪性子弹 并且碰撞的是目标僵尸
		if (isTrack && zombie == bullet->getAimZombie())
			bIsHurt = true;
		//不是追踪子弹
		else if (!isTrack)
			bIsHurt = true;
	}
	//受伤位置最好不要改变，跟实现有关
	if (bIsHurt)
	{
		//进行debuff的更新
		if (Bullet::isDecelerationBullet(attackType))
		{
			zombie->deceleration(attackType,bullet->getDuration());
		}
		if (Bullet::isButterBullet(attackType))
		{
			zombie->butter(bullet->getPosition(),bullet->getDuration());
		}
		//僵尸受伤
		zombie->hurt(bullet->getDamage(),bullet->getAttackType());
		//子弹受伤
		bullet->hurt();
		//把该僵尸放到已攻击列表中
		bullet->addAttackedZombie(zombie);
	}
}