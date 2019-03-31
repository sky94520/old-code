#include "Cannon.h"
Cannon::Cannon()
	:m_kCannonType(kCannonType_1)
{
}
Cannon::~Cannon()
{
}
bool Cannon::init()
{
	bindSprite(Sprite::createWithSpriteFrameName("cannon_level_1.png"));
	return true;
}
void Cannon::aimAt(const Point&target)
{
	//设置朝向
	Point startPos = getWorldPosition();
	Point delta = startPos - target;
	float d = sqrt(pow(delta.x,2)+pow(delta.y,2));
	float radin = std::asin(delta.y/d);
	//设置角度
	float rotation = delta.x>=0?radin*180/PI - 90:fabs(radin*180/PI - 90);
	
	getSprite()->setRotation(rotation);
}
void Cannon::addLevel()
{
	//如果超出范围
	if(m_kCannonType == CannonType::kCannonType_7)
		setType(CannonType::kCannonType_1);
	else
		setType((CannonType)(m_kCannonType+1));
}
void Cannon::subLevel()
{
//如果超出范围
	if(m_kCannonType == CannonType::kCannonType_1)
		setType(CannonType::kCannonType_7);
	else
		setType((CannonType)(m_kCannonType-1));
}
CannonType Cannon::getCannonType()const
{
	return m_kCannonType;
}
float Cannon::getRouteDistance()const
{
	return 80 *(this->getCannonType());
}
void Cannon::setType(CannonType type)
{
	//修改类型
	m_kCannonType = type;
	//修改精灵
	auto text = StringUtils::format("cannon_level_%d.png",m_kCannonType);
	bindSprite(Sprite::createWithSpriteFrameName(text));
}