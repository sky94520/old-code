#include "Bullet.h"
#include "ZombieBase.h"

Bullet::Bullet()
	:m_nRow(0),m_nDamage(0)
	,m_attackType(AttackType::Common)
	,m_duration(0.f)
	,m_bCanTransform(true)
	,m_bulletType(BulletType::Common)
	,m_stopRunningCallback(nullptr)
	,m_deadCallback(nullptr)
{
	this->setCharacterType(CharacterType::Bullet);
}

Bullet::~Bullet()
{
	SDL_SAFE_RELEASE_NULL(m_pAimZombie);
	//ɾ���б��еĽ�ʬ
	for (auto it = m_attackedZombieList.begin();it != m_attackedZombieList.end();)
	{
		auto zombie = *it;
		it = m_attackedZombieList.erase(it);

		zombie->release();
	}
}

void Bullet::setAimZombie(ZombieBase*zombie)
{
	SDL_SAFE_RETAIN(zombie);
	SDL_SAFE_RELEASE(m_pAimZombie);

	m_pAimZombie = zombie;
}

ZombieBase*Bullet::getAimZombie()
{
	return m_pAimZombie;
}

void Bullet::addAttackedZombie(ZombieBase*zombie)
{
	//�������ò��ŵ������б���
	zombie->retain();

	m_attackedZombieList.push_back(zombie);
}

bool Bullet::isHasAttacked(ZombieBase*zombie)
{
	auto it = find_if(m_attackedZombieList.begin(),m_attackedZombieList.end(),[zombie](ZombieBase*z)
	{
		return z == zombie;
	});
	//�����ڣ��򷵻�false
	if (it == m_attackedZombieList.end())
		return false;
	return true;
}

void Bullet::setRow(int row)
{
	m_nRow = row;
}

void Bullet::hurt()
{
	this->hurt(1,AttackType::Common);
}

int Bullet::getRow()const
{
	return m_nRow;
}

void Bullet::contactEnd()
{
}

bool Bullet::isTrackBullet(AttackType attackType)
{
	return attackType == AttackType::Track
		|| attackType == AttackType::TrackAndButter
		|| attackType == AttackType::TrackAndDeceleration;
}

bool Bullet::isDecelerationBullet(AttackType attackType)
{
	return attackType == AttackType::Deceleration
		|| attackType == AttackType::TrackAndDeceleration;
}

bool Bullet::isButterBullet(AttackType attackType)
{
	return attackType == AttackType::TrackAndButter;
}

void Bullet::onHurt()
{
}

void Bullet::rotateInnerSprite()
{
	//������ת����
	auto rotate = RotateBy::create(1.f,90.f);
	auto repeat = RepeatForever::create(rotate);

	this->getSprite()->runAction(repeat);
}

void Bullet::dieAfterRunningAnimation(const string &animationName)
{
	//����������֮������
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);
	//���õ�һ֡Ϊ��ǰ֡
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	//���ж���
	this->getSprite()->setSpriteFrame(firstFrame);
	this->getSprite()->runAction(animate);
	//���ж���������֮������
	DelayTime*delayTime = DelayTime::create(animation->getDuration());
	CallFunc*end = CallFunc::create([this]()
	{
		this->setDead(true);
		//���������ص�����
		if (m_deadCallback)
			m_deadCallback();
	});
	auto seq = Sequence::createWithTwoActions(delayTime,end);

	this->stopAllActions();
	this->runAction(seq);
}

void Bullet::hurt(int damage,AttackType attackType)
{
	onHurt();
}
//-----------------------�㶹�ӵ�PeaBullet------------------------------
bool PeaBullet::init()
{
	auto spriteFrameName = "PeaBullet.png";
	this->bindSpriteWithSpriteFrameName(spriteFrameName);
	//��������
	this->setDamage(20);
	this->setHitPoint(1);
	this->setAttackType(AttackType::Common);

	return true;
}

void PeaBullet::onHurt()
{
	m_nHitPoint = 0;
	//����������֮������
	auto animationName = "pea_bullet_dead_anim";

	this->dieAfterRunningAnimation(animationName);
}
//---------------------��ըBoom-------------------------
Boom::Boom()
{
}

Boom::~Boom()
{
}

bool Boom::init()
{
	return true;
}

void Boom::contactEnd()
{
	m_nHitPoint = 0;
	this->setDead(true);
}

Rect Boom::getCollisionBoundingBox()const
{
	return m_collisionRect;
}
//------------------------CabbageBullet----------------------
bool CabbageBullet::init()
{
	auto spriteFrameName = "CabbageBullet.png";
	//�󶨾���
	this->bindSpriteWithSpriteFrameName(spriteFrameName);
	
	this->rotateInnerSprite();

	return true;
}

