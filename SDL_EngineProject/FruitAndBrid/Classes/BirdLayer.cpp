#include "BirdLayer.h"
#include "Bird.h"
BirdLayer::BirdLayer()
	:m_pBird(nullptr)
{
}
BirdLayer::~BirdLayer()
{
}
bool BirdLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_pBird = Bird::create(1);
	m_pBird->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(m_pBird);

	return true;
}
void BirdLayer::update(float dt)
{
	if(m_pBird->isFlying() == false)  
	{
		m_pBird->down(dt);
	}
}
void BirdLayer::birdFly(SDL_Keycode keyCode,SDL_Event*event)
{
	m_pBird->fly();
}
Bird*BirdLayer::getBird()
{
	return m_pBird;
}