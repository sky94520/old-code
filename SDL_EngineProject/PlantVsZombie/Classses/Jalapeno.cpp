#include "Jalapeno.h"

Jalapeno::Jalapeno()
	:m_state(State::Normal),m_elapsed(0.f)
	,m_duration(0.f),m_nIndex(0)
	,m_nDamage(0)
{
}

Jalapeno::~Jalapeno()
{
}

Jalapeno*Jalapeno::create(const string& plantName)
{
	auto plant = new Jalapeno();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Jalapeno::init(const string& plantName)
{
	this->setPlantName(plantName);
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);
	//绑定精灵
	this->bindSpriteWithAnimate(animate);
	//设置当前状态
	m_state = State::Normal;

	return true;
}

void Jalapeno::updateHook(float dt)
{
	if (m_state == State::Normal)
	{
		m_elapsed += dt;
		//到达发动时间
		if (m_elapsed >= this->getColdDownTime())
		{
			m_elapsed = 0.f;

			this->changeState(State::Skill);
		}
	}
	else if (m_state == State::Skill)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			//设置不可见
			this->setVisible(false);

			this->changeState(State::Dying);
		}
	}
	else if (m_state == State::Dying)
	{
		m_elapsed += dt;
		//定时产生fire
		if (m_elapsed >= 0.05f)
		{
			m_elapsed = 0.f;
			//产生fire
			auto& terrains = m_pDelegate->getTerrainsOfRow(this->getRow());
			//产生的数量足够
			if (m_nIndex < terrains.size())
			{
				this->addFire(terrains.at(m_nIndex));
				m_nIndex++;
			}
			else//真正死亡
			{
				this->setHitPoint(0);
				this->setDead(true);
			}
		}
	}
}

void Jalapeno::onHurt()
{
	if (m_state == State::Normal)
	{
		m_elapsed = 0.f;

		this->changeState(State::Skill);
	}
}

void Jalapeno::addFire(Terrain*terrain)
{
	auto pos = terrain->getPosition();
	auto size = terrain->getContentSize();
	int localZOrder = this->getLocalZOrder();

	m_pDelegate->showFire(pos + Point(0.f,size.height/2),localZOrder);
	m_pDelegate->addBoom(m_nDamage,this->getRow(),terrain->getBoundingBox());
}

void Jalapeno::changeState(State state)
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
	else if (state == State::Skill)
	{
		animationName = StringUtils::format("%sSkill",plantName.c_str());
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