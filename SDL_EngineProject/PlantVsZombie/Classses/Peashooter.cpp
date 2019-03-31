#include "Peashooter.h"
#include "ZombieBase.h"

Peashooter::Peashooter()
{
}

Peashooter::~Peashooter()
{
}

Peashooter*Peashooter::create(const string&plantName)
{
	auto plant = new Peashooter();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Peashooter::init(const string&plantName)
{
	this->setPlantName(plantName);
	//设置正常动画
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);
	//运行动画
	this->bindSpriteWithAnimate(animate);

	return true;
}

void Peashooter::updateAttackState(float dt)
{
	int row = m_pCarrier->getRow();
	//发射子弹
	this->shootPeaBullet(row);
	//攻击结束，转到正常状态
	this->changeState(State::AttackEnd);
}

void Peashooter::updateAttackEndState(float dt)
{
	this->changeState(State::Normal);
}