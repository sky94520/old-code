#include "FlyBehavior.h"
#include "Entity.h"

void SteadyFly::fly(Entity*entity)
{
	auto curAngle = entity->getSprite()->getRotation();
	//根据角度来进行旋转
	//entity->getSprite()->setRotation(curAngle - 90.f);
	//角度转弧度
	float degree = 3.1415926/180 * curAngle;
	//获取x y上的分量
	float x = cos(degree) * entity->getCurSpeed();
	float y = sin(degree) * entity->getCurSpeed();
	//进行坐标运算
	Point curPos = entity->getPosition();
	entity->setPosition(curPos + Point(x,y));
}