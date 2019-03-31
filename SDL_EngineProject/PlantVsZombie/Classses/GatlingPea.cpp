#include "GatlingPea.h"

GatlingPea *GatlingPea::create(const string& plantName)
{
	auto plant = new GatlingPea();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool GatlingPea::init(const string& plantName)
{
	m_plantName = plantName;

	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	this->bindSpriteWithAnimate(animate);

	return true;
}