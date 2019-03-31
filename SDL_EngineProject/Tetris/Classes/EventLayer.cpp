#include "EventLayer.h"
EventLayer::EventLayer()
	:m_pDelegate(nullptr),m_bActive(true)
	,m_elpased(0.f)
{
}
EventLayer::~EventLayer()
{
}
bool EventLayer::init()
{
	//Ìí¼ÓÊÂ¼þ¼àÌý
	EventListenerKeyboard*keyBoard = EventListenerKeyboard::create();
	keyBoard->onKeyPressed = SDL_CALLBACK_2(EventLayer::onKeyPressed,this);
	_eventDispatcher->addEventListener(keyBoard,this);

	EventListenerTouchOneByOne*listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = SDL_CALLBACK_2(EventLayer::onTouchBegan,this);
	listener2->onTouchMoved = SDL_CALLBACK_2(EventLayer::onTouchMoved,this);
	listener2->onTouchEnded = SDL_CALLBACK_2(EventLayer::onTouchEnded,this);
	_eventDispatcher->addEventListener(listener2,this);
	return true;
}
void EventLayer::onKeyPressed(SDL_Keycode keyCode,SDL_Event*event)
{
	m_pDelegate->onKeyPressed(keyCode,event);
}
bool EventLayer::onTouchBegan(Touch*,SDL_Event*event)
{
	return false;
}
void EventLayer::onTouchMoved(Touch*touch,SDL_Event*event)
{
	if(m_elpased < 0.1f)
		return;
	m_elpased = 0.f;
	SDL_Keycode kyecode = SDLK_UNKNOWN;
	float xrel = touch->getDelta().x;
	float yrel = touch->getDelta().y;

	if(abs(xrel) > abs(yrel))
	{
		if(xrel > 0)
			kyecode = SDLK_RIGHT;
		else if(xrel < 0)
			kyecode = SDLK_LEFT;
	}
	else
	{
		if(yrel > 3)
			kyecode = SDLK_DOWN;
	}
	//printf("%.2f\n",yrel);
	if(kyecode == SDLK_UNKNOWN)
		return;
	m_bActive = false;
	this->onKeyPressed(kyecode,event);
}
void EventLayer::onTouchEnded(Touch*,SDL_Event*event)
{
	if(m_bActive == true)
	{
		SDL_Keycode keyCode;
		keyCode = SDLK_UP;
		this->onKeyPressed(keyCode,event);
	}
	m_bActive = true;
}
void EventLayer::update(float dt)
{
	m_elpased += dt;
}
void EventLayer::setDelegate(EventLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
