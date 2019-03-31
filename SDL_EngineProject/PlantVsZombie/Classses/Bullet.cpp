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
	//删除列表中的僵尸
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
	//保存引用并放到攻击列表中
	zombie->retain();

	m_attackedZombieList.push_back(zombie);
}

bool Bullet::isHasAttacked(ZombieBase*zombie)
{
	auto it = find_if(m_attackedZombieList.begin(),m_attackedZombieList.end(),[zombie](ZombieBase*z)
	{
		return z == zombie;
	});
	//不存在，则返回false
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
	//运行旋转动画
	auto rotate = RotateBy::create(1.f,90.f);
	auto repeat = RepeatForever::create(rotate);

	this->getSprite()->runAction(repeat);
}

void Bullet::dieAfterRunningAnimation(const string &animationName)
{
	//死亡动画，之后死亡
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);
	//设置第一帧为当前帧
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	//运行动画
	this->getSprite()->setSpriteFrame(firstFrame);
	this->getSprite()->runAction(animate);
	//运行动作，在这之后死亡
	DelayTime*delayTime = DelayTime::create(animation->getDuration());
	CallFunc*end = CallFunc::create([this]()
	{
		this->setDead(true);
		//调用死亡回调函数
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
//-----------------------豌豆子弹PeaBullet------------------------------
bool PeaBullet::init()
{
	auto spriteFrameName = "PeaBullet.png";
	this->bindSpriteWithSpriteFrameName(spriteFrameName);
	//设置属性
	this->setDamage(20);
	this->setHitPoint(1);
	this->setAttackType(AttackType::Common);

	return true;
}

void PeaBullet::onHurt()
{
	m_nHitPoint = 0;
	//死亡动画，之后死亡
	auto animationName = "pea_bullet_dead_anim";

	this->dieAfterRunningAnimation(animationName);
}
//---------------------爆炸Boom-------------------------
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
	//绑定精灵
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
	//绑定精灵
	this->bindSpriteWithSpriteFrameName(spriteFrameName);
	//设置属性
	this->setDamage(20);
	this->setHitPoint(1);
	this->setDuration(10.f);
	this->setAttackType(AttackType::Deceleration);

	return true;
}

void SnowPeaBullet::onHurt()
{
	m_nHitPoint = 0;
	//死亡动画，之后死亡
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
	//绑定动画
	auto animationName = "FirePeaBullet";
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);
	
	this->bindSpriteWithAnimate(animate);
	//设置两帧内起作用
	m_nTime = 1;
	//设置属性
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
		//死亡动画，之后死亡
		auto animationName = "FirePeaBulletHit";
		//停止原先动画
		this->getSprite()->stopAllActions();
		//开始动画
		this->dieAfterRunningAnimation(animationName);
		//设置锚点
		this->getSprite()->setAnchorPoint(Point(0.f,0.9f));
		//设置伤害
		this->setDamage(m_nDamage / 3);
		//本轮不再造成伤害
		m_nHitPoint = 0;
	}
}

void FirePeaBullet::contactEnd()
{
	if (!m_bFirst)
	{
		//在第二轮造成溅射伤害
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
	//运行动画
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
	//修正宽度TODO 跟图片有关
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
	//绑定精灵并运行动画
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

	//停止原来的动画
	this->getSprite()->stopAllActions();
	//运行死亡动画
	this->dieAfterRunningAnimation(animationName);
}

Rect ShroomBullet::getCollisionBoundingBox()const
{
	auto rect = this->getBoundingBox();
	//确定碰撞面积
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
	//绑定精灵
	this->bindSpriteWithSpriteFrameName(spriteFrameName);

	this->rotateInnerSprite();

	return true;
}

void CornpultBullet::onHurt()
{
	m_nHitPoint = 0;
	m_bDead = true;
}