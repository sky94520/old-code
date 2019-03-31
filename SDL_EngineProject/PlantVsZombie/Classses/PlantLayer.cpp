#include "PlantLayer.h"
#include "PlantFactory.h"
#include "SunFlower.h"
#include "FlowerPot.h"
#include "LilyPad.h"
#include "Chomper.h"
#include "Squash.h"
#include "Jalapeno.h"
#include "NameDef.h"
#include "Carrier.h"
#include "Peashooter.h"
#include "Repeater.h"
#include "Threepeater.h"
#include "GatlingPea.h"
#include "SplitPea.h"
#include "FirePeashooter.h"
#include "PotatoMine.h"
#include "Cabbage.h"
#include "WallNut.h"
#include "TallNut.h"
#include "SnowPea.h"
#include "FumeShroom.h"
#include "Cornpult.h"
#include "NightPlant.h"
#include "IceShroom.h"
#include "PuffShroom.h"
#include "SeaShroom.h"
#include "ScaredyShroom.h"
#include "DoomShroom.h"
#include "Magnetshroom.h"
#include "SunShroom.h"
#include "StaticData.h"
#include "Torchwood.h"
#include "ZombieBase.h"

PlantLayer::PlantLayer()
	:m_pPlantFactory(nullptr),m_pDelegate(nullptr)
{
}

PlantLayer::~PlantLayer()
{
	SDL_SAFE_RELEASE_NULL(m_pPlantFactory);
}

bool PlantLayer::init()
{
	m_pPlantFactory = PlantFactory::create();
	m_pPlantFactory->retain();

	return true;
}

void PlantLayer::update(float dt)
{
	for (auto it = m_plants.begin();it != m_plants.end();)
	{
		auto plant = *it;
		//植物死亡，直接移除 TODO
		if (plant->isDead())
		{
			it = m_plants.erase(it);
			//从载体中移除自己
			auto carrier = plant->getLocatedCarrier();

			if (plant->getPlantType() == PlantType::Defender)
				carrier->clearDefender();
			else
				carrier->clearInnerPlant();
			//把当前植物从场景中删除
			plant->removeFromParent();
		}
		else
		{
			plant->update(dt);
			it++;
		}
	}
	//更新可移动植物
	for (auto it = m_movablePlants.begin(); it != m_movablePlants.end();)
	{
		auto character = *it;

		if (character->isDead())
		{
			it = m_movablePlants.erase(it);
			character->removeFromParent();
		}
		else
		{
			this->updateMovealbePlants(character,dt);
			it++;
		}
	}
}

Plant*PlantLayer::makePlant(const string&name)
{
	Plant*plant = this->createPlant(name);

	if (plant != nullptr)
	{
		m_plants.push_back(plant);
	}
	return plant;
}

bool PlantLayer::removePlant(Plant*plant)
{
	auto it = find(m_plants.begin(),m_plants.end(),plant);

	if (it != m_plants.end())
	{
		m_plants.erase(it);
		return true;
	}
	return false;
}

void PlantLayer::addItemToMovablePlants(Character*character)
{
	m_movablePlants.push_back(character);
}

vector<Character*>& PlantLayer::getMovablePlantList()
{
	return m_movablePlants;
}

void PlantLayer::setDelegate(PlantLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

bool PlantLayer::isTallNut(Plant*plant)
{
	auto plantName = plant->getPlantName();

	return plantName == TALLNUT_NAME;
}

bool PlantLayer::isActiveTimeForPlant(Plant*plant,ActiveTime activeTime)
{
	auto plantActiveTime = plant->getActiveTime();

	//当前活动类型是All，则在任何时间都行
	if (plantActiveTime == ActiveTime::All)
		return true;
	else if (plantActiveTime == activeTime)
		return true;

	return false;
}

Plant*PlantLayer::createPlant(const string&name)
{
	Plant*plant = m_pPlantFactory->makePlant(name);


	if (name == LILYPAD_NAME)
	{
		//对莲叶添加一个上下浮动的效果
		MoveBy*move1 = MoveBy::create(1.f,Point(0.f,5.f));
		MoveBy*move2 = MoveBy::create(1.f,Point(0.f,-5.f));

		auto seq = Sequence::createWithTwoActions(move1,move2);
		RepeatForever*repeat = RepeatForever::create(seq);

		plant->runAction(repeat);
	}

	return plant;
}

void PlantLayer::updateMovealbePlants(Character*character,float dt)
{
	auto type = character->getCharacterType();

	switch (type)
	{
	case CharacterType::Zombie:
		{
			this->zombieUpdate(static_cast<ZombieBase*>(character),dt);
		}break;
	default:break;
	}
}

void PlantLayer::zombieUpdate(ZombieBase*zombie,float dt)
{
	//僵尸死亡或者当前已经有目标，则不进行更新
	if (zombie->isDying())
	{
		return;
	}
	int row = zombie->getRow();
	//auto dir = zombie->getDir();
	auto boundingBox = zombie->getCollisionBoundingBox();

	auto target = m_pDelegate->findFirstCollidedZombie(row,boundingBox);

	if (target != nullptr)
	{
		zombie->setAim(target);
	}
	else
	{
		zombie->clearAim();
	}
	zombie->update(dt);
}
