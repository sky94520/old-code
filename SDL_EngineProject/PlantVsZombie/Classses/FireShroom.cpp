#include "FireShroom.h"
#include "ZombieBase.h"

FireShroom::FireShroom()
	:m_attackScope(0.f),m_nDamage(0)
	,m_state(State::Normal),_elapsed(0.f)
{
}

FireShroom::~FireShroom()
{
}

void FireShroom::updateNotSleeping(float dt)
{
	if (m_state == State::Normal)
	{
		this->updateNormalState(dt);
	}
	else if (m_state == State::Attack)
	{
		this->updateAtkState(dt);
	}
}

void FireShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void FireShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void FireShroom::updateNormalState(float dt)
{
	auto row = m_pCarrier->getRow();
	auto attackDir = this->getDir();
	auto pos = this->getPosition();
	//根据当前方向确定第一个僵尸
	auto zombie = m_pDelegate->findFirstZombieOfRow(row,attackDir,pos);

	if (zombie == nullptr)
		return;

	auto zombiePos = zombie->getPosition();

	auto distance = zombiePos.x - pos.x;
	//在攻击范围内，开始蓄力5
	if (distance <= m_attackScope)
	{
		_elapsed += dt;
		//进行攻击
		if (_elapsed >= this->getColdDownTime())
		{
			_elapsed -= this->getColdDownTime();
			//转入攻击状态
			this->changeState(State::Attack);
		}
	}
}