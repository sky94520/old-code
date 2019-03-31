#include "Chomper.h"
#include "ZombieBase.h"

Chomper::Chomper()
	:m_scope(0.f),m_nDamage(0)
	,m_state(State::Normal)
	,m_elapsed(0.f),m_duration(0.f)
	,m_pAimZombie(nullptr)
{
}

Chomper::~Chomper()
{
}

Chomper*Chomper::create(const string&plantName)
{
	auto plant = new Chomper();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Chomper::init(const string&plantName)
{
	this->setPlantName(plantName);
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);
	//绑定精灵
	this->bindSpriteWithAnimate(animate);
	//设置位置
	auto size = this->getContentSize();
	this->getSprite()->setPosition(Point(size.width/3 * 2,size.height/3));
	//设置当前状态
	m_state = State::Normal;

	return true;
}

void Chomper::updateHook(float dt)
{
	//正常状态进行僵尸的检测
	if (m_state == State::Normal)
	{
		this->updateNormalState(dt);
	}
	//在攻击开始动画结束后自动转入攻击结束状态
	else if (m_state == State::AttackStart)
	{
		m_elapsed += dt;
		//动画结束，再次进行检测
		if (m_elapsed >= m_duration)
		{
			//目标僵尸血量小于等于0，解除绑定
			if (m_pAimZombie->getHitPoint() <= 0)
			{
				SDL_SAFE_RELEASE_NULL(m_pAimZombie);
			}
			else//对目标僵尸造成吞噬伤害
			{
				m_pAimZombie->hurt(m_nDamage,AttackType::Swallow);
			}
			m_elapsed = 0.f;
			this->changeState(State::AttackEnd);
		}
	}
	else if (m_state == State::AttackEnd)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			//当前存在攻击目标转入消化阶段
			if (m_pAimZombie != nullptr)
			{
				this->changeState(State::Digesting);
				SDL_SAFE_RELEASE_NULL(m_pAimZombie);
			}
			else//转入正常阶段
			{
				this->changeState(State::Normal);
			}
			m_elapsed = 0.f;
		}
	}
	//消化阶段
	else if (m_state == State::Digesting)
	{
		m_elapsed += dt;

		if (m_elapsed >= this->getColdDownTime())
		{
			this->changeState(State::Success);

			m_elapsed = 0.f;
		}
	}
	//转入正常阶段
	else if (m_state == State::Success)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			this->changeState(State::Normal);

			m_elapsed = 0.f;
		}
	}
}

void Chomper::updateNormalState(float dt)
{
	//检测僵尸
	int row = m_pCarrier->getRow();

	auto pos = this->getPosition();

	auto zombie = m_pDelegate->findFirstZombieOfRow(row,this->getDir(),pos);
	//当前僵尸不存在 或者僵尸的血量《= 0 直接退出
	if (zombie == nullptr || zombie->getHitPoint() <= 0)
		return;
	//判断该僵尸是否在食人花攻击范围内
	auto delta = (float)SDL_fabs(pos.x - zombie->getPositionX());
	//当前僵尸在攻击范围内,则绑定僵尸，并进入攻击阶段
	if (delta < m_scope)
	{
		m_pAimZombie = zombie;
		SDL_SAFE_RETAIN(m_pAimZombie);

		m_elapsed = 0.f;

		this->changeState(State::AttackStart);
	}
}

void Chomper::changeState(State state)
{
	if (m_state == state)
		return;
	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;

	if (state == State::Normal)
	{
		animationName = plantName;
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Digesting)
	{
		animationName = StringUtils::format("%sDigest",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::AttackStart)
	{
		animationName = StringUtils::format("%sAtkStart",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	else if (state == State::AttackEnd)
	{
		animationName = StringUtils::format("%sAtkEnd",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	else if (state == State::Success)
	{
		animationName = StringUtils::format("%sSuccess",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	if (animation == nullptr)
		return;
	//停止原先的动画
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//创建动画
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}