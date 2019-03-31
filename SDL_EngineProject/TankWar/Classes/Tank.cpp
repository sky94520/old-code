#include "Tank.h"
#include "StaticData.h"

Tank::Tank()
	:m_dir(Direction::Down)
	,m_speed(3.f)
	,m_state(State::Idle)
	,_dirty(true)
{
}

Tank::~Tank()
{
}

Tank* Tank::create(const string& name)
{
	auto tank = new Tank();

	if (tank && tank->init(name))
		tank->autorelease();
	else
		SDL_SAFE_DELETE(tank);

	return tank;
}

bool Tank::init(const string& name)
{
	m_chartletName = name;
	//设置静止状态
	this->changeState(State::Idle);

	return true;
}

bool Tank::move(Direction dir)
{
	auto nextPos = this->getPosition();
	Point delta;
	float rotation = 0.f;
	
	switch (dir)
	{
	case Direction::Down:
		delta.y = m_speed;
		rotation = 180.f;
		break;
	case Direction::Left:
		delta.x = -m_speed;
		rotation = -90.f;
		break;
	case Direction::Right:
		delta.x = m_speed;
		rotation = 90.f;
		break;
	case Direction::Up:
		delta.y = -m_speed;
		rotation = 0.f;
		break;
	default:
		break;
	}
	//获取下一方向
	nextPos += delta;
	//下一方向是否可通过
	//TODO
	//停止动作
	this->stopActionByTag(ACTION_TAG);

	this->getSprite()->setRotation(rotation);
	this->changeState(State::Run);
	this->setPosition(nextPos);

	return true;
}

void Tank::sit()
{
	this->changeState(State::Idle);
}

void Tank::fire()
{
	auto oldState = m_state;
	float duration = this->changeState(State::Fire);

	DelayTime* delayTime = DelayTime::create(duration);
	CallFunc* end = CallFunc::create([this,oldState]()
	{
		this->changeState(oldState);
	});

	auto seq = Sequence::createWithTwoActions(delayTime, end);
	seq->setTag(ACTION_TAG);

	this->stopActionByTag(ACTION_TAG);
	this->runAction(seq);
}

float Tank::changeState(State state)
{
	if (m_state == state && !_dirty)
		return 0.f;
	//设置状态
	_dirty = false;
	m_state = state;
	//停止原来的动画
	if (this->getSprite() != nullptr)
	{
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	}
	Animation* animation = nullptr;
	string animationName;

	switch (m_state)
	{
	case State::Idle:
		{
			animationName = StringUtils::format("%s_run", m_chartletName.c_str());
			animation = AnimationCache::getInstance()->getAnimation(animationName);
			
			auto firstFrame = animation->getFrames().front()->getSpriteFrame();
			//绑定精灵
			if (m_pSprite == nullptr)
				this->bindSpriteWithSpriteFrame(firstFrame);
			else
				m_pSprite->setSpriteFrame(firstFrame);

			animation = nullptr;
		}
		break;
	case State::Run:
		{
			animationName = StringUtils::format("%s_run", m_chartletName.c_str());

			animation = AnimationCache::getInstance()->getAnimation(animationName);
		}
		break;
	case State::Fire:
		{
			animationName = StringUtils::format("%s_fire", m_chartletName.c_str());

			animation = AnimationCache::getInstance()->getAnimation(animationName);
		}
		break;
	default:
		break;
	}
	if (animation == nullptr)
		return 0.f;

	auto animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);

	return animate->getDuration();
}