void CabbageBullet::onHurt()
{
	m_nHitPoint = 0;
	
	this->dieAfterRunningAnimation("pea_bullet_dead_anim");
}
//------------------SnowPeaBullet----------------------------
bool SnowPeaBullet::init()
{
	auto spriteFrameName = "SnowPeaBullet.png";
	//�󶨾���
	this->bindSpriteWithSpriteFrameName(spriteFrameName);
	//��������
	this->setDamage(20);
	this->setHitPoint(1);
	this->setDuration(10.f);
	this->setAttackType(AttackType::Deceleration);

	return true;
}

void SnowPeaBullet::onHurt()
{
	m_nHitPoint = 0;
	//����������֮������
	auto animationName = "snow_pea_bullet_dead_anim";
	
	this->dieAfterRunningAnimation(animationName);
}
//-------------------FirePeaBullet----------------------------
FirePeaBullet::FirePeaBullet()
	:m_bFirst(true),m_nTime(0)
{
}

bool FirePeaBullet::init()
{
	//�󶨶���
	auto animationName = "FirePeaBullet";
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);
	
	this->bindSpriteWithAnimate(animate);
	//������֡��������
	m_nTime = 1;
	//��������
	this->setDamage(40);
	this->setHitPoint(1);
	this->setAttackType(AttackType::FireAndKillDeceleration);

	return true;
}

void FirePeaBullet::onHurt()
{
	if (m_bFirst)
	{
		m_bFirst = false;
		//����������֮������
		auto animationName = "FirePeaBulletHit";
		//ֹͣԭ�ȶ���
		this->getSprite()->stopAllActions();
		//��ʼ����
		this->dieAfterRunningAnimation(animationName);
		//����ê��
		this->getSprite()->setAnchorPoint(Point(0.f,0.9f));
		//�����˺�
		this->setDamage(m_nDamage / 3);
		//���ֲ�������˺�
		m_nHitPoint = 0;
	}
}

void FirePeaBullet::contactEnd()
{
	if (!m_bFirst)
	{
		//�ڵڶ�����ɽ����˺�
		if (m_nTime-- > 0)
		{
			m_nHitPoint = 1;
		}
		else
		{
			m_nHitPoint = 0;
		}
	}
}

Rect FirePeaBullet::getCollisionBoundingBox()const
{
	Rect rect = this->getSprite()->getSpriteFrameRect();
	Rect r = this->getBoundingBox();

	r.origin += rect.origin;
	r.size = rect.size;

	return r;
}
//-------------------FumeShroomBullet------------------------
FumeShroomBullet::FumeShroomBullet()
	:m_fAtkScope(0.f)
{
}

bool FumeShroomBullet::init()
{
	//���ж���
	auto animationName = "fume_shroom_bullet_anim";
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	this->bindSpriteWithAnimate(animate);

	m_pSprite->setAnchorPoint(Point(0.f,0.5f));

	DelayTime*delayTime = DelayTime::create(animate->getDuration());
	CallFunc*end = CallFunc::create([this]()
	{
		this->setDead(true);
	});
	auto seq = Sequence::createWithTwoActions(delayTime,end);

	this->runAction(seq);

	return true;
}

Rect FumeShroomBullet::getCollisionBoundingBox()const
{
	auto rect = this->getBoundingBox();
	//�������TODO ��ͼƬ�й�
	rect.origin.x += 100.f;
	rect.size.width = this->getAtkScope();

	return rect;
}

void FumeShroomBullet::contactEnd()
{
	m_nHitPoint = 0;
}
//-----------------ShroomBullet-----------------------------
bool ShroomBullet::init()
{
	//�󶨾��鲢���ж���
	auto animationName = "ShroomBullet";
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	this->bindSpriteWithAnimate(animate);

	return true;
}

void ShroomBullet::onHurt()
{
	m_nHitPoint = 0;
	auto animationName = "ShroomBulletHit";

	//ֹͣԭ���Ķ���
	this->getSprite()->stopAllActions();
	//������������
	this->dieAfterRunningAnimation(animationName);
}

Rect ShroomBullet::getCollisionBoundingBox()const
{
	auto rect = this->getBoundingBox();
	//ȷ����ײ���
	rect.size.width /= 2;

	return rect;
}
//------------------------CornBullet----------------------
CornpultBullet*CornpultBullet::create(bool isButter)
{
	auto bullet = new CornpultBullet();

	if (bullet && bullet->init(isButter))
		bullet->autorelease();
	else
		SDL_SAFE_DELETE(bullet);

	return bullet;
}

bool CornpultBullet::init(bool isButter)
{
	string spriteFrameName ;
	if (isButter)
	{
		spriteFrameName = "Cornpult_butter.png";
	}
	else
	{
		spriteFrameName = "Cornpult_kernal.png";
	}
	//�󶨾���
	this->bindSpriteWithSpriteFrameName(spriteFrameName);

	this->rotateInnerSprite();

	return true;
}

void CornpultBullet::onHurt()
{
	m_nHitPoint = 0;
	m_bDead = true;
}