#include "KeyboardLayer.h"
KeyboardLayer::KeyboardLayer()
	:m_pDelegate(nullptr)
{
}
KeyboardLayer::~KeyboardLayer()
{
}
bool KeyboardLayer::init()
{
/*	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = SDL_CALLBACK_2(KeyboardLayer::onKeyPressed,this);
	listener->onKeyReleased = SDL_CALLBACK_2(KeyboardLayer::onKeyReleased,this);
	_eventDispatcher->addEventListener(listener,this);*/
	auto listener = EventListenerKeyboardState::create();
	listener->onEvent = SDL_CALLBACK_2(KeyboardLayer::onEvent,this);
	_eventDispatcher->addEventListener(listener,this);

	return true;
}
void KeyboardLayer::onEvent(const Uint8*keyStates,SDL_Event*event)
{
	Point velocity;

	if(keyStates[SDL_SCANCODE_LEFT])
		velocity.x -= 1.f;
	if(keyStates[SDL_SCANCODE_RIGHT])
		velocity.x += 1.f;
	if(keyStates[SDL_SCANCODE_UP])
		velocity.y -= 1.f;
	if(keyStates[SDL_SCANCODE_DOWN])
		velocity.y += 1.f;
	m_pDelegate->playerMove(velocity);

	if(keyStates[SDL_SCANCODE_1])
		m_pDelegate->playerWantShooting();
}
void KeyboardLayer::onKeyPressed(SDL_Keycode keycode,SDL_Event*event)
{
	if(keycode ==SDLK_UP)
		m_velocity.y = -1.f;
	if(keycode == SDLK_DOWN)
		m_velocity.y = 1.f;
	if(keycode == SDLK_LEFT)
		m_velocity.x = -1.f;
	if(keycode == SDLK_RIGHT)
		m_velocity.x = 1.f;

	if(!m_velocity.equals(Point::ZERO))
		m_pDelegate->playerMove(m_velocity);

	if(keycode == SDLK_SPACE)
		m_pDelegate->playerWantShooting();
}
void KeyboardLayer::onKeyReleased(SDL_Keycode keycode,SDL_Event*event)
{
	if(keycode == SDLK_UP)
		m_velocity.y += 1.f;
	if(keycode == SDLK_DOWN)
		m_velocity.y -= 1.f;
	if(keycode == SDLK_LEFT)
		m_velocity.x += 1.f;
	if(keycode == SDLK_RIGHT)
		m_velocity.x -= 1.f;

	m_pDelegate->playerMove(m_velocity);
}
void KeyboardLayer::setDelegate(EventDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}