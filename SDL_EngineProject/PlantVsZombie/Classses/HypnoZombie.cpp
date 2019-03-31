#include "HypnoZombie.h"
#include "ZombieBase.h"

HypnoZombie::HypnoZombie()
	:m_pInnerZombie(nullptr)
{
}

HypnoZombie::~HypnoZombie()
{
}

HypnoZombie* HypnoZombie::create(ZombieBase* zombie)
{
	auto plant = new HypnoZombie();

	if (plant && plant->init(zombie))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool HypnoZombie::init(ZombieBase* zombie)
{
	
	m_pInnerZombie = zombie;

	auto size = zombie->getContentSize();

	m_pInnerZombie->setPosition(size.width/2,size.height/2);
	//设置僵尸的颜色
	m_pInnerZombie->getSprite()->setColorMod(Color3B(255,255,0));

	this->setContentSize(size);
	this->addChild(m_pInnerZombie);

	return true;
}

Rect HypnoZombie::getCollisionBoundingBox()const
{
	auto rect = m_pInnerZombie->getCollisionBoundingBox();
	//TODO
	rect.origin = this->getParent()->convertToNodeSpace(rect.origin);

	return rect;
}

void HypnoZombie::updateHook(float dt)
{
	//寻找目标僵尸，类似于ZombieLayer
	//检测内部僵尸是否死亡

}