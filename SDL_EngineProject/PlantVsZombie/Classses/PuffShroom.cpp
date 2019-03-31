#include "PuffShroom.h"

PuffShroom::PuffShroom()
{
}

PuffShroom::~PuffShroom()
{
}

PuffShroom*PuffShroom::create(const string& plantName)
{
	auto plant = new PuffShroom();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool PuffShroom::init(const string& plantName)
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

void PuffShroom::updateAtkState(float dt)
{
	int damage = this->getDamage();
	int row = m_pCarrier->getRow();
	//确定出生位置
	auto bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/2;
	bornPos.y += size.height/4;
	//直接进行攻击
	m_pDelegate->addShroomBullet(damage,row,bornPos,this->getAttackScope());
	//攻击结束
	this->changeState(State::Normal);
}

void PuffShroom::changeState(State state)
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
	if (animation == nullptr)
		return;
	//停止原先的动画
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//创建动画
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}