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
		//�Ƴ����ӵ�
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
	//���û�������
	PeaBullet*bullet = PeaBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Common);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

Boom*BulletLayer::addBoom()
{
	//���û�������
	auto bullet = Boom::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Boom);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

CabbageBullet*BulletLayer::addCabbageBullet()
{
	//���û�������
	auto bullet = CabbageBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Track);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

CornpultBullet*BulletLayer::addCornpultBullet(bool isButter)
{
	//���û�������
	auto bullet = CornpultBullet::create(isButter);
	bullet->setDead(false);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

SnowPeaBullet*BulletLayer::addSnowPeaBullet()
{
	//���û�������
	auto bullet = SnowPeaBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::Deceleration);
	bullet->setHitPoint(1);
	//����debuff�ĳ���ʱ��
	bullet->setDuration(10.f);

	m_bullets.push_back(bullet);

	return bullet;
}

FirePeaBullet*BulletLayer::addFirePeaBullet()
{
	//���û�������
	auto bullet = FirePeaBullet::create();
	bullet->setDead(false);
	bullet->setAttackType(AttackType::FireAndKillDeceleration);
	bullet->setHitPoint(1);

	m_bullets.push_back(bullet);

	return bullet;
}

ShooterPeaBullet*BulletLayer::addShooterPeaBullet(ShooterPeaBullet::Type type)
{
	//���û�������
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
	//���ö���
	auto length = deltaPos.length();

	auto move = MoveBy::create(length/300.f,deltaPos);
	CallFunc*end = CallFunc::create([bullet]()
	{
		bullet->setDead(true);
	});
	//���ж���
	auto seq = Sequence::createWithTwoActions(move,end);

	return seq;
}

FiniteTimeAction* BulletLayer::jumpRoute(Bullet *bullet,const Point& startPos,const Point& endPos,float speed)
{
	auto x = SDL_fabs(endPos.x - startPos.x);
	float y = -200.f;
	//�ȼ�ʵ�ֳ��ȵļ���
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
		//�ӵ���ǰ�������������˳����ѭ��
		if (bullet->isDying())
			break;
		//�ӵ��Ѿ������������ʬ�ˣ����ٽ��й���
		if (bullet->isHasAttacked(zombie))
			continue;

		auto rect = zombie->getCollisionBoundingBox();
		//��ʬ�յ��˺�
		if (r.intersectRect(rect))
		{
			this->handleCollision(bullet,zombie);
		}
	}
	//�ӵ���ײ����
	bullet->contactEnd();
}

void BulletLayer::handleCollision(Bullet*bullet,ZombieBase*zombie)
{
	auto attackType = bullet->getAttackType();
	bool isTrack = Bullet::isTrackBullet(attackType);
	bool bIsHurt = false;
	//��ǰ�ӵ���Boom ���޷�����
	if (bullet->getAttackType() == AttackType::Boom)
	{
		bIsHurt = true;
	}//��ʬ�Ǻ��ӵ��ܷ�����ײ
	else if (zombie->isActiveForBullet())
	{
		//��׷�����ӵ� ������ײ����Ŀ�꽩ʬ
		if (isTrack && zombie == bullet->getAimZombie())
			bIsHurt = true;
		//����׷���ӵ�
		else if (!isTrack)
			bIsHurt = true;
	}
	//����λ����ò�Ҫ�ı䣬��ʵ���й�
	if (bIsHurt)
	{
		//����debuff�ĸ���
		if (Bullet::isDecelerationBullet(attackType))
		{
			zombie->deceleration(attackType,bullet->getDuration());
		}
		if (Bullet::isButterBullet(attackType))
		{
			zombie->butter(bullet->getPosition(),bullet->getDuration());
		}
		//��ʬ����
		zombie->hurt(bullet->getDamage(),bullet->getAttackType());
		//�ӵ�����
		bullet->hurt();
		//�Ѹý�ʬ�ŵ��ѹ����б���
		bullet->addAttackedZombie(zombie);
	}
}