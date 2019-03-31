#include "HelpfulFish.h"
#include "DynamicData.h"

HelpfulFish::HelpfulFish()
	:m_pRealSprite(nullptr),m_bCaught(false)
{
}
HelpfulFish::~HelpfulFish()
{
}
HelpfulFish*HelpfulFish::create(Fish*pFish)
{
	auto fish = new HelpfulFish();
	if(fish && fish->init(pFish))
		fish->autorelease();
	else
		CC_SAFE_DELETE(fish);
	return fish;
}
bool HelpfulFish::init(Fish*pFish)
{
	auto spriteFrame = pFish->getSprite()->getSpriteFrame();
	auto sprite = Sprite::createWithSpriteFrame(spriteFrame);
	
	bindSprite(sprite);

	m_pRealSprite = Sprite::createWithSpriteFrame(spriteFrame);
	//todo
	Point pos = Point::ZERO - DynamicData::getInstance()->getOffsetRefraction();

	Size s = this->getContentSize();

	pos += Point(s.width/2,s.height/2);

	m_pRealSprite->setPosition(pos);
	m_pRealSprite->setOpacity(100);

	this->addChild(m_pRealSprite);

	return true;
}
void HelpfulFish::runNormalAnimation(Fish*pFish)
{
	auto action1 = pFish->onNormalAnimation();
	auto action2 = pFish->onNormalAnimation();

	this->getSprite()->runAction(action1);

	m_pRealSprite->runAction(action2);
}
float HelpfulFish::runDeadAnimation(Fish*pFish)
{
	auto action1 = pFish->onCaughtAnimation();
	auto action2 = pFish->onCaughtAnimation();

	this->getSprite()->stopAllActions();
	this->getSprite()->runAction(action1);
	//
	m_pRealSprite->stopAllActions();
	m_pRealSprite->runAction(action2);

	return action1->getDuration();
}
void HelpfulFish::updateSpriteStatus(Fish*pFish)
{
	this->getSprite()->setFlippedX(pFish->getSprite()->isFlippedX());
	m_pRealSprite->setFlippedX(pFish->getSprite()->isFlippedX());
}