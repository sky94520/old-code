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
	//Ìí¼Ó´¥Åö¼àÌýÆ÷
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(TouchLayer::onTouchesBegan,this);
	listener->onTouchesMoved = CC_CALLBACK_2(TouchLayer::onTouchesMoved,this);
	listener->onTouchesEnded = CC_CALLBACK_2(TouchLayer::onTouchesEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	//mouse
	auto listener2 = EventListenerMouse::create();
	listener2->onMouseScroll = CC_CALLBACK_1(TouchLayer::onMouseScroll,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2,this);

	return true;
}
void TouchLayer::setDelegate(TouchLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void TouchLayer::onTouchesBegan(const std::vector<Touch*>&touches,Event*event)
{
	
}
void TouchLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
	m_pDelegate->operateBackground(touches,event);
}
void TouchLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
}
void TouchLayer::onMouseScroll(EventMouse*event)
{
	m_pDelegate->setScaleForBackground(event);
}