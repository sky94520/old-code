#include "RotateWithAction.h"
#include "Entity.h"
RotateWithAction::RotateWithAction()
	:m_pInnerAction(nullptr)
{
}
RotateWithAction::~RotateWithAction()
{
	CC_SAFE_RELEASE(m_pInnerAction);
}
RotateWithAction*RotateWithAction::create(ActionInterval*pAction)
{
	auto action = new RotateWithAction();
	if(action && action->init(pAction))
		action->autorelease();
	else
		CC_SAFE_DELETE(action);
	return action;
}
bool RotateWithAction::init(ActionInterval*action)
{
	if(ActionInterval::initWithDuration(action->getDuration()))
	{
		action->retain();
		m_pInnerAction = action;
		return true;
	}
	return false;
}
void RotateWithAction::startWithTarget(Node*target)
{
	ActionInterval::startWithTarget(target);
	m_pInnerAction->startWithTarget(target);
}
bool RotateWithAction::isDone()const
{
	return m_pInnerAction->isDone();
}
void RotateWithAction::update(float time)
{
	Point prePos = _target->getPosition();
	m_pInnerAction->update(time);
	Point curPos = _target->getPosition();

	float tan = -(curPos.y-prePos.y)/(curPos.x - prePos.x);
	float degree = std::atan(tan);
	float angle = degree/3.1415926 * 180;

	auto entity = dynamic_cast<Entity*>(_target);
	auto sprite = entity->getSprite();
	//确定鱼的运动方向
	if(curPos.x > prePos.x)
		sprite->setFlippedX(true);
	else
		sprite->setFlippedX(false);
	//log("%.2f",angle);
	entity->setRotation(angle);
}
void RotateWithAction::stop()
{
	m_pInnerAction->stop();
	ActionInterval::stop();
}