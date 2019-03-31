#include "SDLGameObject.h"
#pragma once
enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};
class MenuButton : public SDLGameObject
{
	public:

	MenuButton(const LoaderParams*pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
};
MenuButton::MenuButton(const LoaderParams*pPrams)
:SDLGameObject(pPrams)
{
	m_currentFrame = MOUSE_OUT;//start at frame 0
}
void MenuButton::draw()
{
	SDLGameObject::draw();
}
void MenuButton::update()
{
	Vector2D*pMousePos = TheInputHandle::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width)
	&& pMousePos->getX() > m_position.getX()
	&& pMousePos->getY() < (m_position.getY() + m_height)
	&& pMousePos->getY() > m_position.getY()
	)
	{
		m_currentFrame = MOUSE_OVER;

		if (TheInputHandle::Instance()->getMouseButtonState(LEFT))
		{
			m_currentFrame = CLICKED;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}
void MenuButton::clean()
{
	SDLGameObject::clean();
}
