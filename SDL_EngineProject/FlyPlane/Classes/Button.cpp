#include "Button.h"
Button::Button()
	:m_pNormalSprite(nullptr),m_pSelectedSprite(nullptr)
	,m_callback(nullptr),m_fingerId(-1)
{
}
Button::~Button()
{
}
Button*Button::create(Sprite*normalSprite,Sprite*selectedSprite)
{
	auto button = new Button();
	if(button && button->init(normalSprite,selectedSprite))
		button->autoRelease();
	else
		SDL_SAFE_DELETE(button);
	return button;
}
bool Button::init(Sprite*normalSprite,Sprite*selectedSprite)
{
	m_pNormalSprite = normalSprite;
	m_pSelectedSprite = selectedSprite;
	
	Size size = m_pNormalSprite->getContentSize();
	this->setContentSize(size);

	m_pNormalSprite->setPosition(size.width/2,size.height/2);

	m_pSelectedSprite->setPosition(size.width/2,size.height/2);
	m_pSelectedSprite->setVisible(false);

	this->addChild(m_pNormalSprite);
	this->addChild(m_pSelectedSprite);

	return true;
}
void Button::setCallback(const ccMenuCallback&callback)
{
	m_callback = callback;
}
void Button::selected()
{
	m_pNormalSprite->setVisible(false);
	m_pSelectedSprite->setVisible(true);
}
void Button::unselected()
{
	m_pNormalSprite->setVisible(true);
	m_pSelectedSprite->setVisible(false);

	m_fingerId = -1;
}
void Button::activate()
{
	if(m_callback)
		m_callback(this);
}