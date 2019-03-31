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
	//¼ÓÔØ±³¾°
	m_pBackground = Sprite::create("background.png");
	this->addChild(m_pBackground);
	return true;
}