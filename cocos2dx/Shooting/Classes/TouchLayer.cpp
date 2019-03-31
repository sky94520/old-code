#include "TouchLayer.h"
TouchLayer::TouchLayer()
	:m_pDelegate(nullptr)
{
}
TouchLayer::~TouchLayer()
{
	//×¢Ïú¼àÌýÆ÷
	_eventDispatcher->removeEventListenersForTarget(this);
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
void TouchLayer::setDelegate(TouchLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
bool TouchLayer::onTouchBegan(Touch*touch,Event*event)
{
	Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
	m_pDelegate->arrowAimAt(pos);
	return true;
}
void TouchLayer::onTouchMoved(Touch*touch,Event*event)
{
	Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
	m_pDelegate->arrowAimAt(pos);
}
void TouchLayer::onTouchEnded(Touch*touch,Event*event)
{
	Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
	m_pDelegate->arrowShootTo(pos);
}