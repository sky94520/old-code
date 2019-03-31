#include "TouchLayer.h"
TouchLayer::TouchLayer()
	:m_pDelegate(nullptr)
{
}
TouchLayer::~TouchLayer()
{
	//注销监听器
	_eventDispatcher->removeEventListenerForTarget(this);
}
bool TouchLayer::init()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = SDL_CALLBACK_2(TouchLayer::onTouchBegan,this);
	listener->onTouchMoved = SDL_CALLBACK_2(TouchLayer::onTouchMoved,this);
	listener->onTouchEnded = SDL_CALLBACK_2(TouchLayer::onTouchEnded,this);
	_eventDispatcher->addEventListener(listener,this);
	return true;
}
void TouchLayer::setDelegate(TouchLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
bool TouchLayer::onTouchBegan(Touch*touch,SDL_Event*event)
{
	auto pos = touch->getLocation();
	//点击了太阳
	if(m_pDelegate->clickSunshine(pos))
		return false;
	//如果点击了种子包
	if(m_pDelegate->clickSeed(pos))
		return true;
	//点击了铲子
	if(m_pDelegate->clickShovel(pos))
		return false;
	//点击地面
	m_pDelegate->clickGround(pos);
	return false;
}
void TouchLayer::onTouchMoved(Touch*touch,SDL_Event*event)
{
}
void TouchLayer::onTouchEnded(Touch*touch,SDL_Event*event)
{
}