#include "Cattail.h"
#include "ZombieBase.h"
#include "Carrier.h"

Cattail::Cattail()
	:m_state(State::Normal),m_elapsed(0.f)
	,m_duration(0.f),m_pAim(nullptr)
	,m_nBulletNum(0),m_nCurBulletNum(0)
	,m_nDamage(20)
{
}

Cattail::~Cattail()
{
	SDL_SAFE_RELEASE_NULL(m_pAim);
}

Cattail*Cattail::create(const string& plantName)
{
	auto plant = new Cattail();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Cattail::init(const string& plantName)
{
	if (VesselPlant::init(TerrainType::LilyPad))
	{
		//设置内部载体不可种植
		this->getInnerCarrier()->setDestroyed(true);
		//设置植物名
		this->setPlantName(plantName);
		//设置动画和贴图
		auto animationName = plantName;
		auto animation = AnimationCache::getInstance()->getAnimation(animationName);
		auto animate = Animate::create(animation);

		animate->setTag(ANIMATION_TAG);
		//绑定精灵
		this->bindSpriteWithAnimate(animate);
		//设置当前状态
		m_state = State::Normal;
		//设置当前子弹个数
		m_nBulletNum = 2;
		//重新设置位置
		auto size = this->getContentSize();
		m_pSprite->setPosition(size.width/5 * 2,size.height/3);
	}
	return true;
}

void Cattail::updateHook(float dt)
{
	switch (m_state)
	{
	case State::Normal: this->updateNormalState(dt);break;
	case State::Attack: this->updateAtkState(dt); break;
	case State::AttackEnd: this->updateAtkEndState(dt); break;
	}
}

void Cattail::updateNormalState(float dt)
{
	if (m_elapsed < this->getColdDownTime())
	{
		m_elapsed += dt;
		return;
	}
	//发现场景是否存在僵尸
	auto zombie = m_pDelegate->findFirstZombieOfRow(-1,this->getDir(),this->getPosition());

	if (zombie != nullptr)
	{
		SDL_SAFE_RETAIN(zombie);

		m_pAim = zombie;
		m_elapsed = 0.f;
		//设置当前攻击子弹
		m_nCurBulletNum = 0;
		//转到攻击状态
		this->changeState(State::Attack);
	}
}

void Cattail::updateAtkState(float dt)
{
	m_elapsed += dt;
	//到达攻击时间
	if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;
		//添加子弹
		m_pDelegate->addCornpultBullet(m_pAim,false,m_nDamage,-1,this->getPosition());

		this->changeState(State::AttackEnd);
	}
}

void Cattail::updateAtkEndState(float dt)
{
	m_nCurBulletNum++;
	m_elapsed = 0.f;
	//到达攻击次数 改变状态并且释放该僵尸
	if (m_nCurBulletNum >= m_nBulletNum)
	{
		this->changeState(State::Normal);
		SDL_SAFE_RELEASE_NULL(m_pAim);
	}
	else//继续攻击
	{
		this->changeState(State::Attack);
	}
}

void Cattail::changeState(State state)
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
	else if (state == State::Attack)
	{
		animationName = StringUtils::format("%sAtk",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	else if (state == State::AttackEnd)
	{
		animationName = StringUtils::format("%sAtkEnd",plantName.c_str());
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