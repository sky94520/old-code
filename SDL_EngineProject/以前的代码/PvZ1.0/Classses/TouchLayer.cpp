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
	auto pos = touch->getLocation();
	//�����̫��
	if(m_pDelegate->clickSunshine(pos))
		return false;
	//�����������Ӱ�
	if(m_pDelegate->clickSeed(pos))
		return true;
	//����˲���
	if(m_pDelegate->clickShovel(pos))
		return false;
	//�������
	m_pDelegate->clickGround(pos);
	return false;
}
void TouchLayer::onTouchMoved(Touch*touch,SDL_Event*event)
{
}
void TouchLayer::onTouchEnded(Touch*touch,SDL_Event*event)
{
}