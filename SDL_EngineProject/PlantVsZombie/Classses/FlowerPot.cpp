#include "FlowerPot.h"
#include "Carrier.h"

FlowerPot::FlowerPot()
{
}

FlowerPot::~FlowerPot()
{
}

FlowerPot*FlowerPot::create(const string&plantName)
{
	auto plant = new FlowerPot();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool FlowerPot::init(const string&plantName)
{
	if (VesselPlant::init(TerrainType::FlowerPot))
	{
		this->setPlantName(plantName);
		//设置正常动画
		auto animationName = plantName;
		auto animation = AnimationCache::getInstance()->getAnimation(animationName);
		auto animate = Animate::create(animation);

		this->bindSpriteWithAnimate(animate);

		return true;
	}
	return false;
}

void FlowerPot::updateHook(float dt)
{
}