#include "SunShroom.h"

SunShroom::SunShroom()
	:m_growUpTimeLeft(0.f),m_state(State::Normal)
	,m_elapsed(0.f),m_duration(0.f)
	,m_bSmall(true),m_elapsedSun(0.f)
{
}

SunShroom::~SunShroom()
{
}

SunShroom*SunShroom::create(const string&plantName)
{
	auto plant = new SunShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool SunShroom::init(const string&plantName)
{
	this->setPlantName(plantName);
	
	auto animationName = StringUtils::format("%s2",plantName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);
	this->bindSpriteWithAnimate(animate);

	m_state = State::Normal;

	return true;
}
void SunShroom::updateNotSleeping(float dt)
{
	//在是小蘑菇时，对成长计时
	if (m_bSmall)
		this->growUpdate(dt);

	if (m_state == State::Normal)
	{
		m_elapsedSun += dt;
		//到达出阳光时间
		if (m_elapsedSun >= this->getColdDownTime())
		{
			m_elapsedSun = 0.f;
			//改变当前状态
			this->changeState(State::ProducingSun);
		}
	}
	else if (m_state == State::Growing
		|| m_state == State::ProducingSun)
	{
		m_elapsed += dt;
		//成长后自动转入正常状态
		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			//阳光菇长大
			if (m_state == State::Growing)
			{
				m_bSmall = false;
			}
			//生产阳光
			else if (m_state == State::ProducingSun)
			{
				this->productSun();
			}
			//切换状态
			this->changeState(State::Normal);
		}
	}
}

void SunShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void SunShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void SunShroom::growUpdate(float dt)
{
	//当前成长时间剩余
	if (m_growUpTimeLeft > 0.f)
	{
		m_growUpTimeLeft -= dt;
		//到达成长时间，成长
		if (m_growUpTimeLeft <= 0.f)
		{
			this->changeState(State::Growing);
		}
	}
}

void SunShroom::productSun()
{
	//设置一个动作
	Size size = this->getContentSize(); 
	auto x = RANDOM(0.f,size.width);
	auto y = 0.f;
	
	JumpBy*jump = JumpBy::create(0.8f,Point(x,y),-size.height,1);
	auto pos = this->getPosition();
	auto realPos = this->getParent()->convertToWorldSpace(pos);
	//确定将要产出的阳光个数
	int number = m_bSmall ? 15 : 25;

	m_pDelegate->makeSun(number,jump,realPos);
}

void SunShroom::changeState(State state)
{
	if (m_state == state)
		return ;

	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;

	if (state == State::Normal)
	{
		if (m_bSmall)
		{
			animationName = StringUtils::format("%s2",plantName.c_str());
		}
		else
			animationName = plantName;
		//停止原先的动画
		this->getSprite()->stopActionByTag(ANIMATION_TAG);

		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Sleeping)
	{
		animationName = StringUtils::format("%sSleep",plantName.c_str());
		//停止原先的动画
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		m_duration = animation->getDuration();
	}
	else if (state == State::Growing)
	{
		animationName = StringUtils::format("%sGrowing",plantName.c_str());
		//停止原先的动画
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		m_duration = animation->getDuration();
	}
	else if (state == State::ProducingSun)
	{
		//产生阳光 时间
		m_duration = 2.f;
		//改变color mod
		this->getSprite()->setColorMod(Color3B(0xee,0xc9,0x00));
	}
	if (animation != nullptr)
	{
		auto animate = Animate::create(animation);
		animate->setTag(ANIMATION_TAG);

		this->getSprite()->runAction(animate);
		//恢复原来的颜色
		this->getSprite()->setColorMod(Color3B(0xff,0xff,0xff));
	}
}