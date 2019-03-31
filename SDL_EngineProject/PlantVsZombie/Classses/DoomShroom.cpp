#include "DoomShroom.h"
#include "Terrain.h"

DoomShroom::DoomShroom()
	:m_state(State::Normal),m_elapsed(0.f)
	,m_boomDuration(0.f),m_nDamage(0)
{
}

DoomShroom::~DoomShroom()
{
}

DoomShroom*DoomShroom::create(const string& plantName)
{
	auto plant = new DoomShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool DoomShroom::init(const string& plantName)
{
	this->setPlantName(plantName);
	
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);
	this->bindSpriteWithAnimate(animate);

	m_state = State::Normal;
	
	return true;
}

void DoomShroom::updateNotSleeping(float dt)
{
	if (m_state == State::Normal)
	{
		//一定时间后转向Boom状态
		m_elapsed += dt;

		if (m_elapsed >= this->getColdDownTime())
		{
			m_elapsed = 0.f;
			this->changeState(State::Boom);
		}
	}
	else if (m_state == State::Boom)
	{
		m_elapsed += dt;
		//到达时间，爆炸
		if (m_elapsed >= m_boomDuration)
		{
			this->boom();
		}
	}
}

void DoomShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void DoomShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void DoomShroom::onHurt()
{
	//不睡则转入Boom
	if (! this->isSleeping())
	{
		this->changeState(State::Boom);
		m_elapsed = 0.f;
	}
}

void DoomShroom::changeState(State state)
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
	else if (state == State::Sleeping)
	{
		animationName = StringUtils::format("%sSleep",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Boom)
	{
		animationName = StringUtils::format("%sBoom",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_boomDuration = animation->getDuration();
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

void DoomShroom::boom()
{
	//当前塔基没有被破坏并且是草地
	if (!m_pCarrier->isDestroyed() && m_pCarrier->getTerrainType() == TerrainType::Lawn)
	{
		auto lawn = dynamic_cast<Lawn*>(m_pCarrier);
		//草地形成弹坑
		lawn->destroyByDoomShroom();
		//展示爆炸动画
		auto pos = this->getPosition();
		pos.y += this->getContentSize().height/2;

		m_pDelegate->showBoom(pos);
		//毁灭菇死亡
		this->setHitPoint(0);
		this->setDead(true);
		//生成全屏炸弹
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//TODO

		Rect rect = Rect(0.f,0.f,visibleSize.width,visibleSize.height);
		m_pDelegate->addBoom(m_nDamage,-1,rect);
	}
}