#include "ScaredyShroom.h"
#include "ZombieBase.h"

ScaredyShroom::ScaredyShroom()
	:m_state(State::Normal),m_elapsed(0.f)
	,m_nDamage(0)
{
}

ScaredyShroom*ScaredyShroom::create(const string&plantName)
{
	auto plant = new ScaredyShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool ScaredyShroom::init(const string& plantName)
{
	//设置正常的动画
	this->setPlantName(plantName);
	//设置正常动画
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);
	
	this->bindSpriteWithAnimate(animate);
	//设置状态为正常状态
	m_state = State::Normal;

	return true;
}

void ScaredyShroom::updateNotSleeping(float dt)
{
	if (m_state == State::Normal)
	{
		this->updateNormalState(dt);
	}
	else if (m_state == State::Attack)
	{
		this->updateAtkState(dt);
	}
	else if (m_state == State::Scared)
	{
		this->updateScaredState(dt);
	}
}

void ScaredyShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void ScaredyShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void ScaredyShroom::updateAtkState(float dt)
{
	int damage = this->getDamage();
	int row = m_pCarrier->getRow();
	//确定出生位置
	auto bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/2;
	bornPos.y += size.height/5;
	//直接进行攻击
	m_pDelegate->addShroomBullet(damage,row,bornPos,-1.f);
	//攻击结束
	this->changeState(State::Normal);
}

void ScaredyShroom::changeState(State state)
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
	else if (state == State::Scared)
	{
		animationName = StringUtils::format("%sCry",plantName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
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

void ScaredyShroom::updateNormalState(float dt)
{
	auto row = m_pCarrier->getRow();
	auto attackDir = this->getDir();
	auto pos = this->getPosition();
	//根据当前方向确定第一个僵尸
	auto zombie = m_pDelegate->findFirstZombieOfRow(row,attackDir,pos);

	if (zombie == nullptr)
		return;
	//发现僵尸回调函数 可能会进行害怕状态
	this->findZombie(zombie);

	m_elapsed += dt;
	//进行攻击
	if (m_elapsed >= this->getColdDownTime())
	{
		m_elapsed -= this->getColdDownTime();
		//转入攻击状态
		this->changeState(State::Attack);
	}
}

void ScaredyShroom::updateScaredState(float dt)
{
	auto row = m_pCarrier->getRow();
	auto attackDir = this->getDir();
	auto pos = this->getPosition();
	//根据当前方向确定第一个僵尸
	auto zombie = m_pDelegate->findFirstZombieOfRow(row,attackDir,pos);
	
	//当前僵尸为空或者距离很远，则退出害怕状态
	if (!isScared(zombie))
	{
		this->changeState(State::Normal);
	}
}

void ScaredyShroom::findZombie(ZombieBase*zombie)
{
	if (this->isScared(zombie))
	{
		this->changeState(State::Scared);
		//计时清空
		m_elapsed = 0.f;
	}
}

bool ScaredyShroom::isScared(ZombieBase*zombie)
{
	//不存在僵尸，不会害怕
	if (zombie == nullptr)
		return false;

	auto zombiePosX = zombie->getCollisionBoundingBox().origin.x;
	auto plantPosX = this->getPositionX();

	auto delta = SDL_fabs(plantPosX - zombiePosX);
	//和僵尸的距离很近，转入害怕状态
	if (delta < 60.f)
		return true;
	else
		return false;
}