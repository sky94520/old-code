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
	m_pInnerAction->startWithTarget(target);
	ActionInterval::startWithTarget(target);
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

	Point vector = curPos - prePos;
	float radins = vector.getAngle();
	float angle = CC_RADIANS_TO_DEGREES(-1*radins);
	//这个是引擎本身的问题，待修复
	_target->setRotation(angle);
	//static_cast<Entity*>(_target)->getSprite()->setRotation(angle);
}
void RotateWithAction::stop()
{
	m_pInnerAction->stop();
	ActionInterval::stop();
}