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
	//��ӵ�������
	_eventDispatcher->addEventListener(listener, this);

	return true;
}

void KeyboardEventLayer::update(float dt)
{
	Direction dir = Direction::Unknown;
	//��ȡ���°��µİ���
	for (auto it = m_keyStates.begin(); it != m_keyStates.end(); it++)
	{
		if (dir == Direction::Unknown)
			dir = it->first;
		else if (m_keyStates[dir] < it->second)
			dir = it->first;
	}
	//�����ƶ�
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
	//�������
	if (keycode == SDLK_SPACE)
	{
		GameScene::getInstance()->fire();
		return ;
	}
	//�������� �����
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