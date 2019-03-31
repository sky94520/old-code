#include "Plant.h"

Plant::Plant()
	:m_fColdDownTime(0.f)
	,m_activeTime(ActiveTime::All),m_pDelegate(nullptr)
	,m_plantType(PlantType::Common),m_pVesselPlant(nullptr)
	,m_pCarrier(nullptr)
{
	this->setCharacterType(CharacterType::Plant);
}

Plant::~Plant()
{
}

void Plant::setDelegate(PlantDelegate*delegate)
{
	m_pDelegate = delegate;
}

void Plant::hurt(int damage,AttackType attackType)
{
	auto afterHP = m_nHitPoint - damage;

	if (afterHP <= 0)
	{
		afterHP = 0;
		m_bDead = true;
	}
	this->setHitPoint(afterHP);

	onHurt();
}

void Plant::setLocatedCarrier(Carrier*carrier)
{
	m_pCarrier = carrier;
}

Carrier*Plant::getLocatedCarrier()
{
	return m_pCarrier;
}

int Plant::getRow()const
{
	return m_pCarrier->getRow();
}

void Plant::update(float dt)
{
	updateHook(dt);
	//保卫者不跟随移动 跟随容器植物运动
	if (this->getPlantType() != PlantType::Defender
		&& m_pVesselPlant != nullptr)
	{
		auto pos = m_pVesselPlant->getPosition();
		auto size = m_pVesselPlant->getContentSize();

		this->setPosition(pos + Point(0,-size.height/2));
	}
}

void Plant::onHurt()
{
/*	auto sprite = this->getSprite();
	//使植物的身体变白
	sprite->setColorMod(Color3B(215,215,215));
	//在一定时间后还原
	DelayTime*delayTime = DelayTime::create(0.15f);
	CallFunc*end = CallFunc::create([sprite]()
	{
		sprite->setColorMod(Color3B(255,255,255));
	});

	auto seq = Sequence::createWithTwoActions(delayTime,end);
	sprite->runAction(seq);*/
}

void Plant::eatenByZombie(ZombieBase*zombie)
{
}

Rect Plant::getCollisionBoundingBox()const
{
	Rect rect = this->getSprite()->getSpriteFrameRect();
	//进行x y坐标的更新
	auto r = this->getBoundingBox();

	rect.origin.x += r.origin.x;
	rect.origin.y += r.origin.y;

	return rect;
}

void Plant::setVesselPlant(Plant*plant)
{
	m_pVesselPlant = plant;
}

Plant*Plant::getVesselPlant()const
{
	return m_pVesselPlant;
}