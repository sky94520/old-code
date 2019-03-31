#include "FlyBehavior.h"
#include "Entity.h"

void SteadyFly::fly(Entity*entity)
{
	auto curAngle = entity->getSprite()->getRotation();
	//���ݽǶ���������ת
	//entity->getSprite()->setRotation(curAngle - 90.f);
	//�Ƕ�ת����
	float degree = 3.1415926/180 * curAngle;
	//��ȡx y�ϵķ���
	float x = cos(degree) * entity->getCurSpeed();
	float y = sin(degree) * entity->getCurSpeed();
	//������������
	Point curPos = entity->getPosition();
	entity->setPosition(curPos + Point(x,y));
}