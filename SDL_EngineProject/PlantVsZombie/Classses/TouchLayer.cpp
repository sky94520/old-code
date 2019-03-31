#include "TouchLayer.h"
#include "GameScene.h"

TouchLayer::TouchLayer()
	:m_pDelegate(nullptr)
{
}
TouchLayer::~TouchLayer()
{
	//×¢Ïú¼àÌýÆ÷
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

void TouchLayer::setDelegate(TouchLayerDelegate* delegate)
{
	m_pDelegate = delegate;
}

bool TouchLayer::onTouchBegan(Touch*touch,SDL_Event*event)
{
	auto state = m_pDelegate->getGameState();
	bool ret = false;

	switch (state)
	{
	case GameState::Play:
		{
			ret = m_pDelegate->touchBeganOfPlayState(touch,event);
		}break;
	case GameState::CardChoose:
		{
			ret = m_pDelegate->touchBeganOfCardChooseState(touch,event);
		}break;
	}

	return ret;
}
void TouchLayer::onTouchMoved(Touch*touch,SDL_Event*event)
{
	auto state = m_pDelegate->getGameState();

	switch (state)
	{
	case GameState::Play:
		{
			m_pDelegate->touchMovedOfPlayState(touch,event);
		}break;
	case GameState::CardChoose:
		{
			m_pDelegate->touchMovedOfCardChooseState(touch,event);
		}break;
	}
}
void TouchLayer::onTouchEnded(Touch*touch,SDL_Event*event)
{
	auto state = m_pDelegate->getGameState();

	switch (state)
	{
	case GameState::Play:
		{
			m_pDelegate->touchEndedOfPlayState(touch,event);
		}break;
	case GameState::CardChoose:
		{
			m_pDelegate->touchEndedOfCardChooseState(touch,event);
		}break;
	}
}