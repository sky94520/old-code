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
	//���ý�ʬ����ɫ
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
	//Ѱ��Ŀ�꽩ʬ��������ZombieLayer
	//����ڲ���ʬ�Ƿ�����

}