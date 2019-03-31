#include "Enemy.h"
#include "MoveBehavior.h"
#include "BehaviorManager.h"
#include "Player.h"

const int Enemy::ENEMY_ANIMATION_TAG = 1;

Enemy::Enemy()
	:m_bBulletImmune(false),m_bStarImmune(false)
	,m_bStampImmune(false)
	,m_bCanHurtEnemy(false),m_bEnemyImmune(false)
	,m_bCollidedWithEnemyFlag(false)
	,m_bCollidedWithPlayerFlag(false)
{
}
Enemy::~Enemy()
{
}
void Enemy::hurt(Entity*entity,EnemyHurtType hurtType)
{
	//ֻҪ���˾͵����������
	bool bRet = onHurt(entity,hurtType);

	if(bRet == false)
		return;
	int damage = entity->getDamage();
	//�����ʱ�Ѿ����������ٵ���
	//if(this->isDying() || this->isDead())
	//	return;
	//�ܵ��ӵ��˺����Ҳ����ӵ�����
	//�ܵ��ȵ��˺����Ҳ��Բ�����
	//�ܵ��޵��˺����Ҳ����޵�����
	//������ײ��û�ܵ��˺�
	if((hurtType == EnemyHurtType::Bullet && m_bBulletImmune == false)
		||(hurtType == EnemyHurtType::Stamp && m_bStampImmune == false)
		||(hurtType == EnemyHurtType::Star && m_bStarImmune == false)
		||(hurtType == EnemyHurtType::Enemy && m_bEnemyImmune == false)
		|| hurtType != EnemyHurtType::None)
	{
		//����Ѫ��
		int curHp = this->getCurHp();
		int afterHp = curHp - damage;
		this->setCurHp(afterHp);

		if(afterHp <= 0)
			onDead(hurtType);//����ʱ����
	}
}
bool Enemy::onHurt(Entity*entity,EnemyHurtType hurtType)
{
	return true;
}
void Enemy::changeDirectionX()
{
	auto velocity = this->getVelocity();
	velocity.x = -velocity.x;
	this->setVelocity(velocity);
}
//-----------------------------����Ģ��-----------------------------------
TriMushroom::TriMushroom()
{
}
TriMushroom::~TriMushroom()
{
}
bool TriMushroom::init()
{
	//�󶨾���
	this->bindSprite(Sprite::createWithSpriteFrameName("trimushroom_r00.png"));

	return true;
}
void TriMushroom::onDead(EnemyHurtType hurtType)
{
	Animate*deadAnimate = nullptr;
	FiniteTimeAction*action = nullptr;

	//��ֹͣԭ��m_pSprite����
	auto curAnimate = m_pSprite->getActionByTag(ENEMY_ANIMATION_TAG);
	if(curAnimate)
		//m_pSprite->stopAllActions();
		m_pSprite->stopActionByTag(ENEMY_ANIMATION_TAG);

	if(hurtType == EnemyHurtType::Stamp)
	{
		m_pSprite->setSpriteFrame("trimushroom_d00.png");
		//��������
		auto fadeOut = FadeOut::create(1.f);
		m_pSprite->runAction(fadeOut);
		//����
		DelayTime*delayTime = DelayTime::create(fadeOut->getDuration());
		CallFunc*end = CallFunc::create([this](){
			this->setDead(true);
		});
		action = Sequence::create(delayTime,end,nullptr);
	}
	else
	{
		this->getSprite()->setFlipY(true);
		//FlipY*flip = FlipY::create(true);
		JumpBy*jump = JumpBy::create(1.f,Point(90,90),-45,1);
		CallFunc*end = CallFunc::create([this](){
			this->setDead(true);
		});
		action = Sequence::create(jump,end,NULL);
	}
	this->setVelocity(Point::ZERO);
	this->stopAllActions();
	this->runAction(action);
}
void TriMushroom::runRunnableAnimation()
{
	auto animate = Entity::createAnimate("trimushroom_r%02d.png",0,1,0.1f,-1);
	animate->setTag(ENEMY_ANIMATION_TAG);
	//����ֹͣ��ǰ����
	auto curAnimate = m_pSprite->getActionByTag(ENEMY_ANIMATION_TAG);
	if(curAnimate)
		m_pSprite->stopActionByTag(ENEMY_ANIMATION_TAG);
	m_pSprite->runAction(animate);
}
Rect TriMushroom::getCollisionBoundingBox()const
{
	Rect r = Rect(0,0,30,30);
	r.origin += this->getBoundingBox().origin;
	return r;
}
bool TriMushroom::tileCollidedX(bool bRight)
{
	return false;
}
bool TriMushroom::tileCollidedY(bool bDown)
{
	return true;
}
//---------------------------- Tortoise----------------------------
const string Tortoise::m_ressurectScheduleStr = "ressurect";
Tortoise::Tortoise()
	:m_stateType(kTortoiseState_Run),m_bLeft(true)
{
}
Tortoise::~Tortoise()
{
	this->unschedule(m_ressurectScheduleStr);
}
bool Tortoise::init()
{
	//�󶨾���
	this->bindSprite(Sprite::createWithSpriteFrameName("tortoise1_00.png"));
	//���ø���ʱ��
	m_ressurectTime = 10.f;

	return true;
}
bool Tortoise::onHurt(Entity*entity,EnemyHurtType hurtType)
{
	bool bRet = true;
	//�ܵ����ǲȵ����ҵ�ǰ��������״̬ => SinkHead
	//�����ǲȵ����Ҵ�����ͷ�˶�״̬ => SinkHead
	if(hurtType == EnemyHurtType::Stamp && 
		(m_stateType == kTortoiseState_Run || m_stateType == kTortoiseState_RunAndSinkHead))
	{
		m_stateType = kTortoiseState_SinkHead;
		this->setCanHurtEnemy(false);
		this->ressurectPeriodOne();
		bRet = false;
	}
	//�����Ƿ�����ײ���ҵ�ǰ�ڹ괦����ͷ״̬ʱ => RunAndSinkHead
	else if((hurtType == EnemyHurtType::Stamp || hurtType == EnemyHurtType::None)
		&& m_stateType == kTortoiseState_SinkHead)
	{
		m_stateType = kTortoiseState_RunAndSinkHead;
		//����ȡ�������ʱ��
		this->unschedule(m_ressurectScheduleStr);
		//ֹͣ����
		this->stopAllActions();
		this->getSprite()->stopActionByTag(ENEMY_ANIMATION_TAG);
		//�ָ��˺�
		m_nDamage = 1;
		//���ÿ����˺�����
		m_bCanHurtEnemy = true;
		//���ݵ�ǰʵ���λ�� �����ٶȷ��� ��ʱ���óɸ����ǵ�ǰ�ٶ��й�
		auto velocity = m_oldVelocity*5;
		if(entity->getPositionX() > this->getPosition().x)
			velocity.x *= -1;
		
		this->setVelocity(velocity);
		//�ٴν��в� �����������ٿ�Ѫ
		bRet = false;
	}
	return bRet;
}
void Tortoise::onDead(EnemyHurtType hurtType)
{
	this->stopAllActions();
	this->getSprite()->stopActionByTag(ENEMY_ANIMATION_TAG);

	this->unschedule(m_ressurectScheduleStr);
	//��������֡
	this->getSprite()->setSpriteFrame("tortoise1_r00.png");
	this->getSprite()->setFlipY(true);
	JumpBy*jump = JumpBy::create(1.f,Point(90,90),-45,1);
	CallFunc*end = CallFunc::create([this](){
		this->setDead(true);
	});
	auto action = Sequence::create(jump,end,NULL);
	//���ж���
	this->runAction(action);
}
bool Tortoise::isInteractiveWithBlock()const
{
	return m_stateType == kTortoiseState_RunAndSinkHead;
}
bool Tortoise::isCanBrokeTile()const
{
	return m_stateType == kTortoiseState_RunAndSinkHead;
}
void Tortoise::runRunnableAnimation()
{
	this->getSprite()->stopActionByTag(ENEMY_ANIMATION_TAG);
	auto animate = Entity::createAnimate("tortoise1_%02d.png",0,1,0.1f,-1);
	animate->setTag(ENEMY_ANIMATION_TAG);
	this->getSprite()->runAction(animate);
}
Rect Tortoise::getCollisionBoundingBox()const
{
	Rect r = Entity::getCollisionBoundingBox();
	//���ݵ�ǰ״̬ȷ����ͬ����ײ���
	if(m_stateType == kTortoiseState_Run)
	{
		r.origin += Point(2,0);
		r.size = Size(46,46);
	}
	else if(m_stateType == kTortoiseState_SinkHead || m_stateType == kTortoiseState_RunAndSinkHead)
	{
		r.size = Size(28,28);
	}
	return r;
}
void Tortoise::changeDirectionX()
{
	m_bLeft = !m_bLeft;
	Enemy::changeDirectionX();
}
bool Tortoise::tileCollidedX(bool bRight)
{
	m_bLeft = !m_bLeft;
	return false;
}
bool Tortoise::tileCollidedY(bool bDown)
{
	return true;
}
void Tortoise::ressurectPeriodOne()
{
	//�����˺�Ϊ0
	this->setDamage(0);
	//�����ٶ�
	this->setVelocity(Point::ZERO);
	//���þ���
	auto pSprite = this->getSprite();
	pSprite->stopActionByTag(ENEMY_ANIMATION_TAG);
	pSprite->setSpriteFrame("tortoise1_r00.png");
	//���ö�ʱ����Ϊ����ʱ��
	this->scheduleOnce(SDL_CALLBACK_1(Tortoise::ressurectPeriodTwo,this)
		,m_ressurectScheduleStr,3.f/4*m_ressurectTime);
}
void Tortoise::ressurectPeriodTwo(float dt)
{
	//���ö���
	auto animate = Entity::createAnimate("tortoise1_r%02d.png",0,1,0.1f,-1);
	animate->setTag(ENEMY_ANIMATION_TAG);

	this->getSprite()->runAction(animate);
	//���ö�ʱ�����ٹ�֮�����������
		this->scheduleOnce(SDL_CALLBACK_1(Tortoise::ressurectPeriodThree,this)
		,m_ressurectScheduleStr,1.f/4*m_ressurectTime);
}
void Tortoise::ressurectPeriodThree(float dt)
{
	//ֹͣ����
	m_pSprite->stopActionByTag(ENEMY_ANIMATION_TAG);
	//�����������߶���
	this->runRunnableAnimation();
	//����Ѫ��
	this->setCurHp(this->getMaxHp());
	//�����˺�
	this->setDamage(1);
	//�����ٶ�Ϊһ��ʼ���ٶ�
	auto v = m_oldVelocity;
	v.x = m_bLeft?-v.x:v.x;
	this->setVelocity(v);
	//����״̬
	m_stateType = kTortoiseState_Run;
	//����y����ֵ todo
	this->setPositionY(this->getPositionY() - 18.f);
}
//--------------------------------WingEnemyDecorator���װ����-----------------
WingEnemyDecorator::WingEnemyDecorator()
	:m_pInnerEnemy(nullptr),m_bWingDead(false)
	,m_curJumpHeight(0.f)
	,MAX_JUMP_HEIGHT(Director::getInstance()->getVisibleSize().height/8)
	,m_bLeft(false)
{
}
WingEnemyDecorator::~WingEnemyDecorator()
{
}
WingEnemyDecorator*WingEnemyDecorator::create(Enemy*enemy)
{
	auto decorator = new WingEnemyDecorator();
	if(decorator && decorator->init(enemy))
		decorator->autoRelease();
	else
		SDL_SAFE_DELETE(decorator);
	return decorator;
}
bool WingEnemyDecorator::init(Enemy*enemy)
{
	m_pInnerEnemy = enemy;
	this->addChild(m_pInnerEnemy);
	Size size = m_pInnerEnemy->getContentSize();
	//�󶨾���
	this->bindSprite(Sprite::createWithSpriteFrameName("wing0.png"));
	this->setContentSize(size);

	m_pInnerEnemy->setPosition(size.width/2,size.height/2);
	//���ó��λ��
	Size pSpriteSize = m_pSprite->getContentSize();
	m_pSprite->setPosition(0,pSpriteSize.height/2);

	return true;
}
bool WingEnemyDecorator::onHurt(Entity*entity,EnemyHurtType hurtType)
{
	bool bRet = false;
	//���δ���� �����ܵ��ȵ��˺�
	if(m_bWingDead == false
		&& hurtType == EnemyHurtType::Stamp)
	{
		bRet = false;
		m_bWingDead = true;
		//�����ʾ
		this->getSprite()->setVisible(false);
		this->getSprite()->stopActionByTag(ENEMY_ANIMATION_TAG);
		//�����ƶ���Ϊ
		this->setMoveBehavior(m_pInnerEnemy->getMoveBehavior());
	}
	//ֱ������
	else if(hurtType != EnemyHurtType::None && hurtType != EnemyHurtType::Stamp)
	{
		this->getSprite()->setVisible(false);
		m_pInnerEnemy->hurt(entity,hurtType);
		bRet = true;
	}
	else
	{
		bRet = false;
		m_pInnerEnemy->hurt(entity,hurtType);
		//todo
		if(m_bWingDead)
		{
			this->setVelocity(m_pInnerEnemy->getVelocity());
			this->setDamage(m_pInnerEnemy->getDamage());
			bool bCanHurtEnemy = m_pInnerEnemy->isCanHurtEnemy();
			this->setCanHurtEnemy(bCanHurtEnemy);
		}
		if(m_pInnerEnemy->isDying())
			bRet = true;
	}
	return bRet;
}
void WingEnemyDecorator::onDead(EnemyHurtType hurtType)
{
}
void WingEnemyDecorator::changeDirectionX()
{
	m_bLeft =! m_bLeft;
	Enemy::changeDirectionX();
	//���ݵ�ǰ�ķ���ȷ������λ��
	Size size = m_pInnerEnemy->getContentSize();
	Size pSpriteSize = m_pSprite->getContentSize();
	if(m_bLeft)
	{
		m_pSprite->setPosition(size.width,pSpriteSize.height/2);
		this->getSprite()->setFlipX(true);
		m_pInnerEnemy->getSprite()->setFlipX(true);
	}
	else
	{
		m_pSprite->setPosition(0,pSpriteSize.height/2);
		this->getSprite()->setFlipX(false);
		m_pInnerEnemy->getSprite()->setFlipX(false);
	}
}
bool WingEnemyDecorator::isInteractiveWithBlock()const
{
	return m_pInnerEnemy->isInteractiveWithBlock();
}
bool WingEnemyDecorator::isCanBrokeTile()const
{
	return m_pInnerEnemy->isCanBrokeTile();
}
void WingEnemyDecorator::runRunnableAnimation()
{
	//���г�򶯻�
	auto animate = Entity::createAnimate("wing%d.png",0,1,0.1f,-1);
	animate->setTag(ENEMY_ANIMATION_TAG);
	this->getSprite()->runAction(animate);

	m_pInnerEnemy->runRunnableAnimation();
	//��⵱ǰ�ٶ��Ƿ�ͷ���ƥ��
	Size size = m_pInnerEnemy->getContentSize();
	Size pSpriteSize = m_pSprite->getContentSize();

	if(this->getVelocity().x < 0)
	{
		m_bLeft = true;
		m_pSprite->setPosition(size.width,pSpriteSize.height/2);
		this->getSprite()->setFlipX(true);
		m_pInnerEnemy->getSprite()->setFlipX(true);
	}
}
Rect WingEnemyDecorator::getCollisionBoundingBox()const
{
	Rect r = m_pInnerEnemy->getCollisionBoundingBox();

	Point pos = this->getPosition();
	Size s = this->getContentSize();
	pos -= Point(s.width/2,s.height/2);
	r.origin += pos;

	return r;
}
void WingEnemyDecorator::performMove(float dt)
{
	if(m_pInnerEnemy->isDead())
	{
		this->setDead(true);
		return;
	}
	//���������ʱ�������ڲ�enemy ֻ���ٶȴ�С
	if(m_bWingDead)
	{
		//ȡ�ٶȴ�С
		auto v = m_pInnerEnemy->getVelocity();
		v.x = SDL_fabs(v.x);
		v.y = SDL_fabs(v.y);
		v.x = m_bLeft ? -v.x:v.x;
		this->setVelocity(v);
	}
	if(m_pMoveBehavior)
	{
		m_pMoveBehavior->performMove(this,dt);
		auto velocity = this->getVelocity();
/*		if(velocity.x > 0)
		{
			this->getSprite()->setFlipX(false);
			m_pInnerEnemy->getSprite()->setFlipX(false);
		}
		else
		{
			this->getSprite()->setFlipX(true);
			m_pInnerEnemy->getSprite()->setFlipX(true);
		}*/
		//��ߵ�����
		if(m_curJumpHeight > MAX_JUMP_HEIGHT)
		{
			m_curJumpHeight = 0.f;
			this->setVelocity(Point(velocity.x,-velocity.y));
		}
		else if(velocity.y < 0.f)
		{
			m_curJumpHeight += SDL_fabs(velocity.y);
		}
	}
	//BehaviorEntity::performMove(dt);
}
bool WingEnemyDecorator::tileCollidedX(bool bRight)
{
	this->changeDirectionX();
	//m_bLeft = !m_bLeft;
	m_curJumpHeight = 0.f;
	return m_pInnerEnemy->tileCollidedX(bRight);
}
bool WingEnemyDecorator::tileCollidedY(bool bDown)
{
	m_curJumpHeight = 0.f;
	return false;
}
//-----------------------------Chomper---------------------------------
Chomper::Chomper()
	:m_maxJumpHeight(0),m_curJumpHeight(0)
	,m_delayTime(0.f),m_elpased(0.f)
	,m_pDelegate(nullptr)
{
}
Chomper::~Chomper()
{
}
bool Chomper::init()
{
	//�󶨾���
	this->bindSprite(Sprite::createWithSpriteFrameName("enemy6_00.png"));
	//�������¸߶�
	m_maxJumpHeight = Director::getInstance()->getVisibleSize().height/4;
	//ʳ�˻�����ߵ�ͣ��ʱ��
	m_delayTime = 0.5f;

	return true;
}
bool Chomper::onHurt(Entity*entity,EnemyHurtType hurtType)
{
	return true;
}
void Chomper::onDead(EnemyHurtType hurtType)
{
	this->setDead(true);
}
void Chomper::runRunnableAnimation()
{
	auto animate = Entity::createAnimate("enemy6_%02d.png",0,1,0.1f,-1);
	animate->setTag(ENEMY_ANIMATION_TAG);
	this->getSprite()->runAction(animate);
}
void Chomper::performMove(float dt)
{
	Player*player = m_pDelegate->getPlayer();
	auto r = player->getCollisionBoundingBox();
	auto r1 = this->getCollisionBoundingBox();
	//���ݵ�ǰ�Ƿ��Ѿ���ˮ�ܣ�������ˣ��Ͳ����ƣ����򣬲��ó�ˮ��
	//��û��ˮ��
	auto v = this->getVelocity();
	if(r.intersectsRect(m_shapeRect))
	{
		auto height = m_maxJumpHeight - m_curJumpHeight;
/*		if(height < r1.size.height && v.y > 0.f)
			return;*/
		if(height > r1.size.height && height < r1.size.height*1.5f && v.y < 0.f)
			return;
	}
	if(m_pMoveBehavior)
	{
		auto velocity = this->getVelocity();
		//�ı� ����delay��ı�
		if(m_curJumpHeight >= m_maxJumpHeight)
		{
			m_elpased += dt;
			if(m_elpased <= m_delayTime)
				return;
			//���¼�ʱ
			m_elpased = 0.f;
			velocity.y = -velocity.y;
			this->setVelocity(velocity);

			m_curJumpHeight -= m_maxJumpHeight;
		}
		m_curJumpHeight += SDL_fabs(velocity.y);

		m_pMoveBehavior->performMove(this,dt);
	}
}
void Chomper::setDelegate(EnemyDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}