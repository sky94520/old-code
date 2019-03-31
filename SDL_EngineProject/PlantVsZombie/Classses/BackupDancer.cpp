#include "BackupDancer.h"

BackupDancer::BackupDancer()
	:m_state(State::None),m_duration(0.f)
	,m_elapsed(0.f)
{
}

BackupDancer::~BackupDancer()
{
}

BackupDancer*BackupDancer::create(const string& zombieName)
{
	auto zombie = new BackupDancer();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool BackupDancer::init(const string& zombieName)
{
	this->setZombieName(zombieName);
	//获取站立状态贴图
	auto animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	this->bindSpriteWithSpriteFrame(firstFrame);
	//运行站立动画
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);

	return true;
}

void BackupDancer::updateAlive(float dt)
{
	//自动转入上升状态
	if (m_state == State::None)
	{
		this->changeState(State::Rising);
		//开启遮罩
		this->setOpenShade(true);
		//显示破土特效
		auto pos = this->getPosition();
		Size size = this->getContentSize();
		auto localZOrder = this->getLocalZOrder();

		m_pDelegate->showRisingDirt(pos + Point(0,size.height/2),localZOrder + 1);
	}//上升状态
	if (m_state == State::Rising)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->setOpenShade(false);
			//转入行走状态
			this->changeState(State::Walk);
		}
	}//行走状态
	else if (m_state == State::Walk)
	{
		this->updateWalkState(dt);
	}//跳舞状态
	else if (m_state == State::Dance || m_state == State::DanceDead)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			State nextState;

			if (m_state == State::Dance)
				nextState = State::Walk;
			else if (m_state == State::DanceDead)
				nextState = State::WalkDead;
			//设置状态
			this->changeState(nextState);
		}
	}
	//攻击状态
	else if (m_state == State::Attack)
	{
		if (m_pAim == nullptr || m_pAim->isDead())
		{
			this->clearAim();
			this->changeState(State::Walk);
		}
		else
		{
			this->eatAim(dt);
		}
	}
}

bool BackupDancer::isCanMove()const
{
	if (m_state == State::Walk || m_state == State::WalkDead)
		return true;

	return false;
}

void BackupDancer::onNormalDead()
{
	State state = State::None;

	if (m_state == State::Walk)
		state = State::WalkDead;
	else if (m_state == State::Attack)
		state = State::AttackDead;
	else if (m_state == State::Dance)
		state = State::DanceDead;

	if (state != State::None)
		this->changeState(state);
}

void BackupDancer::changeState(State state)
{
	//状态没有发生改变，直接退出
	if (m_state == state)
		return ;

	m_state = state;
	string animationName;

	if (m_state == State::Rising)
	{
		//设置持续时间
		m_duration = 0.4f;
		//设置位置
		auto size = this->getSprite()->getContentSize();
		auto pos = this->getSprite()->getPosition();

		this->getSprite()->setPosition(pos + Point(0.f,size.height/2));
		//设置上升动画
		MoveBy*move = MoveBy::create(m_duration,Point(0.f,-size.height/2));

		this->getSprite()->runAction(move);
	}
	else if (m_state == State::Walk)
	{
		animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
		//行走几秒
		m_duration = 3.f;
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",m_zombieName.c_str());
	}
	else if (m_state == State::Dance)
	{
		animationName = StringUtils::format("%sDancing",m_zombieName.c_str());
		//跳舞几秒
		m_duration = 2.f;
	}
	else if (m_state == State::WalkDead)
	{
		animationName = StringUtils::format("%sLostHeadWalk",m_zombieName.c_str());

		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = StringUtils::format("%sLostHeadAttack",m_zombieName.c_str());
		
		this->showZombieHead();
	}
	else if (m_state == State::DanceDead)
	{
		animationName = StringUtils::format("%sLostHeadDancing",m_zombieName.c_str());
		
		this->showZombieHead();
	}
	if (animationName.empty())
	{
		return ;
	}

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void BackupDancer::showZombieHead()
{
	//调整位置
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/4.f;

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getLocalZOrder(),false);
}

void BackupDancer::updateWalkState(float dt)
{
	m_elapsed += dt;
	//存在攻击目标
	if (m_pAim != nullptr)
	{
		this->changeState(State::Attack);
		m_elapsed = 0.f;
	}
	else if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;
		//TODO
		this->changeState(State::Dance);
	}
}