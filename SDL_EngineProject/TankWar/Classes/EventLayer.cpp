#include "EventLayer.h"
#include "GameScene.h"
#include "StaticData.h"

KeyboardEventLayer::KeyboardEventLayer()
{
}

KeyboardEventLayer::~KeyboardEventLayer()
{
}

bool KeyboardEventLayer::init()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = SDL_CALLBACK_2(KeyboardEventLayer::onKeyPressed, this);
	listener->onKeyReleased = SDL_CALLBACK_2(KeyboardEventLayer::onKeyReleased, this);
	//添加到监听器
	_eventDispatcher->addEventListener(listener, this);

	return true;
}

void KeyboardEventLayer::update(float dt)
{
	Direction dir = Direction::Unknown;
	//获取最新按下的按键
	for (auto it = m_keyStates.begin(); it != m_keyStates.end(); it++)
	{
		if (dir == Direction::Unknown)
			dir = it->first;
		else if (m_keyStates[dir] < it->second)
			dir = it->first;
	}
	//尝试移动
	if (dir != Direction::Unknown)
	{
		GameScene::getInstance()->moveBegin(dir);
	}
	else
	{
		//GameScene::getInstance()->moveEnd();
	}
}

void KeyboardEventLayer::onKeyPressed(SDL_Keycode keycode,SDL_Event*)
{
	//射击按键
	if (keycode == SDLK_SPACE)
	{
		GameScene::getInstance()->fire();
		return ;
	}
	//仅仅保存 方向键
	auto dir = this->getDirecton(keycode);

	if (dir != Direction::Unknown)
		m_keyStates[dir] = SDL_GetTicks();
}

void KeyboardEventLayer::onKeyReleased(SDL_Keycode keycode, SDL_Event*)
{
	auto dir = this->getDirecton(keycode);

	auto it = m_keyStates.find(dir);

	if (it != m_keyStates.end())
	{
		m_keyStates.erase(it);
	}
}

Direction KeyboardEventLayer::getDirecton(SDL_Keycode keycode)
{
	Direction dir = Direction::Unknown;

	if (keycode == SDLK_w)
		dir = Direction::Up;
	else if (keycode == SDLK_s)
		dir = Direction::Down;
	else if (keycode == SDLK_a)
		dir = Direction::Left;
	else if (keycode == SDLK_d)
		dir = Direction::Right;

	return dir;
}