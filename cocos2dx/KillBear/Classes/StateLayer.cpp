#include "StateLayer.h"
#include "Global.h"
#include "Hero.h"
StateLayer::StateLayer()
{
	Global::getInstance()->m_pStateLayer = this;
}
bool StateLayer::init()
{
	if(!cocos2d::Layer::init())
		return false;
	m_pHpBar = ui::LoadingBar::create("blood.png");
	
	m_pHpBar->setPercent(Global::getInstance()->m_pHero->getCurLifeValue());
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size hpBarSize = m_pHpBar->getContentSize();
	m_pHpBar->setPosition(Point(150,visibleSize.height - hpBarSize.height));

	Sprite*pHpBarBG = Sprite::create("bloodBg.png");
	pHpBarBG->setPosition(Point(150,visibleSize.height - hpBarSize.height));
	this->addChild(pHpBarBG);
	this->addChild(m_pHpBar);

	this->scheduleUpdate();
	return true;
}
void StateLayer::update(float dt)
{
	m_pHpBar->setPercent(Global::getInstance()->m_pHero->getCurLifeValue());
}