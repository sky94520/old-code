#include "Terrain.h"
#include "Plant.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

bool Terrain::init()
{
	return true;
}

//-----------------------------Lawn--------------------------
bool Lawn::init()
{
	return true;
}

void Lawn::destroyByDoomShroom()
{
	//运行动画TODO
	Animation*animation = AnimationCache::getInstance()->getAnimation("crater11");
	Animate*animate = Animate::create(animation);
	//滞后加载
	if (this->getSprite() == nullptr)
	{
		this->bindSpriteWithAnimate(animate);
	}
	else
	{
		this->getSprite()->runAction(animate);
	}
	//设置当前地形不可用
	this->setDestroyed(true);
	this->getSprite()->setVisible(true);
	//在动画运行之后土地可用
	DelayTime*delayTime = DelayTime::create(animation->getDuration());
	CallFunc*end = CallFunc::create([this]()
	{
		this->setDestroyed(false);
		//设置内部精灵不可见
		this->getSprite()->setVisible(false);
	});
	auto seq = Sequence::createWithTwoActions(delayTime,end);

	this->runAction(seq);
}