#include "VirtualStick.h"
VirtualStick::VirtualStick()
	:m_pStick(nullptr),m_pStickBackground(nullptr)
	,m_fingerId(-1)
{
}
VirtualStick::~VirtualStick()
{
}
VirtualStick*VirtualStick::create(Sprite*stick,Sprite*bg)
{
	auto s = new VirtualStick();
	if(s && s->init(stick,bg))
		s->autoRelease();
	else
		SDL_SAFE_DELETE(s);
	return s;
}
bool VirtualStick::init(Sprite*stick,Sprite*bg)
{
	m_pStick = stick;
	m_pStickBackground = bg;

	Size size = m_pStickBackground->getContentSize();

	m_pStick->setPosition(size.width*0.5f,size.height*0.5f);
	m_pStickBackground->setPosition(size.width*0.5f,size.height*0.5f);

	this->addChild(m_pStick);
	this->addChild(m_pStickBackground);

	this->setContentSize(size);

	return true;
}
void VirtualStick::selected(const Point&pos)
{
	Point nodePoint = this->convertToNodeSpace(pos);
	//²»³ö½ç
	float r = m_pStickBackground->getContentSize().width/2;
	Point startPos = m_pStickBackground->getPosition();
	auto delta = nodePoint - startPos;
	float degree = SDL_atan2(delta.y,delta.x);

	if(delta.length() <= r)
	{
		m_pStick->setPosition(nodePoint);
	}
	else
	{
		float deltaX =  r * SDL_cosf(degree);
		float deltaY = r*SDL_sinf(degree);

		Point endPos = Point(startPos.x+deltaX,startPos.y+deltaY);
		m_pStick->setPosition(endPos);
	}
}
Point VirtualStick::getDirection()
{
	float r = m_pStickBackground->getContentSize().width/2;
	Point point1 = m_pStick->getPosition();
	Point point2 = m_pStickBackground->getPosition();
	Point delta = point1 - point2;

	return Point(delta.x/r,delta.y/r);
}
void VirtualStick::unselected()
{
	m_fingerId = -1;
	m_pStick->setPosition(m_pStickBackground->getPosition());
}
