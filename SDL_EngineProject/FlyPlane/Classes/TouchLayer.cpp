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
	//¼üÅÌÊÂ¼þ¼àÌý
	EventListenerKeyboard*listener = EventListenerKeyboard::create();
	listener->onKeyPressed = SDL_CALLBACK_2(TouchLayer::onKeyPressed,this);
	listener->onKeyReleased = SDL_CALLBACK_2(TouchLayer::onKeyReleased,this);
	_eventDispatcher->addEventListener(listener,this);
	
	return true;
}
void TouchLayer::setDelegate(TouchLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void TouchLayer::onKeyPressed(SDL_Keycode keycode,SDL_Event*event)
{
	m_pDelegate->onKeyPressed(keycode,event);
}
void TouchLayer::onKeyReleased(SDL_Keycode keycode,SDL_Event*event)
{
	m_pDelegate->onKeyReleased(keycode,event);
}