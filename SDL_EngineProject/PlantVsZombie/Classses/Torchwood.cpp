#include "Torchwood.h"
#include "ShooterPeaBullet.h"

Torchwood*Torchwood::create(const string& plantName)
{
	auto plant = new Torchwood();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Torchwood::init(const string& plantName)
{
	this->setPlantName(plantName);

	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	animate->setTag(ANIMATION_TAG);
	//�󶨾���
	this->bindSpriteWithAnimate(animate);

	return true;
}

void Torchwood::updateHook(float dt)
{
	int row = this->getRow();
	auto rect = this->getCollisionBoundingBox();

	auto bullet = m_pDelegate->findFirstShooterPeaBullet(row,rect);
	//���ڸ��ӵ��������ת��
	if (bullet != nullptr)
	{
		auto type = bullet->getShooterPeaBulletType();

		if (type == ShooterPeaBullet::Type::PeaBullet)
		{
			bullet->transformType(ShooterPeaBullet::Type::FirePeaBullet);
			//���ò���ת��
			bullet->setCanTransform(false);
		}
		else if (type == ShooterPeaBullet::Type::SnowPeaBullet)
		{
			bullet->transformType(ShooterPeaBullet::Type::PeaBullet);
			//���ò���ת��
			bullet->setCanTransform(false);
		}
	}
}