#include "Player.h"
const int Player::ANIMATION_TAG = 1;

Player::Player()
	:m_invulnerableTime(0.f),m_moveSpeed(0.f)
	,m_curState(kPlayerState_None),m_bCanJump(false)
	,m_curLevel(1),m_bJumping(false)
	,m_invulnerableType(InvulnerableType::kNone)
	,m_bulletNum(0)
{
}
Player::~Player()
{
	_eventDispatcher->removeEventListenerForTarget(this);
}
bool Player::init()
{
	this->bindSprite(Sprite::createWithSpriteFrameName("mario_0_run00.png"));
	//添加子弹结束监听器
	_eventDispatcher->addEventCustomListener(std::to_string(this->getUniqueID())
		,SDL_CALLBACK_1(Player::bulletOver,this),this);

	return true;
}
void Player::idle()
{
	if(this->changeState(kPlayerState_Idle))
	{
		this->runIdleAnimation();
		m_bCanJump = true;
		m_bJumping = false;
	}
}
void Player::fall()
{
	if(this->changeState(kPlayerState_Falling))
	{
		this->runJumpingAnimation();
		m_bCanJump = false;
		m_bJumping = false;
	}
}
void Player::run(bool bRight)
{
	if(this->changeState(kPlayerState_Runnable))
	{
		this->runRunnableAnimation();
		m_bCanJump = true;
		m_bJumping = false;
	}
	if(bRight)
		this->getSprite()->setFlipX(false);
	else
		this->getSprite()->setFlipX(true);
	//对动画速度进行改变
	Speed*speed = dynamic_cast<Speed*>(m_pSprite->getActionByTag(ANIMATION_TAG));
	if(speed)
	{
		auto velocityX = SDL_fabs(this->getVelocity().x);
		if(velocityX < 1.f)
			velocityX = 1.f;
		speed->setSpeed(SDL_pow(velocityX,0.33333f));
	}
}
void Player::jump()
{
	if(this->changeState(kPlayerState_Jumping))
	{
		this->runJumpingAnimation();
		m_bCanJump = false;
		m_bJumping = true;
	}
}
void Player::sit()
{
	if(this->changeState(kPlayerState_Sit))
	{
		this->runSittingAnimation();
	}
}
void Player::ressurect(float invulnerableTime)
{
	//重新初始化
	m_bJumping = false;
	m_bCanJump = false;

	this->setCurHp(1);
	this->setDead(false);
	//设置当前状态
	m_curState = kPlayerState_None;
	//设置速度为0
	m_velocity = Point::ZERO;
	//设置无敌
	this->makeSelfInvulnerable(InvulnerableType::kWithoutCollision,invulnerableTime);
}
void Player::runIdleAnimation()
{
	if(this->getSprite()->getActionByTag(ANIMATION_TAG))
		m_pSprite->stopActionByTag(ANIMATION_TAG);
	auto str = StringUtils::format("mario_%d_run00.png",m_curLevel-1);
	this->getSprite()->setSpriteFrame(str);
}
void Player::runRunnableAnimation()
{
	if(this->getSprite()->getActionByTag(ANIMATION_TAG))
		m_pSprite->stopActionByTag(ANIMATION_TAG);
	auto str = StringUtils::format("mario_%d_run%s.png",m_curLevel-1,"%02d");
	//运行动画
	auto animate = Entity::createAnimate(str,0,1,0.1f,-1);
	//animate->setTag(ANIMATION_TAG);
	auto speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);
	this->getSprite()->runAction(speed);
}
void Player::runJumpingAnimation()
{
	if(this->getSprite()->getActionByTag(ANIMATION_TAG))
		m_pSprite->stopActionByTag(ANIMATION_TAG);
	//改变动画
	auto str = StringUtils::format("mario_%d_jump00.png",m_curLevel-1);
	this->getSprite()->setSpriteFrame(str);
}
void Player::runSittingAnimation()
{
	if(this->getSprite()->getActionByTag(ANIMATION_TAG))
		m_pSprite->stopActionByTag(ANIMATION_TAG);
	//改变动画
	auto str = StringUtils::format("mario_%d_sit00.png",m_curLevel-1);
	this->getSprite()->setSpriteFrame(str);
}
void Player::runDeadAnimation()
{
	if(this->getSprite()->getActionByTag(ANIMATION_TAG))
		m_pSprite->stopActionByTag(ANIMATION_TAG);
	auto str = StringUtils::format("mario_dead00.png");
	this->getSprite()->setSpriteFrame(str);
}
bool Player::isInvulnerable()const
{
	return m_invulnerableTime > 0.f;
}
void Player::levelUp()
{
	bool bRet = true;
	m_curLevel++;
	if(m_curLevel > 3)
	{
		m_curLevel = 3;
		bRet = false;
	}
	if(bRet == false)
		return;
	//重置 动画和尺寸
	auto str = StringUtils::format("mario_%d_run00.png",m_curLevel-1);
	m_pSprite->setSpriteFrame(str);
	Size size = m_pSprite->getContentSize();
	m_pSprite->setPosition(size.width/2,size.height/2);
	this->setContentSize(size);
	
	//设置当前状态为无状态
	m_curState = kPlayerState_None;
	//设置当前血量
	m_nCurHp++;
}
void Player::levelDown()
{
	//todo
	if(m_curLevel <= 1)
		return;
	m_curLevel--;
	//重置 动画和尺寸
	auto str = StringUtils::format("mario_%d_run00.png",m_curLevel-1);
	m_pSprite->setSpriteFrame(str);
	Size size = m_pSprite->getContentSize();
	m_pSprite->setPosition(size.width/2,size.height/2);
	this->setContentSize(size);
	//设置当前状态为无状态
	m_curState = kPlayerState_None;
	//设置无敌
	this->makeSelfInvulnerable(InvulnerableType::kWithoutCollision,1.5f);
}
void Player::canHurtEnemyWithInvulnearability()
{
	//设置无敌
	this->makeSelfInvulnerable(InvulnerableType::kCanHurtEnemy,6.f);
}
ItemType Player::getGrowingItemType()const
{
	if(this->m_curLevel  == 1)
		return kItemType_Mushroom;
	else
		return kItemType_Flower;
}
bool Player::isDirRight()const
{
	return this->getSprite()->isFlipX() == false;
}
void Player::bulletOver(EventCustom*)
{
	m_bulletNum++;
}
bool Player::isCanShoot()const
{
	return m_curLevel > 2 && m_bulletNum > 0;
}
void Player::onBindSprite()
{
	//对精灵坐标微调整
	auto pos = m_pSprite->getPosition();
	pos.y += 1;
	m_pSprite->setPosition(pos);
}
bool Player::onHurt(int damage)
{
	this->levelDown();
	return true;
}
void Player::onDead()
{
	//先取消当前所有动画以及动作
	m_pSprite->stopAllActions();
	this->stopAllActions();
	//设置死亡帧
	string str = "mario_dead00.png";
	m_pSprite->setSpriteFrame(str);
	//设置死亡动作
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto position = this->getPosition();
	//跳跃高度
	float jumpHeight = this->getContentSize().height;

	JumpBy*jump = JumpBy::create(2.f,Point(0.f,jumpHeight),-60,1);
	CallFunc*end = CallFunc::create([this]()
	{
		this->setDead(true);
	});
	//运行动作
	auto sequence = Sequence::createWithTwoActions(jump,end);
	this->runAction(sequence);
}
Rect Player::getCollisionBoundingBox()const
{
	//根据不同级别和不同状态有不同的尺寸大小
	//这些值是根据TexturePacker进行相应的调整的
	if(m_curState == kPlayerState_Sit)
		return Entity::getCollisionBoundingBox();
	if(m_curLevel == 1)
	{
		Rect r = Rect(4,28,24,34);
		r.origin += this->getBoundingBox().origin;
		return r;
	}
	else
	{
		Rect r = Rect(0,6,30,56);
		r.origin += this->getBoundingBox().origin;
		return r;
	}
	return Entity::getCollisionBoundingBox();
}
bool Player::isInteractiveWithBlock()const
{
	bool bRet = (m_curState == kPlayerState_Jumping);
	return bRet;
}
bool Player::isCanBrokeTile()const
{
	return m_curLevel > 1;
}
bool Player::changeState(PlayerState nextState)
{
	if(m_curState == kPlayerState_Dead || m_curState == nextState)
		return false;
	m_curState = nextState;
	return true;
}
void Player::makeSelfInvulnerable(InvulnerableType type,float invulnerableTime)
{
	//定义无敌动画的tag为5
	const int actionTag = 5;
	//定义定时器的key为player invulnerable
	const std::string key = "player invulnerable";
	//设置当前无敌类型
	m_invulnerableType = type;
	//设置无敌时间
	//m_invulnerableTime = invulnerableTime;
	//尝试删除原有的动作以及定时器
	if(m_pSprite->getActionByTag(actionTag))
		m_pSprite->stopActionByTag(actionTag);
	this->unschedule(key);
	//根据当前无敌类型设置不同的动画效果
	if(type == InvulnerableType::kCanHurtEnemy)
	{
		/*TintTo*tintFrom = TintTo::create(invulnerableTime/2.f,0,255,255);
		TintTo*tintTo = TintTo::create(invulnerableTime/2.f,255,0,255);*/
		ColorMod*c1 = ColorMod::create(255,0,0);
		ColorMod*c2 = ColorMod::create(0,255,0);
		ColorMod*c3 = ColorMod::create(0,0,255);
		ColorMod*c4 = ColorMod::create(255,255,255);
		DelayTime*delay = DelayTime::create(0.1f);

		auto s1 = Sequence::create(c1,delay->clone(),c4->clone(),delay->clone(),NULL);
		auto s2 = Sequence::create(c2,delay->clone(),c4->clone(),delay->clone(),NULL);
		auto s3 = Sequence::create(c3,delay->clone(),c4->clone(),delay->clone(),NULL);

		auto sequence = Sequence::create(s1,s2,s3,NULL);
		//auto sequence = Sequence::create(c1,delay,c2,delay->clone(),c3,delay->clone(),c4,delay->clone(),NULL);
		auto repeat = Repeat::create(sequence,50);
		repeat->setTag(actionTag);

		m_pSprite->runAction(repeat);
	}
	else if(type == InvulnerableType::kWithoutCollision)
	{
		Blink*blink = Blink::create(invulnerableTime,(int)(invulnerableTime*10));
		blink->setTag(actionTag);

		m_pSprite->runAction(blink);
	}
	auto end = [this,actionTag](float)
	{
		this->m_invulnerableType = InvulnerableType::kNone;
	};
	//设置一个定时器
	this->scheduleOnce(end,key,invulnerableTime);
}