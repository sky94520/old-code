#include "RotateAndSpeed.h"
#include "Fish.h"

RotateAndSpeed::RotateAndSpeed()
	:m_pInnerAction(nullptr),m_pTarget(nullptr)
{
}
RotateAndSpeed::~RotateAndSpeed()
{
	SDL_SAFE_RELEASE(m_pInnerAction);
}
RotateAndSpeed*RotateAndSpeed::create(FiniteTimeAction*pAction)
{
	auto action = new RotateAndSpeed();

	if(action && action->init(pAction))
		action->autorelease();
	else
		SDL_SAFE_DELETE(action);

	return action;
}
bool RotateAndSpeed::init(FiniteTimeAction*action)
{
	if(ActionInterval::initWithDuration(action->getDuration()))
	{
		action->retain();
		m_pInnerAction = action;
		return true;
	}

	return false;
}
void RotateAndSpeed::startWithTarget(Node*target)
{
	m_pTarget = static_cast<Fish*>(target);

	m_pInnerAction->startWithTarget(target);

	ActionInterval::startWithTarget(target);
}
bool RotateAndSpeed::isDone()const
{
	return m_pInnerAction->isDone();
}

void RotateAndSpeed::step(float dt)
{
	float speed = m_pTarget->getSpeed();
	//������ſ�����һ�ν���ʱ�����Ŵ�����ʱ���ۺ�ֵ����Ϊ0
	if(_bFirstTick)
	{
		_elapsed = 0;
		_bFirstTick = false;
	}
	else
	{
		if(-FLT_MIN < speed && speed < FLT_MIN)
			_elapsed += dt;
		else
			_elapsed += dt*speed;
	}
	//����update���¶���
	this->update(MAX(0,
		MIN(1, _elapsed /MAX(_duration, FLT_EPSILON))));
}

void RotateAndSpeed::update(float time)
{
	//������ todo
	if(time == 1.f)
	{
		m_pTarget->dead();

		return;
	}

	Point prePos = _target->getPosition();

	m_pInnerAction->update(time);

	Point curPos = _target->getPosition();
	Point delta = curPos - prePos;

	//�������û�����ı� ����x��ı�Ϊ0.f,��ֱ�ӷ���
	if(curPos.x == prePos.x || (delta.x > -FLT_MIN && delta.x < FLT_MIN))
	{
		return;
	}

	float degree = SDL_atan(delta.y/delta.x);
	float angle = SDL_DEGREE_TO_ANGLE(degree);

	if(delta.x < 0)
		angle += 180.f;

	//_target->setRotation(angle);
	Sprite*sprite = m_pTarget->getSprite();
	sprite->setRotation(angle);
}
void RotateAndSpeed::stop()
{
	m_pInnerAction->stop();

	ActionInterval::stop();
}
