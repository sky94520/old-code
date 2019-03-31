#include "BackgroundLayer.h"
BackgroundLayer::BackgroundLayer()
	:m_pBackground(nullptr)
{
}
BackgroundLayer::~BackgroundLayer()
{
}
bool BackgroundLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//±³¾°Í¼Æ¬
	m_pBackground = Sprite::create("bg1.jpg");
	m_pBackground->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(m_pBackground);
	return true;
}