#include "TallNut.h"

TallNut::TallNut()
{
}

TallNut::~TallNut()
{
}

TallNut*TallNut::create(const string&plantName)
{
	auto plant = new TallNut();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool TallNut::init(const string&plantName)
{
	this->setPlantName(plantName);
	//设置正常动画
	auto animationName = plantName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);
	
	auto size = m_pSprite->getContentSize();
	//设置位置
	m_pSprite->setPosition(size.width/2.f,size.height/2.f);
	//设置锚点
	m_pSprite->setAnchorPoint(Point(0.5f,0.65f));

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//设置运行动画
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);
	this->getSprite()->runAction(animate);
	//设置当前状态
	m_state = State::Normal;

	return true;
}