#include "TouchLayer.h"
TouchLayer::TouchLayer()
	:m_pDelegate(nullptr)
{
}
TouchLayer::~TouchLayer()
{
}
bool TouchLayer::init()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
bool TouchLayer::onTouchBegan(Touch*touch,Event*event)
{
	Point pos = Director::getInstance()->convertToUI(touch->getLocationInView());
	m_pDelegate->shoot(pos);
	return false;
}
void TouchLayer::onTouchMoved(Touch*touch,Event*event)
{
}
void TouchLayer::onTouchEnded(Touch*touch,Event*event)
{

}
void TouchLayer::setDelegate(TouchLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}