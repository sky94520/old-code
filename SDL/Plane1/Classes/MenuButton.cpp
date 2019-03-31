#include "MenuButton.h"

MenuButton::MenuButton()
:ShooterObject()
{
	m_currentFrame = MOUSE_OUT;//start at frame 0
}
void MenuButton::load(std::unique_ptr<LoaderParams> const&pParams)
{
    ShooterObject::load(pParams);

    LoaderParams*p = pParams.get();
    m_callbackID = p->getCallbackID();
    m_currentFrame = MOUSE_OUT;
}
void MenuButton::draw()
{
    TheTextureManager::Instance()->drawFrame(m_textureID,m_position.getX(),m_position.getY(),m_width,m_height,m_currentRow,m_currentFrame,m_angle,m_alpha);
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
		if (TheInputHandle::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_callback();
			m_bReleased = false;
		}
		else if(!TheInputHandle::Instance()->getMouseButtonState(LEFT))
		{
		    m_bReleased = true;
		    m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}
void MenuButton::clean()
{
	ShooterObject::clean();
}

