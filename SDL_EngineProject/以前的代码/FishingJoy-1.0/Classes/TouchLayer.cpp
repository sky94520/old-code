#include "TouchLayer.h"
TouchLayer::TouchLayer()
	:m_pDelegate(nullptr)
{
}
TouchLayer::~TouchLayer()
{
	//ע��������
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
	Point target = touch->getLocation();
	Rect rect=Rect(0,288,600,72);
	//���������棬����CannonLayer
	if(!rect.containsPoint(target))
		m_pDelegate->cannonAimAt(target);
	//�������Ĳ��Ǻ��棬����BulletChooseLayer
	else
		m_pDelegate->chooseBullet(target);
	return false;
}
void TouchLayer::onTouchMoved(Touch*touch,SDL_Event*event)
{
	Point target = touch->getLocation();
	Rect rect=Rect(0,288,600,72);
	//���������棬����CannonLayer
	if(!rect.containsPoint(target))
		m_pDelegate->cannonAimAt(target);
}
void TouchLayer::onTouchEnded(Touch*touch,SDL_Event*event)
{
	Point target = touch->getLocation();
	Rect rect=Rect(0,288,600,72);
	//���������棬����CannonLayer
	if(!rect.containsPoint(target))
		m_pDelegate->cannonShootTo(target);
}