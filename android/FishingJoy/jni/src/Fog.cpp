#include "Fog.h"
#include "Fish.h"
#include "StaticData.h"

Fog::Fog()
	:m_pFish(nullptr)
{
}

Fog::~Fog()
{
	_eventDispatcher->removeEventListenerForTarget(this);
}

Fog*Fog::create(Fish*fish)
{
	auto fog = new Fog();

	if(fog && fog->init(fish))
		fog->autoRelease();
	else
		SDL_SAFE_DELETE(fog);

	return fog;
}

bool Fog::init(Fish*fish)
{
	//�󶨾���
	auto spriteName = STATIC_DATA_STRING("fog_sprite_name");
	this->bindSpriteWithSpriteFrameName(spriteName);
	//������������
	auto animationName = STATIC_DATA_STRING("fog_run_anim_name");
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);

	this->getSprite()->runAction(animate);

	m_pFish = fish;

	//����Ϣ
	auto uniqueID = StringUtils::toString(fish->getUniqueID());

	_eventDispatcher->addEventCustomListener(uniqueID,SDL_CALLBACK_1(Fog::fishDeadCallback,this),this);

	return true;
}

void Fog::update(float dt)
{
	auto pos = m_pFish->getPosition();
	//�����ͼƬ�й�
	auto rotation = m_pFish->getSprite()->getRotation();

	this->setPosition(pos);
	this->getSprite()->setRotation(rotation);
}

float Fog::showAt()
{
	return 0.f;
}

void Fog::collided()
{
	//nothing to do
}

void Fog::fishDeadCallback(EventCustom*eventCutom)
{
	this->setActive(false);
	this->setDead(true);
}
