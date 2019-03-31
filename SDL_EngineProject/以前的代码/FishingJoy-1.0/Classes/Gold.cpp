#include "Gold.h"
Gold::Gold()
{
}
Gold::~Gold()
{
}
bool Gold::init()
{
	bindSprite(Sprite::createWithSpriteFrameName("coin_horizontal0.png"));
	auto anim = Entity::createAnimate("coin_horizontal%d.png",0,4,0.1f,-1);
	getSprite()->runAction(anim);
	return true;
}