#include "LilyPad.h"
#include "Carrier.h"

LilyPad::LilyPad()
{
}

LilyPad::~LilyPad()
{
}

LilyPad*LilyPad::create(const string&plantName)
{
	auto plant = new LilyPad();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool LilyPad::init(const string&plantName)
{
	if (VesselPlant::init(TerrainType::LilyPad))
	{
		this->setPlantName(plantName);
		//设置正常动画
		auto animationName = plantName;
		auto animation = AnimationCache::getInstance()->getAnimation(animationName);
		Animate*animate = Animate::create(animation);

		this->bindSpriteWithAnimate(animate);

		return true;
	}
	return false;
}

void LilyPad::updateHook(float dt)
{
}
