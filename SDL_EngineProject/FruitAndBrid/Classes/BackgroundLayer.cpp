#include "BackgroundLayer.h"
BackgroundLayer::BackgroundLayer()
	:m_pSprite1(nullptr),
	m_pSprite2(nullptr),m_speed(1.f)
{
}
BackgroundLayer::~BackgroundLayer()
{
}
bool BackgroundLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//随机加载资源
	//背景
	int i = rand();
	if(i % 2 == 0)
	{
		m_pSprite1 = Sprite::create("pic/morning.png");
		m_pSprite2 = Sprite::create("pic/morning.png");
	}
	else
	{
		m_pSprite1 = Sprite::create("pic/night.png");
		m_pSprite2 = Sprite::create("pic/night.png");

	}
	m_pSprite2->setPosition(visibleSize.width,0);
	this->addChild(m_pSprite1);
	this->addChild(m_pSprite2);

	return true;
}
void BackgroundLayer::update(float dt)
{
	float x1 = m_pSprite1->getPositionX();
	float x2 = m_pSprite2->getPositionX();

	x1 -= m_speed;
	x2 -= m_speed;

	Size size = m_pSprite1->getContentSize();
	//如果第一个地图到达边界，
	if(x1 <= -size.width)
	{
		x1 = size.width;
	}
	else if(x2 <= -size.width)
	{
		x2 = size.width;
	}
	m_pSprite1->setPositionX(x1);
	m_pSprite2->setPositionX(x2);
}