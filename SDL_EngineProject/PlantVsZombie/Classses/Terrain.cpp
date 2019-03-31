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
	//���ж���TODO
	Animation*animation = AnimationCache::getInstance()->getAnimation("crater11");
	Animate*animate = Animate::create(animation);
	//�ͺ����
	if (this->getSprite() == nullptr)
	{
		this->bindSpriteWithAnimate(animate);
	}
	else
	{
		this->getSprite()->runAction(animate);
	}
	//���õ�ǰ���β�����
	this->setDestroyed(true);
	this->getSprite()->setVisible(true);
	//�ڶ�������֮�����ؿ���
	DelayTime*delayTime = DelayTime::create(animation->getDuration());
	CallFunc*end = CallFunc::create([this]()
	{
		this->setDestroyed(false);
		//�����ڲ����鲻�ɼ�
		this->getSprite()->setVisible(false);
	});
	auto seq = Sequence::createWithTwoActions(delayTime,end);

	this->runAction(seq);
}