#include "SnowPea.h"
#include "ZombieBase.h"

SnowPea::SnowPea()
{
}

SnowPea::~SnowPea()
{
}

SnowPea*SnowPea::create(const string&plantName)
{
	auto plant = new SnowPea();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool SnowPea::init(const string&plantName)
{
	this->setPlantName(plantName);
	//������������
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	Animate*animate = Animate::create(animation);
	this->bindSpriteWithAnimate(animate);

	return true;
}

void SnowPea::updateAttackState(float dt)
{
	int row = m_pCarrier->getRow();
	//���亮���㶹��
	this->shootSnowPea(row);
	//ת������״̬
	this->changeState(State::AttackEnd);
}

void SnowPea::updateAttackEndState(float dt)
{
	this->changeState(State::Normal);
}