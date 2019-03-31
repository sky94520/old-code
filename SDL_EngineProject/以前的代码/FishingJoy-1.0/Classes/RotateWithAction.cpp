#include "RotateWithAction.h"
#include "Entity.h"
RotateWithAction::RotateWithAction()
	:m_pInnerAction(nullptr)
{
}
RotateWithAction::~RotateWithAction()
{
	SDL_SAFE_RELEASE(m_pInnerAction);
}
RotateWithAction*RotateWithAction::create(ActionInterval*pAction)
{
	auto action = new RotateWithAction();
	if(action && action->init(pAction))
		action->autoRelease();
	else
		SDL_SAFE_DELETE(action);
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

	float tan = -(curPos.y-prePos.y)/(curPos.x - prePos.x);
	float degree = std::atan(tan);
	float angle = degree/3.1415926 * 180;
	//这个是引擎本身的问题，待修复
	//本来应为_target->setRotation(-angle);
	static_cast<Entity*>(_target)->getSprite()->setRotation(-angle);
}
void RotateWithAction::stop()
{
	m_pInnerAction->stop();
	ActionInterval::stop();
}