#include "KeyEventLayer.h"
KeyEventLayer::KeyEventLayer()
	:m_pDelegate(nullptr)
{
}
KeyEventLayer::~KeyEventLayer()
{
}
bool KeyEventLayer::init()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = SDL_CALLBACK_1(KeyEventLayer::onKeyPressed,this);
	listener->onKeyReleased = SDL_CALLBACK_1(KeyEventLayer::onKeyReleased,this);
	_eventDispatcher->addEventListener(listener,this);
	
	return true;
}
void KeyEventLayer::setDelegate(EventLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void KeyEventLayer::onKeyPressed(SDL_Keycode keycode)
{
	EventType type = kEventType_None;
	if(keycode == SDLK_d)
	{
		type = kEventType_Right;
	}
	else if(keycode == SDLK_a)
	{
		type = kEventType_Left;
	}
	else if(keycode == SDLK_k)
	{
		type = kEventType_Shoot;
	}
	else if(keycode == SDLK_SPACE)
	{
		type = kEventType_Jump;
	}
	else if(keycode == SDLK_s)
	{
		type = kEventType_Down;
	}
	//发送事件
	m_pDelegate->keyPressed(type);
}
void KeyEventLayer::onKeyReleased(SDL_Keycode keycode)
{
	EventType type = kEventType_None;
	if(keycode == SDLK_d)
	{
		type = kEventType_Right;
	}
	else if(keycode == SDLK_a)
	{
		type = kEventType_Left;
	}
	else if(keycode == SDLK_k)
	{
		type = kEventType_Shoot;
	}
	else if(keycode == SDLK_SPACE)
	{
		type = kEventType_Jump;
	}
	else if(keycode == SDLK_s)
	{
		type = kEventType_Down;
	}
	//发送事件
	m_pDelegate->keyReleased(type);
}